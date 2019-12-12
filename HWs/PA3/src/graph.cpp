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

Graph::Graph() {}

Graph::~Graph() {
  for (int i = 0; i < numV; ++i) {
    delete[] weight[i];
  }
  delete[] weight;
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
  // for (const auto& i : vertices) {
  //   cout << i.id << ':';
  //   for (const auto& v : i.Adj) {
  //     cout << vertices[v].id << ' ';
  //   }
  //   cout << '\n';
  // }
  // cout << "--------\n";
  // for (int i = 0; i < numV; ++i) {
  //   for (int j = 0; j < numV; ++j) cout << weight[i][j] << ' ';
  //   cout << '\n';
  // }
}

void Graph::MST_PRIM() {
  unordered_set<Vertex, MyHashFunction> Q_map;
  auto comp = [&](int a, int b) { return vertices[a].key > vertices[b].key; };
  // Q.assign(vertices.begin(), vertices.end());
  Q.resize(numV, NULL);
  for (int i = 0; i < numV; ++i) {
    Q[i] = i;
  }
  for (const auto& i : Q) {
    Q_map.insert(i);
  }
  vertices[Q[0]].key = 0;
  std::make_heap(Q.begin(), Q.end(), comp);

  while (!Q.empty()) {
    pop_heap(Q.begin(), Q.end(), comp);
    Vertex& u = vertices[Q.back()];
    Q.pop_back();
    Q_map.erase(u);
    cout << u.id << ':';
    for (auto& v : u.Adj) {
      cout << v;
      if (Q_map.find(v) != Q_map.end() && weight[u.id][v] < vertices[v].key) {
        cout << '_';
        vertices[v].pi = u.id;
        vertices[v].key = weight[u.id][v];
      }
      cout << ' ';
    }
    cout << '\n';
  }
  cout << "========\n";
  for (const auto& i : vertices) {
    cout << i.id << " : " << i.pi << '\n';
  }
}