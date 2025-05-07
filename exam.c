#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void bellman(int edge[][3], int e, int v, int src, int table[][100], int parent[]) {
    for(int i = 1; i <= v; i++) {
        table[1][i] = (i == src) ? 0 : INT_MAX;
    }

    for(int k = 2; k <= v + 1; k++) {
        for(int i = 1; i <= v; i++) {
            table[k][i] = table[k-1][i];
        }

        for(int i = 0; i < e; i++) {
            int u = edge[i][0];
            int v_dest = edge[i][1];
            int wt = edge[i][2];

            if(table[k-1][u] != INT_MAX && table[k-1][u] + wt < table[k][v_dest]) {
                table[k][v_dest] = table[k-1][u] + wt;
                parent[v_dest] = u;
            }
        }
    }
}

void path(int parent[], int x) {
    if (parent[x] == -1) {
        printf("%d", x);
        return;
    }
    path(parent, parent[x]);
    printf("->%d", x);
}

int main() {
    int v, e, edge[100][3], table[100][100], src, parent[100];

    printf("Enter the no of vertices and edges: ");
    scanf("%d%d", &v, &e);

    for(int i = 1; i <= v; i++)
        parent[i] = -1;

    printf("Enter the edges (src,dest,wt): ");
    for(int i = 0; i < e; i++)
        scanf("%d%d%d", &edge[i][0], &edge[i][1], &edge[i][2]);

    printf("Enter the source: ");
    scanf("%d", &src);

    bellman(edge, e, v, src, table, parent);


    printf("\n%-5s", "k");
    for(int i = 1; i <= v; i++) {
        printf("  %d->%-2d", src, i);
    }
    printf("\n");

    for(int i = 1; i <= v + 1; i++) {
        printf("%-5d", i - 1); 
        for(int j = 1; j <= v; j++) {
            if(table[i][j] == INT_MAX)
                printf("  %-5s", "INF");
            else
                printf("  %-5d", table[i][j]);
        }
        printf("\n");
    }

    
    printf("\nShortest paths from source %d:\n", src);
    for(int i = 1; i <= v; i++) {
        if(i == src) continue;
        path(parent, i);
        printf(": %d\n", table[v + 1][i]);
    }

    return 0;
}



------
///A///
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
bool issafe(int color[],int graph[][4],int n,int col,int node){
    for(int i=0;i<n;i++){
        if(i!=node&&graph[i][node]==1&&color[i]==col)   return false;
    }
    return true;
}
bool solve(int m,int color[],int graph[][4],int n,int node){
    if(node==n) return true;
    for(int i=1;i<=m;i++){
        if(issafe(color,graph,n,i,node)){
            color[node]=i;
            if(solve(m,color,graph,n,node+1))   return true;
            color[node]=0;
        }
    }
    return false;
}
int findcnum(int graph[][4],int n){
    int color[n];
    for(int i=1;i<=n;i++){
        for(int j=0;j<n;j++)    color[j]=0;
        if(solve(i,color,graph,n,0)){
            printf("Minimum number of colors required:%d\n",i);
            printf("Color of each node:\n");
            for(int k=0;k<n;k++){
                printf("Node:%d->%d\n",k+1,color[k]);
            }
            return i;
        }
    }
    return n;
}
int main(){
    int graph[4][4]={{0,1,1,1},{1,0,1,0},{1,1,0,1},{1,0,1,0}};
    findcnum(graph,4);
}


///P///
#include <stdio.h>
#include <stdbool.h>

bool is_safe(int adj[4][4], int color[], int n, int node, int c) {
    for (int i = 0; i < n; i++) {
        if(node == i)continue;
        else if (adj[node][i] && color[i] == c) return false;
    }
    return true;
}

bool find(int node, int adj[4][4], int color[], int m, int n) {
    if (node == n) return true;

    for (int i = 0; i < m; i++) {
        if (is_safe(adj, color, n, node, i)) {
            color[node] = i;
            if (find(node + 1, adj, color, m, n)) return true;
            color[node] = -1; // Backtrack
        }
    }
    return false;
}

int main() {
    int adj[4][4] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0},
    };
   
    int m;
    printf("Enter the number of colors: ");
    scanf("%d", &m);
   
    int color[4];
    for (int i = 0; i < 4; i++) color[i] = -1;
   
    if (find(0, adj, color, m, 4)) {
        for (int i = 0; i < 4; i++) {
            if(i == 2 || i == 3){
                if(i == 2){
                    printf("Node %d -> Color %d\n", i + 1, color[i + 1] + 1);
                }
                if(i == 3){
                    printf("Node %d -> Color %d\n", i + 1, color[i - 1] + 1);
                }
            }
            else {
                printf("Node %d -> Color %d\n", i + 1, color[i] + 1);
            }
        }
    } else {
        printf("Not possible with %d colors.\n", m);
    }
   
    return 0;
}

//S//
#include <stdio.h>
#include <stdbool.h>

#define MAX 100

bool isSafe(int node, int color[], bool graph[MAX][MAX], int n, int col) {
    for (int k = 0; k < n; k++) {
        if (k != node && graph[k][node] == 1 && color[k] == col) {
            return false;
        }
    }
    return true;
}

bool solve(int node, int color[], int m, int N, bool graph[MAX][MAX]) {
    if (node == N) {
        return true;
    }
    for (int i = 1; i <= m; i++) {
        if (isSafe(node, color, graph, N, i)) {
            color[node] = i;
            if (solve(node + 1, color, m, N, graph)) return true;
            color[node] = 0;
        }
    }
    return false;
}

bool graphColoring(bool graph[MAX][MAX], int m, int N, int color[]) {
    return solve(0, color, m, N, graph);
}

void printSolution(int color[], int N) {
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("Node %d -> color %d\n", i + 1, color[i]);
    }
}

