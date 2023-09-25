.intel_syntax noprefix

/* function calls  rdi, rsi, rdi, rdx, rcx, r8, r9 */
/* system   calls  rdi, rsi, rdi, rdx, r10, r8, r9 */
/*                                    HERE         */

.global syscall
_syscall:
        mov r10, rcx
        syscall
        ret

#define create_syscall(x, n) \
.global x;                   \
x:;                          \
        mov rax, n;          \
        jmp _syscall

create_syscall(write, 1)
create_syscall(close, 3)
create_syscall(socket, 41)
create_syscall(accept, 43)
create_syscall(bind, 49)
create_syscall(listen, 50)
create_syscall(exit, 60)


.global _start
_start:
        xor rbp, rbp
        pop rdi         /* argc */
        mov rsi, rsp    /* argv */
        call main
        call exit
