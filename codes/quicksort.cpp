#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// 左右指针法
int Partition_here(vector<int> &a, int left, int right){
	int i = left;
	int j = right;
	int key = a[left];
	while(i!=j){
		while(i<j && a[j]>=key){
			j--;  // 向左找到小于基准值的下标
		}
		while(i<j && a[i]<=key){
		    i++;  // 向右找到大于基准值的下标
	    }
		swap(a[i],a[j]);
	}
	/* i等于j时跳出循环 当前基准值此时在下标为i的位置(合适的位置)*/
	// 重复步骤3，直到最后我们可爱的左右指针相遇，这时我们再将基准值 key，放到这两个指针指向的位置。此时我们就得到了当前划分的位置，基准值 key 也完成了归位
	swap(a[left],a[i]);
	return i;
}


//前后指针法  
int Partition_PreAndCurr(vector<int> &a, int left, int right){
    int pre = left;                          //pre最后找到左半部分最后一个小于基准值的元素
    int curr = pre + 1;                      //curr找到pre指向元素之后的下一个小于基准值的元素
    int key = a[left];

    while(curr <= right){
	if(a[curr] < key && ++pre != curr)   //当a[curr]>=key时pre保持不动,直到最后curr找到下一个小于基准值的元素
	    swap(a[curr], a[pre]);           //pre往后移动到其下一个位置,并交换前后指针指向的元素
	curr++;
    }
    swap(a[left], a[pre]);                   //最后将基准值和此时处于pre位置的小于基准值的元素交换
    return pre;
}



// 三数取中，就是取序列中的最左边，中间，以及最右边三个数进行比较，
// 以这三个数大小为中的元素作为基准值。这样可以更大程度上避免划分位置不好的情况，即使其并不能彻底避免，但是是一个很好的办法。
int GetMid(int a[], int left, int right){
	int mid = (left + right)>>1;
    //六种情况 讨论一波 
	if(a[left]<=a[mid] && a[mid]<=a[right]){
		return mid;
	}
	else if(a[right]<=a[mid] && a[mid]<=a[left]){
		return mid;
	}
	else if(a[mid]<=a[right] && a[right]<=a[left]){
		return right;
	}
	else if(a[left]<=a[right] && a[right]<=a[mid]){
		return right;
	}
	else 
		return left;
}


// 左右指针法 三数取中优化
int Partition_Better(vector<int>& a, int left, int right){
	
    int pos = GetMid(a, left, right);
    swap(a[pos], a[left]); // //将取得的基准值和第一个位置交换 

	int i = left;
	int j = right;
	int key = a[left];
	
	while(!=j){
		while(i<j && a[j]>=key){
			j--;
		} 
		while(i<j && a[i]<=key){
			i++;
		}
		swap(a[i],a[j]);

	}
	swap(a[i], a[left]);
	return i;

}


void Quick_Sort(vector<int> &a, int left, int right){
	if(left >= right){
		return;
	}
	// find a partition point（找到一个划分点）
	int  i = Partition_here(a, left,right);
	Quick_Sort(a,left, i-1);
	Quick_Sort(a, i+1, right);
}


void show(vector<int>& v){
	for(const int & x:v){
		cout<<x<<" ";
	}
	cout<<endl;
}


int main(){
    vector<int> v;
    srand((int)time(0));
    int n = 50;
    while(n--)
	v.push_back(rand() % 100 + 1);
    
    show(v);

    Quick_Sort(v, 0, v.size() - 1);

    cout<<endl<<endl;
    show(v);

    return 0;
}