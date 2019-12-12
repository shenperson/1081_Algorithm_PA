#ifndef CHORD_HEADER_
#define CHORD_HEADER_
using namespace std;
#include <tuple>
#include <unordered_map>

class Chord {
 private:
  int length;
  unordered_map<int, int> chords;
  int** mis;
  int** track;
  vector<int> output;

  int MIS(int i, int j);

 public:
  Chord();
  ~Chord();
  void load_data(char const* path);
  void dump_result(char const* path);
  void MIS();
  void back_track(int i, int j);
};

#endif
