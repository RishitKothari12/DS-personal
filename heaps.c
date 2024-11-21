#include<stdio.h>
#include<stdlib.h> 
void swap(int *a, int *b){ 
int temp = *a; 
*a = *b; 
*b = temp; 
} 
void print(int arr[], int n){ 
printf("Array after sorting: "); 
for (int i = 0; i < n; i++){ 
printf("%d ", arr[i]); 
} 
printf("\n"); 
} 
void max_heapify(int arr[], int n, int i){ 
int largest = i; 
int left = 2*i + 1; 
    int right = 2*i + 2; 
 
    if(left < n && arr[left] > arr[largest]){ 
        largest = left; 
    } 
    if(right < n && arr[right] > arr[largest]){ 
        largest = right; 
    } 
    if (largest != i) { 
        swap(&arr[i], &arr[largest]); 
        max_heapify(arr, n, largest); 
    } 
} 
 
void sort_ascending(int arr[], int n) { 
    for (int i = n/2 - 1; i>=0; i--) 
        max_heapify(arr, n, i); 
    for (int i = n-1; i >= 0; i--) { 
        swap(&arr[0], &arr[i]); 
        max_heapify(arr, i, 0); 
        print(arr,n); 
    } 
} 
 
int main(){ 
    int n; 
    printf("Enter number of elements to insert: "); 
    scanf("%d", &n); 
    int arr[n]; 
    
    for(int i=0; i<n; i++){ 
printf("Enter element %d: ",(i+1)); 
scanf("%d",&arr[i]); 
printf("\n");
} 
sort_ascending(arr,n); 
printf("\nFinal sorted array: "); 
for (int i = 0; i < n; i++){ 
printf("%d ", arr[i]); 
} 
printf("\n"); 
return 0; 
}