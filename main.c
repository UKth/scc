#include<stdio.h>
#include<stdlib.h>

#define MAX_NODE 50
int time;

void rev_dfs(int p, char graph[][MAX_NODE], int n, char* pre, char* post, char* visit){
    pre[p] = time; 

    time++; 
    visit[p] = 1; 

    for(int i = 1; i <= n; i++){
		if(graph[p][i] && !visit[i]){
			rev_dfs(i, graph, n, pre, post, visit); 
		}
	}

    post[p] = time; 
    time++;

}

char* explore(int v, char graph[][MAX_NODE], int n, char* visit, char* scc){
	char stack[MAX_NODE] = {0,};
	int top = 0;
	int cnt = 0;
	char p;

	stack[top] = v;
	while(top >= 0){
		p = stack[top];
		scc[cnt] = p;
		cnt++;
		visit[p] = 1;
		top--;
		for(int i = 1; i <= n; i++){
			if(graph[i][p] && !visit[i]){
				top++;
				stack[top] = i;
			}
		}
	}
	scc[MAX_NODE] = cnt;
	return scc;
}

int find_scc(char graph[][MAX_NODE], int n, FILE* fp){
	char visit[n+1] = {0,};
	char pre[n+1] = {0,};
	char post[n+1] = {0,};
	char buf[MAX_NODE] = {0,};

	time = 1;
	for(int i = 1; i <= n; i++){
		if(!pre[i] && !post[i]){
			rev_dfs(i, graph, n, pre, post, visit);
		}
	}
	// for(int i = 1; i <= n; i++){
	// 	printf("%d %d %d\n", i, pre[i], post[i]);
	// }

	char SCCs[MAX_NODE][MAX_NODE + 1] = {0,}; // [[v1, v2, v3, 0, 0 ..., n], ...]
	int scc_n = 0;
	for(int i = 0; i < n+1; i++){
		visit[i] = 0;
	}
	for(int i = 2*n; i >= 0; i--){
		for(int j = 1; j <= n; j++){
			if(post[j] == i && !visit[j]){
				explore(j, graph, n, visit, SCCs[scc_n]);
				scc_n++;
			}
		}
	}

	printf("\n%d sccs\n", scc_n);
	fprintf(fp, "%d\n", scc_n);
	for(int i = 0; i < scc_n; i++){
		for(int j = 0; j < SCCs[i][MAX_NODE] - 1; j++){
			printf("%d ", SCCs[i][j]);
			fprintf(fp, "%d ", SCCs[i][j]);
		}
		printf("%d\n",SCCs[i][SCCs[i][MAX_NODE] - 1]);
		fprintf(fp, "%d\n",SCCs[i][SCCs[i][MAX_NODE] - 1]);
	}
}


int main(){
	int G_n = 0;
	FILE* fp_in;
	FILE* fp_out;
	char s[MAX_NODE * 2], buf[10];

	fp_in = fopen("scc.in", "r");
    fp_out = fopen("scc.out", "w");
	
	fgets(s, 5, fp_in);
	fputs(s, fp_out);
	G_n = atoi(s);

	for (int i = 0; i < G_n; i++) {
		int n;
		char graph[MAX_NODE][MAX_NODE] = {0,};

		fgets(s, 5, fp_in);
		n = atoi(s);

		for(int j = 1; j <= n; j++){
			fgets(s, MAX_NODE * 2, fp_in);
			for(int k = 1; k <= n; k++){
				graph[j][k] = s[2*(k-1)] - '0';
			}
		}
		find_scc(graph, n, fp_out);

	}

	
    fclose(fp_in);
	fclose(fp_out);
}