#ifndef GRAPH_HEADER_
#define GRAPH_HEADER_
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

#define MAX_INT16 32767
struct Edge {
  int u;
  int v;
  int16_t w;
  Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
  void print() { cout << u << ' ' << v << ' ' << w << '\n'; }
};
struct Vertex {
  int id;
  int16_t key;
  int pi;
  vector<int> Adj;
  Vertex() : id(-1), key(MAX_INT16), pi(-1) {}
  // Vertex(int _id) : id(_id), key(MAX_INT16), pi(-1) {}
  // bool operator==(const Vertex& t) const { return (this->id == t.id); }
};

struct Vertex_ {
  int id;
  int16_t key;
  int pi;
  unordered_set<int> Adj;
  unordered_set<int> pAdj;
  Vertex_(int _id) : id(_id), key(MAX_INT16), pi(-1) {}
  bool operator==(const Vertex& t) const { return (this->id == t.id); }
};

class Graph {
 private:
  bool type;
  int numV, numE;
  vector<Edge> edges;
  // vector<Vertex> vertices;
  Vertex* vertices;
  vector<Vertex_> vertices_;
  vector<Edge*> output;
  long long total_w;

  int** weight;

 public:
  Graph();
  ~Graph();
  void load_data(char const* path);
  void cb();
  void MST_PRIM();
  void GR();
  void dump_file(char const* path);
};

#endif