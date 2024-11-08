#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// 函数 f(x) 的定义
double f(double x, double a, double b) {
    return sqrt(x*x + a) + sqrt((b-x)*(b-x) + 1);
}

// 寻找函数最小值的函数
double findMinimum(double a, double b, double learningRate = 0.001, double precision = 1e-9) {
    double x = b / 2; // 从中间点开始
    double gradient;

    while (true) {
        // 计算数值梯度
        gradient = (f(x + precision, a, b) - f(x - precision, a, b)) / (2 * precision);
        
        double newX = x - learningRate * gradient; // 更新 x
        
        // 检查收敛
        if (fabs(newX - x) < precision) {
            break;
        }
        
        x = newX; // 移动到新的 x
    }

    return f(x, a, b); // 返回最小值
}

int main() {
    double a, b;
    cout << "Enter values for a and b: ";
    cin >> a >> b; // 从键盘读入 a 和 b

    double minimumValue = findMinimum(a, b); // 计算最小值

    cout << fixed << setprecision(6); // 设置输出精度为6位小数
    cout << "The minimum value of the function is: " << minimumValue << endl; // 输出最小值

    return 0;
}
