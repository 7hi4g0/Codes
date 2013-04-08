.data
A:	.word	1, 2, 3, 4, 5, 6, 7, 8, 9, 10
.text
main:
li	$t0,	0		# Contador, ou índice
la	$t1,	A		# Endereço do vetor
loop:				# Ínicio do loop
bge	$t0,	36,	end	# Teste de parada, caso seja maior ou igual a 36 termina o loop
lw	$t2,	A($t0)		# Carrega o valor do vetor na posição t0, ou índice
lw	$t3,	A+4($t0)	# Carrega o valor do vetor na próxima posição do vetor
add	$t2,	$t2,	$t3	# Adiciona os valores da posição atual e próxima
sw	$t2,	A($t0)		# Salva o novo valor no vetor
addi	$t0,	$t0,	4	# Incrementa o índice para apontar para o próximo elemento
j	loop			# Volta para o ínicio do loop
end:				# Fim do loop e do programa
