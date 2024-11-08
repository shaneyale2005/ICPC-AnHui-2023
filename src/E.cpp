#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

// 模拟移动的函数
string simulate(const string& direction, int A, int B, const vector<int>& x, const vector<int>& y, const vector<int>& t) {
    int step = 0;
    int currentA = A, currentB = B;
    map<pair<int, int>, bool> visited;

    while (visited[{currentA, currentB}] == false) {
        if (t[currentA] != t[currentB]) {
            return to_string(step);
        }
        visited[{currentA, currentB}] = true;

        if (direction == "X") {
            currentA = x[currentA];
            currentB = x[currentB];
        } else {
            currentA = y[currentA];
            currentB = y[currentB];
        }
        step++;
    }
    return "GG";
}

// 读取 n, A, B 的函数
void readIntersectionParams(int& n, int& A, int& B) {
    string line;
    while (true) {
        getline(cin, line);
        stringstream ss(line);
        vector<int> n_A_B;
        int val;
        while (ss >> val) n_A_B.push_back(val);
        
        if (n_A_B.size() >= 3) {
            n = n_A_B[0];
            A = n_A_B[1];
            B = n_A_B[2];
            break;
        }
    }
}

// 读取每个路口信息的函数
void readIntersectionData(int n, vector<int>& x, vector<int>& y, vector<int>& t) {
    string line;
    int count = 0;
    while (count < n) {
        getline(cin, line);
        stringstream ss(line);
        vector<int> parts;
        int val;
        while (ss >> val) parts.push_back(val);
        
        if (parts.size() >= 3) {
            x[count] = parts[0];
            y[count] = parts[1];
            t[count] = parts[2];
            count++;
        }
    }
}

// 处理每个测试用例的函数
string processTestCase(int n, int A, int B, const vector<int>& x, const vector<int>& y, const vector<int>& t) {
    // Simulate in two directions
    string stepX = simulate("X", A, B, x, y, t);
    string stepY = simulate("Y", A, B, x, y, t);

    // Find the minimum step
    if (stepX != "GG" && stepY != "GG") {
        return to_string(min(stoi(stepX), stoi(stepY)));
    } else if (stepX != "GG") {
        return stepX;
    } else if (stepY != "GG") {
        return stepY;
    } else {
        return "GG";
    }
}

int main() {
    int T;
    cin >> T;
    cin.ignore();  // To handle newline after reading T

    vector<string> results;

    for (int test_case = 0; test_case < T; test_case++) {
        int n, A, B;

        // Read intersection parameters n, A, B
        readIntersectionParams(n, A, B);

        // Read each intersection information
        vector<int> x(n), y(n), t(n);
        readIntersectionData(n, x, y, t);

        // Process the test case and store the result
        results.push_back(processTestCase(n, A, B, x, y, t));
    }

    // Output results
    for (const string& result : results) {
        cout << result << endl;
    }

    return 0;
}
/*
输入：
2 
3 1 2 
1 2 1 
0 2 0 
0 1 0 
3 1 2 
1 2 0 
2 0 1 
0 1 1 
*/