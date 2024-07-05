#include <iostream>
#include <vector>
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