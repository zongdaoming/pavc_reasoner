#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x),left(NULL),right(NULL){};
    TreeNode(int x,TreeNode *left,TreeNode *right):val(x),left(left),right(right){};
};


// 先序遍历（非递归）
vector<int> preorderTraversal(TreeNode * root){
    vector<int> res;
    if(root==NULL) return res;
    stack<TreeNode *> st;
    st.push(root);
    while(!st.empty()){
        TreeNode * node = st.top();
        st.pop();
        res.push_back(node->val);
        if(node->right!=NULL) st.push(node->right);
        if(node->left!=NULL) st.push(node->left);
    }
    return res;
}

// 中序遍历（非递归）
vector<int> inorderTraversal(TreeNode * root,vector<int> &res){
    if(root == NULL) return;
    stack<TreeNode *> st;
    TreeNode* node = root;
    while(node!=NULL || !st.empty()){
        while(node!=NULL){
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
vector<int> postorderTraversal(TreeNode* root){
    vector<int> res;
    if(root==NULL) return res;
    stack<TreeNode*> s1;
    stack<TreeNode*> s2;
    s1.push(root);
    while(!s1.empty()){
        TreeNode * node = s1.top();
        s1.pop();
        s2.push(node);
        if(node->left!=NULL) s1.push(node->left);
        if(node->right!=NULL) s1.push(node->right);
    }
    while(!s2.empty()){
        // TreeNode *node=s2.top();
        // s2.pop();
        // res.push_back(node->val);
        res.push_back(s2.top()->val);
        s2.pop();
    }
}

// 层次遍历（非递归）
vector<vector<int>> levelOrder(TreeNode* root){
    vector<vector<int>> res;
    if(root==NULL) return res;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int size = q.size();
        vector<int> tmp;
        for(int i=0;i<size;i++){
            TreeNode * node = q.front();
            q.pop();
            tmp.push_back(node->val);   
            if(node->left!=NULL) q.push(node->left);
            if(node->right!=NULL) q.push(node->right);
        }
        res.push_back(tmp);
    }
    return res;
}

// 求二叉树的最大深度
int maxDepth(TreeNode* root)
{
    if(root==NULL) return 0;
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);
    return left>right?left+1:right+1;
}

// 求二叉树的最小深度
int minDepth(TreeNode* root)
{
    if(root==NULL) return 0;
    if(root->left==NULL && root->right==NULL) return 1;
    int left = minDepth(root->left);
    int right = minDepth(root->right);
    if(root->left==NULL || root->right==NULL) return left>right?right+1:left+1;
    return left>right?right+1:left+1;
}

// 求二叉树的节点个数
int countNodes(TreeNode* root)
{
    if(root==NULL) return 0;
    return countNodes(root->left)+countNodes(root->right)+1;
}

int main(){
    cout<<"hello world"<<endl;
    return 0;
}
