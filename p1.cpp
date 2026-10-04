#include <iostream>   // 載入輸入輸出功能，等等會用到 cin、cout、cerr
#include <vector>     // 載入 vector，等等非遞迴版本會拿它當堆疊使用

using Value = unsigned long long;  
// 幫 unsigned long long 取一個比較短的名字叫 Value
// unsigned long long：只能存 0 和正整數，而且可以存很大的數字


// 這是 Ackermann 函數的「遞迴版本」
Value ackermannRecursive(unsigned m, Value n) {

    // 如果 m == 0
    // 根據公式 A(0, n) = n + 1
    if (m == 0) return n + 1;

    // 如果 m 不是 0，但 n == 0
    // 根據公式 A(m, 0) = A(m - 1, 1)
    if (n == 0) return ackermannRecursive(m - 1, 1);

    // 如果 m > 0 而且 n > 0
    // 根據公式 A(m, n) = A(m - 1, A(m, n - 1))
    // 會先算裡面的 A(m, n - 1)，再把結果丟給外面的 A(m - 1, ...)
    return ackermannRecursive(m - 1, ackermannRecursive(m, n - 1));
}


// 這是 Ackermann 函數的「非遞迴版本」
Value ackermannIterative(unsigned m, Value n) {

    // 建立一個 vector，名字叫 pending
    // 一開始先把 m 放進去
    // 這個 vector 用來模擬遞迴時系統幫我們保存的工作
    std::vector<unsigned> pending{m};

    // 只要 pending 裡面還有東西，就繼續計算
    while (!pending.empty()) {

        // 取得 pending 最後面的一個數字
        // 可以把它想成目前要處理的 m
        unsigned current = pending.back();

        // 把剛剛取得的最後一個數字刪掉
        pending.pop_back();

        // 如果目前的 m（current）是 0
        if (current == 0) {

            // A(0, n) = n + 1
            // 所以直接讓 n 加 1
            ++n;

        // 如果 current 不是 0，但是 n == 0
        } else if (n == 0) {

            // 根據 A(m, 0) = A(m - 1, 1)
            // 所以先把 n 改成 1
            n = 1;

            // 接下來要處理 m - 1
            // 所以把 current - 1 放進 pending
            pending.push_back(current - 1);

        // 如果 current > 0，而且 n > 0
        } else {

            // 原公式：
            // A(m, n) = A(m - 1, A(m, n - 1))
            //
            // 因為 vector 這裡當成堆疊使用
            // 最後放進去的東西會最先被拿出來
            // 所以先放「外層」的 m - 1
            pending.push_back(current - 1);

            // 再放「內層」的 m
            // 因為它最後放，所以等等會先被處理
            pending.push_back(current);

            // 內層是 A(m, n - 1)
            // 所以先讓 n 減 1
            --n;
        }
    }

    // pending 全部處理完後
    // n 就是最後算出來的 Ackermann 結果
    return n;
}


// 主程式從這裡開始
int main() {

    // 宣告兩個 long long 整數 m 和 n
    // 用來接收使用者輸入
    long long m, n;

    // 顯示提示文字，叫使用者輸入 m 和 n
    std::cout << "Enter m and n: ";

    // std::cin >> m >> n：讀取使用者輸入
    // !(...)：如果讀取失敗
    // m < 0 || n < 0：或者 m、n 有任何一個是負數
    if (!(std::cin >> m >> n) || m < 0 || n < 0) {

        // 顯示錯誤訊息
        std::cerr << "Error: enter two nonnegative integers.\n";

        // 回傳 1，代表程式發生錯誤並結束
        return 1;
    }

    // 因為 Ackermann 函數成長速度非常誇張
    // 所以限制測試範圍，避免程式跑太久或爆掉
    if (m > 3 || n > 6) {

        // 如果 m > 3 或 n > 6，就顯示錯誤訊息
        std::cerr << "Error: demo range is 0 <= m <= 3, 0 <= n <= 6.\n";

        // 結束程式
        return 1;
    }

    // 呼叫「遞迴版本」的 Ackermann
    // static_cast<unsigned>(m) 是把 m 轉成 unsigned 型態
    // 然後把算出來的答案印出來
    std::cout << "Recursive: "
              << ackermannRecursive(static_cast<unsigned>(m), n)
              << '\n';

    // 呼叫「非遞迴版本」的 Ackermann
    // 同樣把 m 轉成 unsigned
    // 最後印出計算結果
    std::cout << "Nonrecursive: "
              << ackermannIterative(static_cast<unsigned>(m), n)
              << '\n';
}
