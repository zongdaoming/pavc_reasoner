#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
using namespace std;
// *
// * Definition for singly-linked list.
 struct ListNode {
       int val;
       ListNode *next;
       ListNode() : val(0), next(nullptr) {}
       ListNode(int x) : val(x), next(nullptr) {}
       ListNode(int x, ListNode *next) : val(x), next(next) {}
};


void _MergeSort(int* arr, int begin, int end, int* tmp)
{
	if (begin >= end)
	{
		// 递归终止条件
		return;
	}
	//分治递归，让子区间先有序
	// int mid = (begin + end) / 2;
	int mid = begin + (end-begin)>>1;
	_MergeSort(arr, begin, mid, tmp);
	_MergeSort(arr, mid + 1, end, tmp);
	
	int begin1 = begin;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = end;

	int i = begin1; //注意这里的i是tmp数组的下标

	//在arr[begin1,end1]和arr[begin2,end2]两个区间中开始归并
	while ((begin1 <= end1) && (begin2 <= end2))
	{
		//如果arr[begin1]的值小，就让arr[begin1]的值先进入tmp数组
		if (arr[begin1] < arr[begin2])
		{
			tmp[i++] = arr[begin1++];
		}
		//如果arr[begin2]的值小于等于arr[begin1]，就让arr[begin2]的值进入tmp数组
		else
		{
			tmp[i++] = arr[begin2++];
		}
	}
	//如果数组1中的数据还没有归并到tmp中完，就直接将剩下的都放到tmp中
	while (begin1 <= end1)
	{
		tmp[i++] = arr[begin1++];
	}
	//如果数组2中的数据还没有归并到tmp中完，就直接将剩下的都放到tmp中
	while (begin2 <= end2)
	{
		tmp[i++] = arr[begin2++];
	}
	//把归并数据拷贝到原数据
	// void * memcpy ( void * destination, const void * source, size_t num );
	memcpy(arr + begin, tmp + begin, sizeof(int) * (end - begin + 1));
}

void MergeSort(int* arr, int n)
{
    //归并排序需要先申请一个辅助数组
    int* tmp = (int*)malloc(sizeof(int) * n);
    if (tmp == NULL)
    {
        perror("MergeSort malloc fail");
        exit(-1);
    }
    _MergeSort(arr, 0, n - 1, tmp);
}


void sort(int[] nums, int lo, int hi){
    if(lo==hi){
        return;
    }
    int mid = (lo+hi)/2;
    // 利用定义，排序 nums[llo,...,mid]
    sort(nums,lo, mid);
    // 利用定义，排序nums[mid+1,...,hi]
    sort(nums,mid+1,hi);

    // ****************后序位置***********************//
    // 此时两部分子数组已经被排好序
    // 合并两个有序数组，使 nums[lo..hi] 有序    
    merge(nums,lo,mid,hi);
    /*********************/
}

// 将有序数组 nums[lo..mid] 和有序数组 nums[mid+1..hi]
// 合并为有序数组 nums[lo..hi]

void merge(int[] nums, int lo, int mid, int hi){}



class Merge{
    private: vector<int> temp;
    public: 
    void sort(int nums[]){
            // 先给辅助数组开辟内存空间
            int* tmp  = new int[nums.size];
            // int * tmp  = (int*)malloc(sizeof(int)*nums.size());
            // 排序整个数组，[原地修改)
            sort(nums, 0, nums.size()-1); 
        }

    // 定义：将子数组 nums[lo...hi] 进行排序
    void sort(int nums[], int lo, int hi){
        if(lo == hi){
            // 单个元素不用排序
            return;
        }
        // 这样写是为了防止溢出，效果等同于 (hi + lo) / 2
        int mid = lo + (hi - lo) / 2;
        // 先对左半部分数组 nums[lo .. mid] 排序
        sort(nums, lo, mid);
        // 再对右半部分数组 nums[mid+1 .. hi] 排序
        sort(nums, mid+1, hi);
        // 将两部分有序数组合并成一个有序数组
        merge(nums, lo, mid, hi);
    }

