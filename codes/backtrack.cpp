#include<iosteam>
#include<string>
#include<vector>
#include<stack>
using namespace std;

class Solution{
private:
	vector<vector<int>> result; //// 存放符合条件结果的集合

	vector<int> path; //用来存放条件结果

	void backtracking(int n, int k, int startIndex){
		if(path.size()==k){
			result.push(path);
			return;
		}
		for(int i = startIndex; i<=n; i++){
			path.push_back(i); // 处理节点
			backtracking(n, k, i+1); // 递归：控制树的纵向遍历，注意下一层搜索要从i+1开始
			path.pop_back();  // 回溯，撤销处理的节点, 回溯，撤销处理的结果
		}
	}

public:
	vector<vector<int>> combine(int n, int k){
		result.clear();
		path.clear();
		backtracking(n,k,1);
		return result;
	}
}









int main(){


	return 0;
}