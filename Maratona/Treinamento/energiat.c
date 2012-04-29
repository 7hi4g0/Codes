#include <stdio.h>

int main(){
	unsigned int F, P, E, A;
	unsigned int edpp[5001][21];
	
	scanf("%d %d %d %d", &F, &P, &E, &A);
	
	while (!(F == 0 && P == 0 && E == 0 && A == 0)){
		unsigned int edp = 0;
		unsigned int prog, freq, troca;
		
		troca = E * A;
		
		for (prog = 0; prog < P; prog++){
			for (freq = 0; freq < F; freq++){
				scanf("%d %d", &E, &A);
				edpp[prog][freq] = E * A;
			}
		}
		
		for (freq = F - 1; freq > 0; freq--)
			edpp[0][freq] += troca;
		
		for (prog = 1; prog < P; prog++){
			for (freq = 0; freq < F; freq++){
				int aux;
				
				edp = edpp[prog - 1][freq] + edpp[prog][freq];
				
				for (aux = 0; aux < F; aux++){
					int x;
					
					x = edpp[prog - 1][aux] + troca + edpp[prog][freq];
					
					if (x < edp)
						edp = x;
				}
				
				edpp[prog][freq] = edp;
			}
		}
		
		prog = P - 1;
		
		edp = edpp[prog][0];
		
		for (freq = 1; freq < F; freq++)
			if (edpp[prog][freq] < edp)
				edp = edpp[prog][freq];
		
		printf("%d\n", edp);
		
		scanf("%d %d %d %d", &F, &P, &E, &A);
	}
	
	return 0;
}


