#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

void printSubset(const std::vector<std::string>& chosen) {
    std::cout << '{';
    for (std::size_t i = 0; i < chosen.size(); ++i) {
        if (i != 0) std::cout << ", ";
        std::cout << chosen[i];
    }
    std::cout << "}\n";
}

void powerSet(const std::vector<std::string>& elements, std::size_t index,
              std::vector<std::string>& chosen) {
    if (index == elements.size()) {
        printSubset(chosen);
        return;
    }
    // 每個元素有兩種選擇：不加入，或加入目前子集合。
    powerSet(elements, index + 1, chosen);
    chosen.push_back(elements[index]);
    powerSet(elements, index + 1, chosen);
    chosen.pop_back(); // 回溯，還原呼叫前的狀態。
}

int main() {
    int n;
    std::cout << "Number of elements (0-16): ";
    if (!(std::cin >> n) || n < 0 || n > 16) {
        std::cerr << "Error: enter an integer from 0 to 16.\n";
        return 1;
    }
    std::vector<std::string> elements;
    std::unordered_set<std::string> seen;
    std::cout << "Enter distinct elements separated by spaces: ";
    for (int i = 0; i < n; ++i) {
        std::string item;
        if (!(std::cin >> item)) {
            std::cerr << "Error: missing element.\n";
            return 1;
        }
        if (!seen.insert(item).second) {
            std::cerr << "Error: set elements must be distinct.\n";
            return 1;
        }
        elements.push_back(item);
    }
    std::cout << "\nPower set:\n";
    std::vector<std::string> chosen;
    powerSet(elements, 0, chosen);
    std::cout << "Total subsets: " << (1ULL << n) << '\n';
}
