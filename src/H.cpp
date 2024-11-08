#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

/**
 * @brief 执行广度优先搜索 (BFS)，检查从源节点到汇节点是否存在增广路径
 * 
 * @param capacity 容量矩阵，表示每条边的容量
 * @param adj 邻接表，表示图的结构
 * @param source 源节点
 * @param sink 汇节点
 * @param parent 父节点数组，用于存储路径
 * @return true 如果存在增广路径
 * @return false 如果不存在增广路径
 */
bool bfs(const vector<vector<int>>& capacity, vector<vector<int>>& adj, int source, int sink, vector<int>& parent) {
    int n = capacity.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v] && capacity[u][v] > 0) { // 找到一个未访问的且有剩余容量的节点
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == sink) // 到达汇节点，返回true
                    return true;
            }
        }
    }
    return false; // 没有找到增广路径
}

/**
 * @brief 使用Edmonds-Karp算法计算最大流量
 * 
 * @param n 节点数
 * @param source 源节点
 * @param sink 汇节点
 * @param capacity 容量矩阵，表示每条边的容量
 * @param adj 邻接表，表示图的结构
 * @return int 最大流量
 */
int edmondsKarp(int n, int source, int sink, vector<vector<int>>& capacity, vector<vector<int>>& adj) {
    int maxFlow = 0;
    vector<int> parent(n);

    // 当存在增广路径时，不断增加流量
    while (bfs(capacity, adj, source, sink, parent)) {
        int pathFlow = INT_MAX;

        // 找到当前增广路径中的最小容量
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, capacity[u][v]);
        }

        // 更新残余图中的容量
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= pathFlow;
            capacity[v][u] += pathFlow;
        }

        maxFlow += pathFlow; // 累加到最大流量
    }

    return maxFlow;
}

/**
 * @brief 主函数
 * 
 * @return int 程序执行结果
 */
int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> capacity(N, vector<int>(N, 0));
    vector<vector<int>> adj(N);

    for (int i = 0; i < M; ++i) {
        int u, v, cap;
        cin >> u >> v >> cap;
        --u; // 转换为0索引
        --v;
        capacity[u][v] += cap; // 处理可能的多条边情况
        adj[u].push_back(v);
        adj[v].push_back(u); // 添加反向边到邻接表
    }

    int source = 0;     // 发电站编号为1，即0索引
    int sink = N - 1;   // 变电站编号为N，即N-1索引

    int maxFlow = edmondsKarp(N, source, sink, capacity, adj);
    cout << maxFlow << endl; // 输出最大流量

    return 0;
}