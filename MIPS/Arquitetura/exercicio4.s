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
andi	$t5,	$t0,	1	# t5 será zero se t0 for par
beqz	$t5,	then		# Verifica se é zero
else:				# Caso não seja par
add	$t2,	$t2,	$t2	# Multiplica o valor do elemento por 2
j	endif			# Não executa o then
then:				# Caso seja par
lw	$t4,	A+4($t3)	# Carrega o valor do vetor na próxima posição do vetor
add	$t2,	$t2,	$t4	# Adiciona os valores da posição atual e próxima
endif:				# Fim do if
sw	$t2,	A($t3)		# Salva o novo valor no vetor
addi	$t0,	$t0,	1	# Incrementa o índice para apontar para o próximo elemento
j	loop			# Volta para o ínicio do loop
end:				# Fim do loop e do programa
