#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
int INF = 100000000;

int c[20][20];
vector<int> g[20];

int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
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
         c[from][to] = cap;
         g[from].push_back(to);
         g[to].push_back(from);
      }
   }
   f.close();
   int mf = maxflow(source, sink);
   cout << "Max Flow is:" << mf << endl;
}