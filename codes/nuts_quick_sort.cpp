#include <iostream>
#include <vector>
using namespace std;
// 螺钉螺母匹配问题
// 快速排序分治思想的应用与理解


// 究其原因，这其实是我们取最左边的元素作为基准值导致的。
// 我们需要保证每次交换过来的元素是小于等于基准值的，所以我们先动右指针，再动左指针。


void shuffle(vector<int> & v){
	srand((int)time(0));
	for(int i = 0; i<v.size()-1; i++){ //洗牌算法，用于打乱数组
		int ran = rand()%(v.size()-i-1) + i + 1;
		swap(v[i], v[ran]);
	}
}

void match(vector<int> & m, vector<int> & d, int ml, int mr, int dl, int dr){
	int pivot1 = m[ml]; // 将第一个螺母确定为pivot（基数）
	
	for(int i = 0; i<d.size(); i++){
		// 选定与第一个螺母匹配的螺钉
		if(d[i]==pivot1){
			pivot1 = i;
			break;
		}
	}
	int begin1 = dl; end1 = dr; // 以此螺母作为基数，将螺钉数组进行快速排序
    // 选中的基数换到左边来
	swap(d[dl], d[pivot1]);

	while(begin1!=end1){
	    // 先动右指针，再动左指针
		while(d[end1]>=pivot && begin1<end1){
			end1--;
		}
		while(d[begin1]<=pivot1 && begin1<end1){
			beign1++;
		}
		swap(d[begin1],d[end1]);
	}
	// 把基数移动中间
	swap(d[dl],d[end1]);


	int  middle1 = end1; // 确定螺钉基数位置


	int pivot2 = d[middle1]; //以匹配的螺钉作为基数，将螺母数组进行快速排序
	int begin2 = ml; end2 = mr;
	while(begin2!=end2){
		while(begin2<end2 && m[end2]>=pivot2){
			end2--;
		}		
		while(begin2<end2 && m[begin2]>=pivot2){
			begin2++;
		}
		swap(m[begin2],m[end2]);
	}
	swap(m[ml],m[end2]);

	int middle2 = end2; // 确定螺母基数位置

	// *由于两数组相同，基数也相同，那么以上操作执行完成，
	// 已配对的螺钉与螺母所对应的数组下标一定相同

	match(m, d, ml, middle2-1, dl, middle1-1); // 递归执行
	match(m, d, middle2+1, mr, middle+1, dr);

	// 所以本题实际上是一个在两个相同数组中，选定相同基数，分别进行快排，最后使两数组顺序一致的任务。

}

int main(){
	vector<int> luoMu;
	for(int i = 0; i < 10; i++){
		luoMu[i] = i+1;
	}
	shuffle(luoMu); //打乱螺母
	vector<int> luoDing(luoMu.begin(), luoMu.end());
	shuffle(luoDing);// 打乱螺钉
	mathch(luoMu, luoDing, 0, 9, 0, 9);
}


