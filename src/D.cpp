#include <iostream>       // 导入输入输出库
#include <algorithm>      // 导入算法库，用于使用max函数
using namespace std;

int main() {
	// n为路口数，k为可以安装的装置数目 
    int n, k;
    cin >> n >> k;  // 从标准输入读取路口数和安装的装置数量

    // 创建一个二维数组traffic，用于存储每对路口之间的市民通行数量
    int traffic[n + 1][n + 1]; 
    // 读取市民通行数量数据
    for (int i = 1; i < n; i++) { // 循环遍历路口
        for (int j = i + 1; j < n + 1; j++) { 
            cin >> traffic[i][j];  // 输入每对路口之间的通行量
        }
    }
    
    // 定义SUM用于计算从路口1到其他路口的初始通行数量
	int SUM = 0, SUM_max;  // SUM_max用于记录能宣传的最大人数
	for(int x = 2; x <= n; x++) {  // 从路口2开始计算与路口1的通行量
		SUM += traffic[1][x];  // 将路口1到每个其他路口的通行量累加到SUM中
	}
	SUM_max = SUM;  // 将初始的SUM赋值给SUM_max
    
	// 计算能宣传的最大人数
	for(int i = 2; i <= n - k; i++) {  // 遍历可被选中路口
		// 从SUM中减去与路口i的所有相连路口的通行量
		for(int x = 1; x <= i - 1; x++) {
			SUM -= traffic[x][i];  // 对于在i之前的路口
		}
		// 将与路口i相连的后续路口的通行量加到SUM中
		for(int x = i + 1; x <= n; x++) {
			SUM += traffic[i][x];  // 对于在i之后的路口
		}
		SUM_max = max(SUM_max, SUM);  // 用于更新能宣传的最大人数
	}
	
    // 输出能够收到宣传的市民最大总数
    cout << SUM_max << endl;

    return 0;  // 程序结束
}
