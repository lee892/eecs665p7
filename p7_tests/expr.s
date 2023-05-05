.data
gbl_a: .quad 0
gbl_b: .quad 0
gbl_c: .quad 0
gbl_func: .quad 0
gbl_main: .quad 0
str_6: .asciz "\n"
str_5: .asciz "\n"
str_4: .asciz "\n"
str_2: .asciz "\n"
str_1: .asciz "\n"
str_3: .asciz "\n"
str_0: .asciz "\n"
.align 8
.globl main
.text
fun_func: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $0, %rsp
#Fn body func
#Fn epilogue func
lbl_0: addq $0, %rsp
popq %rbp
retq
main: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $192, %rsp
#Fn body main
#            [j] := 234
movq $234, %rax
movq %rax, -24(%rbp)
#            [tmp0] := [j] DIV64 3
movq -24(%rbp), %rax
movq $3, %rbx
cqto
idivq %rbx
movq %rax, -48(%rbp)
#            WRITE [console], [tmp0]
movq $0, %rsi
movq -48(%rbp), %rdi
callq stdJeff_writeInt
#            WRITE [console], str_0
movq $0, %rsi
movq $str_0, %rdi
callq stdJeff_writeString
#            [tmp1] := 1000 MULT64 3
movq $1000, %rax
movq $3, %rbx
imulq %rbx
movq %rax, -56(%rbp)
#            [tmp2] := [j] DIV64 2
movq -24(%rbp), %rax
movq $2, %rbx
cqto
idivq %rbx
movq %rax, -64(%rbp)
#            [tmp3] := [tmp1] ADD64 [tmp2]
movq -56(%rbp), %rax
movq -64(%rbp), %rbx
addq %rax, %rbx
movq %rbx, -72(%rbp)
#            [tmp4] := [tmp3] SUB64 7
movq -72(%rbp), %rax
movq $7, %rbx
subq %rbx, %rax
movq %rax, -80(%rbp)
#            [a] := [tmp4]
movq -80(%rbp), %rax
movq %rax, gbl_a
#            [tmp5] := [a] MULT64 3
movq gbl_a, %rax
movq $3, %rbx
imulq %rbx
movq %rax, -88(%rbp)
#            WRITE [console], [tmp5]
movq $0, %rsi
movq -88(%rbp), %rdi
callq stdJeff_writeInt
#            WRITE [console], str_1
movq $0, %rsi
movq $str_1, %rdi
callq stdJeff_writeString
#            [tmp6] := [j] NEQ64 10000
movq -24(%rbp), %rax
movq $10000, %rbx
cmpq %rax, %rbx
movq $0, %rbx
setne %bl
movq %rbx, -96(%rbp)
#            WRITE [console], [tmp6]
movq $0, %rsi
movq -96(%rbp), %rdi
callq stdJeff_writeBool
#            WRITE [console], str_2
movq $0, %rsi
movq $str_2, %rdi
callq stdJeff_writeString
#            [tmp7] := [a] GTE64 [j]
movq gbl_a, %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rbx
setge %bl
movq %rbx, -104(%rbp)
#            WRITE [console], [tmp7]
movq $0, %rsi
movq -104(%rbp), %rdi
callq stdJeff_writeBool
#            [tmp8] := 201 LTE64 200
movq $201, %rax
movq $200, %rbx
cmpq %rbx, %rax
movq $0, %rbx
setle %bl
movq %rbx, -112(%rbp)
#            WRITE [console], [tmp8]
movq $0, %rsi
movq -112(%rbp), %rdi
callq stdJeff_writeBool
#            WRITE [console], str_3
movq $0, %rsi
movq $str_3, %rdi
callq stdJeff_writeString
#            [j] := [a]
movq gbl_a, %rax
movq %rax, -24(%rbp)
#            [tmp9] := [j] NEQ64 500
movq -24(%rbp), %rax
movq $500, %rbx
cmpq %rax, %rbx
movq $0, %rbx
setne %bl
movq %rbx, -120(%rbp)
#            [tmp10] := 0 AND64 [tmp9]
movq $0, %rax
movq -120(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -128(%rbp)
#            [tmp11] := [j] LTE64 5000
movq -24(%rbp), %rax
movq $5000, %rbx
cmpq %rbx, %rax
movq $0, %rbx
setle %bl
movq %rbx, -136(%rbp)
#            [tmp12] := [tmp10] OR64 [tmp11]
movq -128(%rbp), %rax
movq -136(%rbp), %rbx
orq %rax, %rbx
movq %rbx, -144(%rbp)
#            [k] := [tmp12]
movq -144(%rbp), %rax
movq %rax, -32(%rbp)
#            [tmp13] := [a] GT64 [j]
movq gbl_a, %rax
movq -24(%rbp), %rbx
cmpq %rbx, %rax
movq $0, %rbx
setg %bl
movq %rbx, -152(%rbp)
#            [tmp14] := [j] GTE64 [a]
movq -24(%rbp), %rax
movq gbl_a, %rbx
cmpq %rbx, %rax
movq $0, %rbx
setge %bl
movq %rbx, -160(%rbp)
#            [tmp15] := [tmp13] AND64 [tmp14]
movq -152(%rbp), %rax
movq -160(%rbp), %rbx
andq %rax, %rbx
movq %rbx, -168(%rbp)
#            [l] := [tmp15]
movq -168(%rbp), %rax
movq %rax, -40(%rbp)
#            [tmp16] := [k] NEQ64 [l]
movq -32(%rbp), %rax
movq -40(%rbp), %rbx
cmpq %rax, %rbx
movq $0, %rbx
setne %bl
movq %rbx, -176(%rbp)
#            WRITE [console], [tmp16]
movq $0, %rsi
movq -176(%rbp), %rdi
callq stdJeff_writeBool
#            WRITE [console], str_4
movq $0, %rsi
movq $str_4, %rdi
callq stdJeff_writeString
#            WRITE [console], [a]
movq $0, %rsi
movq gbl_a, %rdi
callq stdJeff_writeInt
#            WRITE [console], str_5
movq $0, %rsi
movq $str_5, %rdi
callq stdJeff_writeString
#            [tmp17] := 3 SUB64 2
movq $3, %rax
movq $2, %rbx
subq %rbx, %rax
movq %rax, -184(%rbp)
#            WRITE [console], [tmp17]
movq $0, %rsi
movq -184(%rbp), %rdi
callq stdJeff_writeInt
#            [tmp18] := 1 AND64 1
movq $1, %rax
movq $1, %rbx
andq %rax, %rbx
movq %rbx, -192(%rbp)
#            WRITE [console], [tmp18]
movq $0, %rsi
movq -192(%rbp), %rdi
callq stdJeff_writeBool
#            WRITE [console], str_6
movq $0, %rsi
movq $str_6, %rdi
callq stdJeff_writeString
#            [tmp19] := 1 OR64 0
movq $1, %rax
movq $0, %rbx
orq %rax, %rbx
movq %rbx, -200(%rbp)
#            WRITE [console], [tmp19]
movq $0, %rsi
movq -200(%rbp), %rdi
callq stdJeff_writeBool
#Fn epilogue main
lbl_1: addq $192, %rsp
popq %rbp
retq
