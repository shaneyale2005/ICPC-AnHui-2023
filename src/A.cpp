#include <iostream>
#include <cmath>

// 计算污染面积减少到M以下所需的年数
int years_until_pollution(double N, double M, double K) {
    int years = 0;
    double current_area = N;

    while (current_area > M) {
        current_area *= (1 - K / 100.0);
        years += 1;
    }

    return years;
}

int main() {
    // 提示用户输入初始污染面积、目标污染面积和每年减少的百分比
    double N, M, K;
    std::cout << "请输入初始污染面积 N: ";
    std::cin >> N;
    std::cout << "请输入目标污染面积 M: ";
    std::cin >> M;
    std::cout << "请输入每年减少的百分比 K: ";
    std::cin >> K;

    // 计算并输出结果
    int output = years_until_pollution(N, M, K);
    std::cout << "污染面积将在 " << output << " 年后减少到 " << M << " 以下。" << std::endl;

    return 0;
}
