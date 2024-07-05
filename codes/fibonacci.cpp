#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

//o(2^N)的 时间复杂度
int fib(int N){
	if(N==1|| N==2) return 1;
	return fib(N-1) + fib(N-2);
}

// 
int fib2(int N){
    // 备忘录全初始化为 0
	int memo[ N + 1];
	memset(memo, 0, sizeof(memo));
	// 进行带备忘录的递归
	return dp(memo, N);
}

// 带着备忘录进行递归
int dp(int memo[], int n){
	// base case
	if(n == 0 || n == 1) return n;
	// 已经计算过了,不用再计算了
	if(memo[n] !=  0) return memo[n];
	memo[n] = dp(memo, n - 1) + dp(memo, n-2);
	return memo[n];
}

int fib(int N){
	if(N == 0) return 0;
	int* dp = new int[N+1];
	// base case
	dp[0] = 0;
	dp[1] = 1;
	// 状态转移
	for(int i =2; i<=N; i++){
		dp[i] = dp[i-1] + dp[i-2];
	}
	return dp[N];
}

// 指明大小并且（初始值相同）的向量
// vector<int> a(10, 1)
// 声明一个初始大小为10且初始值都为1的向量
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);
    // 数组大小为 amount + 1，初始值也为 amount + 1
    dp[0] = 0;
    // 外层 for 循环在遍历所有状态的所有取值
    for (int i = 0; i < dp.size(); i++) {
        // 内层 for 循环在求所有选择的最小值
        for (int coin : coins) {
            // 子问题无解，跳过
            if (i - coin < 0) {
                continue;
            }
            dp[i] = min(dp[i], 1 + dp[i - coin]);
        }
    }
    return (dp[amount] == amount + 1) ? -1 : dp[amount];
}

int main(){
	return 0;
}