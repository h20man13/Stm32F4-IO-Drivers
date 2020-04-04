	.syntax unified
	.cpu cortex-m4
	.thumb
	.global reset_handler
	.type reset_handler, %function
reset_handler:
	LDR r0, =_estack
	MOV sp, r0
	MOVS r0, #0 //clear out R0 The S means condition flags are set
	LDR r1, =_sdata //load data into R1 2 and 3
	LDR r2, =_edata //load end of  data into r2
	LDR r3, =_sidata //start of data init section
	B copy_sidata_loop //branch to the copy data loop function
copy_sidata:
	LDR r4, [r3, r0] //load r4 with Base[r3](sidata) + offset[r0] 
	STR r4, [r1, r0] //stw sidata ito sdata
	ADDS r0, r0, #4 //add 4 to r0
copy_sidata_loop:
	ADDS r4, r0, r1 //Add the start of data to r0
	CMP r4, r2 //Compare r4 to the end of the data section
	BCC copy_sidata //if flags exist branch to copy_sidata
	MOVS r0, #0
	LDR r1, =_sbss
	LDR r2, =_ebss
	B reset_bss_loop
reset_bss:
	STR r0, [r1]
	ADDS r1, r1, #4
reset_bss_loop:
	CMP r1, r2
	BCC reset_bss
	B main
.size reset_handler, .-reset_handler