    void merge(int nums[], int lo, int mid, int hi){
        // 先把 nums[lo..hi] 复制到辅助数组中
        // 以便合并后的结果能够直接存入 nums
        for(int i = lo; i <= hi; i++){
            temp[i] = nums[i];
        }
        // 数组双指针技巧，合并两个有序数组
        int i = lo, j = mid + 1;

        for(int p = lo; p <= hi; p++){
            if(i == mid + 1){
            // 左半边数组已全部被合并
                nums[p] == temp[j++];
            }
            else if (j == hi + 1){
            // 右半边数组已全部被合并
                nums[p] = temp[i++];
            }else if(temp[i]>temp[j]){
                nums[p] = nums[j++];

            }else if(temp[i]<temp[j]){
                nums[p] = temp[i++];
            }
        }
    }
}


class Solution {
public:
    vector<int> temp;
    void sort(vector<int>& nums, int lo, int hi){
        if(lo==hi) 
        {
            // 单个元素不用排序
            return;
        }
        int mid = lo + (hi-lo)/2;
        // 先对左半部分数组 nums[lo..mid] 排序
        sort(nums, lo, mid);
        // 再对右半部分数组 nums[mid+1..hi] 排序
        sort(nums, mid+1, hi);
        // 将两部分有序数组合并成一个有序数组
        merge(nums,lo, mid, hi);
    }

    void merge(vector<int>& nums, int lo, int mid, int hi){
        // 先把 nums[lo..hi] 复制到辅助数组中
        // 以便合并后的结果能够直接存入 nums        
        for(int i= lo; i <= hi; i++){
            temp[i] = nums[i];
        }
        // 数组双指针技巧，合并两个有序数组
        int i = lo, j = mid + 1;

        for(int p=lo; p<=hi; p++){
            if(i==(mid+1)){
                nums[p]=temp[j++];
            }
            else if(j==(hi+1)){
                nums[p]=temp[i++];
            }
            else if(temp[i]<temp[j]){
                nums[p]=temp[i++];
            }
            else{
                nums[p] = temp[j++];
            }
        }
    }
    vector<int> sortArray(vector<int>& nums) {
        temp.resize(nums.size(),0); //这一点很关键       
        sort(nums, 0, nums.size()-1);
        return nums;
    }
};



// 堆排序
class Solution {
public:
    void Down(vector<int>& nums, int i, int n){
        int parent = i;
        int child = 2*i + 1;
        // 循环迭代
        while(child<n){
            if(child +1 < n && nums[child]<nums[child+1]){
                child++;
            }
            if(nums[parent]<nums[child]){
                swap(nums[parent], nums[child]);
                parent = child;
            }
            child = 2*child + 1;
        }
    }
    void buildMaxHeap(vector<int>& nums){
        int n = nums.size();
        for(int i = (n-2)/2; i>=0; i--){
            Down(nums,i, n);
        }
    }
    void headSort(vector<int>& nums){
        int n = nums.size();
        buildMaxHeap(nums); //先建立最大堆
        // 然后调整
        for(int i = n-1; i>=0 ;i--){
         swap(nums[0], nums[i]);
         Down(nums, 0, i);
        }
    }
    vector<int> sortArray(vector<int>& nums) {
        headSort(nums);
        return nums;
    }
};




// 函数递归调用的入口为 mergeSort(nums, 0, nums.length - 1)，递归结束当且仅当 while(child<len) 叶子节点小于整个数组的长度Len
class Solution {
    void maxHeapify(vector<int>& nums, int i, int n) {
        int parent = i;     // 父节点下标
        int child = 2*i+1;  // 子节点下标
        while(child<n){
            if(child+1 <n && nums[child]<nums[child+1]){
                child++;
            }
            if(nums[parent]<nums[child]){ //判断父节点是否小于子节点
                swap(nums[parent], nums[child]); //交换父节点和子节点
                parent = child; //子节点下标赋给父节点下标
            }
            child = 2*child + 1; //换行，比较下面的父节点和子节点
        }
    }
    void buildMaxHeap(vector<int>& nums, int len) {
        for (int i = (n-2)/2; i >= 0; --i) {
            maxHeapify(nums, i, len);
        }
    }

    void heapSort(vector<int>& nums) {
        int len = nums.size();
        buildMaxHeap(nums, len);
        for (int i = len-1; i >= 0; --i) {
            swap(nums[0], nums[i]);
            maxHeapify(nums, 0, i);
        }
    }

public:
    vector<int> sortArray(vector<int>& nums) {
        heapSort(nums);
        return nums;
    }
};



