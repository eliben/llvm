//===- OptUtils.cpp - Utilities for writing optimization tools ------------===//
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
#include "OptUtils.h"

#include "llvm/IR/Verifier.h"
#include "llvm/PassManager.h"
#include "llvm/Transforms/IPO.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

namespace llvm {

void AddOptimizationPasses(PassManagerBase &MPM, FunctionPassManager &FPM,
                           unsigned OptLevel, unsigned SizeLevel,
                           bool DisableInline, bool UnitAtATime,
                           bool DisableUnrollLoops,
                           bool DisableLoopVectorization,
                           bool DisableSLPVectorization) {
  FPM.add(createVerifierPass());

  PassManagerBuilder Builder;
  Builder.OptLevel = OptLevel;
  Builder.SizeLevel = SizeLevel;

  if (DisableInline) {
    // No inlining pass
  } else if (OptLevel > 1) {
    unsigned Threshold = 225;
    if (SizeLevel == 1) // -Os
      Threshold = 75;
    else if (SizeLevel == 2) // -Oz
      Threshold = 25;
    if (OptLevel > 2)
      Threshold = 275;
    Builder.Inliner = createFunctionInliningPass(Threshold);
  } else {
    Builder.Inliner = createAlwaysInlinerPass();
  }
  Builder.DisableUnitAtATime = !UnitAtATime;
  // Builder.DisableUnrollLoops = (DisableLoopUnrolling.getNumOccurrences() > 0)
  // ?
  // DisableLoopUnrolling : OptLevel == 0;
  Builder.DisableUnrollLoops = DisableUnrollLoops;

  // This is final, unless there is a #pragma vectorize enable
  if (DisableLoopVectorization)
    Builder.LoopVectorize = false;
  else if (!Builder.LoopVectorize)
    Builder.LoopVectorize = OptLevel > 1 && SizeLevel < 2;

  // When #pragma vectorize is on for SLP, do the same as above
  Builder.SLPVectorize =
      DisableSLPVectorization ? false : OptLevel > 1 && SizeLevel < 2;

  Builder.populateFunctionPassManager(FPM);
  Builder.populateModulePassManager(MPM);
}

void AddPassToPM(PassManagerBase &PM, Pass *P, bool AppendVerifier) {
  PM.add(P);
  if (AppendVerifier)
    PM.add(createVerifierPass());
}

void AddStandardCompilePasses(PassManagerBase &PM, bool StripDebug,
                              bool VerifyEach, bool DisableOptimizations,
                              bool DisableInline) {
  PM.add(createVerifierPass());

  // If the -strip-debug command line option was specified, do it.
  if (StripDebug)
    AddPassToPM(PM, createStripSymbolsPass(true), VerifyEach);

  if (DisableOptimizations)
    return;

  // -std-compile-opts adds the same module passes as -O3.
  PassManagerBuilder Builder;
  if (!DisableInline)
    Builder.Inliner = createFunctionInliningPass();
  Builder.OptLevel = 3;
  Builder.populateModulePassManager(PM);
}

void AddStandardLinkPasses(PassManagerBase &PM, bool StripDebug,
                           bool VerifyEach, bool DisableOptimizations,
                           bool DisableInline, bool DisableInternalize) {
  PM.add(createVerifierPass());

  // If the -strip-debug command line option was specified, do it.
  if (StripDebug)
    AddPassToPM(PM, createStripSymbolsPass(true), VerifyEach);

  if (DisableOptimizations)
    return;

  PassManagerBuilder Builder;
  Builder.populateLTOPassManager(PM, /*Internalize=*/!DisableInternalize,
                                 /*RunInliner=*/!DisableInline);
}
}
