#include "chord.h"
#include <fstream>
#include <iostream>
#include <string>

Chord::Chord(/* args */) {}

Chord::~Chord() {}

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
  //   for (const auto& i : chords) {
  //     cout << i.first << ' ' << i.second << '\n';
  //   }
  //   for (int i = 0; i < length * 2; ++i)
  //     cout << i << ' ' << chords.find(i)->second << '\n';
}

void Chord::MIS() {
  mis.reserve(length * 2);
  for (int j = 0; j < 2 * length; ++j) {
    vector<vector<pair<int, int>>> temp;
    temp.reserve(2 * length);
    for (int i = 0; i < 2 * length; ++i) {
      vector<pair<int, int>> temptemp;
      temp.push_back(temptemp);
    }
    mis.push_back(temp);
  }
  //   for (auto& i : mis) {
  //     for (auto& j : i) cout << j.size() << ' ';
  //     cout << '\n';
  //   }

  for (int j = 0; j < 2 * length; ++j) {
    int k = chords.find(j)->second;
    for (int i = 0; i < j; ++i) {
      if (k > 0 && i <= k && k <= j - 1 &&
          (mis[k - 1][i].size() + 1 + mis[j - 1][k + 1].size() >
           mis[j - 1][i].size())) {
        if (!mis[k - 1][i].empty()) {
          for (const auto& m : mis[k - 1][i]) {
            mis[j][i].push_back(m);
          }
        }
        mis[j][i].push_back(make_pair(k, j));
        if (!mis[j - 1][k + 1].empty()) {
          for (const auto& m : mis[j - 1][k + 1]) {
            mis[j][i].push_back(m);
          }
        }
      }

      else if (k == 0 && i <= k && k <= j - 1 &&
               1 + mis[j - 1][k + 1].size() > mis[j - 1][i].size()) {
        mis[j][i].push_back(make_pair(k, j));
        if (!mis[j - 1][k + 1].empty()) {
          for (const auto& m : mis[j - 1][k + 1]) {
            mis[j][i].push_back(m);
          }
        }
      }

      else {
        if (!mis[j - 1][i].empty())
          for (const auto& m : mis[j - 1][i]) {
            mis[j][i].push_back(m);
          }
      }
      //   cout << "i = " << i << ", j = " << j << ", k = " << k
      //        << ", size = " << mis[j][i].size() << '\n';
    }
  }
  for (const auto& m : mis[length * 2 - 1][0]) {
    cout << m.first << ' ' << m.second << '\n';
  }
}