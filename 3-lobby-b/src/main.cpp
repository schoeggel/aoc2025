// https://adventofcode.com/2025/day/3

#include <assert.h>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// 12 batterien
// 1. zahl : alle ausser (12-1) letzte
// 2. zahl : alle ausser (12-2) letzte
// 12. zahl: alle ausser (12-12) letzte *also den ganzen rest*

struct MaxDigit {
  int val;
  int pos;
};
MaxDigit GetLargestDigit(string_view s) {
  // cout << s << "\n";
  int maxVal{0};
  int indexOfMaxVal{0};
  for (int i = 0; const char &c : s) {
    if (maxVal < c) {
      maxVal = c;
      indexOfMaxVal = i;
    }
    i++;
  }
  return {maxVal - 48, indexOfMaxVal};
}

ulong GetMaxJolts(string_view s) {
  ulong maxJolts{};
  int startPos{0};
  constexpr int MaxBatteries = 12;
  for (int n = 1; n <= MaxBatteries; n++) {
    auto [digit, index] = GetLargestDigit(
        s.substr(startPos, s.length() - MaxBatteries - startPos + n));
    startPos += (index + 1);
    const ulong value = pow(10, MaxBatteries - n) * digit;
    maxJolts += value;
  }
  return maxJolts;
}

void RunTests() {
  assert(GetMaxJolts("987654321111111") == 987654321111);
  assert(GetMaxJolts("811111111111119") == 811111111119);
  assert(GetMaxJolts("234234234234278") == 434234234278);
}

int main() {

  RunTests();

  std::cout << "Current path is " << std::filesystem::current_path() << '\n';
  std::string line;
  std::ifstream file("../../../../batteries.txt");

  ulong totalJolts{0};

  if (file.is_open()) {
    while (std::getline(file, line)) {
      const ulong jolts = GetMaxJolts(line);
      totalJolts += jolts;
      std::cout << line << ": " << jolts << std::endl;
    }
    file.close();
  } else {
    std::cout << "Error: Unable to open file." << std::endl;
  }
  cout << "Total Jolts: " << totalJolts << "\n";
  return 0;
}
