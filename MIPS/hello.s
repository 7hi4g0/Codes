.data
a:	.word	10
b:	.word	5

.text
main:	
	lw	$t0, a
	lw	$t1, b
	add	$t2, $t0, $t1
