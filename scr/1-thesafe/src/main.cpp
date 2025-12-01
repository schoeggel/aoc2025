// https://adventofcode.com/2025/day/1

#include <assert.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

struct Safe {
  const int _numbers; // 0..99 --> 100 numbers
  int _position{0};
  int _zeroHits{0};

  Safe(int numbers) : _numbers(numbers) {}

  void Turn(int inc) {
    inc = inc % _numbers;
    if (inc < 0) {
      inc = _numbers + inc;
    }
    _position += inc;

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
    assert(safe._position == 97);
    
    safe.Turn(+103);
    assert(safe._position == 0);
    assert(safe._zeroHits == 1);
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

  if (file.is_open()) {
    while (std::getline(file, line)) {
      std::cout << line << std::endl;
    }
    file.close();
  } else {
    std::cout << "Error: Unable to open file." << std::endl;
  }

  return 0;
}
