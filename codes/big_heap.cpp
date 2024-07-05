#include<iostream>
#include<queue>
#include<stack>
using namespace std;

void display(int array[], int size){
	for(int i =0; i<size; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}

void swap(int array[], int x,  int y){
	int temp = array[x];
	array[x] = array[y];
	array[y] = temp;
}

void Down(int array[], int i, int n){
	// 构造一个大顶堆(大根堆)
	// 记录父节点下表
	int parent = i;
	// 左节点下标
	int child = 2*i +1;
	while(child<n){
		if(child+1<n && array[child]<array[child+1]){
			// 判断左右子节点哪个大，大的与父节点比较
			child++;
		}
		if(array[parent]<array[child]){ //判断父节点是否小于子节点
			// 交换父节点和子节点
			swap(array, parent, child);
			parent = child; //子节点下标 赋给 父节点下标
		}
		child = child*2 +1; //换行，比较下面的父节点和子节点
	}
}

void BuildHeap(int array[], int size){
	for(int i=(size-2)/2; i>=0; i--){
		// 从最后一个非叶子节点开始依次下沉，最后一个非叶子节点的数组下标的计算方法是(n-2)/2
		// 数组长度为n
		Down(array, i, size);

	}
}

void HeapSort(int array[], int size){
	for(int i=size-1; i>0; i--){
		// 交换顶点和第i个数据
		swap(array,0,i);
		// 注意是从堆顶开始逐渐“下沉”，重新构建大顶堆（大根堆）
		int len = i;
		Down(array,0,i);
	}
}

int main(){
	int array[]={49,38,65,97,76,27,49,10};
	int size = sizeof(array)/sizeof(int);
	// 建立大根堆
	printf("数组大小 %d\n", size);
	BuildHeap(array,size);
	printf("建堆之后数组 ");
	display(array,size);
	HeapSort(array,size);
	printf("排序之后的数组 ");
	display(array,size);
	return 0;

}

// 数组大小 8
// 建堆之后数组 97 76 65 38 49 27 49 10 
// 排序之后的数组 10 27 38 49 49 65 76 97 