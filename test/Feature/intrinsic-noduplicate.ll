; RUN: llvm-as < %s | llvm-dis | FileCheck %s

; Make sure LLVM knows about the noduplicate attribute on the
; llvm.cuda.syncthreads intrinsic.

declare void @llvm.cuda.syncthreads()

; CHECK: declare void @llvm.cuda.syncthreads() #0
; CHECK: attributes #0 = { noduplicate nounwind }
