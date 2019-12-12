#ifndef GRAPH_HEADER_
#define GRAPH_HEADER_
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define MAX_INT 2147483647
struct Edge {
  int u;
  int v;
  int w;
  Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
  void print() { cout << u << ' ' << v << ' ' << w << '\n'; }
};
struct Vertex {
  int id;
  int key;
  int pi;
  vector<int> Adj;
  Vertex(int _id) : id(_id), key(MAX_INT), pi(-1) {}
  bool operator==(const Vertex& t) const { return (this->id == t.id); }
};

class Graph {
 private:
  bool type;
  int numV, numE;
  vector<Edge> edges;
  vector<Vertex> vertices;
  vector<int> Q;
  int** weight;

 public:
  Graph();
  ~Graph();
  void load_data(char const* path);
  void MST_PRIM();
};

#endif