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

void AddIds(set<ulong> &freshIds, const R &range) {
  for (ulong id = range.start; id <= range.end; id++) {
    freshIds.insert(id);
  }
}

void RunTests() {
  auto s{"12-20"};
  R r(s);
  set<ulong> ids;
  AddIds(ids, r);
  assert(ids.size() == 20 - 11);
}

int main() {

  RunTests();

  vector<R> ranges;
  set<ulong> freshIds;

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

  for (auto range : ranges) {
    cout << ".";
    AddIds(freshIds, range);
  }
  cout << "Secret: " << freshIds.size() << "\n";

  return 0;
}
