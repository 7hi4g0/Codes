.data
A:	.space	40
.text
main:
li	$t0,	0
la	$t1,	A
loop:
bge	$t0,	36,	end
lw	$t2,	A($t0)
lw	$t3,	A+4($t0)
add	$t2,	$t2,	$t3
sw	$t2,	A($t0)
addi	$t0,	$t0,	4
j	loop
end:
