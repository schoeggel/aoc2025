// https://adventofcode.com/2025/day/5

#include <algorithm>
#include <assert.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

struct R {
  ulong start;
  ulong end;
  R(std::string_view s) {
    auto sep = s.find("-");
    assert(sep < s.length());
    string s1{s.substr(0, sep)};
    string s2{s.substr(sep + 1)};
    char *p_end{};
    start = strtol(s1.data(), &p_end, 10);
    end = strtol(s2.data(), &p_end, 10);
    assert(start <= end);
  }
};

struct Item {
  ulong id;
  Item(const string &s) {
    char *p_end{};
    id = strtol(s.data(), &p_end, 10);
  }
};

bool IsInRange(const Item &item, const R &range) {
  return item.id >= range.start && item.id <= range.end;
}

bool IsInRanges(const Item &item, const vector<R> &ranges) {
  for (const auto &range : ranges) {
    if (IsInRange(item, range)) {
      return true;
    }
  }
  return false;
}

void RunTests() {
  auto s{"12-345"};
  R r(s);
}

int main() {

  RunTests();

  vector<R> ranges;
  vector<Item> items;
  uint freshCounter{};

  std::cout << "Current path is " << std::filesystem::current_path() << '\n';
  std::string line;

  {
    std::ifstream file("../../../../input-ranges.txt");
    if (file.is_open()) {
      while (std::getline(file, line)) {
        ranges.push_back(R(line));
      }
      cout << "Ranges loaded from file: " << ranges.size() << "\n";
      file.close();
    } else {
      std::cout << "Error: Unable to open file." << std::endl;
    }
  }
  {
    std::ifstream file("../../../../input-items.txt");
    if (file.is_open()) {
      while (std::getline(file, line)) {
        items.push_back(Item(line));
      }
      cout << "Items loaded from file: " << items.size() << "\n";
      file.close();
    } else {
      std::cout << "Error: Unable to open file." << std::endl;
    }
  }
 
  for (auto item : items) { 
    if (IsInRanges(item, ranges)) {
     freshCounter++;
    }
  }
  std::cout << "Secret: " << freshCounter << "\n";

  return 0;
}
