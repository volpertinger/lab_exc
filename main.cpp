#include <bitset>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
#include <vector>

class mem_lick {
  int *arr;

public:
  mem_lick() { arr = new int[10]; }
};

class mem_lick_fix {
  int *arr;

public:
  ~mem_lick_fix() { delete arr; }
  mem_lick_fix() { arr = new int[10]; }
};

class exception {
  std::string message;

public:
  exception(std::string error) : message(error) {}
  std::string get_error() { return message; }
};

class ages {
  int list[5];

public:
  ages() {}
  int get_len() { return 5; };
  void set_age(int age, int index) {
    if (age < 0)
      throw exception("invalid age");
    if (index > 4)
      throw exception("invalid index");
    list[index] = age;
  }
};

int main() {
  // gen exc for std::out_of_range

  std::vector<int> vec(2);
  try {
    vec.at(3) = 100;
  } catch (const std::out_of_range &oor) {
    std::cerr << "Out of Range " << oor.what() << '\n';
  }

  // gen exc for length_error

  try {
    std::vector<int> vec;
    vec.resize(vec.max_size() + 1);
  } catch (const std::length_error &le) {
    std::cerr << "Length error: " << le.what() << '\n';
  }

  // gen exc for invalid_argument

  try {
    std::bitset<5> bit(std::string("01234"));
  } catch (const std::invalid_argument &ia) {
    std::cerr << "Invalid argument: " << ia.what() << '\n';
  }

  // gen exc for bad_cast

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
    std::cerr << e.what() << '\n';
  }

  // gen exc for bad_alloc

  try {
    while (true) {
      new int[100000000ul];
    }
  } catch (const std::bad_alloc &e) {
    std::cerr << "Allocation failed: " << e.what() << '\n';
  }

  // gen exc for my exc class

  ages list;
  try {
    list.set_age(5, 6);
  } catch (exception &exc) {
    std::cerr << "error: " << exc.get_error() << "\n";
  }

  // lick of memory

  mem_lick lick;

  // no lick of memory

  mem_lick_fix no_lick;

  return 0;
}
