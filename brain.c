#include <stdio.h>
#include <string.h>

int loop(int instruction);

char vector[3000];
int pointer;
int pos;
char input[100001];
char program[100001];

int command(int instruction){
	int i;
	
	switch(program[instruction]){
		case '>' :	pointer++;
					break;
		case '<' :	pointer--;
					break;
		case '+' :	vector[pointer]++;
					break;
		case '-' :	vector[pointer]--;
					break;
		case '.' :	printf("%c", vector[pointer]);
					break;
		case ',' :	vector[pointer] = input[pos++];
					break;
		case '[' :	return loop(++instruction);
					break;
		case ']' :	break;
		case '#' :	for (i = 0; i < 10; i++){
						printf("%c", vector[pointer]);
					}
					break;
		default : break;
	}
	
	return ++instruction;
}

void run(){
	int instruction = 0;
	
	while(program[instruction] != '\0'){
		instruction = command(instruction);
	}
	printf("\n\n");
}

int loop(int instruction){
	int inst;
	
	while (vector[pointer] != 0){
		inst = instruction;
		while(program[inst] != ']'){
			inst = command(inst);
		}
	}
	
	for (inst = 1; inst > 0; instruction++){
		if (program[instruction] == '[')
			inst++;
		else if (program[instruction] == ']')
			inst--;
	}
	
	return instruction;
}

int main(){
	int instance;
	int i;
	
	scanf("%d", &instance);
	
	for (i = 1; i <= instance; i++){
		
		pointer = 0;
		pos = 0;
		memset(vector, 0, 3000);
		
		scanf("\n%s\n%s", input, program);
		
		printf("Instancia %d\n", i);
		run();
	}
	
	return 0;
}
