#include <iostream>
#include <vector>

using Value = unsigned long long;

// 依題目定義，先處理 m == 0，避免 A(0, 0) 落入第二條規則。
Value ackermannRecursive(unsigned m, Value n) {
    if (m == 0) return n + 1;
    if (n == 0) return ackermannRecursive(m - 1, 1);
    return ackermannRecursive(m - 1, ackermannRecursive(m, n - 1));
}

Value ackermannIterative(unsigned m, Value n) {
    std::vector<unsigned> pending{m};
    while (!pending.empty()) {
        unsigned current = pending.back();
        pending.pop_back();
        if (current == 0) {
            ++n;
        } else if (n == 0) {
            n = 1;
            pending.push_back(current - 1);
        } else {
            // 後進先出：先計算內層 A(current, n-1)，再算外層。
            pending.push_back(current - 1);
            pending.push_back(current);
            --n;
        }
    }
    return n;
}

int main() {
    long long m, n;
    std::cout << "Enter m and n: ";
    if (!(std::cin >> m >> n) || m < 0 || n < 0) {
        std::cerr << "Error: enter two nonnegative integers.\n";
        return 1;
    }
    // 示範程式限制輸入，讓兩種演算法都能在一般電腦上完成。
    if (m > 3 || n > 6) {
        std::cerr << "Error: demo range is 0 <= m <= 3, 0 <= n <= 6.\n";
        return 1;
    }
    std::cout << "Recursive: " << ackermannRecursive(static_cast<unsigned>(m), n) << '\n';
    std::cout << "Nonrecursive: " << ackermannIterative(static_cast<unsigned>(m), n) << '\n';
}
