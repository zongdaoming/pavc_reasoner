#include<iostream>
#include<vector>
#include<bits/stdc++.h>
using namespace std;

int partition(vector<int>& a, int left, int right){
    // int pos = GetMid(a, left, right);
    // swap(a[pos], a[left]);                   //将取得的基准值和第一个位置交换	

	int i = left;
	int j = right;
	int key = a[left];
	while(i!=j){
		while(i<j && a[j] >= key){ //向左找到小于基准值的值的下标
			j--;
		}
		while(i<j && a[i]<= key){ // //向右找到大于基准值的值的下标
			i++;
		}
		swap(a[i],a[j]);
	}
	/*   i等于j时跳出循环 当前基准值此时在下标为i的位置(合适的位置)   */
	swap(a[left],a[i]); // 最左边的元素变为处于当前合适位置的元素,把基准值放在合适位置
	return i; // 返回合适位置(i,j都可以)
}


void quicksort(vector<int> &a, int left, int right){
	if(left >= right){
		return;
	}
	int i = partition(a, left, right);
	quicksort(a, left, i-1);
	quicksort(a, i+1, right);
}
