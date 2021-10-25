#include <cstdio>
#include <queue>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


int c[255][255];
int flowPassed[255][255];
std::vector<int> g[255];
int parList[255];
int currentPathC[255];


int bfs(int sNode, int eNode)
{
   memset(parList, -1, sizeof(parList));
   memset(currentPathC, 0, sizeof(currentPathC));
   std::queue<int> q;
   q.push(sNode);
   parList[sNode] = -1; 
   currentPathC[sNode] = 999; 
   while (!q.empty())
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
               currentPathC[to] = std::min(currentPathC[currNode],
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
   std::cout<<"Flow"<<"  "<<"Path"<<std::endl;
   while (true)
   {
      int flow = bfs(sNode, eNode);
      if (flow == 0)
      {
         break;
      }
      maxFlow += flow;
      int currNode = eNode;  
      std::cout<<flow<<"     ";
      std::cout<<eNode<<" ";
      while (currNode != sNode)
      {
         int prevNode = parList[currNode];
         std::cout<<std::to_string(prevNode)<<" ";
         flowPassed[prevNode][currNode] += flow;
         flowPassed[currNode][prevNode] -= flow;
         currNode = prevNode;
      }
      std::cout<<std::endl;
   }
   std::cout << "Max Flow is:" << maxFlow << std::endl;
   return maxFlow;
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
   int maxFlow = edmondsKarp(source, sink); 
   
}