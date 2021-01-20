//
//
//  Kosaraju SCC
//
//  Created by Saurabh Savara on 9/22/20.
//  Copyright © 2020 Saurabh Savara. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#define MAX_N 1000
using namespace std;


int vertices;  // Store number of vertices of the input  graph
int edges;  // Store number of edges of the input graph
vector<vector <int> >graph(MAX_N),graph_rev(MAX_N); // Allocate vectors for the normal and reverse graph
vector<bool> scanned,scc_visited; // Vertex Visited vectors  for graph and SCC graph

vector <int> dfsorder,scc; // Store vertexs for Topological sort and SCC
stack<int> dfsquickest; // Maintain stack for DFS pass 1


//First Pass of DFS on a given Graph when Vertex V is passed through it. Recursive Function

void dfspass1(int v)
{
    scanned[v]=true;
    for(size_t i=0; i<graph[v].size(); i++)
    {
        if(!scanned[graph[v][i]])
        {
          dfspass1(graph[v][i]);
        }
    }
    dfsorder.push_back(v); // Used for Topological sort
    dfsquickest.push(v); // Used for Quickest Time in Kosaraju's Algorithm
}

//Second Pass of DFS on a given Graph when Vertex V is passed through it. Recursive Function

void dfspass2(int v)
{
    scanned[v] = true;
    scc.push_back(v);
    for(size_t i=0;i<graph_rev[v].size();i++)
    {
        if(!scanned[graph_rev[v][i]])
        {
            dfspass2(graph_rev[v][i]);
        }
    }

}

//Set Scanned Vector of Vetices to Not Visited or False

void setnotvisited()
{
    for(int i=0;i<vertices;i++)
    {
        scanned[i]=false;
    }
}

// Set Scanned Vector of SCC Vertices to Not Visited or False

void setsccnotvisited(vector<vector<int> >scc_list)
{
    for(size_t i=0;i<scc_list.size();i++)
          {
              scc_visited[i]=false;
          }
}

// Given two Vertices check if they belong to the same SCC , Used for Processing Kernel Graph

bool samescc(int a,int b,vector<vector <int> > scc_list)
{
    for(size_t i=0;i<scc_list.size();i++)
    {
        for(size_t j=0;j<scc_list[i].size();j++)
        {
            if(a==scc_list[i][j])
            {
                for(size_t k=0;k<scc_list[i].size();k++)
                    if(b==scc_list[i][k])
                        return true;

            }
        }
    }
    return false;

}

//Given a Vertex get which SCC it belongs to, Used for Graph Kernel Processing

int getscc(int a,vector< vector <int> > scc_list)
{
    for(size_t i=0;i<scc_list.size();i++)
    {
        for(size_t j=0;j<scc_list[i].size();j++)
        {
            if(a==scc_list[i][j])
            {
                return i;
            }
        }
    }
    return false;
}

//Get the topological ordering of a graph, used to reduce time complexity for Graph Kernel

void topologicalsort()
{
    setnotvisited();
    dfsorder.clear();
    for(int i=0;i<vertices;++i)
    {
        if(!scanned[i])
        {
            dfspass1(i);
        }
    }
    reverse(dfsorder.begin(), dfsorder.end());
}

// Main method

int main(int argc, char* argv[]) {

    // Take Input from user
    int count=1;
    vector<int> a;
    vector<int> b;
    cin>>vertices;
    cin>>edges;
    string s;
    int i ,j;
    cin.ignore();
    do{
        cin>>i;
        cin>>j;
        //Push edges into a forward graph and reverse graph
        graph[i].push_back(j);
        graph_rev[j].push_back(i);
        count++;
    }while(edges>count);
    cin>>i;
    cin>>j;

    //Push last edge into a forward graph and reverse graph
    graph[i].push_back(j);
    graph_rev[j].push_back(i);


    //Set the size of our Scanned Vertices Vector

    scanned.resize(vertices);

    //Initialize Scanned to false

    setnotvisited();

    //Run First DFS on the graph

    for(int i=0;i<vertices;i++)
    {
        if(scanned[i]==false)
            dfspass1(i);

    }
    //Reset Scanned Vertices vector flags
    setnotvisited();

    //List to store all SCC found.
    vector<vector <int> > scc_list;

    //Run DFS another time , this time on the reverse graph using the stack obtained from DFS1

    while(!dfsquickest.empty())
    {
        int v=dfsquickest.top();
        dfsquickest.pop();
        if(!scanned[v])
        {
            dfspass2(v);
            scc_list.push_back(scc);
            scc.clear();
        }
    }

    //Print out the SCC in the given Graph
    cout<<"The given graph has "<<scc_list.size()<<" Strongly Connected Components"<<endl;

    for(size_t i=0;i<scc_list.size();i++)
    {
        cout<<"Connected Component #"<<i<<"  ";
        for(size_t j=0;j<scc_list[i].size();j++)
        {
            cout<<scc_list[i][j]<<",";
        }
        cout<<endl;
    }


    //Part 2, Find and Print Graph Kernel from the Given Graph

    //Get a topological sort ordering on the Graph
    topologicalsort();

    //Initialize Vector to store Edges
    vector<int> kernels;
    //Initialize Scc Scanned Vector to False
    scc_visited.resize(scc_list.size());
    setsccnotvisited(scc_list);
    //Count Number of Edges in Graph Kernel
    int scc_edges=0;

    for(size_t k=0;k<dfsorder.size();k++)
    {
        for(size_t j=1;j<dfsorder.size();j++)
        {
            //Check if two Vertices from Topological Sort are not part of the same SCC
            if(!samescc(dfsorder[k],dfsorder[k+j],scc_list))
            {
                for(size_t i=0;i<graph[dfsorder[k]].size();i++)
            {
                //Check if there exists an edge from one vertex to another given that we have not
                //visited that SCC from that edge before
                if(graph[dfsorder[k]][i]==dfsorder[k+j] && scc_visited[getscc(dfsorder[k+j], scc_list)]==false)
                         {
                             kernels.push_back(dfsorder[k]);
                             kernels.push_back(dfsorder[k+j]);
                             scc_visited[getscc(dfsorder[k+j], scc_list)]=true;
                             scc_edges++;
                         }
            }

            }

        }
        //Reset Scanned Vector to False
        setsccnotvisited(scc_list);
    }

    //Print out the Graph Kernel

    cout<<endl;
    cout<<"Graph Kernel"<<endl;
    cout<<scc_list.size()<<endl;
    cout<<scc_edges<<endl;

    //i incremented by 2 since we have stored the edges in a single dimension Vector
    for(size_t i=0;i<kernels.size();i=i+2)
    {
        cout<<kernels[i]<< " "<<kernels[i+1]<<endl;
    }

    return 0;
}

