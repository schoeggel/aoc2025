#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <vector>

using namespace std;

struct IdRange {
  ulong first;
  ulong last;
};
// max 10 ziffern
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

vector<int> GetDenominators(int digitcount) {
  switch (digitcount) {
  case 1:
    return vector<int>{1};
  case 2:
    return vector<int>{2};
  case 3:
    return vector<int>{3};
  case 4:
    return vector<int>{2, 4};
  case 5:
    return vector<int>{5};
  case 6:
    return vector<int>{2, 3, 6};
  case 7:
    return vector<int>{7};
  case 8:
    return vector<int>{2, 4, 8};
  case 9:
    return vector<int>{3, 9};
  case 10:
    return vector<int>{2, 5, 10};
  default:
    return vector<int>{1};
  }
}

bool ArePartsEqual(const string_view &s, int parts) {
  if (parts <= 1) {
    return false;
  }
  assert(s.length() % parts == 0);
  const auto chunklength = s.length() / parts;

  vector<string_view> views;
  for (int pos = 0; pos < s.length(); pos += chunklength) {
    views.push_back(s.substr(pos, chunklength));
  }

  for (const auto &chunk : views) {

    auto areChunksEqual = chunk.compare(views.at(0)) == 0;
    if (!areChunksEqual) {
      return false;
    }
  }
  cout << s << ": All chunks are equal, this is a bad id.\n";
  return true;
}

bool process(const string_view &s) {
  // basierend auf der lange entscheiden auf wieviele teile zu pruefen
  auto dens = GetDenominators(s.length());
  for (const auto &parts : dens) {
    if (ArePartsEqual(s, parts)) {
      return true;
    }
  }
  return false;
}

void RunTests() {
  {
    ArePartsEqual("9292992920", 1);
    ArePartsEqual("12", 2);
    ArePartsEqual("4545", 2);
    ArePartsEqual("1234", 2);
    ArePartsEqual("8899", 2);
    ArePartsEqual("9292992929", 2);
    ArePartsEqual("121212", 2);
    ArePartsEqual("121212", 3);
  }
}

int main() {

  RunTests();

  ulong bad{};

  for (const auto &idRange : ids) {
    for (ulong num = idRange.first; num <= idRange.last; num++) {
      const auto numAsText{to_string(num)};
      if (process(numAsText)) {
        bad += num;
      }
    }
    cout << ".";
    // cout << bad << "  | " << idRange.first << ".." << idRange.last << "\n";
  }

  cout << "\n bad id sum: " << bad << "\n";
  return 0;
}
