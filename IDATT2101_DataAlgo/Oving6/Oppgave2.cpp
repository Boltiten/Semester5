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
    void bfs(int start)
    {
        //sett alle veier til "ikke traversert"
        std::vector<int> queue;
        visited[start] = true;
        queue.push_back(start);

        std::vector<int>::iterator i;

        while (!queue.empty())
        {
            start = queue.front();
            std::cout << start << " ";
            queue.erase(queue.begin());

            for (i = graph[start].begin(); i != graph[start].end(); ++i)
            {
                if (!visited[*i])
                {
                    visited[*i] = true;
                    queue.push_back(*i);
                }
            }
        }
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
            visited[i] = false;
        }

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
    }
};

int main()
{

    //finn størrelsen...
    std::string filename = "L7Skandinavia.txt";
    std::fstream f(filename, std::ios::in);
    int inputNumber;
    int i = 0;
    int temp = 0;

    Graph *g = (Graph*)malloc(100000000*sizeof(Graph));
    if (f.is_open())
    {
        f >> inputNumber;
    }
    else
    {
        std::cout << "Can't open file by name: " << filename << std::endl;
        return 1;
    }
    g->visited.assign(inputNumber, false);
    g->graph.assign(inputNumber, std::vector<int>());
    f >> inputNumber; //skipper tallet om antall kanter..
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
                g->addEdge(temp, inputNumber);
                //std::cout << "Added: " << temp << " " << inputNumber << std::endl;
            }
        }
    }

    g->topologicalSort();

    f.close();
    free(g);
    return 0;
}