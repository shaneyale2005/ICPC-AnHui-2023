#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>

using namespace std;

struct Volunteer {
    int t_i;
    int c_i;
    int p_i;
};

vector<int> solve_volunteer_tasks(int n, int m, const vector<Volunteer>& volunteers, int q, const vector<pair<int, int>>& tasks);
unordered_map<int, vector<int>> build_graph(const vector<Volunteer>& volunteers, int max_time);
int find_shortest_path(const unordered_map<int, vector<int>>& graph, int start, int end);

int main() {
    int n = 10;
    int m = 10;
    vector<Volunteer> volunteers = {
        {2, 1, 5}, {5, 4, 3}, {8, 7, 1}, {9, 8, 2},
        {3, 1, 7}, {6, 3, 6}, {9, 6, 4}, {6, 2, 8},
        {6, 7, -2}, {10, 8, -8}
    };
    int q = 4;
    vector<pair<int, int>> tasks = {{11, 10}, {12, 9}, {13, 10}, {14, 10}};

    vector<int> results = solve_volunteer_tasks(n, m, volunteers, q, tasks);
    for (int result : results) {
        cout << result << endl;
    }

    return 0;
}

vector<int> solve_volunteer_tasks(int n, int m, const vector<Volunteer>& volunteers, int q, const vector<pair<int, int>>& tasks) {
    vector<int> results;
    for (const auto& task : tasks) {
        int w_i = task.first;
        int x_i = task.second;
        // 构建图
        unordered_map<int, vector<int>> graph = build_graph(volunteers, w_i);
        // 寻找最短路径
        int min_volunteers = find_shortest_path(graph, 1, x_i);
        results.push_back(min_volunteers != INT_MAX ? min_volunteers : -1);
    }
    return results;
}

unordered_map<int, vector<int>> build_graph(const vector<Volunteer>& volunteers, int max_time) {
    unordered_map<int, vector<int>> graph;
    for (size_t i = 0; i < volunteers.size(); ++i) {
        int t_i = volunteers[i].t_i;
        int c_i = volunteers[i].c_i;
        int p_i = volunteers[i].p_i;
        for (int t = t_i; t <= t_i + abs(c_i); ++t) {
            if (t > max_time) break;
            int position = p_i + (t - t_i) / (c_i > 0 ? 1 : -1);
            if (graph.find(position) == graph.end()) {
                graph[position] = vector<int>();
            }
            // 检查其他志愿者是否在同一位置
            for (size_t j = 0; j < volunteers.size(); ++j) {
                if (i != j) {
                    int t_j = volunteers[j].t_i;
                    int c_j = volunteers[j].c_i;
                    int p_j = volunteers[j].p_i;
                    if (t_j <= t && t <= t_j + abs(c_j)) {
                        int other_position = p_j + (t - t_j) / (c_j > 0 ? 1 : -1);
                        if (other_position == position) {
                            graph[position].push_back(j);
                        }
                    }
                }
            }
        }
    }
    return graph;
}

int find_shortest_path(const unordered_map<int, vector<int>>& graph, int start, int end) {
    // 使用BFS或Dijkstra算法寻找最短路径
    // 这里我们使用BFS
    unordered_map<int, int> distance;
    queue<int> q;
    q.push(start);
    distance[start] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == end) {
            return distance[current];
        }

        if (graph.find(current) != graph.end()) {
            for (int neighbor : graph.at(current)) {
                if (distance.find(neighbor) == distance.end()) {
                    distance[neighbor] = distance[current] + 1;
                    q.push(neighbor);
                }
            }
        }
    }

    return INT_MAX;
}