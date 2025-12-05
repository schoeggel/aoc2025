// https://adventofcode.com/2025/day/5

#include <algorithm>
#include <assert.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

struct R {
  ulong start;
  ulong end;
  bool merged{false};
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
  auto operator<=>(R const &rhs) const = default;
};

bool IsOverlapping(R &lhs, R &rhs) {
  return (lhs.end >= rhs.start && lhs.end <= rhs.end) ||
         (rhs.end >= lhs.start && rhs.end <= lhs.end);
}

void MergeRanges(R &lhs, R &rhs) {
  if (!IsOverlapping(lhs, rhs)) {
    return;
  }
  if (lhs.start == rhs.start && lhs.end == rhs.end) {
    return;
  }
  ulong start = min(lhs.start, rhs.start);
  ulong end = max(lhs.end, rhs.end);
  lhs.start = start;
  rhs.start = start;
  lhs.end = end;
  rhs.end = end;
}

void RunTests() {
  auto s{"12-20"};
  R r1(s);
  R r2("0-100");
  R r3("50-60");
  R r4("100-101");
  R r5("102-200");

  MergeRanges(r1, r2);
  MergeRanges(r2, r3);
  MergeRanges(r3, r4);
  MergeRanges(r4, r5);
}

int main() {

  RunTests();

  vector<R> ranges;

  cout << "Current path is " << filesystem::current_path() << '\n';
  string line;

  {
    ifstream file("../../../../input-ranges.txt");
    if (file.is_open()) {
      while (getline(file, line)) {
        ranges.push_back(R(line));
      }
      cout << "Ranges loaded from file: " << ranges.size() << "\n";
      file.close();
    } else {
      cout << "Error: Unable to open file." << endl;
    }
  }

  cout << "Start" << endl;
  for (auto &lhs : ranges) {
    for (auto &rhs : ranges) {
      MergeRanges(lhs, rhs);
    }
  }

  set<R> unique;
  for (auto &range : ranges) {
    unique.insert(range);
  }

  cout << "unique: " << unique.size() << "\n";

  ulong ids{};
  for (auto range : unique) {
    ids += range.end - range.start + 1;
  }
  cout << "secret: " << ids << "\n";
  return 0;
}
