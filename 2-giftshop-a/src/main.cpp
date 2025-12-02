#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <sys/types.h>

using namespace std;

struct IdRange {
  ulong first;
  ulong last;
};

const IdRange ids[] = {{2, 20},
                       {30, 42},
                       {89, 123},
                       {636, 933},
                       {78847, 119454},
                       {7143759788, 7143793713},
                       {9960235, 10043487},
                       {44480, 68595},
                       {23468, 43311},
                       {785189, 1014654},
                       {3829443354, 3829647366},
                       {647009, 692765},
                       {120909, 197026},
                       {5477469, 5677783},
                       {9191900808, 9191943802},
                       {1045643, 1169377},
                       {46347154, 46441299},
                       {2349460, 2379599},
                       {719196, 779497},
                       {483556, 641804},
                       {265244, 450847},
                       {210541, 230207},
                       {195, 275},
                       {75702340, 75883143},
                       {58, 84},
                       {2152, 3237},
                       {3367, 5895},
                       {1552, 2029},
                       {9575, 13844},
                       {6048, 8966},
                       {419388311, 419470147},
                       {936, 1409},
                       {9292901468, 9292987321}};

bool AreHalfesEqual(const string_view &s) {
  if (s.length() % 2 != 0) {
    return false;
  }
  const int mid = s.length() / 2;
  auto left = s.substr(0, mid);
  auto right = s.substr(mid);
  auto result = left.compare(right) == 0;
  // cout << left << " and " << right << " are eq: " << result << "\n";
  return result;
}

void RunTests() {
  {
    AreHalfesEqual("12");
    AreHalfesEqual("123");
    AreHalfesEqual("4545");
    AreHalfesEqual("1234");
    AreHalfesEqual("8899");
    AreHalfesEqual("9292992929");
    AreHalfesEqual("9292992920");
  }
}

int main() {

  RunTests();

  ulong bad{};

  for (const auto &idRange : ids) {
    for (ulong num = idRange.first; num <= idRange.last; num++) {
      const auto numAsText{to_string(num)};
      if (AreHalfesEqual(numAsText)) {
        bad += num;
      }
    }
    cout << ".";
    // cout << bad << "  | " << idRange.first << ".." << idRange.last << "\n";
  }

  cout << "\n bad id sum: " << bad << "\n";
  return 0;
}
