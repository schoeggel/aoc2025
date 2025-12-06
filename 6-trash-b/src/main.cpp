// https://adventofcode.com/2025/day/5

#include <algorithm>
#include <assert.h>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <set>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

uint ReadDigitOrZero(const string &s, uint pos) {
  if (s.length() <= pos) {
    return 0;
  }
  const char offset{'0'};
  return s.at(pos) - offset;
}
vector<ulong> ReadCephalopodNumbers(const vector<string> &human) {

  auto longestNumber = std::max_element(
      human.begin(), human.end(),
      [](const auto &a, const auto &b) { return a.size() < b.size(); });

  vector<ulong> cephalopodNumbers;

  for (auto pos = longestNumber->length(); pos--;) {
    ulong n{0};
    n += 1000 * ReadDigitOrZero(human.at(0), pos);
    n += 100 * ReadDigitOrZero(human.at(1), pos);
    n += 10 * ReadDigitOrZero(human.at(2), pos);
    n += ReadDigitOrZero(human.at(3), pos);
    cephalopodNumbers.push_back(n);
  }
  return cephalopodNumbers;
}

ulong opMultiply(ulong a, ulong b) { return a * b; }

struct Calculation {
  vector<string> s;
  vector<ulong> humanNumbers;
  char op{0};
  ulong debugResult{0};

  ulong Solve() {
    vector<ulong> humanNumbers = ReadCephalopodNumbers(s);
    ulong prod{1};
    if (op == '*') {
      for_each(humanNumbers.begin(), humanNumbers.end(),
               [&prod](ulong i) { prod *= i; });
      debugResult = prod;
      return prod;
    }
    ulong sum{1};
    if (op == '+') {
      for_each(humanNumbers.begin(), humanNumbers.end(),
               [&sum](ulong i) { sum += i; });
      debugResult = sum;
      return sum;
    }
    assert(false);
  }
};

void RunTests() {}

int main() {

  RunTests();

  cout << "Current path is " << filesystem::current_path() << '\n';
  ifstream file("../../../../input.txt");
  string line;
  vector<string> parsedNumbers;
  vector<char> parsedOperators;

  if (file.is_open()) {
    while (getline(file, line)) {
      const char *delimiters = " ";
      char *token = std::strtok(line.data(), delimiters);
      char *p_end{};
      while (token) {
        ulong value = strtol(token, &p_end, 10);
        if (value > 0) {
          string s{token};
          parsedNumbers.push_back(s);
        } else {
          parsedOperators.push_back(*token);
        }
        cout << *token << "\n";
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
    c.s.push_back(parsedNumbers.at(i));
    c.s.push_back(parsedNumbers.at(i + 1 * countCalculations));
    c.s.push_back(parsedNumbers.at(i + 2 * countCalculations));
    c.s.push_back(parsedNumbers.at(i + 3 * countCalculations));
    secret += c.Solve();
    calculations.push_back(c);
  }

  cout << "\nsecret: " << secret << "\n";
  return 0;
}
