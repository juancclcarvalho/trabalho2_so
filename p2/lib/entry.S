	.equ	USER,16
	.equ	CONTEXT_SIZE,136
	
#define	SAVE_CONTEXT(offset) \
	movq	%rsp,scratch			  ; \
	movq	current_running,%rsp		  ; \
	leaq	((offset)+CONTEXT_SIZE)(%rsp),%rsp ; \
	pushq	scratch				  ; \
	pushq	%rax				  ; \
	pushq	%rbx				  ; \
	pushq	%rcx				  ; \
	pushq	%rdx				  ; \
	pushq	%rsi				  ; \
	pushq	%rdi				  ; \
	pushq	%rbp				  ; \
	pushq	%r8				  ; \
	pushq	%r9				  ; \
	pushq	%r10				  ; \
	pushq	%r11				  ; \
	pushq	%r12				  ; \
	pushq	%r13				  ; \
	pushq	%r14				  ; \
	pushq	%r15				  ; \
	pushfq					  ; \
	movq	scratch,%rsp

#define RESTORE_CONTEXT(offset) \
	movq	current_running,%rsp ; \
	leaq	(offset)(%rsp),%rsp  ; \
	popfq			     ; \
	popq	%r15		     ; \
	popq	%r14		     ; \
	popq	%r13		     ; \
	popq	%r12		     ; \
	popq	%r11		     ; \
	popq	%r10		     ; \
	popq	%r9		     ; \
	popq	%r8		     ; \
	popq	%rbp		     ; \
	popq	%rdi		     ; \
	popq	%rsi		     ; \
	popq	%rdx		     ; \
	popq	%rcx		     ; \
	popq	%rbx		     ; \
	popq	%rax		     ; \
	popq	%rsp
	
	.section .data
scratch: .quad	0
	
	.text
	.globl	scheduler_entry
	
// TODO: This function executes the following steps:
// 1. saves the context of the running thread
// 2. calls the scheduler to select the thread to be executed
// 3. restores the context of the selected thread
scheduler_entry:
	SAVE_CONTEXT(USER)
	call	scheduler
	RESTORE_CONTEXT(USER)
	ret