int main() {
    bool graph[MAX][MAX] = {0};  // Initialize all to 0
    int color[MAX] = {0};
    int N, m;

    printf("Enter number of nodes: ");
    scanf("%d", &N);
    if (N <= 0 || N > MAX) {
        printf("Invalid number of nodes.\n");
        return 1;
    }

    printf("\nEnter adjacency matrix (1 for edge, 0 for no edge):\n\n    ");
    for (int j = 0; j < N; j++) {
        printf("c%-3d", j);// coloumn header
    }
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("r%-3d", i);
        for (int j = 0; j < N; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nEnter number of colors: ");
    scanf("%d", &m);
    if (m <= 0) {
        printf("Invalid number of colors.\n");
        return 1;
    }

    if (graphColoring(graph, m, N, color)) {
        printSolution(color, N);
    } else {
        printf("\nSolution does not exist.\n");
    }

    return 0;
}

//log//bf//
//kns//
#include <stdio.h>

typedef struct {
    int profit, weight, original_index;
    float ratio;
} Item;

void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

// Function to compute Greatest Common Divisor (GCD) using Euclidean algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void sortByRatio(Item arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].ratio < arr[j+1].ratio) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void sortByProfit(Item arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].profit < arr[j+1].profit) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void sortByWeight(Item arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].weight > arr[j+1].weight) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void knapsack(int n, int m, Item items[]) {
    float solution[n];
    float total = 0;
    int remaining = m;
    
    // Initialize solution array
    for (int i = 0; i < n; i++) {
        solution[i] = 0;
    }
    
    // Fill the knapsack
    for (int i = 0; i < n; i++) {
        if (items[i].weight <= remaining) {
            solution[items[i].original_index] = 1;
            total += items[i].profit;
            remaining -= items[i].weight;
        } else if (remaining > 0) {
            // Calculate fraction in simplest form directly
            int common_divisor = gcd(remaining, items[i].weight);
            int simplified_num = remaining / common_divisor;
            int simplified_den = items[i].weight / common_divisor;
            
            solution[items[i].original_index] = (float)remaining / items[i].weight;
            total += items[i].profit * ((float)remaining / items[i].weight);
            remaining = 0;
            
            // Print the fraction immediately in simplest form
            printf("\nSolution -> ");
            for (int k = 0; k < n; k++) {
                if (k == items[i].original_index) {
                    printf("%d/%d ", simplified_num, simplified_den);
                } else if (solution[k] == 1) {
                    printf("1 ");
                } else {
                    printf("0 ");
                }
            }
            printf("\nTotal profit -> %.2f\n", total);
            return;
        }
    }
    
    // If we get here, all items were either fully included or excluded
    printf("\nSolution -> ");
    for (int i = 0; i < n; i++) {
        if (solution[i] == 1) {
            printf("1 ");
        } else {
            printf("0 ");
        }
    }
    printf("\nTotal profit -> %.2f\n", total);
}

int main() {
    int n, m, mode;
    Item items[100];
    
    printf("Enter number of items & capacity: ");
    scanf("%d %d", &n, &m);
    
    printf("Enter profit and weight for each item:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &items[i].profit, &items[i].weight);
        items[i].ratio = (float)items[i].profit / items[i].weight;
        items[i].original_index = i;
    }
    
    while (1) {
        printf("\n1. Max Profit/Weight\n2. Max Profit\n3. Min Weight\n4. Exit\nChoose: ");
        scanf("%d", &mode);
        if (mode == 4) break;
        
        Item temp[n];
        for (int i = 0; i < n; i++) temp[i] = items[i];
        
        if (mode == 1) sortByRatio(temp, n);
        else if (mode == 2) sortByProfit(temp, n);
        else if (mode == 3) sortByWeight(temp, n);
        
        knapsack(n, m, temp);
    }
    
    return 0;
}

//bf//
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void bellman(int edge[][3], int e, int v, int src, int table[][100], int parent[]) {
    for(int i = 1; i <= v; i++) {
        table[1][i] = (i == src) ? 0 : INT_MAX;
    }

    for(int k = 2; k <= v + 1; k++) {
        for(int i = 1; i <= v; i++) {
            table[k][i] = table[k-1][i];
        }

        for(int i = 0; i < e; i++) {
            int u = edge[i][0];
            int v_dest = edge[i][1];
            int wt = edge[i][2];

            if(table[k-1][u] != INT_MAX && table[k-1][u] + wt < table[k][v_dest]) {
                table[k][v_dest] = table[k-1][u] + wt;
                parent[v_dest] = u;
            }
        }
    }
}

void path(int parent[], int x) {
    if (parent[x] == -1) {
        printf("%d", x);
        return;
    }
    path(parent, parent[x]);
    printf("->%d", x);
}

int main() {
    int v, e, edge[100][3], table[100][100], src, parent[100];

    printf("Enter the no of vertices and edges: ");
    scanf("%d%d", &v, &e);

    for(int i = 1; i <= v; i++)
        parent[i] = -1;

    printf("Enter the edges (src,dest,wt): ");
    for(int i = 0; i < e; i++)
        scanf("%d%d%d", &edge[i][0], &edge[i][1], &edge[i][2]);

    printf("Enter the source: ");
    scanf("%d", &src);

    bellman(edge, e, v, src, table, parent);

    // Print header row
    printf("\n%-5s", "k");
    for(int i = 1; i <= v; i++) {
        printf("  %d->%-2d", src, i);
    }
    printf("\n");

    // Print table rows
    for(int i = 1; i <= v + 1; i++) {
        printf("%-5d", i - 1);  // 0 to v
        for(int j = 1; j <= v; j++) {
            if(table[i][j] == INT_MAX)
                printf("  %-5s", "INF");
            else
                printf("  %-5d", table[i][j]);
        }
        printf("\n");
    }

    // Print shortest paths
    printf("\nShortest paths from source %d:\n", src);
    for(int i = 1; i <= v; i++) {
        if(i == src) continue;
        path(parent, i);
        printf(" (Cost: %d)\n", table[v + 1][i]);
    }

    return 0;
}


------
#include<stdio.h>
#include<stdlib.h>



Item item[100];


void swap(float *a ,float *b){
	float temp = *a;
	*a = *b;
	*b= temp ;
	
} 

void sortitem_1(int n,float profit[],float ratio,float weight[],float ratio[],){
	for(int i=0; i< n-1 ;i++) {
		for(int j= 0 ;j<n-i-1;i++){
			if(arr[j]>arr[j+1]){
			swap(&ratio[j],&ratio[j+1]);
			int temp =index[j] =index[j+1];
			index[j+1] = temp;
			
			}
			
			
		}	
	}			
	

}

void sortitem_2(int n,float ratio,float weight[],float ratio[],){
	for(int i=0; i< n-1 ;i++) {
		for(int j= 0 ;j<n-i-1;i++){
			if(arr[j]>arr[j+1]){
			swap(&ratio[j],&ratio[j+1]);
			int temp =index[j] =index[j+1];
			index[j+1] = temp;
			
			}
			
			
		}	
	}			


}	


void sortitem_3(int n,float ratio,float weight[],float ratio[],){
	for(int i=0; i< n-1 ;i++) {
		for(int j= 0 ;j<n-i-1;i++){
			if(arr[j]>arr[j+1]){
			swap(&ratio[j],&ratio[j+1]);
			int temp =index[j] =index[j+1];
			index[j+1] = temp;
			
			}
			
			
		}	
	}			


}	


