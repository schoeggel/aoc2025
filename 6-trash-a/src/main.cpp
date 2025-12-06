// https://adventofcode.com/2025/day/5

#include <algorithm>
#include <assert.h>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
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

struct Calculation {
  vector<ulong> v;
  char op{0};

  ulong Solve() {
    if (op == '*') {
      return v.at(0) * v.at(1) * v.at(2) * v.at(3);
    }
    if (op == '+') {
      return v.at(0) + v.at(1) + v.at(2) + v.at(3);
    }
    assert(false);
  }
};

void RunTests() {}

int main() {

  RunTests();

  vector<R> ranges;

  cout << "Current path is " << filesystem::current_path() << '\n';
  ifstream file("../../../../input.txt");
  string line;
  vector<ulong> parsedNumbers;
  vector<char> parsedOperators;

  if (file.is_open()) {
    while (getline(file, line)) {
      const char *delimiters = " ";
      char *token = std::strtok(line.data(), delimiters);
      char *p_end{};
      while (token) {
        ulong value = strtol(token, &p_end, 10);
        if (value > 0) {
          parsedNumbers.push_back(value);
          std::cout << value << '\n';
        } else {
          parsedOperators.push_back(*token);
          cout << *token << "\n";
        }
        token = std::strtok(nullptr, delimiters);
      }
    }
    file.close();

  } else {
    cout << "Error: Unable to open file." << endl;
  }
  ulong secret{0};
  vector<Calculation> calculations;
  const uint countCalculations = parsedOperators.size();
  for (uint i = 0; i < countCalculations; i++) {
    Calculation c;
    c.op = parsedOperators.at(i);
    c.v.push_back(parsedNumbers.at(i));
    c.v.push_back(parsedNumbers.at(i + 1 * countCalculations));
    c.v.push_back(parsedNumbers.at(i + 2 * countCalculations));
    c.v.push_back(parsedNumbers.at(i + 3 * countCalculations));
    // cout << c.Solve() << " ";
    secret += c.Solve();
    calculations.push_back(c);
  }

  cout << "\nsecret: " << secret << "\n";
  return 0;
}
