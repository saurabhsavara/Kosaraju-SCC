//
//  kosaraju.h
//  Kosaraju SCC
//
//  Created by Saurabh Savara on 9/22/20.
//  Copyright © 2020 Saurabh Savara. All rights reserved.
//

#ifndef kosaraju_h
#define kosaraju_h
#include <vector>
using namespace std;



class Graph
{
    int vertices;
    vector<vector <int> >adjlist;
    vector<bool> scanned;
    vector <int> dfsorder;
    vector<int> myrevgraph; //need to figure out
    
public:
    Graph(int n){
        this->vertices=n;
        
    }
    void addEdge(int u, int v){
        adjlist[u].push_back(v);
        //adjlist[v].push_back(u); when using reverse graph
    }
    void dfs(int v)
    {
        scanned[v]=true;
        for(int i=0; i<adjlist[v].size(); ++i)
        {
            if(!scanned[adjlist[v][i]])
            {
                dfs(adjlist[v][i]);
            }
        }
            dfsorder.push_back(v);
        }
    void dfspass2(int v)
    {
        
    }
};


#endif /* kosaraju_h */
