#include "graph.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "usage:\t./cb <input file name> <output file name>\n";
    exit(-1);
  }
  Graph graph;
  graph.load_data(argv[1]);
  graph.cb();
  graph.dump_file(argv[2]);
}
