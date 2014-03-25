//===-- NVPTXPrintfToVprintf.cpp - Convert prinfc calls to vprintf --------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// The NVPTX target implements printf as a call to the vprintf syscall. Unlike
// printf, which is a vararg, vprintf requires a different argument layout:
//
//   printf("format string", obj1, obj2, obj3);
//
// Is converted to (schematic C pseudocode):
//
//   object buf[] = {obj1, obj2, obj3};
//   vprintf("format string", buf);
//
//===----------------------------------------------------------------------===//

#include "NVPTX.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/PassManager.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
/// \brief NVPTXPrintfToVprintf
class NVPTXPrintfToVprintf : public ModulePass {
public:
  static char ID;

  NVPTXPrintfToVprintf() : ModulePass(ID) {}

  virtual bool runOnModule(Module &M);

  virtual void getAnalysisUsage(AnalysisUsage &AU) const {}

private:
  /// \brief Finds a valid printf function in the module.
  ///
  /// If no declaration of printf is found, or the declaration doesn't match
  /// our expectation of what printf looks like (this could happen if the module
  /// defines its own version of printf, for example), returns nullptr.
  Function *findPrintfFunction(Module &M);

  Function *insertVprintfDeclaration(Module &M);
};
}

char NVPTXPrintfToVprintf::ID = 0;

namespace llvm {
void initializeNVPTXPrintfToVprintfPass(PassRegistry &);
}
INITIALIZE_PASS(NVPTXPrintfToVprintf, "printf-to-vprintf",
                "Convert printf calls to the vprintf syscall", false, false)

bool NVPTXPrintfToVprintf::runOnModule(Module &M) {
  errs() << "I runz, yay\n";

  Function *PrintfFunc = findPrintfFunction(M);
  if (PrintfFunc == nullptr) {
    return false;
  }

  Function *VprintfFunc = insertVprintfDeclaration(M);

  M.dump();

  PrintfFunc->dump();

  const DataLayout *DL = M.getDataLayout();

  // Go over all the uses of printf in the module. The iteration pattern here
  // (increment the iterator immediately after grabbing the current instruction)
  // is required to allow this loop to remove the actual uses and still keep
  // running over all of them properly.
  for (Value::use_iterator UI = PrintfFunc->use_begin(),
                           UE = PrintfFunc->use_end();
       UI != UE;) {
    CallInst *Call = dyn_cast<CallInst>(UI->getUser());
    if (!Call) {
      report_fatal_error("Only 'call' uses of 'printf' are allowed for NVPTX");
    }
    UI++;

    errs() << Call->getNumArgOperands() << "\n";
    // First compute the buffer size required to hold all the formatting
    // arguments, and create the buffer with an alloca.
    // TODO: what happens if no formatting args?
    unsigned Bufsize = 0;
    for (unsigned I = 1, IE = Call->getNumArgOperands(); I < IE; ++I) {
      Bufsize += DL->getTypeAllocSize(Call->getArgOperand(I)->getType());
    }

    Type *Int32Ty = Type::getInt32Ty(M.getContext());
    Value *BufferPtr;

    if (Bufsize == 0) {
      BufferPtr = ConstantInt::get(Int32Ty, 0);
    } else {
      BufferPtr = new AllocaInst(Type::getInt8Ty(M.getContext()),
                                 ConstantInt::get(Int32Ty, Bufsize),
                                 "buf_for_vprintf_args", Call);

      unsigned Offset = 0;
      for (unsigned I = 1, IE = Call->getNumArgOperands(); I < IE; ++I) {
        Value *GEPIndex[] = {ConstantInt::get(Int32Ty, Offset)};
        GetElementPtrInst *GEP =
            GetElementPtrInst::Create(BufferPtr, GEPIndex, "", Call);

        Value *Operand = Call->getArgOperand(I);
        BitCastInst *Cast =
            new BitCastInst(GEP, Operand->getType()->getPointerTo(), "", Call);
        new StoreInst(Operand, Cast, false, 1, Call);

        Offset += DL->getTypeAllocSize(Operand->getType());
      }
    }

    Value *VprintfArgs[] = {Call->getArgOperand(0), BufferPtr};
    CallInst *VprintfCall =
        CallInst::Create(VprintfFunc, VprintfArgs, "", Call);

    Call->replaceAllUsesWith(VprintfCall);
    Call->eraseFromParent();
  }

  M.dump();
  return true;
}

Function *NVPTXPrintfToVprintf::findPrintfFunction(Module &M) {
  // Looking for a declaration of a function named "printf". If this function
  // is *defined* in the module, bail out.
  Function *PrintfFunc = M.getFunction("printf");
  if (!PrintfFunc || !PrintfFunc->isDeclaration()) {
    return nullptr;
  }

  // So this is just a declaration. If so, it must match what we expect from
  // printf; otherwise, it's an error.
  FunctionType *FT = PrintfFunc->getFunctionType();

  if (FT->getNumParams() == 1 && FT->isVarArg() &&
      FT->getReturnType() == Type::getInt32Ty(M.getContext()) &&
      FT->getParamType(0) == Type::getInt8PtrTy(M.getContext())) {
    return PrintfFunc;
  } else {
    report_fatal_error("Found printf in module but it has an invalid type");
    return nullptr;
  }
}

Function *NVPTXPrintfToVprintf::insertVprintfDeclaration(Module &M) {
  if (M.getFunction("vprintf") != nullptr) {
    report_fatal_error("It is illegal to declare vprintf with C linkage");
  }

  // Create a declaration for vprintf with the proper type and insert it into
  // the module.
  Type *ArgTypes[] = {Type::getInt8PtrTy(M.getContext()),
                      Type::getInt8PtrTy(M.getContext())};
  FunctionType *VprintfFuncType =
      FunctionType::get(Type::getInt32Ty(M.getContext()), ArgTypes, false);

  return Function::Create(VprintfFuncType, GlobalVariable::ExternalLinkage,
                          "vprintf", &M);
}

ModulePass *llvm::createNVPTXPrintfToVprintfPass() {
  return new NVPTXPrintfToVprintf();
}
