.data
gbl_foo: .quad 0
gbl_bar: .quad 0
gbl_main: .quad 0
str_0: .asciz "doesn't get to here\n"
.align 8
.globl main
.text
fun_foo: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $16, %rsp
#Fn body foo
#            [i] := 1
movq $1, %rax
movq %rax, -24(%rbp)
#            WRITE [console], [i]
movq $0, %rsi
movq -24(%rbp), %rdi
callq stdJeff_writeInt
#            setret [i]
movq -24(%rbp), %rax
#            goto lbl_0
jmp lbl_0
#Fn epilogue foo
lbl_0: addq $16, %rsp
popq %rbp
retq
fun_bar: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $80, %rsp
#Fn body bar
#            getarg 1 [a]
movq %rdi, -24(%rbp)
#            getarg 2 [b]
movq %rsi, -32(%rbp)
#            getarg 3 [c]
movq %rdx, -40(%rbp)
#            getarg 4 [d]
movq %rcx, -48(%rbp)
#            getarg 5 [e]
movq %r8, -56(%rbp)
#            getarg 6 [f]
movq %r9, -64(%rbp)
#            getarg 7 [g]
movq 24(%rbp), %rbx
movq %rbx, -72(%rbp)
#            getarg 8 [h]
movq 16(%rbp), %rbx
movq %rbx, -80(%rbp)
#            getarg 9 [i]
movq 8(%rbp), %rbx
movq %rbx, -88(%rbp)
#            WRITE [console], str_0
movq $0, %rsi
movq $str_0, %rdi
callq stdJeff_writeString
#            WRITE [console], [a]
movq $0, %rsi
movq -24(%rbp), %rdi
callq stdJeff_writeInt
#            WRITE [console], [e]
movq $0, %rsi
movq -56(%rbp), %rdi
callq stdJeff_writeInt
#Fn epilogue bar
lbl_1: addq $80, %rsp
popq %rbp
retq
main: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $16, %rsp
#Fn body main
#            [i] := 1
movq $1, %rax
movq %rax, -24(%rbp)
#            WRITE [console], [i]
movq $0, %rsi
movq -24(%rbp), %rdi
callq stdJeff_writeInt
#            setarg 1 [i]
movq -24(%rbp), %rdi
#            setarg 2 2
movq $2, %rsi
#            setarg 3 3
movq $3, %rdx
#            setarg 4 4
movq $4, %rcx
#            setarg 5 5
movq $6, %r8
#            setarg 6 6
movq $6, %r9
#            setarg 7 7
movq $7, %rax
pushq %rax
#            setarg 8 8
movq $8, %rax
pushq %rax
#            setarg 9 9
movq $9, %rax
pushq %rax
#            call bar
pushq $0 
callq fun_bar
addq $32, %rsp
#            setret 0
movq $0, %rax
#            goto lbl_2
jmp lbl_2
#Fn epilogue main
lbl_2: addq $16, %rsp
popq %rbp
retq
