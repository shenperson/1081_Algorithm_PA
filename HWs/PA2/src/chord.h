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
  vector<vector<vector<pair<int, int>>>> mis_old;
  // vector<vector<int>> mis;
  // vector<vector<int>> track;
  int** mis;
  int** track;
  vector<int> output;

 public:
  Chord(/* args */);
  ~Chord();
  void load_data(char const* path);
  void MIS_old();
  void MIS();
  int MIS(int i, int j);
  void dump_result(char const* path);
  void dump_result_old(char const* path);
  void back_track(int i, int j);
};

#endif
