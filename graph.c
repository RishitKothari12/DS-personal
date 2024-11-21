#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define INF -1

struct node {
    int data;
    struct node *next;
};

struct graph {
    int ver;
    struct node* array[MAX];
};

struct node *insert(int data) {
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

struct graph *create(int ver) {
    struct graph *graph = (struct graph*)malloc(sizeof(struct graph));
    graph->ver = ver;

    for (int i = 0; i < ver; i++) {
        graph->array[i] = NULL;
    }
    
    return graph;
}

void addedge(struct graph *graph, int start, int end) {
    struct node* newnode = insert(end);
    newnode->next = graph->array[start];
    graph->array[start] = newnode;
}

void display(struct graph *graph) {
    for (int i = 0; i < graph->ver; i++) {
        struct node *temp = graph->array[i];
        printf("Adjacency list of vertex %d ->", i);
        while (temp != NULL) {
            printf(" %d ->", temp->data);
            temp = temp->next;
        }
        printf(" NULL\n");
    }
}

void bfs(struct graph *graph, int start) {
    int queue[MAX], front = 0, rear = 0; 
    int visited[MAX] = {0}; 
    int parent[MAX];         
    int distance[MAX];     

    
    for (int i = 0; i < graph->ver; i++) {
        parent[i] = INF;     
        distance[i] = INF;   
    }


    visited[start] = 1;
    parent[start] = -1;   
    distance[start] = 0;   
    queue[rear++] = start;   
    
    printf("Initial Queue: ");
    for (int i = front; i < rear; i++) {
        printf("%d ", queue[i]);
    }
    printf("\nInitial Parent: ");
    for (int i = 0; i < graph->ver; i++) {
        printf("%d ", parent[i]);
    }
    printf("\nInitial Distance: ");
    for (int i = 0; i < graph->ver; i++) {
        printf("%d ", distance[i]);
    }
    printf("\n----------------------\n");

    while (front < rear) {
        int current = queue[front++];  
        printf("Exploring vertex %d:\n", current);
        
        struct node *temp = graph->array[current]; 
        while (temp != NULL) {
            int adj = temp->data;
            if (!visited[adj]) {
                visited[adj] = 1;
                parent[adj] = current;            
                distance[adj] = distance[current] + 1; 
                queue[rear++] = adj;              
            }
            temp = temp->next;
        }
        
        
        printf("Updated Queue: ");
        for (int i = front; i < rear; i++) {
            printf("%d ", queue[i]);
        }
        printf("\nUpdated Parent: ");
        for (int i = 0; i < graph->ver; i++) {
            printf("%d ", parent[i]);
        }
        printf("\nUpdated Distance: ");
        for (int i = 0; i < graph->ver; i++) {
            printf("%d ", distance[i]);
        }
        printf("\n----------------------\n");
    }
}

int main() {
    int ver = 7;
    
    struct graph *graph = create(ver);
    printf("vertex 0 -> Everett\nvertex 1 -> Seatle\nvertex 2 -> North Bend\nvertex 3 -> Olympia\nvertex 4 -> Centralia\nvertex 5 -> Spokane\nvertex 6 -> Portland\n");
    addedge(graph, 0, 1); 
    addedge(graph, 0, 2); 
    addedge(graph, 0, 5); 
    addedge(graph, 1, 3); 
    addedge(graph, 3, 4); 
    addedge(graph, 4, 5); 
    addedge(graph, 4, 6); 
    addedge(graph, 2, 5); 
    addedge(graph, 3, 6); 
 
    
    printf("\nBFS starting from vertex 0 (Everett):\n");
    bfs(graph, 0);
    
    printf("\nBFS starting from vertex 3 (Olympia):\n");
    bfs(graph, 3);
    return 0;
}