void knapsack_3(int n,float capacity,float profit[],float weight[]){
	float x[n];
	int U = m;
	float totalprofit=0.0;
	int currentweight = 0.0;
	float ratio[n];
	
	//sorting_2(n,ratio,profit,weight);
	for(int i=0;i<n;i++){
	index[i]= [i];
	x[i]=0.0;
	}	
	
	sorting_3(n,ratio,profit,weight);
	
	for(int i=0;i<n;i++){
	if(currentweight + weight[i] <= capacity)
		x[i]=0;
		currentweight=weight[index[i]];
		totalprofit+=profit[i];
	} else {
	
		x[i]=capacity-currentweight/weight[i];
		totalprofit+=x[i]*profit[index[i]];
		break;
	
	
	}
	
}	
	printf("\np/w\n");
	float r[3]={0.00,.55}
	
	
	for(int i =0 ;i<n ;i++){
		printf("%d\t%.2f\t%.2f\t%.2f\n",i+1,weight[i].profit[i],x[i]);
	printf("total profit : %2.f\n",totalprofit);
	

	
for(int i=0;i<n;i++){
	tempitems[i]=item[i];
	x[i]=0.0;
	
}	

bubblesort(tempitem,n,mode);


for(int i= 0;i<n;i++){
	if(tempitems[i].weight <= U) {
	x[i]=1;
	totalweight = totalweight + tempitems[i].weight;
	totalprofit = totalprofit + tempitems[i].profit);
	U = U - tempitem[i].weight;
	} else {
	x[i] = U/tempitems[i].weight;
	fractionprofit = x[i]*tempitems[i].profit;
	totalprofit=totalprofit+factionprofit;
	break ;
	
	}
}	
	for(int i=0;i<n;i++){
	printf("solution: %2f ",x[i]);
       
 }
 printf("maximum profit is %2f ",totalprofit);

}


void bubblesort(Item tempitem[],n,mode){
	for(int i=0; i< n-1 ;i++) {
		for(int j= 0 ;j<n-i-1;i++){
			int condition;
			if(mode ==1) 
			condition = (tempitem[j].profit < tempitems[j+1].profit);
			
			else if (mode ==2) 
			condition = (tempitem[j].weight > tempitems[j+1],profit);
			
			else (mode == 3)
			condition = (tempitem[j].ratio < tempitems[j+1].profit);
			
			if(condition){
			
			swap(tempitem,&a[j],a[j+1]);	
			
			}
		
		}
		
	}
	

}

int main(){
	while(1) {
	int n,ch;
	float capacity;
	
	
	
	printf("enter the no of items\n");
	scanf("%d",&n);
	
	float frofit[n],weight[n];
	
	
	
	printf("enter the profit and weight of the item\n");
	
		float ratio =(float)item[i].profit/item[i].weight;
	}
		
	knapsack(m,n);
		
	
	}
	return 0;	
	
}
	

----
#include <stdio.h>
#include <limits.h>

#define max 11
#define INF INT_MAX

void printPath(int i, int j, int next[max][max]) {
    if (next[i][j] == -1) {
        printf("No path");
        return;
    }
    printf("Path: %d", i);
    while (i != j) {
        i = next[i][j];
        printf(" -> %d", i);
    }
    printf("\n");
}

void floyd(int n, int graph[max][max]) {
    int dist[max][max];
    int next[max][max];
    int i, j, k;

    // Initialize distance and next matrices
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != INF && i != j)
                next[i][j] = j;
            else
                next[i][j] = -1;
        }
    }

    // Floyd-Warshall algorithm
    for (k = 1; k <= n; k++) {
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }

        // Display intermediate results
        printf("\nAfter including node %d:\n", k);
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (dist[i][j] == INF)
                    printf("%7s", "INF");
                else
                    printf("%7d", dist[i][j]);
            }
            printf("\n");
        }
    }

    // Print final distances and paths
    printf("\nFinal shortest paths and distances:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i != j) {
                printf("Shortest path from %d to %d: ", i, j);
                if (dist[i][j] == INF) {
                    printf("No path\n");
                } else {
                    printf("Cost = %d, ", dist[i][j]);
                    printPath(i, j, next);
                }
            }
        }
    }
}

int main() {
    int graph[max][max];
    int n, i, j;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (-1 for no connection):\n");
    p
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            int val;
            scanf("%d", &val);
            if (val == -1)
                graph[i][j] = INF;
            else
                graph[i][j] = val;
        }
    }

    floyd(n, graph);

    return 0;
}
----
#include <stdio.h>
#include <limits.h>

#define MAX 11 
#define INF INT_MAX  

void printPath(int i, int j, int nextNode[MAX][MAX]) {

    if (nextNode[i][j] == -1) {
        printf("No path");
        return;
    }

    printf("%d", i);
    
    while (i != j) {
        
        i = nextNode[i][j];
        
        printf(" -> %d", i);
    }
}


void floydWarshall(int n, int graph[MAX][MAX]) {
    int dist[MAX][MAX], nextNode[MAX][MAX], i, j, k;

    
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            dist[i][j] = graph[i][j]; 
            
            if (graph[i][j] != INF && i != j) {
                nextNode[i][j] = j;
            } else {
                
                nextNode[i][j] = -1;
                
            }
        }
    }

            
   
    for (k = 1; k <= n; k++) { 
        for (i = 1; i <= n; i++) {  
            for (j = 1; j <= n; j++) {  
                
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j]; 
                    nextNode[i][j] = nextNode[i][k]; 
                }
            }
        }

        
        printf("\nA(%d):", k);
        for (i = 1; i <= n; i++) {
            printf("%5d", i);  
        }
        printf("\n");

       
        for (i = 1; i <= n; i++) {
            printf("%-5d", i);  
            for (j = 1; j <= n; j++) {
                
                if (dist[i][j] == INF) {
                    printf("  INF");
                } else {
                    
                    printf("%5d", dist[i][j]);
                }
            }
            printf("\n");
        }
    }

   
    printf("\nShortest Paths with intermediate nodes:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i != j && dist[i][j] != INF) { 
                printPath(i, j, nextNode);  
                printf(": %d\n", dist[i][j]);  
            }
        }
    }
}

int main() {
    int n, i, j;
    int graph[MAX][MAX];

   
    printf("Enter number of vertices (max %d): ", MAX - 1);
    scanf("%d", &n);

    
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
           
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = INF;  
            }
        }
    }

  
    printf("\nEnter the adjacency matrix (use -1 for infinity):\n");
    for (i = 1; i <= n; i++) {  
        for (j = 1; j <= n; j++) { 
           
            printf("Enter weight for edge %d -> %d: ", i, j);
            scanf("%d", &graph[i][j]);
           
            if (graph[i][j] == -1) {
                graph[i][j] = INF;
            }
        }
    }

    
    printf("\nInitial Adjacency Matrix:\n     ");
    for (i = 1; i <= n; i++) {
        printf("%5d", i); 
    }
    printf("\n");

    
    for (i = 1; i <= n; i++) {
        printf("%-5d", i);  
        for (j = 1; j <= n; j++) {
            
            if (graph[i][j] == INF) {
                printf("  INF");
            } else {
                
                printf("%5d", graph[i][j]);
            }
        }
        printf("\n");
    }

    
    floydWarshall(n, graph);

    return 0;
}
-------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node* next;
} node;

node *adj[100];

node *create(int x) {
    node *head = (node *)malloc(sizeof(node));
    head->data = x;
    head->next = NULL;
    return head;
}

void add(int src, int dest) {
    if (!adj[src]) {
        adj[src] = create(dest);
        return;
    }
    node *t = adj[src];
    while (t->next)
        t = t->next;
    t->next = create(dest);
}

bool safe(int *color, int x, int index) {
    node *t = adj[x];
    while (t) {
        if (color[t->data] == index)
            return false;
        t = t->next;
    }
    return true;
}

