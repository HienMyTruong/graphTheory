
#include <iostream>
using namespace std;

class Edge
{
public:
    int src, dest;
};

// a structure to represent a graph
class Graph
{
public:
    // V-> Number of vertices, E-> Number of edges
    int V, E;

    // graph is represented as an array of edges
    Edge *edge;
};

// Creates a graph with V vertices and E edges
Graph *createGraph(int V, int E)
{
    Graph *graph = new Graph();
    graph->V = V;
    graph->E = E;

    graph->edge = new Edge[graph->E * sizeof(Edge)];

    return graph;
}

// for the unionfind algoritm can be used to check if an undirected graph has a cicle, assuming that it doesn't contain any self loops

int find(int parent[], int index)
{
    if (parent[index] == -1)
    {
        return index;
    }
    return find(parent, parent[index]);
}

void Union(int parent[], int subset1, int subset2)
{
    parent[subset1] = subset2;
}

int isCycle(Graph *graph)
{
    // allocates an amount of memory needed to store the creation of V subsets
    int *parent = new int[graph->V * sizeof(int)];
    // converts value of sizeof(int) * graph->V to unassigned char
    // initialize all subsets as single element sets
    memset(parent, -1, sizeof(int) * graph->V);
}