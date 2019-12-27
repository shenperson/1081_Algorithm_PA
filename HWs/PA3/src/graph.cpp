#include "graph.h"
#include <bits/stdc++.h>
#include <algorithm>
#include <fstream>
#include <set>
#include <string>
#include <unordered_set>
typedef pair<int, int> Pair;
#define undirected 1
#define directed 0

Graph::Graph() : total_w(0) {}

Graph::~Graph() {
  // for (int i = 0; i < numV; ++i) {
  //   delete[] weight[i];
  // }
  // delete[] weight;
}

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
    // vertices.reserve(numV);
    vertices = new Vertex[numV]();
    // for (int i = 0; i < numV; ++i) vertices.push_back(Vertex(i));
    for (int i = 0; i < numV; ++i) vertices[i].id = i;
    // weight = new int*[numV];
    // for (int j = 0; j < numV; ++j) {
    //   weight[j] = new int[numV]();
    // }
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
      // weight[u][v] = -w;
      // weight[v][u] = -w;
    }
    // for (int i = 0; i < numE; ++i) {
    //   cout << i << ' ' << edges[i].u << ' ' << edges[i].v << '\n';
    // }
    // cout << "--------\n";
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
  // cout << "zzz" << endl;
}

void Graph::dump_file(char const* path) {
  ofstream ss(path);
  ss << total_w << '\n';
  for (const auto& i : output) {
    ss << i->u << ' ' << i->v << ' ' << -(i->w) << '\n';
  }
}
// ( key, id )
typedef pair<int, int> Pair;
/* ----- undirected ----- */
void Graph::MST_PRIM() {
  // cout << "zzz" << endl;
  auto comp = [&](int a, int b) { return vertices[a].key > vertices[b].key; };
  // vector<int> Q;
  priority_queue<Pair, vector<Pair>, greater<Pair>> Q;
  bool* Q_map = new bool[numV]();
  // Q.resize(numV, NULL);
  // for (int i = 0; i < numV; ++i) {
  // Q[i] = i;
  // }

  // for (int i = 0; i < numV; ++i) {
  //   cout << i << ": ";
  //   for (auto& j : vertices[i].Adj)
  //     cout << edges[j].u << '_' << edges[j].v << '_' << ' ';
  //   cout << endl;
  // }

  Q.push(make_pair(0, 0));
  vertices[0].key = 0;
  // cout << "zzz" << endl;
  while (!Q.empty()) {
    int u = Q.top().second;
    // cout << u << ' ';
    Q.pop();
    Q_map[u] = 1;
    for (auto& v : vertices[u].Adj) {
      int id = (u == edges[v].v) ? (edges[v].u) : edges[v].v;
      // cout << id;
      if (Q_map[id] == 0 && edges[v].w < vertices[id].key) {
        // cout << "_set_to_" << edges[v].w << '_' << v;
        vertices[id].pi = u;
        vertices[id].key = edges[v].w;
        Q.push(make_pair(edges[v].w, id));
      }
      // cout << ' ';
    }
    // cout << endl;
    // make_heap(Q.begin(), Q.end(), comp);
    // pop_heap(Q.begin(), Q.end(), comp);
    // Vertex& u = vertices[Q.back()];
    // Q.pop_back();
    // Q_map[u.id] = 1;
    // // cout << u.id << ' ';
    // for (auto& v : u.Adj) {
    //   // cout << v << '=';
    //   int id = (u.id == edges[v].v) ? (edges[v].u) : edges[v].v;
    //   // cout << id;
    //   if (Q_map[id] != 1 && edges[v].w < vertices[id].key) {
    //     // cout << '_';
    //     vertices[id].pi = u.id;
    //     vertices[id].key = edges[v].w;
    //   }
    //   // cout << ' ';
    // }
    // // cout << '\n';
  }

  // auto comp = [&](int a, int b) { return vertices[a].key > vertices[b].key;
  // }; vector<int> Q; bool* Q_map = new bool[numV](); Q.resize(numV, NULL); for
  // (int i = 0; i < numV; ++i) {
  //   Q[i] = i;
  // }

  // vertices[Q[0]].key = 0;

  // while (!Q.empty()) {
  //   make_heap(Q.begin(), Q.end(), comp);
  //   pop_heap(Q.begin(), Q.end(), comp);
  //   Vertex& u = vertices[Q.back()];
  //   Q.pop_back();
  //   Q_map[u.id] = 1;

  //   for (auto& v : u.Adj) {
  //     if (Q_map[v] != 1 && weight[u.id][v] < vertices[v].key) {
  //       vertices[v].pi = u.id;
  //       vertices[v].key = weight[u.id][v];
  //     }
  //   }
  // }
  for (int i = 0; i < numE; ++i) {
    if (vertices[edges[i].u].pi != edges[i].v &&
        vertices[edges[i].v].pi != edges[i].u) {
      output.push_back(&(edges[i]));
      total_w -= edges[i].w;
    }
  }
  delete[] Q_map;
}
//////////////////////////////////////////////////////////
void Graph::GR() {
  bool* V_map = new bool[numV]();
  int counter = numV;
  set<int> s1, s2;
  while (counter > 0) {
    for (int i = 0; i < numV; ++i) {
      if (V_map[i] == 0 && vertices_[i].Adj.empty()) {
        --counter;
        V_map[i] = 1;
        s2.insert(i);
        for (const auto& j : vertices_[i].Adj) {
          vertices_[j].pAdj.erase(i);
        }
      }
    }
    for (int i = 0; i < numV; ++i) {
      if (V_map[i] == 0 && vertices_[i].pAdj.empty()) {
        --counter;
        V_map[i] = 1;
        s1.insert(i);
        for (const auto& j : vertices_[i].pAdj) {
          vertices_[j].Adj.erase(i);
        }
      }
    }
    int max = -2147483648, max_id = -2147483648;

    for (int i = 0; i < numV; ++i) {
      if (V_map[i] == 0) {
        int delta = vertices_[i].Adj.size() - vertices_[i].pAdj.size();
        max_id = (delta > max) ? i : max_id;
        max = (delta > max) ? delta : max;
        --counter;
        V_map[i] = 1;
        s1.insert(i);
      }
    }
  }
}