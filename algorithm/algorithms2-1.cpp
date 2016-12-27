#include <stdio.h>//注释
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
#define N 5
struct node{
	int num;
	struct node *parent;
};
struct node Node[N];
int COST[N][N] = {{00,10,30,50,70},
									{10,00,40,60,20},
									{30,40,00,30,50},
									{50,60,30,00,10},
									{70,20,50,10,00}},DIST[N];
int min(int DIST[],int S[], int n) {
	int tm = -1;
	for(int i = 0; i < n; i++){
		if(!S[i]){
			tm = i;
			break;
		}
	}
	if(tm == -1) return tm;
	for(int i = tm; i < n; i++) {
		if(!S[i]) {
			if(DIST[tm] > DIST[i]) {
				tm = i;
			}
		}
	}
	return tm;
}
void SHORTEST_PATHS(int v,int COST[][N], int DIST[], int n) {
	int S[n];
	int u, num, i, w, j = 0;
	for(i = 0; i < n; i++){//将S集合初始化为空
		S[i] = 0;
		DIST[i] = COST[v][i];
	}
	S[v] = 1;
	DIST[v] = 0;
	for (num = 1; num < n; num++) {
		u = min(DIST, S, n);
		if(u == -1) {
			return ;
		}
		S[u] = 1;
		for(w = 0; w < n; w++){
			if(S[w] == 0) {
				if(DIST[w] > DIST[u] + COST[u][w]) {
					DIST[w] = DIST[u] + COST[u][w];
					Node[w].parent = &(Node[u]);
				}
			}
		}
	}
}
int main() {
	int start = 0;
	for (size_t i = 0; i < N; i++) {
		Node[i].num = i;
		Node[i].parent = &Node[start];
	}
	Node[start].parent = NULL;
	SHORTEST_PATHS(start, COST, DIST, N);
	int path[N], j = 0;
	printf("start\tend\tlength\tnodes list\n");
	for (size_t i = 0; i < N; i++) {
		j = 0;
		printf("%d\t%d\t", start, i);
		printf("%d\t", DIST[i]);
		struct node *p;
		p = &Node[i];
		do {
			path[j] = p->num;
//			printf("%d ",p->num);
			p = p->parent;
			j++;
		} while(p);
		for (size_t ji = j; ji > 0; ji--) {
			printf("%d ", path[ji-1]);
		}
		printf("\n");
	}
	return 0;
}