void cancolor(int m, int x, int *color, int vertex, int *solutionCount) {
    if (x == vertex + 1) {
        (*solutionCount)++;
        printf("Solution %d:\n", *solutionCount);
        for (int i = 1; i <= vertex; i++) {
            printf("Node %d -> color %d\n", i, color[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 1; i <= m; i++) {
        if (safe(color, x, i)) {
            color[x] = i;
            cancolor(m, x + 1, color, vertex, solutionCount);
            color[x] = -1; 
        }
    }
}

int main() {
    int edges, vertex;
    printf("Enter number of vertices: ");
    scanf("%d", &vertex);

    for (int i = 0; i <= vertex; i++)
        adj[i] = NULL;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges:\n");
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d%d", &src, &dest);
        add(src, dest);
        add(dest, src);
    }

    printf("Enter number of colors: ");
    int m;
    scanf("%d", &m);

    int color[vertex + 1];
    for (int i = 1; i <= vertex; i++)
        color[i] = -1;

    int solutionCount = 0;
    cancolor(m, 1, color, vertex, &solutionCount);

    if (solutionCount == 0)
        printf("Coloring not possible\n");

    return 0;
}

-----
#include<stdio.h>
#include<stdlib.h>
float arr[10];
int pos[10];
typedef struct{
	float weight[100];
	float profit[100];
	
}Knap;
void swap(float *a,float *b){
	float t=*a;
	*a=*b;
	*b=t;
}
float greedy1(Knap k,int capacity,int n){
	for(int i=0;i<n;i++){
		pos[i]=i;
		arr[i]=0;
	}
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(k.profit[j]<k.profit[j+1]){
				swap(&k.profit[j],&k.profit[j+1]);
				swap(&k.weight[j],&k.weight[j+1]);
				int temp=pos[j];
				pos[j]=pos[j+1];
				pos[j+1]=temp;
			}
		}
	}
	float ans=0;
	for(int i=0;i<n && capacity;i++){
		float wt=k.weight[i];
		float p=k.profit[i];
		
		if(wt<=capacity){
			ans+=p;
			arr[pos[i]]=1;
			capacity-=wt;
		}else{
			ans+=p*(capacity/wt);
			arr[pos[i]]=capacity/wt;
			capacity=0;
		}
	}
	for(int i=0;i<n;i++)
	printf("%.2f  ",arr[i]);
	return ans;
}
float greedy2(Knap k,int capacity,int n){
	for(int i=0;i<n;i++){
		pos[i]=i;
		arr[i]=0;
	}
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(k.weight[j]>k.weight[j+1]){
				swap(&k.profit[j],&k.profit[j+1]);
				swap(&k.weight[j],&k.weight[j+1]);
				int temp=pos[j];
				pos[j]=pos[j+1];
				pos[j+1]=temp;
			}
		}
	}
	float ans=0;
	for(int i=0;i<n && capacity;i++){
		float wt=k.weight[i];
		float p=k.profit[i];
		if(wt<=capacity){
			ans+=p;
			arr[pos[i]]=1;
			capacity-=wt;
		}else{
			ans+=p*(capacity/wt);
			arr[pos[i]]=capacity/wt;
			capacity=0;
		}
	}
	for(int i=0;i<n;i++)
	printf("%.2f  ",arr[i]);
	return ans;
}
float greedy3(Knap k,int capacity,int n){
	for(int i=0;i<n;i++){
		pos[i]=i;
		arr[i]=0;
	}
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(k.profit[j]/k.weight[j]<k.profit[j+1]/k.weight[j+1]){
				swap(&k.profit[j],&k.profit[j+1]);
				swap(&k.weight[j],&k.weight[j+1]);
				int temp=pos[j];
				pos[j]=pos[j+1];
				pos[j+1]=temp;
			}
		}
	}
	float ans=0;
	for(int i=0;i<n && capacity;i++){
		float wt=k.weight[i];
		float p=k.profit[i];
		if(wt<=capacity){
			ans+=p;
			arr[pos[i]]=1;
			capacity-=wt;
		}else{
			ans+=p*(capacity/wt);
			arr[pos[i]]=capacity/wt;
			capacity=0;
		}
	}
	for(int i=0;i<n;i++)
	printf("%.2f  ",arr[i]);
	return ans;
}
int main(){
	Knap k;
	int n,capacity,ch;
	
	printf("Enter the no of items:\n ");
	scanf("%d",&n);
	printf("Enter the the capacity of knap: \n");
	scanf("%d",&capacity);
	for(int i=0;i<n;i++){
		printf("Enter the profit and weight %d items",i+1);
		scanf("%f%f",&k.profit[i],&k.weight[i]);
	}
	do{  
		printf("Enter 1 to check maximum profit based on maximum profit\n");
		printf("Enter 2 to check maximum profit based on minimum weight\n");
		printf("Enter 3 to check maximum profit based on maximum profit/weight \n");
		printf("Enter 4 to exit\n");
		printf("Enter your choice:\n");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				printf("maximum profit based on maximum profit %.2f\n",greedy1(k,capacity,n));
				break;
			case 2: 
				printf("maximum profit based on minimum weight %.2f\n",greedy2(k,capacity,n));
				break;
			case 3:
				printf("maximum profit based on maximum (profit/weight) %.2f\n",greedy3(k,capacity,n));
				break ;
			case 4:
				printf("exits\n"); 
				break;
		}
	}while(ch!=4);
	return 0;
}
------------
#include <stdio.h>
#include <limits.h>
#define max 10

void parenthe(int s[max][max], int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        parenthe(s, i, s[i][j]);
        parenthe(s, s[i][j] + 1, j);
        printf(")");
    }
}

void print_table(int m[max][max], int s[max][max], int n) {
    printf("\n m table\n");

    printf("       ");
    for (int i = 1; i < n; i++) {
        printf("   %3d ", i); // Print column numbers for m table
    }
    printf("\n");

    for (int i = 1; i < n; i++) {
        printf(" %3d: ", i); // Print row numbers for m table
        for (int j = i; j < n; j++) {  
            printf(" %6d ", m[i][j]);  // Properly aligned values in m table
        }
        printf("\n");
    }

    // Print the s table header
    printf("\n s table\n");

    printf("       ");
    for (int i = 1; i < n; i++) {
        printf(" %3d ", i); // Print column numbers for s table
    }
    printf("\n");

    // Print the rows of the s table
    for (int i = 1; i < n; i++) {
        printf(" %3d: ", i); // Print row numbers for s table
        for (int j = i; j < n; j++) {  
            if (s[i][j] != 0) { 
                printf(" %3d ", s[i][j]);  // Properly aligned values in s table
            } else {
                printf("     ");  // If s[i][j] is zero, print spaces
            }
        }
        printf("\n");
    }
}

int filltable(int p[], int n) {
    int min, q, j;
    int m[max][max] = {0};
    int s[max][max] = {0};

    // Matrix chain multiplication logic
    for (int d = 1; d < n - 1; d++) {
        for (int i = 1; i < n - d; i++) {
            j = i + d;
            min = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < min) {
                    min = q;
                    s[i][j] = k;  // Store index of optimal split
                }
            }
            m[i][j] = min;  // Store minimum multiplication cost
        }
    }

    // Print the m and s tables
    print_table(m, s, n);

    // Display parenthesization
    printf("Parenthesisation is:\n");
    parenthe(s, 1, n - 1);

    return m[1][n - 1];  // Return the minimum multiplication cost
}

