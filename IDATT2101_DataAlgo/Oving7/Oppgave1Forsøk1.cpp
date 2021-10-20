#include <iostream>
#include <string>
#include <fstream>
#include <vector>


void gotHere(std::string tag){
    std::cout<<"Got here: " << tag<<std::endl;
}

typedef struct Edge
{
    int weight;
    int destination;
} Edge;
typedef struct Node
{
    int vertex;
    std::vector<Edge> edgesV;
} Node;

Edge *newEdge(Node *n, int w, int d)
{
    
    Edge *edge = (Edge *)malloc(sizeof(Edge));    
    edge->weight = w;
    edge->destination = d;
    return edge;
}
Node *newNode(int v)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->vertex = v;
    node->edgesV.push_back(*newEdge(node, 11, 12));
    return node;
}
class Graph
{
};



int main()
{

    // finn størrelsen...
    std::string filename = "flytgraf1.txt";
    std::fstream f(filename, std::ios::in);
    int inputNumber;
    int vertexes, edges;
    int i = 0;
    int temp = 0;

    if (f.is_open())
    {
        f >> vertexes;
        f >> edges;
    }
    else
    {
        std::cout << "Can't open file by name: " << filename << std::endl;
        return 1;
    }

    if (f.is_open())
    {
        while (f >> inputNumber)
        {
            //std::cout << inputNumber << " ";
            i++;
            if (i == 3)
            {
                i = 0;
                //std::cout << std::endl;
            }
        }
    }
    Graph g;
    Node *n = newNode(10);
    gotHere("After Node");

    for (auto e : n->edgesV)
    {
        std::cout<<"Edge weight: "<<e.weight<<std::endl;
    }
    

    f.close();

    return 0;
}