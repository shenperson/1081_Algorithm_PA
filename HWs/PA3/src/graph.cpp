#include "graph.h"
#include <bits/stdc++.h>
// #include <algorithm>
#include <deque>
#include <fstream>
// #include <set>
#include <string>
// #include <unordered_set>
#define undirected 1
#define directed 0

typedef pair<int, int> Pair;
Graph::Graph() : total_w(0) {}

Graph::~Graph() {}

void Graph::cb() {
  if (type == undirected)
    MST_PRIM();
  else
    GR();
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
  if (type == undirected) {
    edges.reserve(numE);
    vertices = new Vertex[numV]();
    for (int i = 0; i < numV; ++i) vertices[i].id = i;
    for (int i = 0; i < numE; ++i) {
      int u, v, w;
      ss >> s;
      u = stoi(s);
      ss >> s;
      v = stoi(s);
      ss >> s;
      w = stoi(s);
      edges.push_back(Edge(u, v, -w));
      vertices[u].Adj.push_back(i);
      vertices[v].Adj.push_back(i);
    }
  } else {
    edges.reserve(numE);
    vertices_.reserve(numV);
    for (int i = 0; i < numV; ++i) vertices_.push_back(Vertex_(i));
    weight = new int*[numV];
    for (int j = 0; j < numV; ++j) {
      weight[j] = new int[numV]();
    }
    for (int i = 0; i < numE; ++i) {
      int u, v, w;
      ss >> s;
      u = stoi(s);
      ss >> s;
      v = stoi(s);
      ss >> s;
      w = stoi(s);
      edges.push_back(Edge(u, v, w));
      vertices_[u].Adj.insert(v);
      vertices_[v].pAdj.insert(u);
      weight[u][v] = w;
    }
  }
}

void Graph::dump_file(char const* path) {
  ofstream ss(path);
  ss << total_w << '\n';
  if (type == undirected)
    for (const auto& i : output) {
      ss << i->u << ' ' << i->v << ' ' << -(i->w) << '\n';
    }
  else
    for (const auto& i : output) {
      ss << i->u << ' ' << i->v << ' ' << i->w << '\n';
    }
}

/* ----- undirected ----- */
void Graph::MST_PRIM() {
  auto comp = [&](int a, int b) { return vertices[a].key > vertices[b].key; };
  priority_queue<Pair, vector<Pair>, greater<Pair>> Q;
  bool* Q_map = new bool[numV]();
  Q.push(make_pair(0, 0));
  vertices[0].key = 0;
  while (!Q.empty()) {
    int u = Q.top().second;
    Q.pop();
    Q_map[u] = 1;
    for (auto& v : vertices[u].Adj) {
      int id = (u == edges[v].v) ? (edges[v].u) : edges[v].v;
      if (Q_map[id] == 0 && edges[v].w < vertices[id].key) {
        vertices[id].pi = u;
        vertices[id].key = edges[v].w;
        Q.push(make_pair(edges[v].w, id));
      }
    }
  }
  for (int i = 0; i < numE; ++i) {
    if (vertices[edges[i].u].pi != edges[i].v &&
        vertices[edges[i].v].pi != edges[i].u) {
      output.push_back(&(edges[i]));
      total_w -= edges[i].w;
    }
  }
  delete[] Q_map;
}
/* ----- directed ----- */
void Graph::GR() {
  bool* V_map = new bool[numV]();
  int counter = numV;
  deque<int> s1, s2;
  while (counter > 0) {
    for (int i = 0; i < numV; ++i) {
      if (V_map[i] == 0 && vertices_[i].Adj.empty()) {
        --counter;
        V_map[i] = 1;
        s2.push_front(i);
        for (const auto& j : vertices_[i].Adj) {
          vertices_[j].pAdj.erase(i);
        }
        for (const auto& j : vertices_[i].pAdj) {
          vertices_[j].Adj.erase(i);
        }
      }
    }
    for (int i = 0; i < numV; ++i) {
      if (V_map[i] == 0 && vertices_[i].pAdj.empty()) {
        --counter;
        V_map[i] = 1;

        s1.push_back(i);
        for (const auto& j : vertices_[i].pAdj) {
          vertices_[j].Adj.erase(i);
        }

        for (const auto& j : vertices_[i].Adj) {
          vertices_[j].pAdj.erase(i);
        }
      }
    }
    int max = -2147483648, max_id = -2147483648;

    for (int i = 0; i < numV; ++i) {
      if (V_map[i] == 0) {
        int delta = 0;
        for (auto& adj : vertices_[i].Adj) {
          delta += weight[i][adj];
        }
        for (auto& padj : vertices_[i].pAdj) {
          delta -= weight[padj][i];
        }
        max_id = (delta > max) ? i : max_id;
        max = (delta > max) ? delta : max;
      }
    }
    if (counter <= 0) break;
    --counter;
    V_map[max_id] = 1;
    s1.push_back(max_id);
    if (!vertices_[max_id].Adj.empty()) {
      for (const auto& j : vertices_[max_id].Adj) {
        vertices_[j].pAdj.erase(max_id);
      }
    }
    if (!vertices_[max_id].pAdj.empty())
      for (const auto& j : vertices_[max_id].pAdj) {
        vertices_[j].Adj.erase(max_id);
      }
  }
  // for (auto& i : s1) cout << i << ' ';
  // for (auto& i : s2) cout << i << ' ';
  // cout << endl;
  // s1 <- {s1,s2}
  for (auto& i : s2) s1.push_back(i);
  int* order = new int[numV]();

  for (int i = 0; i < numV; ++i) {
    order[s1[i]] = i;
  }

  for (int i = 0; i < numE; ++i) {
    if (order[edges[i].u] > order[edges[i].v]) {
      output.push_back(&(edges[i]));
      total_w += edges[i].w;
    }
  }
  for (int i = 0; i < numV; ++i) {
    delete[] weight[i];
  }
  delete[] weight;
  delete[] order;
}