int main() {
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    int p[max];

    // Input matrix dimensions
    printf("Enter the dimensions of the matrix:\n");
    for (int i = 0; i <= n; i++) {
        scanf("%d", &p[i]);
    }
    printf("\n");

    // Compute and print the minimum multiplication cost
    int minmul = filltable(p, n + 1);

    printf("Minimum multiplication is: %d\n", minmul);
    return 0;
}


--------
#include<stdio.h>
#include<limits.h>
#define max 10

void parenthe(int s[max][max],int i,int j)
{
	if(i==j) {
	printf("A%d",i);
	
	}
	else {
	printf("(");
	parenthe(s,i,s[i][j]);
	parenthe(s,s[i][j]+1,j);	
	printf(")");
	}

}


void print_table(int m[max][max],int s[max][max],int n)
{
printf("\n m table\n");
for(int d=n-2 ; d>=0; d--) {
	for(int s =0 ;s< d*6 ;s++) printf(" ");
	 for(int i=1 ; i<=(n-1)-d; i++) {
	 int j = i + d;
	 printf(" %8d", m[i][j]);
	 
	 
	 }
	 printf("\n\n");
	
	
}
	
	
printf("\n s table\n");
for(int d=n-2 ; d>0; d--) {
	for(int s =0 ;s< d*6 ;s++) printf(" ");
	 for(int i=1 ; i<=(n-1)-d; i++) {
	 int j = i+d;
	 printf(" %8d", s[i][j]);
	 	

	} 
	printf("\n\n");	
	}

}


int filltable(int p[],int n)
{
int min,q,j;
int m[max][max] = {0};
int s[max][max] = {0};


	for(int d = 1 ;d<n-2 ;d++) {
		for( int i=1 ; i<n-d ;i++) {
		j = i + d;
		min = INT_MAX;
		for(int k = i ; k <= j-1 ;k++)
		{
		q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
		if(q<min) {
		min = q;
		s[i][j] = k;
		
		}
		
		}
		m[i][j] = min;
		
	}

	}
	
	print_table(m,s,n);
	
	printf("parenthesisation is:\n");
	parenthe(s,1,n-1);
	
	return m[1][n-1];
}

int main() {
int n;
printf("enter the no of matrices:");
scanf("%d",&n);

int p[max];

printf("enter the dimensions of the matrix:\n");
for(int i=0;i<=n;i++) {
scanf("%d",&p[i]);

}
printf("\n");

int minmul = filltable(p,n+1);

printf("minimul multiplication is:%d\n",minmul);
return 0;

}
//write a c program to implement 15 puzzle
//sidhant.hansda.it27
//Pnc3I7Ww
//https://github.comjavahitk/qatar.git
		
		
		
		------------
#include <stdio.h>
void find(char queen[][100],int col[],int left[],int right[],int i,int n,int *c)
{
    if(i==n)
    {
        printf("Solution %d:\n",*c); (*c)++;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(queen[i][j]=='.')
                printf("%c ",queen[i][j]);
                else
                printf("%c%d ",queen[i][j],i+1);
            }
            printf("\n");;
        }
        printf("\n");
        return;
        
    }
    for(int j=0;j<n;j++)
    {
        if(!col[j]&&!left[j-i+n-1]&&!right[i+j])
        {
            queen[i][j]='Q';
            col[j]=1;
            left[j-i+n-1]=1;
            right[i+j]=1;
            find(queen,col,left,right,i+1,n,c);
            queen[i][j]='.';
            col[j]=0;
            left[j-i+n-1]=0;
            right[i+j]=0;
        }
    }
}
int main()
{
    int n;
    printf("Enter no of queen : ");
    scanf("%d",&n);

    char queen[100][100];
    
    for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
    queen[i][j]='.';

    int col[100],left[100],right[100];
    for(int i=0;i<n;i++)
    col[i]=0;

    for(int i=0;i<2*n-1;i++)
    {
        left[i]=0;
        right[i]=0;
    }
    int c=1;
    find(queen,col,left,right,0,n,&c);
    return 0;
}
		
#include <stdio.h>
#include <stdbool.h>

int c = 0;

void print(int n, char board[4][4]) {
    printf("Solution %d:\n", ++c);
    printf("  \t1\t2\t3\t4\n");

    int q_num = 1;  

    for (int i = 0; i < n; i++) {
        printf("%d\t", i + 1);
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'Q') {
                printf("Q%d\t", q_num);
                q_num++;
            }
           
            else {
                printf(".\t");
            }
        }
        printf("\n");
    }

    printf("\n");
}

bool is_safe(int n, char board[4][4], int row, int col) {
    for (int i = 0; i < n; i++) {
        if (i == col) continue;
        if (board[row][i] == 'Q') return false;
    }

    for (int i = 0; i < n; i++) {
        if (i == row) continue;
        if (board[i][col] == 'Q') return false;
    }

    int i = row - 1, j = col - 1;
    while (i >= 0 && j >= 0) {
        if (board[i][j] == 'Q') return false;
        i--;
        j--;
    }

    i = row - 1;
    j = col + 1;
    while (i >= 0 && j < n) {
        if (board[i][j] == 'Q') return false;
        i--;
        j++;
    }

    return true;
}

void check(int n, char board[4][4], int row) {
    if (row == n) {
        print(n, board);
        return;
    }

    for (int j = 0; j < n; j++) {
        if (is_safe(n, board, row, j)) {
            board[row][j] = 'Q';
            check(n, board, row + 1);
            board[row][j] = ' ';
        }
    }
}



-----------

int main() {
    char board[4][4];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            board[i][j] = ' ';

    check(4, board, 0);

    return 0;
}


-------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int goal[4][4]={{1,2,3,4},
                {5,6,7,8},
                {9,10,11,12},
                {13,14,15,0}};

int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};

typedef struct Node{
    int mat[4][4];
    int x,y;
    int level,cost;
    struct Node *parent;
    struct Node *next;
}Node;

Node *newnode(int mat[4][4],int x,int y,int newx,int newy,int level,Node *parent)
{
    Node *node=(Node *)malloc(sizeof(Node));
    memcpy(node->mat,mat,sizeof(node->mat));

    int t=node->mat[x][y];
    node->mat[x][y]=node->mat[newx][newy];
    node->mat[newx][newy]=t;

    node->x=newx;
    node->y=newy;
    node->level=level;
    node->cost=0;
    node->parent=parent;
    node->next=NULL;
    return node;
}

int dist(int mat[4][4])
{
    int ans=0;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            int val=mat[i][j]-1;
            int goalx=val%4;
            int goaly=val/4;
            ans+=abs(goalx-j)+abs(goaly-i);
        }
    }
    return ans;
}

