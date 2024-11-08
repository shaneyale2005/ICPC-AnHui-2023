#include <iostream>  // 用于输入输出操作
#include <vector>    // 用于使用std::vector
#include <set>       // 用于使用std::set
#include <cmath>     // 用于使用sqrt函数

using namespace std;

// 生成环保数列
vector<int> generate_magical_numbers(int limit) {
    set<int> magical_numbers;
    for (int a = 2; a <= sqrt(limit); ++a) {
        for (int b = 1; b < a; ++b) {
            if ((a - b) % 2 == 0) {
                int n = (a - b) * (a + b);
                if (n > limit) break;
                magical_numbers.insert(n);
            }
        }
    }
    return vector<int>(magical_numbers.begin(), magical_numbers.end());
}

// 计算不超过 N 的环保数的个数
int count_f(int N) {
    if (N < 3) return 0;
    
    // 计算不超过 N 的奇数个数
    int count_odds = (N - 1) / 2;
    
    // 计算不超过 N 的4的倍数个数 >=8
    int count_mult4 = (N >= 8) ? (N / 4) - 1 : 0;
    
    return count_odds + count_mult4;
}

// 使用二分查找找到环保数列的第 x 项
int find_xth_number(int x) {
    int low = 3;
    int high = 4 * x + 10;  // 设定一个足够大的上界

    while (low < high) {
        int mid = (low + high) / 2;
        int c = count_f(mid);
        if (c >= x) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    // low 应该是第 x 项的值，且是环保数
    return low;
}

// 主函数
int main() {
    int T;
    cin >> T;  // 读取组数
    
    vector<int> results;  // 存储每次的结果
    
    for (int i = 0; i < T; ++i) {
        int x;
        cin >> x;
        int nth_number = find_xth_number(x);
        results.push_back(nth_number);  // 将结果存储到数组中
    }
    
    // 输出所有结果
    for (const int& result : results) {
        cout << result << endl;
    }

    return 0;
}
