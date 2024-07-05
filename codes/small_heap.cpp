#include<iostream>
#include<queue>
#include<stack>
using namespace std;

void display(int array[], int size){
	for(int i=0; i<size; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}

void swap(int array[], int x, int y){
	int temp = array[x];
	array[x] = array[y];
	array[y] = temp;
}

void Down(int array[], int i, int n){
	int parent = i;
	int child = 2*i + 1;
	// 循环判断：当前的父节点和左右子节点的关系
	// 循环终止的条件
	while(child<n){
		// 判断较小的那个子节点
		if(child+1<n && array[child]>array[child+1]){
			child++;
		}
		if(array[parent]>array[child]){
			swap(array, parent, child);
			parent = child;
		}
		child =  2*child + 1;
	}
}

void buildHeap(int array[], int size){
	for(int i=(size-2)/2; i>=0; i--){
		Down(array, i, size);
	}
}

void HeapSort(int array[], int size){
	for(int i=size-1; i>0; i--){
		swap(array,0,i);
		Down(array,0,i);
	}
}

int main(){
	int array[]={48,38,65,97,76,27,49,10};
	int size = sizeof(array)/sizeof(int);
	// 建立小根堆
	printf("数组大小 %d\n", size);
	buildHeap(array,size);
	printf("建堆之后数组 ");
	display(array,size);
	HeapSort(array,size);
	printf("排序之后的数组 ");
	display(array,size);
	return 0;
}

// 数组大小 8
// 建堆之后数组 10 38 27 48 76 65 49 97 
// 排序之后的数组 97 76 65 49 48 38 27 10 