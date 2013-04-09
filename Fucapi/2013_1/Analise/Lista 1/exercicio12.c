#include <stdlib.h>
#include <stdio.h>

typedef struct {
	double altura;
	int sexo;
} registroAluno;

int main(void) {
	registroAluno alunos[10];
	double maior;
	double menor;
	double mediaMulheres = 0;
	int quantidadeMulheres = 0;
	double mediaTurma = 0;
	
	for (int aluno = 0; aluno < 10; aluno++) {
		scanf("%lf %d", &alunos[aluno].altura, &alunos[aluno].sexo);
		
		if (aluno == 0) {
			maior = menor = alunos[aluno].altura;
		} else if (alunos[aluno].altura > maior) {
			maior = alunos[aluno].altura;
		} else if (alunos[aluno].altura < menor) {
			menor = alunos[aluno].altura;
		}
		
		if (alunos[aluno].sexo == 2) {
			mediaMulheres += alunos[aluno].altura;
			quantidadeMulheres++;
		}
		
		mediaTurma += alunos[aluno].altura;
	}
	
	mediaMulheres /= quantidadeMulheres;
	mediaTurma /= 10;
	
	printf("Maior altura da turma: %.2lf\n", maior);
	printf("Menor altura da turma: %.2lf\n", menor);
	printf("Média de altura das mulheres: %.2lf\n", mediaMulheres);
	printf("Média de altura da turma: %.2lf\n", mediaTurma);
	
	return 0;	
}
