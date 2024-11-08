#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 结构体用于存储吸光能力及其对应的仓库索引
struct ValueIndex {
    int value;
    int index;
};

// 自定义比较函数，用于按吸光能力从大到小排序
bool compare(const ValueIndex &a, const ValueIndex &b) {
    return a.value > b.value;
}

// 读取输入数据
void readInput(int &n, vector<pair<int, int>> &roads, vector<int> &values) {
    cin >> n;
    roads.resize(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        roads[i] = {a - 1, b - 1};  // 转换为 0-based 索引
    }
    values.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }
}

// 构建无向图（树）
void buildGraph(int n, const vector<pair<int, int>> &roads, vector<vector<int>> &graph) {
    graph.resize(n);
    for (auto road : roads) {
        int a = road.first, b = road.second;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
}

// 对吸光能力从大到小排序
void sortValues(const vector<int> &values, vector<ValueIndex> &valuesSorted) {
    int n = values.size();
    valuesSorted.resize(n);
    for (int i = 0; i < n; i++) {
        valuesSorted[i] = {values[i], i};
    }
    sort(valuesSorted.begin(), valuesSorted.end(), compare);
}

// 计算最大吸光能力总和
int calculateAbsorptionSum(int n, const vector<ValueIndex> &valuesSorted, const vector<int> &values, const vector<vector<int>> &graph) {
    vector<bool> visited(n, false);
    int absorptionSum = 0;

    for (auto vi : valuesSorted) {
        int node = vi.index;

        if (visited[node]) {
            continue;
        }

        visited[node] = true;

        int maxValue = -1;
        int bestNeighbor = -1;
        for (int neighbor : graph[node]) {
            if (!visited[neighbor] && values[neighbor] > maxValue) {
                maxValue = values[neighbor];
                bestNeighbor = neighbor;
            }
        }

        if (bestNeighbor != -1) {
            absorptionSum += vi.value * values[bestNeighbor];
            visited[bestNeighbor] = true;
        }
    }

    return absorptionSum;
}

int main() {
    int n;
    vector<pair<int, int>> roads;
    vector<int> values;

    // 读取输入数据
    readInput(n, roads, values);

    // 构建无向图（树）
    vector<vector<int>> graph;
    buildGraph(n, roads, graph);

    // 对吸光能力从大到小排序
    vector<ValueIndex> valuesSorted;
    sortValues(values, valuesSorted);

    // 计算最大吸光能力总和
    int absorptionSum = calculateAbsorptionSum(n, valuesSorted, values, graph);

    // 输出最大吸光能力总和
    cout << absorptionSum << endl;

    return 0;
}



/*
输入：
5
1 2
1 3
2 4
2 5
1 2 3 4 5
*/
