#ifndef CHORD_HEADER_
#define CHORD_HEADER_
using namespace std;
#include <tuple>
#include <unordered_map>
#include <vector>

class Chord {
 private:
  /* data */
  int length;
  unordered_map<int, int> chords;
  vector<vector<vector<pair<int, int>>>> mis;

 public:
  Chord(/* args */);
  ~Chord();
  void load_data(char const* path);
  void MIS();
};

#endif