// 函数递归调用的入口为 mergeSort(nums, 0, nums.length - 1)，递归结束当且仅当 l >= r。MergeSort 二叉树的递归
class Solution {
    vector<int> tmp;
    void mergeSort(vector<int>& nums, int l, int r) {
        if (l >= r) return;
        int mid = (l + r) >> 1;
        mergeSort(nums, l, mid);
        mergeSort(nums, mid + 1, r);
        int i = l, j = mid + 1;
        int cnt = 0;
        while (i <= mid && j <= r) {
            if (nums[i] <= nums[j]) {
                tmp[cnt++] = nums[i++];
            }
            else {
                tmp[cnt++] = nums[j++];
            }
        }
        while (i <= mid) {
            tmp[cnt++] = nums[i++];
        }
        while (j <= r) {
            tmp[cnt++] = nums[j++];
        }
        for (int i = 0; i < r - l + 1; ++i) {
            nums[i + l] = tmp[i];
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        tmp.resize((int)nums.size(), 0);
        mergeSort(nums, 0, (int)nums.size() - 1);
        return nums;
    }
};










class Solution {
public:
    ListNode* sortList(ListNode* head) { 
        return mergeSort(head);
    }

    /**
     * 对给定的链表进行归并排序
    */
    ListNode* mergeSort(ListNode* head){
        // 如果链表为空或只有一个节点，无需排序直接返回
        // 递归终止条件
        if(!head || !head->next){
            return head;    
        }
        // 获取链表的中间节点，分别对左右子链表进行排序
        ListNode* mid = getMid(head);
        ListNode* rightSorted = mergeSort(mid->next);   // 排序右子链表
        if(mid)mid->next = nullptr;                     // 断开两段子链表
        ListNode* leftSorted = mergeSort(head);         // 排序左子链表
        return mergeTwoLists(leftSorted, rightSorted);  // 两个子链表必然有序，合并两个有序的链表
    }

    /**
     * 获取以head为头节点的链表中间节点
     * 如果链表长度为奇数，返回最中间的那个节点
     * 如果链表长度为偶数，返回中间靠左的那个节点
    */
    ListNode* getMid(ListNode* head){
        if(!head)return head;   
        ListNode* slow = head, *fast = head->next;          // 快慢指针，慢指针初始为
        while(fast != nullptr && fast->next != nullptr)     
        {
            fast = fast->next->next;    // 快指针每次移动两个节点
            slow = slow->next;          // 慢指针每次移动一个节点
        }
        return slow;    // 快指针到达链表尾部时，慢指针即指向中间节点
    }

    /**
     * 合并两个有序链表list1和list2
    */
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode();   // 伪头节点，用于定位合并链表的头节点
        ListNode* node = dummy;             // 新链表当前的最后一个节点，初始为伪头节点
        // 直到两个链表都遍历完了，合并结束
        while(list1 != nullptr || list2 != nullptr){
            int val1 = list1 == nullptr ? 50001 : list1 -> val;   // 如果链表1已经遍历完，val1取最大值，保证链表2的节点被选择到       
            int val2 = list2 == nullptr ? 50001 : list2 -> val;   // 如果链表2已经遍历完，val2取最大值，保证链表1的节点被选择到 
            if(val1 < val2){
                // 链表1的节点值更小，加入到合并链表，并更新链表1指向的节点
                node -> next = list1;
                list1 = list1 -> next;
            }else{
                // 链表2的节点值更小，加入到合并链表，并更新链表2指向的节点
                node -> next = list2;
                list2 = list2 -> next;
            }
            node = node -> next;    // 更新合并链表当前的最后一个节点指向
        }
        return dummy -> next;       // 伪头节点的下一个节点即为合并链表的头节点
    }
};



// 快慢指针 —— 链表中点
// 使用 快慢双指针，快指针一次走两步，慢指针一次走一步，十分 tricky；
LinkNode* FindMid(LinkNode *p){
    if (!p) return NULL;
    LinkNode* slow = p, *fast = p;
    while (fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}


int main(){
	return 0;
}