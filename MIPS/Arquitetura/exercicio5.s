.data
vetor:	.word	2, 5, 7, 9, 1, 10, 4, 6, 3, 8
.text
main:
li	$t1,	36		# Última posição correta							1*1
la	$t2,	vetor		# Endereço do vetor								5*1
li	$s0,	0		# Quantidade de execução do loop externo					NC
li	$s1,	0		# Quantidade de execução do loop interno					NC
li	$s2,	0		# Quantidade de execução do if							NC
loop1:				# Ínicio do loop externo							NC
addi	$s0,	$s0,	1	# Incrementa quantidade de execuções						NC
li	$t0,	0		# Índice									1*7
li	$t3,	0		# Última posição trocada							1*7
loop2:				# Ínicio do loop interno							NC
bge	$t0,	$t1,	end2	# Condicão de parada do loop, continua até o último na posição correta		2*7 + 2*44
addi	$s1,	$s1,	1	# Incrementa quantidade de execuções						NC
lw	$t4,	vetor($t0)	# Carrega posição atual do vetor						5*44
lw	$t5,	vetor+4($t0)	# Carrega próxima posição do vetor						5*44
ble	$t4,	$t5,	endif	# Verifica se valor atual é menor que o próximo					2*44
addi	$s2,	$s2,	1	# Incrementa quantidade de execuções						NC
sw	$t4,	vetor+4($t0)	# Troca valores									5*19
sw	$t5,	vetor($t0)	# Troca valores									5*19
addi	$t3,	$t0,	4	# Atualiza última posição trocada						3*19
endif:				# Fim do if									NC
addi	$t0,	$t0,	4	# Avança o índice								3*44
j	loop2			# Volta para o ínicio do loop interno						1*44
end2:				# Fim do loop interno								NC
move	$t1,	$t3		# Atualiza a última posição correta com a última posição trocada		1*7
beqz	$t1,	end1		# Condição de parada, continua até todas as posições estarem corretas		2*7
j	loop1			# Volta para o ínicio do loop externo						1*7
end1:				# Fim do loop interno e do programa						NC
