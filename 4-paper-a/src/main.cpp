// https://adventofcode.com/2025/day/3

#include <array>
#include <assert.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

using namespace std;

constexpr uint PUZZLE_SIZE = 137;

optional<vector<int>> LoadDataFromFile() {
  std::string line;
  std::ifstream file("../../../../input.txt");
  // std::ifstream file("../../../../example.txt");
  if (file.is_open()) {
    vector<int> v;
    ulong col{};
    ulong row{};
    while (std::getline(file, line)) {
      for (auto c : line) {
        if (c == '@') {
          v.push_back(1);
        } else if (c == '.') {
          v.push_back(0);
        } else {
          throw;
        }
      }
    }
    file.close();
    return v;
  }
  return nullopt;
}

struct Point {
  int x;
  int y;
  Point operator+(const Point &other) {
    return Point(x + other.x, y + other.y);
  }
};

static constexpr array<Point, 8> deltasToNearest8{
    {Point(+1, -1), Point(+1, 0), Point(+1, +1), Point(0, +1), Point(-1, +1),
     Point(-1, -0), Point(-1, -1), Point(0, -1)}};

template <uint Columns, uint Rows> struct PaperMap {
  uint _removedPaper{};
  vector<int> _map;
  PaperMap(vector<int> &&data) : _map(std::move(data)) {}

  bool IsInBound(Point p) const {
    return p.x >= 0 && p.y >= 0 && p.x < Columns && p.y < Rows;
  }

  bool IsFree(Point p) const { return _map.at(p.x + p.y * Columns) == 0; }

  vector<Point> GetValidNearest8(Point point) const {
    vector<Point> v;
    for (const auto &delta : deltasToNearest8) {
      if (IsInBound(point + delta)) {
        v.push_back(point + delta);
      }
    }
    return v;
  }

  uint CountAdjacentPaper(Point p) const {
    uint counter{};
    for (auto adjacent : GetValidNearest8(p)) {
      if (!IsFree(adjacent)) {
        counter++;
      }
    }
    return counter;
  }

  void RemovePaper(Point p) {
    _map.at(p.x + p.y * Columns) = 0;
    _removedPaper++;
  }
  uint CountRemovedPaper() const { return _removedPaper; }
  bool ForkLiftCanAccess(Point p) { return CountAdjacentPaper(p) < 4; }
};

void RunTests() {}

int main() {
  auto data = LoadDataFromFile();
  if (!data) {
    return 1;
  }

  PaperMap<PUZZLE_SIZE, PUZZLE_SIZE> map{std::move(data.value())};

  uint progress{};
  do {
    progress = 0;
    for (int y = 0; y < PUZZLE_SIZE; y++) {
      for (int x = 0; x < PUZZLE_SIZE; x++) {
        const Point p{x, y};
        if (map.IsFree(p)) {
          continue;
        }
        if (map.ForkLiftCanAccess(p)) {
          map.RemovePaper(p);
          progress++;
        }
      }
    }
  } while (progress > 0);

  cout << "Result: " << map.CountRemovedPaper() << "\n";

  RunTests();

  return 0;
}
