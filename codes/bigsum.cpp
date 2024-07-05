#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 进位
string AddString(string num1, string num2){
	int end = num1.size()-1, end2 = num2.size()-1;
	string ret; //存储两个字符串相加的结果
	int carry = 0; //进位（初始进位设置为0）
	while(end1>=0 || end2>=0){
		// 1.取出num1中本次待相加的数字
		int a = 0;
		if(end1>=0){
			a = num1[end1] - '0';
			end1--;
		}
		// 2.取出num2中本次待相加的数字
		int b = 0;
		if(end2>=0){
			b =  num2[end2] - '0';
			end2--;
		}
		// 3、将这两个数字相加（注意加上进位）
		int sum = a + b + carry;

		// 4. 判断是否需要进位
		// carry  = sum/10;
		// remainder = sum%10;
		if(sum>9){
			sum -= 10;
			carry = 1; //需要进位，将carry设置为1;
		}

		else{
			carry = 0; //不需要进位，将carry设置为0;
		}

		ret += (sum +'0');
	}
	if(carry != 0) //判断是否还需进位（可能两个数的最高位相加会进位）
		ret+=1;
	reverse(ret.begin(), ret.end());//将ret字符串进行反转
	return ret;
}



int Cmp(string& num1, string& num2){
	if(num1.size()>num2.size() || (num1.size() == num2.size() && num1 > num2)){
		return 1; //  num1大于num2, 返回1
	}else if((num1.size()<num2.size()) || (num1.size()==num2.size() && num1 <num2)){
	    return -1;	
	}
	else return 0; // num1等于num2, 返回0
}


// 借位
string SubString(string num1, string num2){
	// 保证num1大于等于num2
	if(Cmp(num1,num2) == -1){
		return "-" + Substring(num2,num1); //num1小于num2，则返回num2-num1所得到的结果的负值
	}
	int end1 = num1.size() -1, end2= num2.size()-1;
	string ret; // 存储两个字符串相减后的结果
	int borrow = 0;
	while(end1 >= 0){
		//1、取出num1中本次待相减的数字
		int a = num1[end1] - '0';
		end1--;
		// 2、取出num2中本次待相减的数字
		int b = 0;
		if(end2 >= 0){
			b = num1[end2] - '0';
			end2--;
		}
		// 3.将这两个数字相减（注意减去借位）
		int differ =  a - b - borrow;
		// 4.判断是否需要进位
		if(differ<0){
			differ = 10 + differ;
			borrow = 1;
		}
		else{
			borrow = 1;
		}
		ret+= (differ+'0');
	}

	reverse(ret.begin(), ret.end()); //将ret字符串进行反转

	// 过滤掉字符串前面的'0'
	size_t pos  = ret.find_first_not_of('0');

	if(pos ==string::npos) //ret中全部为'0'，则两个数相减后的结果为0
    {
    	return "0";
    }

    return ret.substr(pos);// //返回两个字符串相减后的结果
}


// 大数乘法
string MulString(string num1, string num2){
	if(num1 == '0' || num2 == '0'){ // 两个操作数中有一个为0，则结果为0
		return "0";
	}
	int m = num1.size(), n = num2.size();
	vector<int> arr(m+n, 0); //开辟数组arr的大小为m+n，并且全部初始化为0
	//1、取乘数的每一位与被乘数的每一位相乘，将结果累加到数组arr的对应下标位置
	
	for(int i = n-1; i>=0; i--){  //取乘数的每一位
		int a = num2[i] - '0';
		for(int j = m - 1; j>=0; j--){ //取被乘数的每一位
			int b = num1[j] - '0';
			arr[i + j + 1] += a*b; // 乘数第i位与被乘数第j位相乘后的结果累加到数组arr中下标为i+j+1的位置	
		}
	}

	// 2. 从后往前对数组arr进行进位操作
	int end = m + n -1;
	while(end>0){
		arr[end-1] += arr[end] / 10; //进位的值加到前一个位置
		arr[end] %= 10; //进位后剩下的值存放到当前位
		end--; //处理下一位
	}

	//3、依次将数据尾插到字符串ret当中
	string ret; //存放两个字符串相乘后的结果
	int flag = 1; //默认有效值从数组arr当中下标为1的位置开始
	
	if (arr[0] != 0)
		flag = 0; //若数组arr当中下标为0的位置的值不为0，则有效值从第0位开始
	
	for(int i = flag; i< m+n; i++){
		ret += (arr[i]+'0');
	}
	return ret; //返回两个字符串相乘后的结果
}




//大数除法
string DivString(string num1, string num2, int n)
{
	if (num2 == "0") //除数不能为0
		return "error";
	string ret; //存储两个字符串相除后的结果
	string tmp; //余数

	//1、先计算小数点前面的数
	if (num1.size() < num2.size()) //num1的位数小于num2
	{
		ret += "0."; //商为0
		tmp = num1; //余数为num1
	}
	else //num1的位数大于等于num2
	{
		size_t len = num2.size(); //除数的长度
		tmp = num1.substr(0, len); //先取出被除数的高len位
		while (1)
		{
			//a、计算tmp当中最多有多少个num2（tmp除以num2的商）
			int count = 0;
			while (Cmp(tmp, num2) != -1) //tmp大于等于num2，则说明商可以更大
			{
				tmp = SubString(tmp, num2);
				count++; 
			}

			//b、将商值尾插到ret当中
			ret += (count + '0');

			//c、如果num1的所有位都被取完了，则小数点之前的结果计算完毕
			if (len >= num1.size())
				break;

			//d、如果num1当中还有未取的位，则继续从num1中一位尾插到tmp当中
			tmp += num1[len];
			len++; //下一次待取位下标
		}
		ret += "."; //小数点之前的结果计算完毕，加上小数点

		//如果ret最高位为0，且该位后面不是小数点，则需要将这个0过滤掉
		if (ret.size() != 2 && ret[0] == '0')
			ret = ret.substr(1);
	}

	//2、再计算小数点后面的数（保留n位小数）
	for (int i = 0; i < n; i++)
	{
		if (tmp == "0") //tmp为0（余数为0）
		{
			ret += "0"; //则直接在ret后面补0即可
		}
		else //tmp不为0（余数不为0）
		{
			tmp += "0"; //在余数后面补0，继续进行计算

			//a、计算tmp当中最多有多少个num2（tmp除以num2的商）
			int count = 0;
			while (Cmp(tmp, num2) != -1)
			{
				tmp = SubString(tmp, num2);
				count++;
			}

			//b、将商值尾插到ret当中
			ret += (count + '0');
		}
	}
	return ret; //返回两个字符串相除后的结果
}





int main(){






}




