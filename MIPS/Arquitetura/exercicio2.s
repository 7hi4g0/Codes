.data
A:	.space	40
.text
main:
li	$t0,	0
la	$t1,	A
loop:
bge	$t0,	40,	end
lw	$t2,	A($t0)
add	$t2,	$t2,	$t0	# Antônio Júnior disse que é dessa forma mesmo
sw	$t2,	A($t0)
addi	$t0,	$t0,	4
j	loop
end:
