#include <iostream>       // 載入輸入輸出功能，例如 cin、cout、cerr
#include <string>         // 載入 string，讓我們可以使用字串
#include <unordered_set>  // 載入 unordered_set，用來檢查有沒有輸入重複元素
#include <vector>         // 載入 vector，用來存元素和目前選到的元素


// 這個函式負責把「一個子集合」印出來
// chosen 裡面放的就是目前選到的元素
void printSubset(const std::vector<std::string>& chosen) {

    // 先印出左大括號 {
    std::cout << '{';

    // 從 chosen 的第 0 個元素開始，一個一個印
    for (std::size_t i = 0; i < chosen.size(); ++i) {

        // 如果不是第一個元素
        // 就先印 ", "
        // 例如 {A, B, C}
        if (i != 0) std::cout << ", ";

        // 印出目前第 i 個元素
        std::cout << chosen[i];
    }

    // 所有元素印完後，印出 } 並換行
    std::cout << "}\n";
}


// 這個函式負責用「遞迴」產生所有子集合
//
// elements：原本所有元素
// index：目前正在決定第幾個元素
// chosen：目前已經選進子集合的元素
void powerSet(const std::vector<std::string>& elements,
              std::size_t index,
              std::vector<std::string>& chosen) {

    // 如果 index 已經等於元素總數
    // 代表每個元素都已經決定「選」或「不選」了
    if (index == elements.size()) {

        // 把目前完成的子集合印出來
        printSubset(chosen);

        // 這條路已經走到底了，所以回去上一層
        return;
    }


    // ===== 第一種選擇：不要目前這個元素 =====

    // 不把 elements[index] 加進 chosen
    // 直接處理下一個元素
    powerSet(elements, index + 1, chosen);


    // ===== 第二種選擇：要目前這個元素 =====

    // 把目前元素加入 chosen
    chosen.push_back(elements[index]);

    // 接著處理下一個元素
    powerSet(elements, index + 1, chosen);


    // 把剛剛加入的元素刪掉
    // 這叫「回溯」
    // 目的是把 chosen 恢復成進入這一層之前的樣子
    chosen.pop_back();
}


// 主程式從這裡開始
int main() {

    // n 代表使用者要輸入幾個元素
    int n;

    // 提示使用者輸入元素數量
    std::cout << "Number of elements (0-16): ";

    // std::cin >> n：讀取 n
    //
    // 如果：
    // 1. 輸入失敗
    // 2. n < 0
    // 3. n > 16
    // 任何一個成立，就進入 if
    if (!(std::cin >> n) || n < 0 || n > 16) {

        // 顯示錯誤訊息
        std::cerr << "Error: enter an integer from 0 to 16.\n";

        // 結束程式，1 代表發生錯誤
        return 1;
    }


    // 建立一個 vector
    // 用來存使用者輸入的所有元素
    std::vector<std::string> elements;


    // 建立 unordered_set
    // 用來檢查使用者有沒有輸入重複的元素
    std::unordered_set<std::string> seen;


    // 提示使用者輸入元素
    std::cout << "Enter distinct elements separated by spaces: ";


    // 執行 n 次
    // 也就是讀取 n 個元素
    for (int i = 0; i < n; ++i) {

        // 建立一個字串 item
        // 暫時存目前輸入的元素
        std::string item;


        // 讀取一個元素放進 item
        // 如果讀取失敗，代表輸入的元素數量不夠
        if (!(std::cin >> item)) {

            // 顯示錯誤訊息
            std::cerr << "Error: missing element.\n";

            // 結束程式
            return 1;
        }


        // seen.insert(item)
        // 嘗試把 item 放進 seen
        //
        // .second 會告訴我們「有沒有成功加入」
        //
        // 如果 item 原本不存在：
        // .second == true
        //
        // 如果 item 已經存在：
        // .second == false
        //
        // 前面的 ! 是取反
        // 所以這裡代表「如果元素重複」
        if (!seen.insert(item).second) {

            // 顯示錯誤訊息
            std::cerr << "Error: set elements must be distinct.\n";

            // 結束程式
            return 1;
        }


        // 確定沒有重複後
        // 把這個元素加入 elements
        elements.push_back(item);
    }


    // 印出標題
    // 前面的 \n 代表先換一行
    std::cout << "\nPower set:\n";


    // 建立 chosen
    // 用來記錄「目前這條遞迴路線選了哪些元素」
    //
    // 一開始什麼都還沒選，所以是空的
    std::vector<std::string> chosen;


    // 開始產生 Power Set
    //
    // elements：全部元素
    // 0：從第 0 個元素開始
    // chosen：目前選到的元素
    powerSet(elements, 0, chosen);


    // Power Set 的子集合數量一定是 2^n
    //
    // 1ULL << n
    // 就是把二進位的 1 往左移 n 格
    // 效果等於 2^n
    //
    // 例如：
    // n = 3
    // 1 << 3
    // 0001 → 1000
    // 1000 的十進位就是 8
    std::cout << "Total subsets: " << (1ULL << n) << '\n';
}
