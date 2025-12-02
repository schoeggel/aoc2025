// https://adventofcode.com/2025/day/1

#include <algorithm>
#include <assert.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

struct Safe {
  const int _numbers; // 0..99 --> 100 numbers
  int _position{50}; // dial starts pointing at 50
  int _zeroHits{0};

  Safe(int numbers) : _numbers(numbers) {}

  void Turn(int inc) {
    _position += inc;
    _position = _position % _numbers;

    if (_position < 0) {
      _position = _numbers + _position;
    }

    if (_position == 0) {
      _zeroHits++;
    }
  }

  int getHits() { return _zeroHits; }
};

bool RunTests() {
  {
    Safe safe{10};
    safe.Turn(12);
    assert(safe._position == 2);
  }
  {
    Safe safe{10};
    safe.Turn(1001);
    assert(safe._position == 1);
  }
  {
    Safe safe{10};
    safe.Turn(-12);
    assert(safe._position == 8);
  }
  {
    Safe safe{10};
    safe.Turn(-103);
    assert(safe._position == 7);
  }
  {
    Safe safe{100};
    safe.Turn(-103);
    assert(safe._position == 47);
    safe.Turn(+103);
    assert(safe._position == 50);
    assert(safe._zeroHits == 0);
    safe.Turn(+50);
    assert(safe._position == 0);
    assert(safe._zeroHits == 1);
    safe.Turn(-260);
    assert(safe._position == 40);
    safe.Turn(+60);
    assert(safe._position == 0);
    assert(safe._zeroHits == 2);
    safe.Turn(+0);
    assert(safe._position == 0);
    assert(safe._zeroHits == 3);
  }

  return true;
}

int main() {

  if (!RunTests()) {
    return 1;
  }

  std::cout << "Current path is " << std::filesystem::current_path() << '\n';
  std::string line;
  std::ifstream file("../../../../rotations.txt");

  Safe safe{100};

  if (file.is_open()) {
    while (std::getline(file, line)) {
      std::replace(line.begin(), line.end(), 'L', '-');
      std::replace(line.begin(), line.end(), 'R', '+');
      auto inc = std::stoi(line);
      std::cout << inc << std::endl;
      safe.Turn(inc);
    }
    file.close();
  } else {
    std::cout << "Error: Unable to open file." << std::endl;
  }

  std::cout << "Secret: " << safe.getHits() << "\n";

  return 0;
}
