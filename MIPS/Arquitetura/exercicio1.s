.data
A:	.word	1, 2, 3, 4, 5, 6, 7, 8, 9, 10
.text
main:
li	$t0,	0		# Contador, ou índice
la	$t1,	A		# Endereço do vetor
loop:				# Ínicio do loop
bge	$t0,	40,	end	# Teste de parada, caso seja maior ou igual a 40 termina o loop
lw	$t2,	A($t0)		# Carrega o valor do vetor na posição t0, ou índice
addi	$t2,	$t2,	1	# Adiciona 1 a valor do elemento atual
sw	$t2,	A($t0)		# Salva o novo valor no vetor
addi	$t0,	$t0,	4	# Incrementa o índice para apontar para o próximo elemento
j	loop			# Volta para o ínicio do loop
end:				# Fim do loop e do programa
