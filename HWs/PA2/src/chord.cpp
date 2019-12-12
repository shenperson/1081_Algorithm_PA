#include "chord.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#define MAX_INT 32767

Chord::Chord() {}

Chord::~Chord() {
  for (int j = 0; j < 2 * length; ++j) {
    delete[] mis[j];
    delete[] track[j];
  }
  delete[] mis;
  delete[] track;
}

void Chord::load_data(char const* path) {
  ifstream ss(path);
  string s;
  ss >> s;
  length = stoi(s) / 2;
  chords.reserve(length * 2);
  for (int i = 0; i < length; ++i) {
    int t1, t2;
    ss >> s;
    t1 = stoi(s);
    ss >> s;
    t2 = stoi(s);
    chords[t1] = t2;
    chords[t2] = t1;
  }
}

void Chord::MIS() {
  mis = new int*[2 * length];
  track = new int*[2 * length];
  for (int j = 0; j < 2 * length; ++j) {
    int* temp1 = new int[j]();
    int* temp2 = new int[j]();
    fill_n(temp2, j, MAX_INT);
    track[j] = temp1;
    mis[j] = temp2;
  }

  int i = MIS(0, 2 * length - 1);

  back_track(0, 2 * length - 1);
}

int Chord::MIS(int i, int j) {
  if (i >= j) {
    return 0;
  }
  if (mis[j][i] < MAX_INT) {
    return mis[j][i];
  }
  int k = chords.find(j)->second;
  // case 3
  if (k == i && (1 + MIS(i + 1, j - 1)) > MIS(i, j - 1)) {
    mis[j][i] = 1 + MIS(i + 1, j - 1);
    track[j][i] = k;
    return mis[j][i];
  }

  // case 2
  else if (k <= j && k > i &&
           (MIS(i, k - 1) + 1 + MIS(k + 1, j - 1)) > MIS(i, j - 1)) {
    mis[j][i] = MIS(i, k - 1) + 1 + MIS(k + 1, j - 1);
    track[j][i] = k;
    return mis[j][i];
  }
  // case 1
  else {
    mis[j][i] = MIS(i, j - 1);
    track[j][i] = k;
    return mis[j][i];
  }
}

void Chord::back_track(int i, int j) {
  if (i >= j) return;
  int k = track[j][i];

  if (k >= j || k < i || mis[j][i] == mis[j - 1][i]) {
    back_track(i, j - 1);
  } else if (i <= k && k < j) {
    back_track(i, k - 1);
    back_track(k + 1, j - 1);

    output.push_back(k > chords[k] ? chords[k] : k);
  } else {
    output.push_back(k > chords[k] ? chords[k] : k);
    back_track(i + 1, j - 1);
  }
}

void Chord::dump_result(char const* path) {
  ofstream ss(path);
  ss << output.size() << '\n';
  sort(output.begin(), output.end());
  for (const auto& i : output) {
    ss << i << ' ' << chords[i] << '\n';
  }
}
