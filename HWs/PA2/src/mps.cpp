#include <fstream>
#include <iostream>
#include "chord.h"
using namespace std;
void load(char const*);
int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "usage:\t./mps <input file name> <output file name>";
    return 0;
  }
  load(argv[1]);
}
void load(char const* input) {}