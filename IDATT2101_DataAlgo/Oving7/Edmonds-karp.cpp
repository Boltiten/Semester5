#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
int c[10][10];
int flowPassed[10][10];
vector<int> g[10];
int parList[10];
int currentPathC[10];
int bfs(int sNode, int eNode) // breadth first search
{
   memset(parList, -1, sizeof(parList));
   memset(currentPathC, 0, sizeof(currentPathC));
   queue<int> q; // declare queue vector
   q.push(sNode);
   parList[sNode] = -1;       // initialize parlist’s source node
   currentPathC[sNode] = 999; // initialize currentpath’s source node
   while (!q.empty())         // if q is not empty
   {
      int currNode = q.front();
      q.pop();
      for (int i = 0; i < g[currNode].size(); i++)
      {
         int to = g[currNode][i];
         if (parList[to] == -1)
         {
            if (c[currNode][to] - flowPassed[currNode][to] > 0)
            {
               parList[to] = currNode;
               currentPathC[to] = min(currentPathC[currNode],
                                      c[currNode][to] - flowPassed[currNode][to]);
               if (to == eNode)
               {
                  return currentPathC[eNode];
               }
               q.push(to);
            }
         }
      }
   }
   return 0;
}
int edmondsKarp(int sNode, int eNode)
{
   int maxFlow = 0;
   while (true)
   {
      int flow = bfs(sNode, eNode);
      if (flow == 0)
      {
         break;
      }
      maxFlow += flow;
      int currNode = eNode;
      while (currNode != sNode)
      {
         int prevNode = parList[currNode];
         flowPassed[prevNode][currNode] += flow;
         flowPassed[currNode][prevNode] -= flow;
         currNode = prevNode;
      }
   }
   return maxFlow;
}
int main()
{
   int nodCount, edCount;
   // finn størrelsen...
   std::string filename = "flytgraf1.txt";
   std::fstream f(filename, std::ios::in);
   int inputNumber;
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
      while (f >> inputNumber)
      {
         // std::cout << inputNumber << " ";
         int from, to, cap;
         from = inputNumber;
         f >> to;
         f >> cap;
         c[from][to] = cap;
         g[from].push_back(to);
         g[to].push_back(from);
      }
   }
   int maxFlow = edmondsKarp(source, sink);
   cout << endl
        << endl
        << "Max Flow is:" << maxFlow << endl;
}