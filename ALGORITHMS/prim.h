#ifndef PRIM_H
#define PRIM_H

#include <vector>

struct PrimEdge {
    int to;
    int cost;
    PrimEdge* next;
};

struct PrimNode {
    char name[4];
    PrimEdge* head;
};

class PrimGraph {
private:
    std::vector<PrimNode> nodes;
    int findIndex(const char* name);
public:
    void addNode(const char* name);
    void addEdge(const char* from, const char* to, int cost);
    void buildMST();
};

#endif // PRIM
