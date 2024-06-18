#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;
//Definition for a binary tree node.
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
    TreeNode(int x, TreeNode *left, TreeNode *right):val(x),left(left),right(right){}
};

// 递归函数, 先序遍历
void f(TreeNode *head, vector<int>& ans){
    if(head==NULL){return;}
    ans.push_back(head->val);
    f(head->left,ans);
    f(head->right,ans);
}

// 中序遍历
void f2(TreeNode* head, vector<int> & ans){
    if(head==NULL)return;
    f2(head->left, ans);
    ans.push_back(head->val);
    f2(head->right, ans);
}

// 后序遍历
void f3(TreeNode* head, vector<int> & ans){
    if(head==NULL)return;
    f3(head->left, ans);
    f3(head->right, ans);
    ans.push_back(head->val);
}

// 调用递归，返回前序遍历顺序
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans;
    f(root,ans);
    return ans;
}

// 非递归的方式进行先序遍历（利用栈）
vector<int> preorderTraversal(TreeNode* root){
    vector<int> ans;
    stack<TreeNode*> s;
    if(root!=NULL)return {};
    s.push(root);
    while(!s.empty()){
        TreeNode *node=s.top();
        s.pop();
        ans.push_back(node->val);
        if(node->right!=NULL)s.push(node->right);
        if(node->left!=NULL)s.push(node->left);
    }
    return ans;
}

// 非递归的方式进行中序遍历（利用栈）
vector<int> inorderTraversal(TreeNode* root){
    vector<int> ans;
    stack<TreeNode*> s;
    if(root!=NULL)return {};
    TreeNode *p=root;
    while(p!=NULL||!s.empty()){
        while(p!=NULL){
            s.push(p);
            p=p->left;
        }
        p=s.top();
        s.pop();
        ans.push_back(p->val);
        p=p->right;
    }
    return ans;
}

// 非递归的方式进行后序遍历（利用栈）
vector<int> postorderTraversal(TreeNode* root){
    vector<int> ans;
    stack<TreeNode*> s1;
    stack<TreeNode*> s2;
    if(root!=NULL)return {};
    s1.push(root);
    while(!s1.empty()){
        TreeNode *node=s1.top();
        s1.pop();
        s2.push(node);
        if(node->left!=NULL)s1.push(node->left);
        if(node->right!=NULL)s1.push(node->right);
    }
    while(!s2.empty()){
        TreeNode *node=s2.top();
        s2.pop();
        ans.push_back(node->val);
    }
    return ans;   
}

// 层次遍历
vector<vector<int>> levelOrder(TreeNode* root){
    vector<vector<int>> ans;
    if(root==NULL)return ans;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int size=q.size();
        vector<int> temp;
        for(int i=0;i<size;i++){
            TreeNode *node=q.front();
            q.pop();
            temp.push_back(node->val);
            if(node->left!=NULL)q.push(node->left);
            if(node->right!=NULL)q.push(node->right);
        }
        ans.push_back(temp);
    }
    return ans;
}

int main(){
    cout<<"Test "<<endl;
    return 0;
}

