# Homework 1 作業報告

## 第一題：Ackermann Function

##  題目說明

Ackermann Function實作

## 解題策略

這題要使用遞迴和非遞迴兩種方式計算 Ackermann Function。

Ackermann Function 的規則如下：

m = 0 時：

A(m,n) = n + 1

m > 0 且 n = 0 時：

A(m,n) = A(m-1,1)

m > 0 且 n > 0 時：

A(m,n) = A(m-1,A(m,n-1))

這題比較需要注意的是第三種情況，因為裡面還有一個 Ackermann Function，所以要先把裡面的 A(m,n-1) 算完，再把結果放到外面的函數繼續計算。

---

### 2. 遞迴方式

遞迴的寫法比較直接，基本上就是按照題目給的三個公式去判斷。

```cpp
using Value = unsigned long long;

Value ackermannRecursive(unsigned m, Value n) {
    if (m == 0)
        return n + 1;

    if (n == 0)
        return ackermannRecursive(m - 1, 1);

    return ackermannRecursive(
        m - 1,
        ackermannRecursive(m, n - 1)
    );
}
```

例如計算 A(1,2)：

```text
A(1,2) = A(0,A(1,1))
A(1,1) = A(0,A(1,0))
A(1,0) = A(0,1) = 2
A(1,1) = A(0,2) = 3
A(1,2) = A(0,3) = 4
```

所以最後可以得到：

A(1,2) = 4

這種方法的優點是程式很短，而且跟原本的公式很接近，所以比較容易理解。

缺點是當 m 和 n 變大時，遞迴次數會增加得非常快，也會產生很多層函數呼叫。

---

### 3. 非遞迴方式

非遞迴版本不能直接讓函數一直呼叫自己，所以我使用 vector 當作 stack，自己記錄還有哪些計算沒有完成。

```cpp
Value ackermannIterative(unsigned m, Value n) {
    std::vector<unsigned> pending{m};

    while (!pending.empty()) {
        unsigned current = pending.back();
        pending.pop_back();

        if (current == 0) {
            ++n;
        }
        else if (n == 0) {
            n = 1;
            pending.push_back(current - 1);
        }
        else {
            pending.push_back(current - 1);
            pending.push_back(current);
            --n;
        }
    }

    return n;
}
```

這裡比較重要的是 push_back() 的順序。

因為 stack 是後進先出，所以遇到：

A(m-1,A(m,n-1))

要先放入外面的 m-1，再放入裡面的 m。

這樣下一次迴圈才會先處理裡面的 A(m,n-1)，等裡面的結果算完之後，再繼續處理外面的部分。

以 A(1,2) 為例：

步驟 0：
pending = [1]
n = 2

步驟 1：
pending = [0,1]
n = 1

步驟 2：
pending = [0,0,1]
n = 0

步驟 3：
pending = [0,0,0]
n = 1

步驟 4：
pending = [0,0]
n = 2

步驟 5：
pending = [0]
n = 3

步驟 6：
pending = []
n = 4

當 pending 清空時，代表所有計算都已經完成，所以最後回傳 n = 4。

---

### 4. 輸入與輸出

主程式會先讀取 m 和 n，再把同一組資料分別交給遞迴版本和非遞迴版本。

目前程式限制：

0 <= m <= 3

0 <= n <= 6

這個限制主要是避免 Ackermann Function 的運算量變得太大，不是 Ackermann Function 本身只能計算到這裡。

例如輸入：

```text
3 4
```

輸出：

```text
Recursive: 125
Nonrecursive: 125
```

可以看到兩種方法算出來的答案相同。

---

### 5. 時間與空間

Ackermann Function 的成長速度很快。

幾個比較簡單的公式如下：

m = 0：

A(0,n) = n + 1

m = 1：

A(1,n) = n + 2

m = 2：

A(2,n) = 2n + 3

m = 3：

A(3,n) = 2^(n+3) - 3

雖然函數的答案可能看起來沒有非常大，但是實際計算的過程會產生很多次函數呼叫。

遞迴版本使用系統本身的函數呼叫 stack，而非遞迴版本則是使用 vector 自己模擬 stack。

所以兩種方法最後得到的答案一樣，主要差別是在於怎麼保存還沒有完成的計算。

---

### 6. 測試結果

我使用不同的 m 和 n 測試兩個版本。

```text
m=0, n=0
Recursive: 1
Nonrecursive: 1

m=1, n=2
Recursive: 4
Nonrecursive: 4

m=2, n=3
Recursive: 9
Nonrecursive: 9

m=3, n=0
Recursive: 5
Nonrecursive: 5

m=3, n=4
Recursive: 125
Nonrecursive: 125

m=3, n=6
Recursive: 509
Nonrecursive: 509
```

