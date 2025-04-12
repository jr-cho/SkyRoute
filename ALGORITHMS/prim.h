#ifndef PRIM_H
#define PRIM_H

#include "vector.h"
#include <string>

struct PrimEdge {
    int to;
    int cost;
    PrimEdge* next;
};

struct PrimNode {
    std::string name;
    PrimEdge* head;
};

class PrimGraph {
private:
    Vector<PrimNode> nodes;
    int findIndex(const std::string& name);
public:
    void addNode(const std::string& name);
    void addEdge(const std::string& from, const std::string& to, int cost);
    void buildMST();
};

#endif // PRIM