void printmat(int mat[4][4])
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(mat[i][j]==0)
            printf("\t");
            else printf("%2d\t",mat[i][j]);
        }
        printf("\n");
    }
    printf("-----------\n");
}

int issafe(int x,int y)
{
    return x<4&&y<4&&x>=0&&y>=0;
}

int isgoal(int mat[4][4])
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(mat[i][j]!=goal[i][j])
            return 0;
        }
    }
    return 1;
}
void push(Node **head,Node *node)
{
    if(!(*head)||node->cost<(*head)->cost)
    {
        node->next=(*head);
        (*head)=node;
    }
    else
    {
        Node* curr = *head;
        while (curr->next && curr->next->cost <= node->cost)
            curr = curr->next;
        node->next = curr->next;
        curr->next = node;
    }
}
Node* pop(Node **head)
{
    if(!(*head))
    return NULL;

    Node *t=(*head);
    *head=(*head)->next;
    return t;
}

void printpath(Node *node)
{
    if(!node)
    return;
    printpath(node->parent);
    printmat(node->mat);
}

void solve(int initial[4][4],int x,int y)
{
    Node *openlist=NULL;
    Node *node=newnode(initial,x,y,x,y,0,NULL);
    node->cost=dist(node->mat);

    push(&openlist,node);

   // int steps;
    while(openlist)
    {
        Node *curr=pop(&openlist);
        if(isgoal(curr->mat))
        {
            printf("Solved in %d steps!\n\n", curr->level);
            printpath(curr);
            return;
        }
        
        for(int i=0;i<4;i++)
        {
            int newx=curr->x+dx[i];
            int newy=curr->y+dy[i];

            if(issafe(newx,newy))
            {
                Node *child=newnode(curr->mat,curr->x,curr->y,newx,newy,curr->level+1,curr);
                child->cost=dist(child->mat)+child->level;
                push(&openlist,child);
            }
        }
        
    }
    printf("No soln found\n");
}
int main()
{
    int initial[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9,10, 7,11},
        {13,14,15,12}
    };

    int x, y;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (initial[i][j] == 0)
                x = i, y = j;

    solve(initial, x, y);

    return 0;
}


-----------
#include <stdio.h>
#include <limits.h>
int path[100][100];
void find(int u,int v,int adj[][100])
{
    if(path[u][v]==0||adj[u][v]==-1)
    return;
    printf("Path from %d to %d: ",u,v);
    int t=u;
    printf("%d ",u);
    while(t!=v)
    {
        t=path[t][v];
        printf("-> %d",t);
    }
    printf(" : %d\n",adj[u][v]);
}
void print(int adj[][100],int v)
{
    for(int i=1;i<=v;i++)
    {
        for(int j=1;j<=v;j++)
        {
            printf("%d ",adj[i][j]);
        }
        printf("\n");
    }
}
void floyd(int adj[][100],int v)
{
    for(int i=1;i<=v;i++)
    for(int j=1;j<=v;j++)
    {
        if(adj[i][j]==-1)
        adj[i][j]=INT_MAX;
        else if(i!=j)
        path[i][j]=j;
    }

    for(int k=1;k<=v;k++)
    {
        for(int i=1;i<=v;i++)
        for(int j=1;j<=v;j++)
        {
            if(adj[i][k]==INT_MAX||adj[k][j]==INT_MAX)
            continue;
            if(adj[i][j]>adj[i][k]+adj[k][j])
            {
                adj[i][j]=adj[i][k]+adj[k][j];
                path[i][j]=path[i][k];
            }
        }
        if(k==v)
        printf("Optimal Solution : \n");
        else
        printf("Intermediate step %d : \n",k);
        print(adj,v);
    }
    for(int i=1;i<=v;i++)
    for(int j=1;j<=v;j++)
    if(adj[i][j]==INT_MAX)
    adj[i][j]=-1;

}
int main()
{
    int v,edges;
    printf("Enter no of vertices : ");
    scanf("%d",&v);
    int adj[100][100];
    for(int i=1;i<=v;i++)
    for(int j=1;j<=v;j++)
    {
        adj[i][j]=-1;
        path[i][j]=0;
    }

    printf("Enter no of edges : ");
    scanf("%d",&edges);

    printf("Enter edges : (src,dest,weight)");
    for(int i=0;i<edges;i++)
    {
        int src,dest,wt;
        scanf("%d%d%d",&src,&dest,&wt);
        adj[src][dest]=wt;
        path[src][dest]=dest;
    }
    for(int i=1;i<=v;i++)
    adj[i][i]=0;

    floyd(adj,v);
    printf("\nPATH : \n");
    for(int i=1;i<=v;i++)
    {
        for(int j=1;j<=v;j++)
        {
            find(i,j,adj);
        }
    }
    return 0;
}


--------#include <stdio.h>
#include <limits.h>
#define max 10

void parenthe(int s[max][max], int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        parenthe(s, i, s[i][j]);
        parenthe(s, s[i][j] + 1, j);
        printf(")");
    }
}

void print_table(int m[max][max], int s[max][max], int n) {
    printf("\n m table\n");

    printf("       ");
    for (int i = 1; i < n; i++) {
        printf("   %3d ", i);
    }
    printf("\n");

    for (int i = 1; i < n; i++) {
        printf(" %3d: ", i);
        for (int j = i; j < n; j++) {
            printf(" %6d ", m[i][j]);
        }
        printf("\n");
    }

    printf("\n s table\n");

    // This prints the header with proper spacing
    printf("       ");
    for (int i = 1; i < n; i++) {
        printf("   %3d ", i);
    }
    printf("\n");

    for (int i = 1; i < n; i++) {
        printf(" %3d: ", i);
        for (int j = i; j < n; j++) {
            if (s[i][j] != 0) {  // Print the split index, or blank if it's 0
                printf(" %3d ", s[i][j]);
            } else {
                printf("     ");  // Blank if no split
            }
        }
        printf("\n");
    }
}

int filltable(int p[], int n) {
    int min, q, j;
    int m[max][max] = {0};
    int s[max][max] = {0};

    for (int d = 1; d < n - 1; d++) {
        for (int i = 1; i < n - d; i++) {
            j = i + d;
            min = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < min) {
                    min = q;
                    s[i][j] = k;
                }
            }
            m[i][j] = min;
        }
    }

    print_table(m, s, n);

    printf("Parenthesisation is:\n");
    parenthe(s, 1, n - 1);

    return m[1][n - 1];
}

