; RUN: llc < %s -march=nvptx64 -mcpu=sm_20 | FileCheck %s

target datalayout = "e-i64:64-v16:16-v32:32-n16:32:64"
target triple = "nvptx64-unknown-unknown"

@.str = private unnamed_addr constant [13 x i8] c"%d %f %c %d\0A\00", align 1

; Function Attrs: nounwind
define void @foo(i32 %a, float %b, i8 signext %c, i32 %e) {
entry:
  %a.addr = alloca i32, align 4
  %b.addr = alloca float, align 4
  %c.addr = alloca i8, align 1
  %e.addr = alloca i32, align 4
  store i32 %a, i32* %a.addr, align 4
  store float %b, float* %b.addr, align 4
  store i8 %c, i8* %c.addr, align 1
  store i32 %e, i32* %e.addr, align 4
  %0 = load i32* %a.addr, align 4
  %1 = load float* %b.addr, align 4
  %conv = fpext float %1 to double
  %2 = load i8* %c.addr, align 1
  %conv1 = sext i8 %2 to i32
  %3 = load i32* %e.addr, align 4
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([13 x i8]* @.str, i32 0, i32 0), i32 %0, double %conv, i32 %conv1, i32 %3)
  ret void
}

declare i32 @printf(i8*, ...)

; CHECK: extern .func  (.param .b32 func_retval0) vprintf
; CHECK: (
; CHECK:  .param .b64 vprintf_param_0,
; CHECK:  .param .b64 vprintf_param_1
; CHECK: )

; CHECK: .visible .func foo(
; CHECK:   .local .align 4 .b8   __local_depot0[40]

; CHECK:   call.uni (retval0), 
; CHECK:   vprintf, 
; CHECK:   (
; CHECK:   param0, 
; CHECK:   param1
; CHECK:   );
