.data
vetor:	.word	2, 5, 7, 9, 1, 10, 4, 6, 3, 8
.text
main:
li	$t1,	36		# Última posição correta
la	$t2,	vetor		# Endereço do vetor
loop1:				# Ínicio do loop externo
li	$t0,	0		# Índice
li	$t3,	0		# Última posição trocada
loop2:				# Ínicio do loop interno
bge	$t0,	$t1,	end2	# Condicão de parada do loop, continua até o último na posição correta
lw	$t4,	vetor($t0)	# Carrega posição atual do vetor
lw	$t5,	vetor+4($t0)	# Carrega próxima posição do vetor
ble	$t4,	$t5,	endif	# Verifica se valor atual é menor que o próximo
sw	$t4,	vetor+4($t0)	# Troca valores
sw	$t5,	vetor($t0)	# Troca valores
addi	$t3,	$t0,	4	# Atualiza última posição trocada
endif:				# Fim do if
addi	$t0,	$t0,	4	# Avança o índice
j	loop2			# Volta para o ínicio do loop interno
end2:				# Fim do loop interno
move	$t1,	$t3		# Atualiza a última posição correta com a última posição trocada
beqz	$t1,	end1		# Condição de parada, continua até todas as posições estarem corretas
j	loop1			# Volta para o ínicio do loop externo
end1:				# Fim do loop interno e do programa