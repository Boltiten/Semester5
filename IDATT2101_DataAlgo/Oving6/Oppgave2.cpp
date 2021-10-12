#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stack>

class Graph
{
public:
    std::vector<bool> visited;
    std::vector<std::vector<int>> graph;
    void addEdge(int vertex, int destination)
    {
        graph[vertex].push_back(destination);
    }

    void topologicalSortUtil(int start, std::stack<int> &Stack)
    {
        visited[start] = true;

        std::vector<int>::iterator i;
        for (i = graph[start].begin(); i != graph[start].end(); ++i)
        {
            if (!visited[*i])
            {
                topologicalSortUtil(*i, Stack);
            }
        }

        Stack.push(start);
    }
    void topologicalSort()
    {
        std::stack<int> Stack;

        for (int i = 0; i < visited.size(); i++)
        {
            if (visited[i] == false)
            {
                topologicalSortUtil(i, Stack);
            }
        }
            

        while (Stack.empty() == false)
        {
            std::cout << Stack.top() << " ";
            Stack.pop();
        }
        std::cout<<std::endl;
    }
};

int main()
{

    //finn størrelsen...
    std::string filename = "L7g5.txt";
    std::fstream f(filename, std::ios::in);
    int inputNumber;
    int vertexes, edges;
    int i = 0;
    int temp = 0;

    Graph g;
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
    g.visited.assign(vertexes, false);
    g.graph.assign(edges, std::vector<int>());
    std::cout<<"Assign ferdig"<<std::endl;
    if (f.is_open())
    {
        while (f >> inputNumber)
        {
            i++;
            if (!((i % 2) == 0))
            {
                temp = inputNumber;
            }
            else
            {
                g.addEdge(temp, inputNumber);
                //std::cout << "Added: " << temp << " " << inputNumber << std::endl;
            }
        }
    }
    std::cout<<"Ferdig å legge til tall"<<std::endl;
    g.topologicalSort();
    std::cout<<"Sort ferdig"<<std::endl;
    f.close();
    return 0;
}