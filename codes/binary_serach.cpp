#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <stack>
#include <priority_queue>
using namespace std;

// binary search template
int bianrySearch(vector<int>& nums, int target){
	int left = 0 , right = nums.size()-1;
	while(left<right){
		int mid = left + (right-left)/2;
		if(nums[mid]==target){};
		else if(nums[mid]<target){left = mid + 1};
		else if(nums[mid]>target){right = mid -1};
	}
	return left;
}

// levelOrderTraversal
vector<int> levelOrderTraversal(TreeNode *root){
	if(root == nullptr) return;
	queue<TreeNode*> q;
	vector<int> res
	q.push(root);
	while(!q.empty()){
		int sz=q.size();
		for(int i=0; i<sz; i++){
			TreeNode* cur = q.front();
			q.pop();
			res.push_back(cur->val);
			if(cur->left!=nullptr) { q.push(cur->left) };
			if(cur->right!=nullptr){ q.push(cur->right) };
		}
	}
	return res;
}




class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = left_bound(nums, target);
        int right = right_bound(nums, target);
        return {left, right};
    }

    int left_bound(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        // 搜索区间为 [left, right]
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                // 搜索区间变为 [mid+1, right]
                left = mid + 1;
            } else if (nums[mid] > target) {
                // 搜索区间变为 [left, mid-1]
                right = mid - 1;
            } else if (nums[mid] == target) {
                // 收缩右侧边界
                right = mid - 1;
            }
        }
        // 检查出界情况
        if (left >= nums.size() || nums[left] != target) {
            return -1;
        }
        return left;
    }

    int right_bound(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else if (nums[mid] == target) {
                // 这里改成收缩左侧边界即可
                left = mid + 1;
            }
        }
        // 这里改为检查 right 越界的情况，见下图
        if (right < 0 || nums[right] != target) {
            return -1;
        }
        // return right;
        return right;

    }
};









int main(){
	return 0;
}