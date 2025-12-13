// https://adventofcode.com/2025/day/12

#include <algorithm>
#include <array>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

using namespace std;

struct Pos {
  int x;
  int y;
  Pos operator+(const Pos &other) const {
    return Pos(x + other.x, y + other.y);
  }
};

//  0 1 2
//  3 4 5
//  6 7 8
struct Gift {

  constexpr Gift(array<bool, 9> &&shape) : _shape(std::move(shape)) {}
  auto operator<=>(Gift const &rhs) const = default;

  array<bool, 9> _shape;
  void Print() const {
    printf("\n%c%c%c\n%c%c%c\n%c%c%c\n", _shape.at(0) ? '#' : '.',
           _shape.at(1) ? '#' : '.', _shape.at(2) ? '#' : '.',
           _shape.at(3) ? '#' : '.', _shape.at(4) ? '#' : '.',
           _shape.at(5) ? '#' : '.', _shape.at(6) ? '#' : '.',
           _shape.at(7) ? '#' : '.', _shape.at(8) ? '#' : '.');
  }

  void MirrorV() {
    swap(_shape.at(0), _shape.at(6));
    swap(_shape.at(1), _shape.at(7));
    swap(_shape.at(2), _shape.at(8));
  }
  void MirrorH() {
    swap(_shape.at(0), _shape.at(2));
    swap(_shape.at(3), _shape.at(5));
    swap(_shape.at(6), _shape.at(8));
  }

  void RotateLeft() {
    //  0 1 2         2 5 8
    //  3 4 5   -->   1 4 7
    //  6 7 8         0 3 6
    array<bool, 9> old{_shape};
    _shape.at(0) = old.at(2);
    _shape.at(1) = old.at(5);
    _shape.at(2) = old.at(8);
    _shape.at(3) = old.at(1);
    _shape.at(5) = old.at(7);
    _shape.at(6) = old.at(0);
    _shape.at(7) = old.at(3);
    _shape.at(8) = old.at(6);
  }

  uint GetArrayIndex(const Pos &p) const { return p.y * 3 + p.x; }

  bool IsSolidAt(const Pos &pos) const {
    return 0 != _shape.at(GetArrayIndex(pos));
  }
};

set<Gift> GetAllVariants(const Gift &g) {
  Gift v{g};
  set<Gift> s;
  s.insert(g); // original
  v.RotateLeft();
  s.insert(v); // Rotate 1
  v.RotateLeft();
  s.insert(v); // Rotate 2 (same as mirror H+V)
  v.RotateLeft();
  s.insert(v); // Rotate 3
  v.RotateLeft();
  v.MirrorH();
  s.insert(v); // mirror H
  v.MirrorH();
  v.MirrorV();
  s.insert(v); // mirror V
  return s;
}

//    0:        1:        2:        3:        4:        5:
//    ###       ###       ..#       ###       ..#       ###
//    ###       .#.       .##       ..#       .##       .##
//    ..#       ###       ###       ###       ##.       ##.
constexpr array<Gift, 6> gifts = {
    Gift{{1, 1, 1, 1, 1, 1, 0, 0, 1}}, Gift{{1, 1, 1, 0, 1, 0, 1, 1, 1}},
    Gift{{0, 0, 1, 0, 1, 1, 1, 1, 1}}, Gift{{1, 1, 1, 0, 0, 1, 1, 1, 1}},
    Gift{{0, 0, 1, 0, 1, 1, 1, 1, 0}}, Gift{{1, 1, 1, 0, 1, 1, 1, 1, 0}}};

constexpr array<Pos, 9> allPositionsInShape = {Pos{0, 0}, Pos{1, 0}, Pos{2, 0},
                                               Pos{0, 1}, Pos{1, 1}, Pos{2, 1},
                                               Pos{0, 2}, Pos{1, 2}, Pos{2, 2}};

constexpr array<Pos, 8> surroundingPositions = {
    Pos{-1, -1}, Pos{0, -1}, Pos{1, -1}, Pos{-1, 0},
    Pos{1, 0},   Pos{-1, 1}, Pos{0, 1},  Pos{1, 1}};

