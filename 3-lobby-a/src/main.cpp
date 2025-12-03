// https://adventofcode.com/2025/day/1

#include <algorithm>
#include <assert.h>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>

// 987654321111111
// 811111111111119
// 234234234234278
// 818181911112111

using namespace std;

struct MaxDigit {
  int val;
  int pos;
};
MaxDigit GetLargestDigit(string_view s) {
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

int GetMaxtJolts(string_view s) {
  // max value digit in whole range except last digit
  auto [firstDigit, firstIndex] = GetLargestDigit(s.substr(0, s.length() - 1));

  // max value digit left of max value digit including the very last digit
  auto [secondDigit, secondIndex] = GetLargestDigit(s.substr(firstIndex + 1));
  return 10 * firstDigit + secondDigit;
}

void RunTests() {
  auto ok_98 = GetMaxtJolts("987654321111111");
  auto ok_54 = GetMaxtJolts("154");
  auto ok_89 = GetMaxtJolts("123456789");
  auto ok_55 = GetMaxtJolts("0555555");
  auto ok_59 = GetMaxtJolts("555519");
  auto ok_99 = GetMaxtJolts("988889");
}

int main() {

  RunTests();

  std::cout << "Current path is " << std::filesystem::current_path() << '\n';
  std::string line;
  std::ifstream file("../../../../batteries.txt");

  int totalJolts{0};

  if (file.is_open()) {
    while (std::getline(file, line)) {
      const int jolts = GetMaxtJolts(line);
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
