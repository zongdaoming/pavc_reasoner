#include <iostream>
#include <string>
#include <vector>
using namespace std;
// 快排
class Solution {
public:
    void quickSort(vector<int>& nums, int lo, int hi){
        // 选取最左边的为基数
        // 递归终止的条件
        if(lo>hi){
        	return;
        }
        int key = nums[lo];
        int left = lo;
        int right = hi;
        while(left!=right){
            while(left<right && nums[right]>=key){
                right--;
            }
            while(left<right && nums[left]<=key){
                left++;
            }
            swap(nums[left], nums[right]);
        }
        swap(nums[lo],nums[left]);
        // quick sort 确定 partition 的位置
        // 排除key这个点
        quickSort(nums, lo, left-1);
        quickSort(nums, left+1, hi);
    }

    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, nums.size()-1);
        return nums;
    }
};


// 三路快排
class Solution {
public:
    void quickSort3ways(vector<int>& nums, int left, int right) {
        if(left>right){
            return;
        }
        // 确定基值
        int key = nums[left];
        int lt = left;
        int gt = right + 1;
        int i = left + 1;
        while (i < gt) { // 循环继续的条件
            if (nums[i] < key) {
                swap(nums[i], nums[lt+1]);
                i++;
                lt++;
            } else if (nums[i] > key) {
                swap(nums[i], nums[gt - 1]);
                gt--;
            } else {
                i++;
            }
        }
        swap(nums[left], nums[lt]);
        quickSort3ways(nums, left, lt - 1);
        quickSort3ways(nums, gt, right);
    }

    vector<int> sortArray(vector<int>& nums) {
        quickSort3ways(nums, 0, nums.size() - 1);
        return nums;
    }
};



int main(){

}
