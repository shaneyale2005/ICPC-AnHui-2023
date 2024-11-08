#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;

// 定义 π 常量
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 定义点 (x, y) 为 pair
typedef pair<double, double> Point;

// 读取一个点的坐标
Point read_point() {
    double x, y, z;
    cin >> x >> y >> z;
    return { x, z };  // 只使用 x 和 z，投影到 2D 平面
}

// 计算两点之间的欧几里得距离
double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

// 计算点到直线的距离
double distance_point_to_line(const Point& A, const Point& B, const Point& C) {
    double cross = abs((B.first - A.first) * (A.second - C.second) - (B.second - A.second) * (A.first - C.first));
    return cross / distance(A, B);
}

// 计算点 P 到圆 C 的切点
vector<Point> tangent_points(const Point& P, const Point& C, double R) {
    double dx = P.first - C.first;
    double dy = P.second - C.second;
    double dist = hypot(dx, dy);

    if (dist < R) {
        return {};  // 点在圆内，没有切点
    } else if (dist == R) {
        return { P };  // 点在圆上，切点就是点本身
    } else {
        double angle_PC = atan2(dy, dx); // 计算点 P 相对于圆心 C 的角度
        double alpha = acos(R / dist); // 计算切线与半径的夹角
        double t1 = angle_PC + alpha;
        double t2 = angle_PC - alpha;
        Point tp1 = { C.first + R * cos(t1), C.second + R * sin(t1) };
        Point tp2 = { C.first + R * cos(t2), C.second + R * sin(t2) };
        return { tp1, tp2 };
    }
}

// 计算圆心 C 到两点 P1 和 P2 之间的角度
double angle_between(const Point& C, const Point& P1, const Point& P2) {
    double v1x = P1.first - C.first;
    double v1y = P1.second - C.second;
    double v2x = P2.first - C.first;
    double v2y = P2.second - C.second;

    double dot = v1x * v2x + v1y * v2y;
    double mag1 = hypot(v1x, v1y);
    double mag2 = hypot(v2x, v2y);

    if (mag1 == 0 || mag2 == 0) {
        return 0;
    }

    double cos_theta = dot / (mag1 * mag2);
    cos_theta = max(min(cos_theta, 1.0), -1.0);  // 防止浮点数误差
    return acos(cos_theta);
}

// 计算点 A 和点 B 绕圆 C 的最短路径
double compute_path(const Point& A, const Point& B, const Point& C, double R) {
    double dist_AB = distance(A, B);
    double dist_to_line = distance_point_to_line(A, B, C);

    if (dist_to_line >= R) {
        return dist_AB;  // 直线不穿过圆
    }

    // 计算点 A 和点 B 的切点
    vector<Point> tangents_A = tangent_points(A, C, R);
    vector<Point> tangents_B = tangent_points(B, C, R);

    if (tangents_A.empty() || tangents_B.empty()) {
        return numeric_limits<double>::infinity();  // 无效路径
    }

    double min_path = numeric_limits<double>::infinity();

    // 计算所有可能的路径并选择最短路径
    for (const Point& ta : tangents_A) {
        for (const Point& tb : tangents_B) {
            double angle = angle_between(C, ta, tb);
            double arc = min(angle, 2.0 * M_PI - angle) * R;  // 选择较小的弧长
            double path = distance(A, ta) + arc + distance(B, tb);
            min_path = min(min_path, path);
        }
    }

    return min_path;
}

int main() {
    // 读取点 A, B, C 和半径 R
    Point A = read_point();
    Point B = read_point();
    Point C = read_point();
    double R;
    cin >> R;

    // 计算最短路径的长度
    double path_length = compute_path(A, B, C, R);

    if (isinf(path_length)) {
        cout << "No valid path" << endl;
    } else {
        // 输出结果，保留两位小数
        cout << fixed << setprecision(2) << path_length << endl;
    }

    return 0;
}
