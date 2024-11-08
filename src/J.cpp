#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <functional>

const int MODULO = 1000000007;

std::set<int> prime_factors(int num) {
    std::set<int> primes;
    if (num == 1) {
        return primes;
    }
    int divisor = 2;
    while (divisor * divisor <= num) {
        while (num % divisor == 0) {
            primes.insert(divisor);
            num /= divisor;
        }
        divisor += 1;
    }
    if (num > 1) {
        primes.insert(num);
    }
    return primes;
}

struct SetHash {
    std::size_t operator()(const std::set<int>& s) const {
        std::size_t hash = 0;
        for (int i : s) {
            hash ^= std::hash<int>{}(i) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

std::vector<std::vector<int>> classify_by_prime_factors(int limit) {
    std::unordered_map<std::set<int>, std::vector<int>, SetHash> factor_classes;
    for (int value = 1; value <= limit; ++value) {
        std::set<int> factors = prime_factors(value);
        factor_classes[factors].push_back(value);
    }
    std::vector<std::vector<int>> result;
    for (const auto& pair : factor_classes) {
        result.push_back(pair.second);
    }
    return result;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int count_valid_permutations(int n, const std::vector<int>& a) {
    std::map<int, int> assigned;
    std::set<int> available_numbers;
    for (int i = 1; i <= n; ++i) {
        available_numbers.insert(i);
    }
    for (int idx = 0; idx < n; ++idx) {
        int num = a[idx];
        int pos = idx + 1;
        if (num != 0) {
            if (available_numbers.find(num) == available_numbers.end()) {
                return 0;
            }
            assigned[pos] = num;
            available_numbers.erase(num);
        }
    }

    std::unordered_map<int, std::set<int>> coprime_slots;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i != j && gcd(i, j) == 1) {
                coprime_slots[i].insert(j);
            }
        }
    }

    std::unordered_map<int, std::set<int>> coprime_numbers;
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= n; ++y) {
            if (gcd(x, y) == 1) {
                coprime_numbers[x].insert(y);
            }
        }
    }

    std::vector<int> unassigned_slots;
    for (int pos = 1; pos <= n; ++pos) {
        if (assigned.find(pos) == assigned.end()) {
            unassigned_slots.push_back(pos);
        }
    }
    std::vector<int> remaining_numbers(available_numbers.begin(), available_numbers.end());

    if (unassigned_slots.size() > remaining_numbers.size()) {
        return 0;
    }

    int count = 0;

    std::function<void(int, std::map<int, int>&, std::set<int>&)> backtrack;
    backtrack = [&](int idx, std::map<int, int>& current_assignment, std::set<int>& used_nums) {
        if (idx == unassigned_slots.size()) {
            count = (count + 1) % MODULO;
            return;
        }

        int slot = unassigned_slots[idx];
        for (int number : remaining_numbers) {
            if (used_nums.find(number) == used_nums.end()) {
                bool valid = true;
                for (const auto& pair : current_assignment) {
                    int assigned_slot = pair.first;
                    int assigned_number = pair.second;
                    if (coprime_slots[slot].find(assigned_slot) != coprime_slots[slot].end() && gcd(number, assigned_number) != 1) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    current_assignment[slot] = number;
                    used_nums.insert(number);
                    backtrack(idx + 1, current_assignment, used_nums);
                    current_assignment.erase(slot);
                    used_nums.erase(number);
                }
            }
        }
    };

    std::map<int, int> initial_assignment = assigned;
    std::set<int> used_numbers;
    for (const auto& pair : assigned) {
        used_numbers.insert(pair.second);
    }

    backtrack(0, initial_assignment, used_numbers);
    return count;
}

int main() {
    std::cout << "请输入测试用例的数量:" << std::endl;
    int test_cases;
    std::cin >> test_cases;
    for (int i = 0; i < test_cases; ++i) {
        std::cout << "\n请输入n的值:" << std::endl;
        int n;
        std::cin >> n;
        std::cout << "请输入长度为" << n << "的数组（用空格分隔）:" << std::endl;
        std::vector<int> a(n);
        for (int j = 0; j < n; ++j) {
            std::cin >> a[j];
        }
        int solution = count_valid_permutations(n, a);
        std::cout << "满足条件的排列数为: " << solution << std::endl;
    }
    return 0;
}