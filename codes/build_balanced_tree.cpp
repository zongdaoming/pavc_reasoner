#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 直观地看，我们可以选择中间数字作为二叉搜索树的根节点，
// 这样分给左右子树的数字个数相同或只相差 1，可以使得树保持平衡。
// 如果数组长度是奇数，则根节点的选择是唯一的，如果数组长度是偶数，
// 则可以选择中间位置左边的数字作为根节点或者选择中间位置右边的数字作为根节点，
// 选择不同的数字作为根节点则创建的平衡二叉搜索树也是不同的


// nums = [-10,-3,0,5,9]

// 输出：[0,-3,9,-10,null,5]
// 解释：[0,-10,5,null,-3,null,9] 也将被视为正确答案

// 方法一：中序遍历，总是选择中间位置左边的数字作为根节点
// 选择中间位置左边的数字作为根节点，则根节点的下标为 mid=(left+right)/2，此处的除法为整数除法。


class Solution {
public:
    TreeNode* buildBalancedBST(vector<int>& nums, int left, int right){
        // 递归终止的条件
        if(left>right){
            return nullptr;
        }
        // 单层递归的过层
        int mid = (right+left)/2; //每次都选择中左的样本点作为根节点
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = buildBalancedBST(nums, left, mid-1);
        root->right = buildBalancedBST(nums,mid+1, right);
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {

        int n =  nums.size()-1;
        TreeNode* root =  buildBalancedBST(nums,0,n);
        return root;
    }
};

// 方法二：中序遍历，总是选择中间位置右边的数字作为根节点
// 选择中间位置右边的数字作为根节点，则根节点的下标为 mid=(left+right+1)/2，此处的除法为整数除法。
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0, nums.size() - 1);
    }

    TreeNode* helper(vector<int>& nums, int left, int right) {
        if (left > right) {
            return nullptr;
        }

        // 总是选择中间位置右边的数字作为根节点
        int mid = (left + right + 1) / 2;

        TreeNode* root = new TreeNode(nums[mid]);
        root->left = helper(nums, left, mid - 1);
        root->right = helper(nums, mid + 1, right);
        return root;
    }
};


// 方法三：中序遍历，选择任意一个中间位置数字作为根节点
// 选择任意一个中间位置数字作为根节点，则根节点的下标为 mid=(left+right)/2 和 mid=(left+right+1)/2 两者中随机选择一个，此处的除法为整数除法。
// rand()%2 

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0, nums.size() - 1);
    }

    TreeNode* helper(vector<int>& nums, int left, int right) {
        if (left > right) {
            return nullptr;
        }

        // 选择任意一个中间位置数字作为根节点
        int mid = (left + right + rand() % 2) / 2;

        TreeNode* root = new TreeNode(nums[mid]);
        root->left = helper(nums, left, mid - 1);
        root->right = helper(nums, mid + 1, right);
        return root;
    }
};


