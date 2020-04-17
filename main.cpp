#include <bitset>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
#include <vector>

class data {
  double x, y;
  std::string message;

  data(double a, double b, std::string m) : x(a), y(b), message(m) {}

  double dividing(double x, double y) {
    if (y == 0)
      throw data(x, y, "dividing on zero");
    if (x < 0 || y < 0)
      throw data(x, y, "negative result");
    return x/y;
  }
};

int main() {
  // gen div for std::out_of_range
  std::vector<int> vec(2);
  try {
    vec.at(3) = 100;
  } catch (const std::out_of_range &oor) {
    std::cerr << "Out of Range " << oor.what() << '\n';
  }

  // gen div for length_error

  try {
    std::vector<int> vec;
    vec.resize(vec.max_size() + 1);
  } catch (const std::length_error &le) {
    std::cerr << "Length error: " << le.what() << '\n';
  }

  // gen div for invalid_argument

  try {
    std::bitset<5> bit(std::string("01234"));
  } catch (const std::invalid_argument &ia) {
    std::cerr << "Invalid argument: " << ia.what() << '\n';
  }

  // gen div for bad_cast

  struct S1 {
    virtual ~S1() {}
  };
  struct S2 {
    virtual ~S2() {}
  };
  S2 b;
  try {
    S1 &f = dynamic_cast<S1 &>(b);
  } catch (const std::bad_cast &e) {
    std::cout << e.what() << '\n';
  }

  // gen div for bad_alloc

  try {
    while (true) {
      new int[100000000ul];
    }
  } catch (const std::bad_alloc &e) {
    std::cout << "Allocation failed: " << e.what() << '\n';
  }

  return 0;
}
