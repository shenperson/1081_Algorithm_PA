#include "graph.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_set>

#define undirected 1
#define directed 0
// for unordered_map
class MyHashFunction {
 public:
  size_t operator()(const Vertex& t) const { return t.id; }
};

Graph::Graph() : total_w(0) {}

Graph::~Graph() {
  for (int i = 0; i < numV; ++i) {
    delete[] weight[i];
  }
  delete[] weight;
}

void Graph::cb() {
  if (type == undirected) MST_PRIM();
}

void Graph::load_data(char const* path) {
  ifstream ss(path);
  string s;
  ss >> s;
  type = (s == "u") ? undirected : directed;
  ss >> s;
  numV = stoi(s);
  ss >> s;
  numE = stoi(s);
  edges.reserve(numE);
  vertices.reserve(numV);

  weight = new int*[numV];
  for (int j = 0; j < numV; ++j) {
    weight[j] = new int[numV]();
  }

  for (int i = 0; i < numV; ++i) vertices.push_back(Vertex(i));
  for (int i = 0; i < numE; ++i) {
    int u, v, w;
    ss >> s;
    u = stoi(s);
    ss >> s;
    v = stoi(s);
    ss >> s;
    w = stoi(s);
    edges.push_back(Edge(u, v, w));
    vertices[u].Adj.push_back(v);
    vertices[v].Adj.push_back(u);
    weight[u][v] = -w;
    weight[v][u] = -w;
  }
}

void Graph::dump_file(char const* path) {
  ofstream ss(path);
  ss << total_w << '\n';
  for (const auto& i : output) {
    ss << i->u << ' ' << i->v << ' ' << i->w << '\n';
  }
}

/* ----- undirected ----- */
void Graph::MST_PRIM() {
  auto comp = [&](int a, int b) { return vertices[a].key > vertices[b].key; };
  vector<int> Q;
  unordered_set<int> Q_map;
  Q.resize(numV, NULL);
  for (int i = 0; i < numV; ++i) {
    Q[i] = i;
    Q_map.insert(i);
  }

  vertices[Q[0]].key = 0;

  while (!Q.empty()) {
    make_heap(Q.begin(), Q.end(), comp);
    pop_heap(Q.begin(), Q.end(), comp);
    Vertex& u = vertices[Q.back()];
    Q.pop_back();
    Q_map.erase(u.id);

    for (auto& v : u.Adj) {
      if (Q_map.find(v) != Q_map.end() && weight[u.id][v] < vertices[v].key) {
        vertices[v].pi = u.id;
        vertices[v].key = weight[u.id][v];
      }
    }
  }
  for (int i = 0; i < numE; ++i) {
    if (vertices[edges[i].u].pi != edges[i].v &&
        vertices[edges[i].v].pi != edges[i].u) {
      output.push_back(&(edges[i]));
      total_w += edges[i].w;
    }
  }
}