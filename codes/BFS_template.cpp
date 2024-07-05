#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<unorderd_set>
#include<set>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

struct TreeNode{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(): val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode* right): val(x), left(nullptr), right(nullptr) {}
}

int BFS(Node start, Node target) {
    queue<Node> q; 
    set<Node> visited;
    
    q.push(start); 
    visited.insert(start);

    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            Node cur = q.front();
            q.pop();
            if (cur == target)
                return step;
            for (Node x : cur.adj()) {
                if (visited.count(x) == 0) {
                    q.push(x);
                    visited.insert(x);
                }
            }
        }
    }
    // 如果走到这里，说明在图中没有找到目标节点
}

int minDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    queue<TreeNode*> q;
    q.push(root);
    // root itself is the first level, so depth initialize as 1
    int depth = 1;
    
    while (!q.empty()) {
        /**<向下扩展-200>
        <div class="img-content"><img src="/images/dijkstra/1.jpeg" class="myimage"/></div>
        */
        int sz = q.size();
        /*将当前队列中的所有节点向四周扩散*/
        for (int i = 0; i < sz; i++) {
            TreeNode* cur = q.front();
            q.pop();
            /*判断是否到达终点*/
            if (cur->left == nullptr && cur->right == nullptr) 
                return depth;
            /*将 cur 的相邻节点加入队列*/
            if (cur->left != nullptr)
                q.push(cur->left);
            if (cur->right != nullptr) 
                q.push(cur->right);
        }
        /* 这里增加步数 */
        depth++;
    }
    return depth;
}