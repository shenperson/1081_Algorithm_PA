#include <iostream>
#include <vector>
int main(int argc, char* argv[]) {
  std::vector<int> a;
  a.push_back(1);
  a.push_back(1);
  a.push_back(1);
  for (auto&& i : a) {
    std::cout << i << '\n';
  }

  std::cout << "HIHI\n";
}