int main() {
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    int p[max];

    printf("Enter the dimensions of the matrix:\n");
    for (int i = 0; i <= n; i++) {
        scanf("%d", &p[i]);
    }
    printf("\n");

    int minmul = filltable(p, n + 1);

    printf("Minimum multiplication is: %d\n", minmul);
    return 0;
}
---------
///A///
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
bool issafe(int color[],int graph[][4],int n,int col,int node){
    for(int i=0;i<n;i++){
        if(i!=node&&graph[i][node]==1&&color[i]==col)   return false;
    }
    return true;
}
bool solve(int m,int color[],int graph[][4],int n,int node){
    if(node==n) return true;
    for(int i=1;i<=m;i++){
        if(issafe(color,graph,n,i,node)){
            color[node]=i;
            if(solve(m,color,graph,n,node+1))   return true;
            color[node]=0;
        }
    }
    return false;
}
int findcnum(int graph[][4],int n){
    int color[n];
    for(int i=1;i<=n;i++){
        for(int j=0;j<n;j++)    color[j]=0;
        if(solve(i,color,graph,n,0)){
            printf("Minimum number of colors required:%d\n",i);
            printf("Color of each node:\n");
            for(int k=0;k<n;k++){
                printf("Node:%d->%d\n",k+1,color[k]);
            }
            return i;
        }
    }
    return n;
}
int main(){
    int graph[4][4]={{0,1,1,1},{1,0,1,0},{1,1,0,1},{1,0,1,0}};
    findcnum(graph,4);
}


///P///
#include <stdio.h>
#include <stdbool.h>

bool is_safe(int adj[4][4], int color[], int n, int node, int c) {
    for (int i = 0; i < n; i++) {
        if(node == i)continue;
        else if (adj[node][i] && color[i] == c) return false;
    }
    return true;
}

bool find(int node, int adj[4][4], int color[], int m, int n) {
    if (node == n) return true;

    for (int i = 0; i < m; i++) {
        if (is_safe(adj, color, n, node, i)) {
            color[node] = i;
            if (find(node + 1, adj, color, m, n)) return true;
            color[node] = -1; // Backtrack
        }
    }
    return false;
}

int main() {
    int adj[4][4] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0},
    };
   
    int m;
    printf("Enter the number of colors: ");
    scanf("%d", &m);
   
    int color[4];
    for (int i = 0; i < 4; i++) color[i] = -1;
   
    if (find(0, adj, color, m, 4)) {
        for (int i = 0; i < 4; i++) {
            if(i == 2 || i == 3){
                if(i == 2){
                    printf("Node %d -> Color %d\n", i + 1, color[i + 1] + 1);
                }
                if(i == 3){
                    printf("Node %d -> Color %d\n", i + 1, color[i - 1] + 1);
                }
            }
            else {
                printf("Node %d -> Color %d\n", i + 1, color[i] + 1);
            }
        }
    } else {
        printf("Not possible with %d colors.\n", m);
    }
   
    return 0;
}

//S//
#include <stdio.h>
#include <stdbool.h>

#define MAX 100

bool isSafe(int node, int color[], bool graph[MAX][MAX], int n, int col) {
    for (int k = 0; k < n; k++) {
        if (k != node && graph[k][node] == 1 && color[k] == col) {
            return false;
        }
    }
    return true;
}

bool solve(int node, int color[], int m, int N, bool graph[MAX][MAX]) {
    if (node == N) {
        return true;
    }
    for (int i = 1; i <= m; i++) {
        if (isSafe(node, color, graph, N, i)) {
            color[node] = i;
            if (solve(node + 1, color, m, N, graph)) return true;
            color[node] = 0;
        }
    }
    return false;
}

bool graphColoring(bool graph[MAX][MAX], int m, int N, int color[]) {
    return solve(0, color, m, N, graph);
}

void printSolution(int color[], int N) {
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("Node %d -> color %d\n", i + 1, color[i]);
    }
}

int main() {
    bool graph[MAX][MAX] = {0};  // Initialize all to 0
    int color[MAX] = {0};
    int N, m;

    printf("Enter number of nodes: ");
    scanf("%d", &N);
    if (N <= 0 || N > MAX) {
        printf("Invalid number of nodes.\n");
        return 1;
    }

    printf("\nEnter adjacency matrix (1 for edge, 0 for no edge):\n\n    ");
    for (int j = 0; j < N; j++) {
        printf("c%-3d", j);// coloumn header
    }
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("r%-3d", i);
        for (int j = 0; j < N; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nEnter number of colors: ");
    scanf("%d", &m);
    if (m <= 0) {
        printf("Invalid number of colors.\n");
        return 1;
    }

    if (graphColoring(graph, m, N, color)) {
        printSolution(color, N);
    } else {
        printf("\nSolution does not exist.\n");
    }

    return 0;
}

//log//bf//
//kns//
#include <stdio.h>

typedef struct {
    int profit, weight, original_index;
    float ratio;
} Item;

void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

// Function to compute Greatest Common Divisor (GCD) using Euclidean algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void sortByRatio(Item arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].ratio < arr[j+1].ratio) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void sortByProfit(Item arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].profit < arr[j+1].profit) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void sortByWeight(Item arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].weight > arr[j+1].weight) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void knapsack(int n, int m, Item items[]) {
    float solution[n];
    float total = 0;
    int remaining = m;
    
    // Initialize solution array
    for (int i = 0; i < n; i++) {
        solution[i] = 0;
    }
    
    // Fill the knapsack
    for (int i = 0; i < n; i++) {
        if (items[i].weight <= remaining) {
            solution[items[i].original_index] = 1;
            total += items[i].profit;
            remaining -= items[i].weight;
        } else if (remaining > 0) {
            // Calculate fraction in simplest form directly
            int common_divisor = gcd(remaining, items[i].weight);
            int simplified_num = remaining / common_divisor;
            int simplified_den = items[i].weight / common_divisor;
            
            solution[items[i].original_index] = (float)remaining / items[i].weight;
            total += items[i].profit * ((float)remaining / items[i].weight);
            remaining = 0;
            
            // Print the fraction immediately in simplest form
            printf("\nSolution -> ");
            for (int k = 0; k < n; k++) {
                if (k == items[i].original_index) {
                    printf("%d/%d ", simplified_num, simplified_den);
                } else if (solution[k] == 1) {
                    printf("1 ");
                } else {
                    printf("0 ");
                }
            }
            printf("\nTotal profit -> %.2f\n", total);
            return;
        }
    }
    
    // If we get here, all items were either fully included or excluded
    printf("\nSolution -> ");
    for (int i = 0; i < n; i++) {
        if (solution[i] == 1) {
            printf("1 ");
        } else {
            printf("0 ");
        }
    }
    printf("\nTotal profit -> %.2f\n", total);
}

int main() {
    int n, m, mode;
    Item items[100];
    
    printf("Enter number of items & capacity: ");
    scanf("%d %d", &n, &m);
    
    printf("Enter profit and weight for each item:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &items[i].profit, &items[i].weight);
        items[i].ratio = (float)items[i].profit / items[i].weight;
        items[i].original_index = i;
    }
    
    while (1) {
        printf("\n1. Max Profit/Weight\n2. Max Profit\n3. Min Weight\n4. Exit\nChoose: ");
        scanf("%d", &mode);
        if (mode == 4) break;
        
        Item temp[n];
        for (int i = 0; i < n; i++) temp[i] = items[i];
        
        if (mode == 1) sortByRatio(temp, n);
        else if (mode == 2) sortByProfit(temp, n);
        else if (mode == 3) sortByWeight(temp, n);
        
        knapsack(n, m, temp);
    }
    
    return 0;
}

