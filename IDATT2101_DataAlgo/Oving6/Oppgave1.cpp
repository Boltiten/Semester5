#include <iostream>
#include <vector>
#include <fstream>
#include <string>

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

        while(!queue.empty())
        {
            start = queue.front();
            std::cout<<start<<" ";
            queue.erase(queue.begin());

            for (i = graph[start].begin(); i != graph[start].end(); ++i)
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

int main()
{

    //finn størrelsen...
    Graph g;
    g.visited.assign(50,false);
    g.graph.assign(50, std::vector<int>());

    std::string filename = "tall.txt";
    std::fstream f(filename, std::ios::in);
    int inputNumber;
    int i = 0;
    int temp = 0;

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
    
    g.bfs(1);

    f.close();

    return 0;
}