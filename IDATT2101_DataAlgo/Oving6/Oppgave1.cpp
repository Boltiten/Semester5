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
            //std::cout<<start<<" ";

            queue.erase(queue.begin());

            for (i = graph[start].begin(); i != graph[start].end(); ++i)
            {
                    std::cout<<"i: "<<*i<<std::endl;
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
    std::string filename = "L7g1.txt";
    std::fstream f(filename, std::ios::in);
    int inputNumber;
    int i = 0;
    int temp = 0;
    
    Graph g;
    if(f.is_open())
    {
        f>>inputNumber;
    } 
    else 
    {
        std::cout<<"Can't open file by name: "<<filename<<std::endl;
        return 1;
    }
    g.visited.assign(inputNumber,false);
    g.graph.assign(inputNumber, std::vector<int>());
    f>>inputNumber; //skipper tallet om antall kanter..

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
                //std::cout<<"Added: "<<temp<<" "<<inputNumber<<std::endl;
            }
        }
    }
    
    g.bfs(5);

    f.close();

    return 0;
}