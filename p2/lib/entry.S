	.section .data
scratch: .quad	0
	
	.text
	.globl	scheduler_entry
	
// TODO: This function executes the following steps:
// 1. saves the context of the running thread
// 2. calls the scheduler to select the thread to be executed
// 3. restores the context of the selected thread
scheduler_entry:
	ret

