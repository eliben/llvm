//===- OptUtils.h - Utilities for writing optimization tools --------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Utilities for writing tools that involve LLVM optimizations.
///
//===----------------------------------------------------------------------===//
#ifndef LLVM_TOOLS_OPT_OPTUTILS_H
#define LLVM_TOOLS_OPT_OPTUTILS_H

namespace llvm {

namespace legacy {
class PassManagerBase;
class FunctionPassManager;
}
using legacy::PassManagerBase;
using legacy::FunctionPassManager;

class Pass;

/// \brief Helper for adding optimization passes to pass managers.
///
/// The passes are added based on the given OptLevel and SizeLevel, with
/// additional options controlling optional passes.
void AddOptimizationPasses(PassManagerBase &MPM, FunctionPassManager &FPM,
                           unsigned OptLevel, unsigned SizeLevel,
                           bool DisableInline = false, bool UnitAtATime = false,
                           bool DisableUnrollLoops = false,
                           bool DisableLoopVectorization = false,
                           bool DisableSLPVectorization = false);

/// \brief Adds a pass to a PM, optionally adding a verifier after it.
void AddPassToPM(PassManagerBase &PM, Pass *P, bool AppendVerifier = false);

/// \brief Adds standard compilation passes to a pass manager.
///
/// Also provides some boolean controls to enable or disable certain passes.
void AddStandardCompilePasses(PassManagerBase &PM, bool StripDebug = false,
                              bool VerifyEach = false,
                              bool DisableOptimizations = false,
                              bool DisableInline = false);

/// \brief Adds standard linking passes to a pass manager.
///
/// Also provides some boolean controls to enable or disable certain passes.
void AddStandardLinkPasses(PassManagerBase &PM, bool StripDebug = false,
                           bool VerifyEach = false,
                           bool DisableOptimizations = false,
                           bool DisableInline = false,
                           bool DisableInternalize = false);
}

#endif // LLVM_TOOLS_OPT_OPTUTILS_H
