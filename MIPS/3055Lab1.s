# ECE 3055 Lab 1 Patrick Jackson

# Declare program data
	.data

# Declare strings and newline
title:	.asciiz	"Program computes the parity of the input 2's complement integer"
prompt:	.asciiz	"Input an integer? "
o_title:	.asciiz	"The parity value of n is "
o_odd:	.asciiz "odd"
o_even:	.asciiz "even"
newline:	.byte	10,13,00,00

# Force to word boundary
	.align 2

# Declare integer variables
n:	.word	0
p_bit:	.word	0


# Begin program
	.text
main:
# Print out program description
#	puts	title
	li	$v0,4
	la	$a0,title
	syscall
# Print out carriage return and line feed
#	putc	'\n'
	li	$v0,4
	la	$a0,newline
	syscall
# Print out carriage return and line feed
#	putc	'\n'
	li	$v0,4
	la	$a0,newline
	syscall
# Prompt user for input
#	puts	prompt
	li	$v0,4
	la	$a0,prompt
	syscall
# Read in an integer, N
#	geti	$a0
	li	$v0,5
	syscall
# Transfer value to $a0 and save in memory
	add	$a0,$v0,$zero	# integer now placed in $a0
	sw $a0,n
# Call subroutine
	# testing stack ops
	xor $a2,$a2,$a2
	xor $a3,$a3,$a3

	jal parity
	# testing stack ops
	bne $a2,$zero,exit
	bne $a3,$zero,exit
# Retrieve n from memory
	lw $a0,n
# save result (some registers will be destroyed by puts call)
	sw	$a1,p_bit
# Print out carriage return and line feed
#	putc	'\n'
	li	$v0,4
	la	$a0,newline
	syscall
# Print out output title string
#	puts	o_title
	li	$v0,4
	la	$a0,o_title
	syscall
# Load result
	lw	$a0,p_bit
# Print out even or odd dependent on value of $a0
	li $v0,4
	beq $a0,$zero,evenval
#	puts	o_odd
	la $a0,o_odd
	j eodone
evenval:
#	puts	o_even
	la $a0,o_even
eodone:
	syscall
# Print out carriage return and line feed
#	putc	'\n'
	li	$v0,4
	la	$a0,newline
	syscall
# End program and return to simulator
#	done
exit:
	li	$v0,10
	syscall

# Put 1 for odd parity or 0 for even parity in $a1
parity:	
# Push $a2 on the stack for use
	addi $sp,$sp,-8
	sw $a2,0($sp)
	sw $a3,4($sp)
# Zero out register $a2 and $a3
	xor $a2,$a2,$a2
	xor $a3,$a3,$a3
	addi $a3,$a3,32
# ploop places the total count of 1's in $a0
# Uses $a2 as temp
ploop:
	andi $a2,$a0,1
	add $a1,$a1,$a2
	srl $a0,$a0,1
	addi $a3,$a3,-1
	bne $a3,$zero,ploop
# Reduce loop output to only 1-bit
	andi $a1,$a1,1
# Pop $a2 off the stack and return
	lw $a2,0($sp)
	lw $a3,4($sp)
	addi $sp,$sp,8
	jr $ra
