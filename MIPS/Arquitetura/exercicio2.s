.data
A:	.word	1, 2, 3, 4, 5, 6, 7, 8, 9, 10
.text
main:
li	$t0,	0		# Contador, ou índice
la	$t1,	A		# Endereço do vetor
loop:				# Ínicio do loop
bge	$t0,	10,	end	# Teste de parada, caso seja maior ou igual a 10 termina o loop
mul	$t3,	$t0,	4	# Transforma o índice para endereçar o bytes
lw	$t2,	A($t3)		# Carrega o valor do vetor na posição t0, ou índice
add	$t2,	$t2,	$t0	# Adiciona índice ao valor do elemento atual
sw	$t2,	A($t3)		# Salva o novo valor no vetor
addi	$t0,	$t0,	1	# Incrementa o índice para apontar para o próximo elemento
j	loop			# Volta para o ínicio do loop
end:				# Fim do loop e do programa
