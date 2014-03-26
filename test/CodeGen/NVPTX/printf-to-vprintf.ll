; RUN: opt < %s -S -nvptx-printf-to-vprintf -O2 | FileCheck %s

target datalayout = "e-i64:64-v16:16-v32:32-n16:32:64"
target triple = "nvptx64-unknown-unknown"

@.str = private unnamed_addr constant [13 x i8] c"%d %f %c %d\0A\00", align 1

; Function Attrs: nounwind
define void @foo(i32 %a, float %b, i8 signext %c, i32 %e) {
entry:
; CHECK: %buf_for_vprintf_args1 = alloca [24 x i8], align 4
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
; CHECK:  %[[A:[0-9]]] = bitcast [24 x i8]* %buf_for_vprintf_args1 to i32*
; CHECK:  store i32 %a, i32* %[[A]], align 4
; CHECK:  %[[BCONV_ADDR:[0-9]]] = getelementptr [24 x i8]* %buf_for_vprintf_args1, i64 0, i64 8
; CHECK:  %[[BCONV:[0-9]]] = bitcast i8* %[[BCONV_ADDR]] to double*
; CHECK:  store double %conv, double* %[[BCONV]], align 8
; CHECK:  %[[CCONV_ADDR:[0-9]]] = getelementptr [24 x i8]* %buf_for_vprintf_args1, i64 0, i64 16
; CHECK:  %[[CCONV:[0-9]]] = bitcast i8* %[[CCONV_ADDR]] to i32*
; CHECK:  store i32 %conv1, i32* %[[CCONV]], align 4
; CHECK:  %[[E_ADDR:[0-9]]] = getelementptr [24 x i8]* %buf_for_vprintf_args1, i64 0, i64 20
; CHECK:  %[[E:[0-9]]] = bitcast i8* %5 to i32*
; CHECK:  store i32 %e, i32* %[[E]], align 4
; CHECK: call i32 @vprintf({{.*}}, i8* %buf_for_vprintf_args1
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([13 x i8]* @.str, i32 0, i32 0), i32 %0, double %conv, i32 %conv1, i32 %3)
  ret void
}

; CHECK-NOT: @printf
; CHECK: declare i32 @vprintf

declare i32 @printf(i8*, ...)

