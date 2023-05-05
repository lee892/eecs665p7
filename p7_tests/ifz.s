.data
gbl_main: .quad 0
.align 8
.globl main
.text
main: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $32, %rsp
#Fn body main
#            [a] := 2
movq $2, %rax
movq %rax, -24(%rbp)
#            [i] := 1
movq $1, %rax
movq %rax, -32(%rbp)
#            [tmp0] := [a] NEQ64 2
movq -24(%rbp), %rax
movq $2, %rbx
cmpq %rax, %rbx
movq $0, %rbx
setne %bl
movq %rbx, -40(%rbp)
#            IFZ [tmp0] GOTO lbl_1
movq -40(%rbp), %rdi
cmpq $0, %rdi
je lbl_1#            [i] := 2
movq $2, %rax
movq %rax, -32(%rbp)
#            goto lbl_2
jmp lbl_2
lbl_1: #lbl_1:      nop
nop
#            [i] := 3
movq $3, %rax
movq %rax, -32(%rbp)
lbl_2: #lbl_2:      nop
nop
#            WRITE [console], [i]
movq $0, %rsi
movq -32(%rbp), %rdi
callq stdJeff_writeInt
#            setret [i]
movq -32(%rbp), %rax
#            goto lbl_0
jmp lbl_0
#Fn epilogue main
lbl_0: addq $32, %rsp
popq %rbp
retq
