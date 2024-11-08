#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

struct Cup {
    double gain;  // 边际收益
    int index;    // 烧杯的编号
    
    bool operator<(const Cup& other) const {
        return gain < other.gain; // C++ 默认是最大堆
    }
};

// 初始化边际收益堆
priority_queue<Cup> initializeHeap(const vector<int>& p, const vector<int>& l) {
    priority_queue<Cup> heap;
    for (int i = 0; i < p.size(); ++i) {
        if (l[i] == 0) {
            heap.push({0.0, i});
        } else {
            double gain = static_cast<double>(p[i]) / (l[i] + 1);
            heap.push({gain, i});
        }
    }
    return heap;
}

// 分配物质β
void allocateBeta(int t, vector<int>& b, const vector<int>& p, const vector<int>& l, priority_queue<Cup>& heap) {
    for (int i = 0; i < t; ++i) {
        if (heap.empty()) {
            break;
        }
        Cup top = heap.top();
        heap.pop();
        
        int idx = top.index;
        b[idx] += 1; // 给这个烧杯分配1毫升物质β
        
        if (b[idx] < l[idx]) {
            double new_gain = static_cast<double>(p[idx]) * l[idx] / pow((l[idx] + b[idx] + 1), 2);
            heap.push({new_gain, idx});
        }
    }
}

// 计算期望值
double calculateExpectedValue(const vector<int>& p, const vector<int>& l, const vector<int>& b) {
    double total_E = 0.0;
    for (int i = 0; i < p.size(); ++i) {
        if (b[i] > 0) {
            total_E += (static_cast<double>(b[i]) / (l[i] + b[i])) * p[i];
        }
    }
    return total_E;
}

// 处理查询并重新分配
void handleQuery(int t, int tj, int rj, vector<int>& p, vector<int>& l, vector<int>& b) {
    if (tj == 1) {
        l[rj] += 1; // 增加1毫升物质α
    } else if (tj == 2) {
        l[rj] -= 1; // 减少1毫升物质α
    }

    // 重新分配物质β
    fill(b.begin(), b.end(), 0);  // 重置所有分配
    priority_queue<Cup> heap = initializeHeap(p, l);
    allocateBeta(t, b, p, l, heap);
}

int main() {
    int n, t, q;
    cin >> n >> t >> q;
    
    vector<int> p(n), l(n), b(n, 0); // p[i]: 新能源量, l[i]: 物质α量, b[i]: 物质β分配量
    
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    
    for (int i = 0; i < n; ++i) {
        cin >> l[i];
    }
    
    // 初始化堆并分配物质β
    priority_queue<Cup> heap = initializeHeap(p, l);
    allocateBeta(t, b, p, l, heap);
    
    // 计算初始期望值
    double total_E = calculateExpectedValue(p, l, b);
    
    vector<double> results;  // 存储所有查询后的期望值
    
    // 处理查询
    for (int i = 0; i < q; ++i) {
        int tj, rj;
        cin >> tj >> rj;
        rj -= 1;  // 转换为0索引
        
        handleQuery(t, tj, rj, p, l, b);
        
        // 重新计算期望值
        total_E = calculateExpectedValue(p, l, b);
        
        // 将结果保存到结果数组中
        results.push_back(total_E);
    }
    
    // 输出所有结果，精度为9位小数
    for (const double& result : results) {
        cout << fixed << setprecision(9) << result << endl;
    }
    
    return 0;
}
