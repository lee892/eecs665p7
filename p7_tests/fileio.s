.data
gbl_main: .quad 0
str_5: .asciz "fileio1.txt"
str_4: .asciz "hello\n"
str_3: .asciz "fileio2.txt"
str_2: .asciz "\n"
str_1: .asciz "\n"
str_0: .asciz "so this works\n"
.align 8
.globl main
.text
main: pushq %rbp
movq %rsp, %rbp
addq $16, %rbp
subq $32, %rsp
#Fn body main
#            READ [console], [i]
movq $1, %rdi
callq stdJeff_readInt
movq %rax, -24(%rbp)
#            READ [console], [b]
movq $1, %rdi
callq stdJeff_readBool
movq %rax, -32(%rbp)
#            WRITE [console], str_0
movq $0, %rsi
movq $str_0, %rdi
callq stdJeff_writeString
#            WRITE [console], [i]
movq $0, %rsi
movq -24(%rbp), %rdi
callq stdJeff_writeInt
#            WRITE [console], str_1
movq $0, %rsi
movq $str_1, %rdi
callq stdJeff_writeString
#            WRITE [console], [b]
movq $0, %rsi
movq -32(%rbp), %rdi
callq stdJeff_writeBool
#            WRITE [console], str_2
movq $0, %rsi
movq $str_2, %rdi
callq stdJeff_writeString
#            open [f1] writable str_3
movq $str_3, %rdi
movq $1, %rsi
callq stdJeff_openFP
movq %rax, -40(%rbp)
#            WRITE [f1], str_4
movq -40(%rbp), %rsi
movq $str_4, %rdi
callq stdJeff_writeString
#            close [f1]
movq -40(%rbp), %rdi
callq stdJeff_closeFP
#            open [f2] readable str_5
movq $str_5, %rdi
movq $0, %rsi
callq stdJeff_openFP
movq %rax, -48(%rbp)
#            close [f2]
movq -48(%rbp), %rdi
callq stdJeff_closeFP
#Fn epilogue main
lbl_0: addq $32, %rsp
popq %rbp
retq
