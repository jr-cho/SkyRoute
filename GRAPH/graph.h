#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>

struct Node {
  int weight;
  int pos;

  std::string name;
};

class Graph {
  Node();
  int len;

  public:
    Graph();
    ~Graph();

    void connectNode();

    void display();
};

#endif