//bf//
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void bellman(int edge[][3], int e, int v, int src, int table[][100], int parent[]) {
    for(int i = 1; i <= v; i++) {
        table[1][i] = (i == src) ? 0 : INT_MAX;
    }

    for(int k = 2; k <= v + 1; k++) {
        for(int i = 1; i <= v; i++) {
            table[k][i] = table[k-1][i];
        }

        for(int i = 0; i < e; i++) {
            int u = edge[i][0];
            int v_dest = edge[i][1];
            int wt = edge[i][2];

            if(table[k-1][u] != INT_MAX && table[k-1][u] + wt < table[k][v_dest]) {
                table[k][v_dest] = table[k-1][u] + wt;
                parent[v_dest] = u;
            }
        }
    }
}

void path(int parent[], int x) {
    if (parent[x] == -1) {
        printf("%d", x);
        return;
    }
    path(parent, parent[x]);
    printf("->%d", x);
}

int main() {
    int v, e, edge[100][3], table[100][100], src, parent[100];

    printf("Enter the no of vertices and edges: ");
    scanf("%d%d", &v, &e);

    for(int i = 1; i <= v; i++)
        parent[i] = -1;

    printf("Enter the edges (src,dest,wt): ");
    for(int i = 0; i < e; i++)
        scanf("%d%d%d", &edge[i][0], &edge[i][1], &edge[i][2]);

    printf("Enter the source: ");
    scanf("%d", &src);

    bellman(edge, e, v, src, table, parent);

    // Print header row
    printf("\n%-5s", "k");
    for(int i = 1; i <= v; i++) {
        printf("  %d->%-2d", src, i);
    }
    printf("\n");

    // Print table rows
    for(int i = 1; i <= v + 1; i++) {
        printf("%-5d", i - 1);  // 0 to v
        for(int j = 1; j <= v; j++) {
            if(table[i][j] == INT_MAX)
                printf("  %-5s", "INF");
            else
                printf("  %-5d", table[i][j]);
        }
        printf("\n");
    }

    // Print shortest paths
    printf("\nShortest paths from source %d:\n", src);
    for(int i = 1; i <= v; i++) {
        if(i == src) continue;
        path(parent, i);
        printf(" (Cost: %d)\n", table[v + 1][i]);
    }

    return 0;
}//



-------
#include <stdio.h>
#include <limits.h>
#define max 10

void parenthe(int s[max][max], int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        parenthe(s, i, s[i][j]);
        parenthe(s, s[i][j] + 1, j);
        printf(")");
    }
}

void print_table(int m[max][max], int s[max][max], int n) {
    printf("\n m table\n");
    // Print column indices (start at 1 for proper spacing)
    printf("       ");
    for (int i = 1; i < n; i++) {
        printf("   %3d ", i); // print column indices with extra space for alignment
    }
    printf("\n");

    // Print the m table
    for (int i = 1; i < n; i++) {
        printf(" %3d: ", i); // print row indices
        for (int j = i; j < n; j++) {  // Only print upper triangular part
            printf(" %6d ", m[i][j]);
        }
        printf("\n");
    }

    printf("\n s table\n");
    // Print column indices for s table
    printf("       ");
    for (int i = 1; i < n; i++) {
        printf("   %3d ", i); // print column indices with extra space for alignment
    }
    printf("\n");

    // Print the s table
    for (int i = 1; i < n; i++) {
        printf(" %3d: ", i); // print row indices
        for (int j = i; j < n; j++) {  // Only print upper triangular part
            if (s[i][j] != 0) { // Only print non-zero values
                printf(" %6d ", s[i][j]);
            } else {
                printf("        "); // Print blank space for zero values
            }
        }
        printf("\n");
    }
}

int filltable(int p[], int n) {
    int min, q, j;
    int m[max][max] = {0};
    int s[max][max] = {0};

    // Fill the m and s tables using dynamic programming
    for (int d = 1; d < n - 1; d++) {
        for (int i = 1; i < n - d; i++) {
            j = i + d;
            min = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < min) {
                    min = q;
                    s[i][j] = k;
                }
            }
            m[i][j] = min;
        }
    }

    print_table(m, s, n);

    printf("Parenthesisation is:\n");
    parenthe(s, 1, n - 1);

    return m[1][n - 1];
}

int main() {
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    int p[max];

    printf("Enter the dimensions of the matrix:\n");
    for (int i = 0; i <= n; i++) {
        scanf("%d", &p[i]);
    }
    printf("\n");

    int minmul = filltable(p, n + 1);

    printf("Minimum multiplication is: %d\n", minmul);
    return 0;
}

------------
#include <stdio.h>
#include <limits.h>
int path[100][100];
void find(int u,int v,int adj[][100])
{
    if(path[u][v]==0||adj[u][v]==-1)
    return;
    printf("Path from %d to %d: ",u,v);
    int t=u;
    printf("%d ",u);
    while(t!=v)
    {
        t=path[t][v];
        printf("-> %d",t);
    }
    printf(" : %d\n",adj[u][v]);
}
void print(int adj[][100],int v)
{
    for(int i=1;i<=v;i++)
    {
        for(int j=1;j<=v;j++)
        {
            printf("%d ",adj[i][j]);
        }
        printf("\n");
    }
}
void floyd(int adj[][100],int v)
{
    for(int i=1;i<=v;i++)
    for(int j=1;j<=v;j++)
    {
        if(adj[i][j]==-1)
        adj[i][j]=INT_MAX;
        else if(i!=j)
        path[i][j]=j;
    }

    for(int k=1;k<=v;k++)
    {
        for(int i=1;i<=v;i++)
        for(int j=1;j<=v;j++)
        {
            if(adj[i][k]==INT_MAX||adj[k][j]==INT_MAX)
            continue;
            if(adj[i][j]>adj[i][k]+adj[k][j])
            {
                adj[i][j]=adj[i][k]+adj[k][j];
                path[i][j]=path[i][k];
            }
        }
        if(k==v)
        printf("Optimal Solution : \n");
        else
        printf("Intermediate step %d : \n",k);
        print(adj,v);
    }
    for(int i=1;i<=v;i++)
    for(int j=1;j<=v;j++)
    if(adj[i][j]==INT_MAX)
    adj[i][j]=-1;

}
int main()
{
    int v,edges;
    printf("Enter no of vertices : ");
    scanf("%d",&v);
    int adj[100][100];
    for(int i=1;i<=v;i++)
    for(int j=1;j<=v;j++)
    {
        adj[i][j]=-1;
        path[i][j]=0;
    }

    printf("Enter no of edges : ");
    scanf("%d",&edges);

    printf("Enter edges : (src,dest,weight)");
    for(int i=0;i<edges;i++)
    {
        int src,dest,wt;
        scanf("%d%d%d",&src,&dest,&wt);
        adj[src][dest]=wt;
        path[src][dest]=dest;
    }
    for(int i=1;i<=v;i++)
    adj[i][i]=0;

    floyd(adj,v);
    printf("\nPATH : \n");
    for(int i=1;i<=v;i++)
    {
        for(int j=1;j<=v;j++)
        {
            find(i,j,adj);
        }
    }
    return 0;
}


