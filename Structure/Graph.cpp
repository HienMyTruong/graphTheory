
#include <iostream>
using namespace std;

class Edge
{
public:
    int source, destination, weight;
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

// a negative cycle is one in which the overall sum of the cycle becomes negative-
// introducing weight in this problem since it has certain applications, especially negative weight in this case
bool isNegativeBellmanFord(Graph *graph, int source)
{

    /* AGORITM: to find if there is a negative weight cycle reachable from the given source
        1. distances from the source is initialized to all vertices as infinite (maxint)
        and distance to the source itself as 0. An array of distances of size abs(V) with
        all values as maxint (infinite) except the value with the sourcevertex-index (distances[source]).

        2. Calculate the shortest distances by doing


    */
    int V = graph->V;
    int E = graph->E;
    int distances[abs(V)];
    // initializing distances from source to all other nodes as infinite
    for (int i = 0; i < V; i++)
    {
        distances[i] = INT_MAX;
    }
    distances[source] = 0;

    for (int i = 1; i <= abs(V) - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int js = graph->edge[j].source;
            int jd = graph->edge[j].destination;
            int weight = graph->edge[j].weight;
            if (distances[js] != INT_MAX && distances[js] + weight < distances[jd])
            {
                distances[jd] = distances[js] + weight;
            }
        }
    }

    for (int i = 0; i < E; i++)
    {
        int js = graph->edge[i].source;
        int jd = graph->edge[i].destination;
        int weight = graph->edge[i].weight;
        if (distances[js] != INT_MAX && distances[js] + weight < distances[jd])
        {
            return true;
        }
    }
    return false;
}

void testIsCycle()
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
}

void testNegativeCycleBellamnFord()
{

    int V = 5;
    int E = 8;
    Graph *graph = createGraph(V, E);

    // adding edge 0-1
    graph->edge[0].source = 0;
    graph->edge[0].destination = 1;
    graph->edge[0].weight = -1;

    // add edge 0-2
    graph->edge[1].source = 0;
    graph->edge[1].destination = 2;
    graph->edge[1].weight = 4;

    // add edge 1-2
    graph->edge[2].source = 1;
    graph->edge[2].destination = 2;
    graph->edge[2].weight = 3;

    // add edge 1-3
    graph->edge[3].source = 1;
    graph->edge[3].destination = 3;
    graph->edge[3].weight = 2;

    // add edge 1-4
    graph->edge[4].source = 1;
    graph->edge[4].destination = 4;
    graph->edge[4].weight = 2;

    // add edge 3-2
    graph->edge[5].source = 3;
    graph->edge[5].destination = 2;
    graph->edge[5].weight = 5;

    // add egde 3-1
    graph->edge[6].source = 3;
    graph->edge[6].destination = 1;
    graph->edge[6].weight = 1;

    // add edge 4-3
    graph->edge[7].source = 4;
    graph->edge[7].destination = 3;
    graph->edge[7].weight = -3;

    if (isNegativeBellmanFord(graph, 0))
        cout << "Yes";
    else
        cout << "No";
}

int main()
{
    // testIsCycle();
    testNegativeCycleBellamnFord();
    return 0;
}
