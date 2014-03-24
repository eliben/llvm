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

  void insertVprintfDeclaration(Module &M);
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

  insertVprintfDeclaration(M);

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

    Call->dump();
    errs() << Call->getNumArgOperands() << "\n";
    for (unsigned I = 0, IE = Call->getNumArgOperands(); I != IE; ++I) {
      Value *Operand = Call->getArgOperand(I);
      Operand->dump();
      errs() << "size: " << DL->getTypeAllocSize(Operand->getType()) << "\n";
      errs() << "alignment: " << DL->getABITypeAlignment(Operand->getType()) << "\n";
    }
  }

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

void NVPTXPrintfToVprintf::insertVprintfDeclaration(Module &M) {
  if (M.getFunction("vprintf") != nullptr) {
    report_fatal_error("It is illegal to declare vprintf with C linkage");
  }

  // Create a declaration for vprintf with the proper type and insert it into
  // the module.
  Type *ArgTypes[] = {Type::getInt8PtrTy(M.getContext()),
                      Type::getInt8PtrTy(M.getContext())};
  FunctionType *VprintfFuncType =
      FunctionType::get(Type::getInt32Ty(M.getContext()), ArgTypes, false);

  Function::Create(VprintfFuncType, GlobalVariable::ExternalLinkage, "vprintf",
                   &M);
}

ModulePass *llvm::createNVPTXPrintfToVprintfPass() {
  return new NVPTXPrintfToVprintf();
}
