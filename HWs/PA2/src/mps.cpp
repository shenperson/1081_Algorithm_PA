#include <iostream>
#include "chord.h"
void load(char const*);
int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "usage:\t./mps <input file name> <output file name>\n";
    return 0;
  }
  Chord chord;
  chord.load_data(argv[1]);
  chord.MIS();
}