struct Region {
  vector<uint> _area;
  uint _placedGifts{0};
  uint _width{0};
  uint _length{0};
  Region(uint width, uint length) : _width(width), _length(length) {
    _area.resize(_length * _width);
    fill(_area.begin(), _area.end(), 0);
  }

  uint GetArrayIndex(const Pos &p) const { return p.y * _width + p.x; }

  Pos GetPos(const uint arrayIndex) const {
    return Pos(arrayIndex % _width, arrayIndex / _width);
  }

  bool IsFree(const Pos &p) const {
    if (p.x >= 0 && p.y >= 0 && p.x < _width && p.y < _length) {
      return _area.at(GetArrayIndex(p)) == 0;
    }
    return false;
  }

  bool IsPosInBound(const Pos &p) const {
    // Respect region border
    return p.x <= _width - 3 && p.y <= _length - 3;
  }

  bool PlaceGift(const Pos &placement, const Gift &g) {
    // p marks the top left corner of the gift
    if (!IsPosInBound(placement)) {
      return false;
    }

    const uint n = ++_placedGifts;
    for (const auto &p : allPositionsInShape) {

      if (!g.IsSolidAt(p)) {
        continue;
      }

      const uint i = GetArrayIndex(placement + p);

      // Collision?
      if (_area.at(i) > 0) {
        return false;
        ;
      }

      _area.at(i) = n;
    }

    return true;
  }

  void Print() {
    printf("\n");
    for (uint y = 0; y < _length; y++) {
      for (uint x = 0; x < _width; x++) {
        printf("%d", _area.at(GetArrayIndex(Pos(x, y))));
      }
      printf("\n");
    }
  }

  uint ScoreRegion() {
    // returns higher score for more and better quality free space in region
    auto getScore = [this](const Pos &p) {
      uint score{0};
      for (const auto &neighbor : surroundingPositions) {
        const Pos neighborToCheck(neighbor + p);
        if (IsFree(neighborToCheck)) {
          ++score;
        }
      }
      return score;
    };

    uint regionScore{0};
    for (uint i = 0; i < _area.size(); ++i) {
      auto p = GetPos(i);
      // printf("Pos (%d, %d)\n", p.x, p.y);
      regionScore += getScore(p);
    }
    return regionScore;
  }
};

void RunTests() {

  {
    Region r(3, 3);
    r.Print();
    uint score = r.ScoreRegion(); // 40
  }
  {
    Region r(8, 5);
    r.Print();
    uint score = r.ScoreRegion(); // 246
  }
  {
    Region r(5, 8);
    r.Print();
    uint score = r.ScoreRegion(); // 246
  }

  Gift g{{1, 1, 1, 0, 1, 0, 1, 1, 1}};
  g.Print();
  g.MirrorH();
  g.Print();
  g.MirrorV();
  g.Print();

  cout << "\n";
  auto x = gifts.at(0);
  x.Print();
  x.MirrorH();
  x.Print();
  x.MirrorH();
  x.Print();
  x.MirrorV();
  x.Print();

  Region r(8, 5);
  r.Print();
  uint score = r.ScoreRegion();
  r.PlaceGift(Pos(1, 1), g);
  r.Print();
  score = r.ScoreRegion();

  for (const auto &g : gifts) {
    printf("-------\n");
    const auto variants = GetAllVariants(g);
    for (const auto v : variants) {
      v.Print();
    }
  }
}

int main() {

  RunTests();

  cout << "Current path is " << filesystem::current_path() << '\n';
  ifstream file("../../../../input.txt");
  string line;

  if (file.is_open()) {
    while (getline(file, line)) {
      const char *delimiters = " ";
      char *token = std::strtok(line.data(), delimiters);
      char *p_end{};
      while (token) {
        ulong value = strtol(token, &p_end, 10);
        if (value > 0) {
          std::cout << value << '\n';
        } else {
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
  cout << "\nsecret: " << secret << "\n";
  return 0;
}
