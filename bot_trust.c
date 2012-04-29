#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char robot;
	int button;
} seq;

int main(){
	int T, N, count;
	
	scanf("%d", &T);
	
	scanf("%d", &N);
	
	for (count = 1; count <= T; count++){
		seq order[N];
		int robot[2] = {1, 1};
		int time[2] = {0, 0};
		int total = 0;
		
		//printf("%d ", N);
		for (int i = 0; i < N; i++){
			char str[2];
			scanf("%s %d", str, &order[i].button);
			order[i].robot = str[0];
			
			//printf("%c %d ", order[i].robot, order[i].button);
		}
		//printf("\n");
		
		for (int i = 0; i < N; i++){
			int bot;
			int temp;
			
			if (order[i].robot == 'O')
				bot = 0;
			else
				bot = 1;
			
			temp = abs(order[i].button - robot[bot]) + time[bot];
			
			if (total < temp)
				total = temp;
			
			total++;
			time[bot] = total;
			robot[bot] = order[i].button;
		}
		
		printf("Case #%d: %d\n", count, total);
		
		scanf("%d", &N);
	}
	
	return 0;
}
