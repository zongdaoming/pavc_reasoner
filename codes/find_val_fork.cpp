#include <iostream>
#include <vector>
using namespace std;

// 定义：在以 root 为根的二叉树中寻找值为 val 的节点
// LCA解题模版
// LCA（Lowest Common Ancestor）作为最近公共祖先节点的缩写


 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 // 递归函数的参数及其返回值
TreeNode* find(TreeNode* root, int val){
	// 确定递归终止的条件
	if(root==nullptr){
		return nullptr;
	}

	// 确定单层递归的逻辑
	// 看看 root->val 是不是要找的
	if(root->val == val){
		return root;
	}

	// root不是目标节点，那就去左子树找
	TreeNode* left = find(root->left, val);
	if(left != nullptr){
		return left;
	}
// 左子树找不着，那就去右子树找
	TreeNode* right =find(root->right, val);
	if(righ!=nullptr){
		return right;
	}

    // 实在找不到了
    return nullptr;

}

TreeNode* find2(TreeNode* root, int val) {
    if (root == nullptr) {
        return nullptr;
    }
    // 前序位置
    if (root->val == val) {
        return root;
    }
    // root 不是目标节点，去左右子树寻找
    TreeNode* left = find(root->left, val);
    TreeNode* right = find(root->right, val);
    // 看看哪边找到了
    return left != nullptr ? left : right;
}


TreeNode* find3(TreeNode* root, int val) {
    if (root == nullptr) {
        return nullptr;
    }
    // 先去左右子树寻找
    TreeNode* left = find(root->left, val);
    TreeNode* right = find(root->right, val);
    // 后序位置，看看 root 是不是目标节点
    if (root->val == val) {
        return root;
    }
    // root 不是目标节点，再去看看哪边的子树找到了
    return left != nullptr ? left : right;
}


// 最后，我再改一下题目，现在不让你找值为 val 的节点，而是寻找值为 val1 或 val2 的节点，函数签名如下：
// 1.确定递归函数的参数和返回值
TreeNode* find(TreeNode* root, int val1, int val2){
	// 终止条件
	if(root==nullptr){
		return nullptr;
	}
	// 前序位置,看看root是不是目标值
	if(root->val == val || root->val == val2){
		return root;
	}
	// 去左右子树寻找
	TreeNode* left = find(root->left, val1, val2);
	TreeNode* right = find(root->right, val1, val2);
	// 后序位置
	return left!=nullptr?left:right; 
}



TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q){
	return find(root, p->val, q->val);

}


TreeNode* find(TreeNode* root, int val1, int val2){
	if(root==nullptr){
		return nullptr;
	}
	// 前序位置
	if(root->val==val1 || root->val == val2){
		 // 如果遇到目标值，直接返回
		return root;
	}
	TreeNode* left = find(root->left, val1, val2);
	// if(left!=nullptr){
	// 	return left;
	// }
	TreeNode* right = find(root->right, val1, val2);
	// if(right!=nullptr){
	// 	return right;
	// }

	// 后序位置，已经知道左右子树是否存在目标值
	
	if(left!=nullptr && right!=nullptr){
		// 左右子树都不为空，那么这个根节点就是最近公共祖先节点
		// 当前节点是LCA节点
		return root;
	}
	return left!=nullptr?left :right;
}





























