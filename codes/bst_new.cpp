#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// 二叉树节点结构体
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 插入节点到二叉搜索树中
TreeNode* insertNode(TreeNode* root, int val) {
    if (!root) {
        return new TreeNode(val);
    }
    if (val < root->val) {
        root->left = insertNode(root->left, val);
    } else if (val > root->val) {
        root->right = insertNode(root->right, val);
    }
    return root;
}

// 构建二叉搜索树
TreeNode* buildBST(const std::vector<int>& nums) {
    TreeNode* root = NULL;
    for (const int& num : nums) {
        root = insertNode(root, num);
    }
    return root;
}
// 搜索二叉搜索树,判断val是否在二叉搜索树中
bool searchBST(TreeNode* root, int val) {
    if (!root) {
        return false;
    }
    if (root->val == val) {
        return true;
    } else if (val < root->val) {
        return searchBST(root->left, val);
    } else {
        return searchBST(root->right, val);
    }
}

// 中序遍历二叉搜索树
void inorderTraversal(TreeNode* root) {
    if (root) {
        inorderTraversal(root->left);
        std::cout << root->val << " ";
        inorderTraversal(root->right);
    }
}

// 中序遍历二叉搜索树
vector<int> inorderTraversal(TreeNode* root){
    vector<int> ans;
    stack<TreeNode*> st;
    if(!root) return {};
    TreeNode* cur = root;
    while(st.size() || cur!=NULL){
        if(cur!=NULL){
            st.push_back(cur);
            cur = cur->left;
        }
        else{
            cur = st.top();
            st.pop();
            ans.push_back(cur->val);
            cur = cur->right;
        }
    }
    return ans;
}

// 先序遍历
vector<int> preorderTraversal(TreeNode* root){
    vector<int> ans;
    stack<TreeNode*> st;
    if(root==NULL) return {};
    st.push(root);
    while(!st.empty()){
        TreeNode* cur = st.top();
        st.pop();
        if(cur->right!=NULL) st.push(cur->right);
        if(cur->left!=NULL) st.push(cur->left);
    }
    return ans;
}

// 后续遍历
vector<int> postorderTraversal(TreeNode* root){
    vector<int> ans;
    if(root==NULL) return{};
    stack<TreeNode*> s1;
    stack<TreeNode*> s2;
    s1.push(root);
    while(!st.empty()){
        TreeNode* cur = s1.top();
        s1.pop();
        s2.push(cur);
        if(cur->left!=NULL) s1.push(cur->left);
        if(cur->right!=NULL) s2.push(cur->right);
    }
    while(s2.size()){
        TreeNode* cur = s2.top();
        s2.pop();
        ans.push_back(cur->val);

    }
    return ans;
}


// 宽度优先遍历
void levelOrder(TreeNode* root){
    if(root==NULL) return;
    queue<TreeNode*> q;
    q.push(root);
    while(q.size()){
        TreeNode* cur = q.front();
        q.pop();
        if(cur->left!=NULL) q.push(cur->left);
        if(cur->right!=NULL) q.push(cur->right);
    }
    return;
}


int main() {
    // 输入数组，以空格分隔，回车结束
    vector<int> nums;
    int num;
    cout << "请输入数组: ";
    while (cin >> num) {
        // 以回车结束输入
        nums.push_back(num);
        if(cin.get() == '\n') {
            break;
        }
    }
    // 输入待搜索的数
    int target;
    cin >> target;

    // 构建二叉搜索树
    TreeNode* root = buildBST(nums);
    cout << "二叉搜索树中序遍历: ";
    inorderTraversal(root);
    cout << endl;

    // 判断target是否在二叉搜索树中
    if (searchBST(root, target)) {
        cout << "二叉搜索树中存在: " << target << endl;
    } else {
        cout << "二叉搜索树中不存在: " << target << endl;
    }

    return 0;
}