#include <iostream>
#include <list>
#include <string>
#include <fstream>

class Graph
{
    int vertices;
    std::list<int> *adjecents;

public:
    Graph(int vertices)
    {
        this->vertices = vertices;
        adjecents = new std::list<int>[vertices];
    }

    void addEdge(int vertex, int destination)
    {
        adjecents[vertex].push_back(destination);
    }
    void bfs(int start)
    {
        //sett alle veier til "ikke traversert"
        bool *visited = new bool[vertices];
        for (size_t i = 0; i < vertices; i++)
        {
            visited[i] = false;
        }

        std::list<int> queue;
        visited[start] = true;
        queue.push_back(start);

        std::list<int>::iterator i;

        while(!queue.empty())
        {
            start = queue.front();
            std::cout<<start<<" ";
            queue.pop_front();

            for (i = adjecents[start].begin(); i != adjecents[start].end(); ++i)
            {
                if(!visited[*i])
                {
                    visited[*i] = true;
                    queue.push_back(*i);
                }
            }
            
        }        
    }
};


int main ()
{

    std::string filename = "tall.txt";
    std::fstream f(filename, std::ios::in);
    int inputNumber;
    int i = 0;
    int temp = 0;

    Graph g(50);
    if(f.is_open())
    {
        while(f >> inputNumber)
        {
            i++;
            if(!((i%2)==0))
            {
                temp = inputNumber;
            }
            else
            {
                g.addEdge(temp, inputNumber);
                std::cout<<"Added: "<<temp<<" "<<inputNumber<<std::endl;
            }
        }
    }
    
    g.bfs(7);

    f.close();
    return 0;
}