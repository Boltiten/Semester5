#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>

int INF = 100000000;

void printHere(std::string tag){
    std::cout<<"You got here: "<<tag<<std::endl;
}

int n;
std::vector<std::vector<int>> capacity;
std::vector<std::vector<int>> adj;

int bfs(int s, int t, std::vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    std::queue<std::pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = std::min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    printHere("1");
    int flow = 0;
    std::vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main()
{
   int nodCount, edCount;
   // finn størrelsen...
   std::string filename = "flytgraf1.txt";
   std::fstream f(filename, std::ios::in);
   int from, to, cap;
   int i = 0;
   int temp = 0;

   if (f.is_open())
   {
      f >> nodCount >> edCount;
   }
   else
   {
      std::cout << "Can't open file by name: " << filename << std::endl;
      return 1;
   }
   
   int source, sink;
   source = 0;
   sink = 7;
   
   if (f.is_open())
   {
      while (f >> from >> to >> cap)
      {
         capacity[from][to] = cap;
         adj[from].push_back(to);
         adj[to].push_back(from);
      }
   }
   f.close();
   int mf = maxflow(source, sink);
   std::cout << "Max Flow is:" << mf << std::endl;
}