測試結果中，遞迴和非遞迴版本都得到相同的答案。

另外也測試了錯誤輸入，例如負數、超過設定範圍以及輸入非數字內容，程式都會顯示錯誤訊息。

---

## 第二題：Power Set

### 1. 題目說明

這題要使用遞迴的方法，把一個集合的所有子集合列出來。

例如集合：

S = {a,b,c}

它的子集合包含：

```text
{}
{a}
{b}
{c}
{a,b}
{a,c}
{b,c}
{a,b,c}
```

每個元素都有「選」和「不選」兩種可能，所以如果集合裡面有 n 個元素，總共會有：

2^n

個子集合。

---

### 2. 解題方法

我的做法是從第一個元素開始，每次都分成兩種情況：

1. 不選目前這個元素
2. 選目前這個元素

然後繼續處理下一個元素。

使用 chosen 來記錄目前已經選了哪些元素。

當 index 等於 elements.size() 時，代表所有元素都已經決定完成，這時就把 chosen 印出來。

---

### 3. 程式實作

產生 Power Set 的主要程式如下：

```cpp
void powerSet(const std::vector<std::string>& elements,
              std::size_t index,
              std::vector<std::string>& chosen) {

    if (index == elements.size()) {
        printSubset(chosen);
        return;
    }

    powerSet(elements, index + 1, chosen);

    chosen.push_back(elements[index]);
    powerSet(elements, index + 1, chosen);

    chosen.pop_back();
}
```

其中：

```cpp
powerSet(elements, index + 1, chosen);
```

代表不選目前的元素。

接著：

```cpp
chosen.push_back(elements[index]);
```

把目前的元素加入 chosen，代表選擇這個元素。

再呼叫一次 powerSet()，繼續處理下一個元素。

最後：

```cpp
chosen.pop_back();
```

把剛剛加入的元素移除。

這一步很重要，因為如果沒有把元素移除，上一條路徑選到的元素就會留在 chosen 裡面，影響下一條路徑的結果。

這個過程就是回溯。

---

### 4. 簡單範例

假設輸入：

S = {a,b}

a 有選和不選兩種情況，b 也有選和不選兩種情況。

所以會得到：

```text
a不選、b不選 -> {}
a不選、b選   -> {b}
a選、b不選   -> {a}
a選、b選     -> {a,b}
```

總共有：

2^2 = 4

個子集合。

---

### 5. 執行結果

例如輸入：

```text
3
a b c
```

程式輸出：

```text
{}
{c}
{b}
{b, c}
{a}
{a, c}
{a, b}
{a, b, c}

Total subsets: 8
```

因為輸入了 3 個元素，所以子集合數量為：

2^3 = 8

符合預期結果。

---

### 6. 時間與空間

每一個元素都有選和不選兩種可能，所以 n 個元素會產生 2^n 個子集合。

因為最後還需要把每個子集合的內容印出來，所以時間複雜度可以寫成：

O(n * 2^n)

遞迴最多會進入 n 層，而 chosen 最多也只會存放 n 個元素，所以額外空間大約是：

O(n)

這個程式沒有把全部的子集合一次存在記憶體裡，而是每產生一個子集合就直接輸出。

---

### 7. 測試結果

我測試了不同大小的集合：

```text
n=0 -> 1 個子集合
n=1 -> 2 個子集合
n=2 -> 4 個子集合
n=3 -> 8 個子集合
n=8 -> 256 個子集合
```

產生的數量都有符合 2^n。

另外也測試了一些錯誤輸入：

```text
重複元素 -> 顯示錯誤
n < 0 -> 顯示錯誤
n > 16 -> 顯示錯誤
輸入非數字的 n -> 顯示錯誤
輸入的元素數量不足 -> 顯示錯誤
```

程式都可以正常判斷。

---

## 總結

第一題主要是練習遞迴和非遞迴的差別。

遞迴版本可以直接按照 Ackermann Function 的公式寫，所以程式比較簡單。非遞迴版本則需要自己使用 vector 模擬 stack，記錄還沒有完成的計算。

第二題是利用遞迴產生 Power Set。每一個元素都有選和不選兩種情況，再利用 push_back() 和 pop_back() 記錄目前選到的元素。

做完這兩題後，我比較能理解遞迴在程式裡實際執行的方式，也比較清楚 stack 和回溯的用途。
