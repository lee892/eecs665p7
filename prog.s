.data
gbl_foo: .quad 0
gbl_bar: .quad 0
gbl_main: .quad 0
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
movq %rax, -24(%rbp)
#            goto lbl_0
jmp lbl_0
#Fn epilogue foo
lbl_0: addq $16, %rsp
popq %rbp
retq
fun_bar: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $16, %rsp
#Fn body bar
#            getarg 1 [i]
movq %rdi, -24(%rbp)
#            [i] := 1
movq $1, %rax
movq %rax, -24(%rbp)
#            WRITE [console], [i]
movq $0, %rsi
movq -24(%rbp), %rdi
callq stdJeff_writeInt
#            setret [i]
movq %rax, -24(%rbp)
#            goto lbl_1
jmp lbl_1
#Fn epilogue bar
lbl_1: addq $16, %rsp
popq %rbp
retq
main: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $96, %rsp
#Fn body main
#            getarg 1 [a]
movq %rdi, -40(%rbp)
#            getarg 2 [b]
movq %rsi, -48(%rbp)
#            getarg 3 [c]
movq %rdx, -56(%rbp)
#            getarg 4 [d]
movq %rcx, -64(%rbp)
#            getarg 5 [e]
movq %r8, -72(%rbp)
#            getarg 6 [f]
movq %r9, -80(%rbp)
#            getarg 7 [g]
#            getarg 8 [h]
#            getarg 9 [i]
#            [i] := 1
movq $1, %rax
movq %rax, -104(%rbp)
#            WRITE [console], [i]
movq $0, %rsi
movq -104(%rbp), %rdi
callq stdJeff_writeInt
#            call foo
callq fun_foo
#            setarg 1 [i]
movq -104(%rbp), %rdi
#            call bar
callq fun_bar
#            setret [a]
movq %rax, -40(%rbp)
#            goto lbl_2
jmp lbl_2
#Fn epilogue main
lbl_2: addq $96, %rsp
popq %rbp
retq
