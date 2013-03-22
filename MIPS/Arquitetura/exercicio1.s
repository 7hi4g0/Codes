.data
A:	.space	40
.text
main:
li	$t0,	0
la	$t1,	A
loop:
bge	$t0,	40,	end
lw	$t2,	A($t0)
addi	$t2,	$t2,	1
sw	$t2,	A($t0)
addi	$t0,	$t0,	4
j	loop
end:
