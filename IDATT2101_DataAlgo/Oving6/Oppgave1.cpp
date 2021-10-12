#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>

class Graph
{   
public:
    std::vector<bool> visited;
    std::vector<std::vector<int>> graph;
    void addEdge(int vertex, int destination)
    {
        graph[vertex].push_back(destination);
    }
    void bfs(int start, int nodes)
    {
        //sett alle veier til "ikke traversert"
        std::queue<int> queue;
        visited[start] = true;
        queue.push(start);

        int* dist = new int[nodes];
        dist[start] = 0;
        int* prev = new int[nodes];
        prev[start] = start;

        while(!queue.empty())
        {
            start = queue.front();
            std::cout<<start<<" ";
            queue.pop();

            for (int i = 0; i < graph[start].size(); ++i)
            {
                int b = graph[start][i];
                if(!visited[b]){
                    queue.push(b);
                    dist[b] = dist[start]+1;
                    prev[b] = start;
                    visited[b] = true;
                }
            }            
        }
        std::cout<<std::endl;
        std::cout<< "Nodes"<< "  "<< "Prev" << "  " << "Dist" <<std::endl;
        for (size_t i = 0; i < nodes; i++)
        {
            if(visited[i]){
                std::cout<<"  "<< i << "     " << prev[i] << "     " << dist[i] <<std::endl;
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
        std::cout<<"Can't open file by name: "<<filename<<std::endl;
        return 1;
    }
    g.visited.assign(edges,false);
    g.graph.assign(edges, std::vector<int>());

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
    g.bfs(5, vertexes);

    f.close();

    return 0;
}