#include<iostream>
#include<vector>
using namespace std;


struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 在一棵普通的二叉树中寻找，可以这样写代码
TreeNode* searchBST(TreeNode*root, int target){
    if(root == nullptr) return nullptr;
    if(root->val == target) return root;
    // 当前节点没找到就递归地去左右子树寻找
    TreeNode* left = searchBST(root->left, target);
    TreeNode* right = searchBST(root->right, target);
    return left!=nullptr?left:right;
}


TreeNode* searchBST(TreeNode* root, int val){
    // 递归终止条件
    if(root == nullptr){
        return nullptr;
    }
    // 去左子树搜索
    if(root->val > target){
        return searchBST(root->left, target);
    }
    // 去右子树搜索
    if(root->val < target){
        return searchBST(root->right, target)
    }
    return root;
}
 

// 在 BST 中插入一个数
// 对数据结构的操作无非遍历 + 访问，遍历就是「找」，访问就是「改」。具体到这个问题，插入一个数，就是先找到插入位置，然后进行插入操作。
// 上一个问题，我们总结了 BST 中的遍历框架，就是「找」的问题。直接套框架，加上「改」的操作即可。一旦涉及「改」，
// 就类似二叉树的构造问题，函数要返回 TreeNode 类型，并且要对递归调用的返回值进行接收。
TreeNode * insertIntoBST(TreeNode* root, int val){
    // 函数递归终止的条件
    // 找到空位置插入新节点
    if(root == nullptr) return new TreeNode(val);
    if(root->val < val){
        root->right = insertIntoBST(root->right, val);
    }
    if(root->val > val){
        root->left = insertIntoBST(root->left, val);
    }
    return root;
}




TreeNode* deleteNode(TreeNode* root, int key) {
    if (root->val == key) {
        // 找到啦，进行删除
    } else if (root->val > key) {
        // 去左子树找
        root->left = deleteNode(root->left, key);
    } else if (root->val < key) {
        // 去右子树找
        root->right = deleteNode(root->right, key);
    }
    return root;
}


// 找到目标节点了，比方说是节点 A，如何删除这个节点，这是难点。
// 因为删除节点的同时不能破坏 BST 的性质。有三种情况，用图片来说明。
// 在BST中删除一个数
TreeNode* deleteNode(TreeNode* root, int key){
    
    if(root->left==nullptr && root->right==nullptr){return nullptr;}
    // 当根节点为空，则直接返回null
    if(root==nullptr) return nullptr;

    if(root->val == key){
        // 当节点为叶子节点或者只有一个子节点时，直接返回该子节点
        // A 只有一个非空子节点，那么它要让这个孩子接替自己的位置

        if(root->left==nullptr) return root->right;
        if(root->right==nullptr) return root->left;
        
        // 当节点有两个子节点时，用其右子树最小的节点(左子树中的最大节点)代替该节点
        //  获得右子树最小的节点
        TreeNode* minNode = getMin(root->right);
        
        // 删除右子树最小的节点
        root->right = deleteNode(root->right, minNode->val);
        
        // 完成swap的过程

        // 用右子树最小的节点替换 root 节点
        
        // 先处理后继节点
        minNode->left = root->left;
        minNode->right = root->right;
        // 再处理前驱节点
        root = minNode;

    }else if(root->val > key){
        // 删除节点在左子树中
        root->left = deleteNode(root->left, key);
    }else if(root->val < key){
        // 删除节点在右子树中
        root->right = deleteNode(root->right, key);
    }
    return root;
}


TreeNode* getMin(TreeNode* node){
    while(node->left!=nullptr){
        node = node->left;
    }
    return node;
}


// 在二叉树递归的框架的基础上，扩展出一套BST代码框架
void BST(TreeNode root, int target) {
    if (root.val == target)
        // 找到目标，做点什么
    if (root.val < target) 
        BST(root.right, target);
    if (root.val > target)
        BST(root.left, target);
}













