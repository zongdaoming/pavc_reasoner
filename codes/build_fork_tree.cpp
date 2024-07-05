// 1、是否可以通过遍历一遍二叉树得到答案？如果可以，用一个 traverse 函数配合外部变量来实现，这叫「遍历」的思维模式。

// 2、是否可以定义一个递归函数，通过子问题（子树）的答案推导出原问题的答案？如果可以，写出这个递归函数的定义，并充分利用这个函数的返回值，这叫「分解问题」的思维模式。



// 构建最大二叉树
// 主函数

struct TreeNode{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    return build(nums, 0, nums.size() - 1);
}


// 1.确定递归函数的参数和返回值
TreeNode* build(vector<int>& nums, int left, int right){
	// 2.确定终止条件
	if(left>right){
		return nullptr;
	}
    // 3.确定单层遍历的逻辑
	// 找到数组中最大值和对应的索引
	int index = -1, maxVal = INT_MIN;
	for(int i=left, i<right; i++){
		if(maxVal<nums[i]){
			index = i;
			maxVal=nums[i];
		}
	}
	// 先构造出来根节点
	TreeNode* root =new TreeNode(maxVal);
	// 排除中间的最大值
	root->left = build(nums, left, index-1);
	root->right = build(nums, index+1, right);
	return root
}




unordered_map<int,int> valToIndex;

// 前中 ，后中都能确定唯一的一颗二叉树，而前后无法确定一颗唯一的二叉树
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder){
	// 存储inorder中值到索引的映射
	for(int i=0; i<inorder.size();i++){
		valToIndex[inorder[i]]=i;
	}

	return build(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
}

/* 
    build 函数的定义：
    若前序遍历数组为 preorder[preStart..preEnd]，
    中序遍历数组为 inorder[inStart..inEnd]，
    构造二叉树，返回该二叉树的根节点 
*/

TreeNode *build(vector<int>& preorder, int preStart, int preEnd, vector<int>& inorder, int inStart, int inEnd){
	// root 节点对应的值就是前序遍历数组的第一个元素
	int rootVal = preorder[preStart];
	// rootVal 在中序遍历数组中的索引
	int index = valToIndex(rootVal);
	int leftSize =  index-inStart;

    // 构造出当前根节点
	TreeNode*  root = new TreeNode(rootVal);
    //递归构造左右子树  
   //剔除根节点+断裂左子树数组和断裂右子树数组
    root->left = build(preorder, preStart+1, preStart+leftSize, inorder, inStart, index-1);
    root->right = build(preorder,preStart+leftSize+1, preEnd, inorder, index+1, inEnd);

	return root;

}




