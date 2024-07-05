#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x):val(x),left(nullptr),right(nullptr){};
	TreeNode(int x, TreeNode *left, TreeNode *right):val(x),left(left),right(right){};
}

// 先序遍历（非递归）
vector<int> preOrderTraversal(TreeNode * root){
	vector<int> res;
	if(root==nullptr) return {};
	stack<TreeNode*>  st;
	st.push(root);
	while(!st.empty()){
		TreeNode * node =  st.top();
		st.pop();
		res.push_back(node->val);
		if(node->right!=nullptr) st.push(node->right);
		if(node->left!=nullptr) st.push(node->left);
	}
	return res;
}

// 中序遍历（非递归）
vector<int> inorderTraversal(TreeNode * root){
	vector<int> res;
	stack<TreeNode*> st;
	TreeNode * node = root;
	while(!st.empty()){
		while(node!=nullptr){
			st.push(node);
			node = node->left;
		}
		node = st.top();
		st.pop();
		res.push_back(node->val);
		node = node->right;
	}
	return res;
}


// 后序遍历（非递归）
vector<int> postorderTraversal(TreeNode * root){
	vector<int> res;
	if(root==nullptr) return {};
	stack<TreeNode*> s1;
	stack<TreeNode*> s2;
	s1.push(root);
	while(!s1.empty){
		TreeNode *node = s1.top();
		s1.pop();
		s2.push(root);
		if(node->left!=nullptr) s1.push(node->left);
		if(node->right!=nullptr) s2.push(node->right);
	}
	while(!s2.empty()){
		TreeNode *node = s2.top();
		s2.pop();
		res.push_back(node->val);
	}
	return res;
}

vector<int>  levelTraversal(TreeNode* root){
	if(root == nullptr)  return;
	queue<TreeNode *> q;
    vector<int> res;
	q.push(root);
	// 从上倒下遍历二叉树的每一层
	while(!q.empty()){
		int sz= q.size();
		for(int i=0; i<sz; i++){
			TreeNode *cur = q.front();
			q.pop();
			res.push_back(cur->val);
			if(cur->left!=nullptr){q.push(cur->left);}
			if(cur->right!=nullptr){q.push(cur->right);}

		}
	}
	return res;
}



int main(){

	return 0;
}




