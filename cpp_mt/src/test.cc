#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
class Num {
 public:
  int n_ = 0;
  int val_ = 0;
  Num() {}
  Num(int n, int val) : n_(n), val_(val) {}
  static bool Comparator(Num n1, Num n2) {
    if (n1.n_ == 0) return true;
    if (n2.n_ == 0) return false;
    return (1.0 * n1.val_ / n1.n_) > (1.0 * n2.val_ / n2.n_);
  }
};
std::ostream &operator<<(std::ostream &os, const Num &m) {
  return os << "(" << m.val_ << "/" << m.n_ << ") ";
}
int main() {
  vector<Num> vec{{0, 3}, {2, 0}, {1, 0}, {2, 1}, {0, 4}, {10, 2}};
  sort(vec.begin(), vec.end(), Num::Comparator);
  for (auto elem : vec) {
    cout << elem << endl;
  }

  return 0;
}
