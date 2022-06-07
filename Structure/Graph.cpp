
#include <iostream>
using namespace std;

class Edge
{
public:
    int source, destination;
};

// a structure to represent a graph
class Graph
{
public:
    // V represents number of vertices, E, number of edges
    int V, E;

    // array of edges
    Edge *edge;
};

// creates a graph with V vertices and E edges
Graph *createGraph(int V, int E)
{
    Graph *graph = new Graph();
    graph->V = V;
    graph->E = E;

    graph->edge = new Edge[graph->E * sizeof(Edge)];

    return graph;
}

// for the unionfind algoritm can be used to check if an undirected graph has a cicle, assuming that it doesn't contain any self loops

// if we have
/*
0
| \
|  \
1---2

and would like to assign parents to each node
we assign every individual node to -1 in out parent array
0   1   2
-1  -1  -1

if we assign 1 as a parent to 0, we change the array value (-1) to the value of the the node (1), such as
0  1  2
1 -1 -1

we do the same when directing 1 to 2
0  1  2
1  2 -1

we only have 2 left, not assigned to any parent. 2 is the parent in this case.
Any index assigned with the value -1 is a parent.

*/
int find(int parent[], int val)
{
    if (parent[val] == -1)
    {
        return val;
    }
    return find(parent, parent[val]);
}

void Union(int parent[], int subset1, int subset2)
{
    parent[subset1] = subset2;
}

bool isCycle(Graph *graph)
{
    // allocates an amount of memory needed to store the creation of V subsets
    int *parent = new int[graph->V * sizeof(int)];
    // converts value of sizeof(int) * graph->V to unassigned char
    // initialize all subsets as single element sets
    memset(parent, -1, sizeof(int) * graph->V);

    for (int i = 0; i < graph->E; ++i)
    {
        int start = find(parent, graph->edge[i].source);
        int finish = find(parent, graph->edge[i].destination);

        if (start == finish)
        {
            return true;
        }
        Union(parent, start, finish);
    }
    return false;
}

int main()
{

    /*
    0
    | \
    |  \
    1---2
    */

    int V = 3;
    int E = 3;
    Graph *graph = createGraph(V, E);

    // add edge 0-1
    graph->edge[0].source = 0;
    graph->edge[0].destination = 1;

    // add edge 1-2
    graph->edge[1].source = 1;
    graph->edge[1].destination = 2;

    // add edge 2-0
    graph->edge[2].source = 2;
    graph->edge[2].destination = 0;

    if (isCycle(graph))
        cout << "contains cycle";
    else
        cout << "doesn't contain cycle";

    return 0;
}
