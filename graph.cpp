#include<climits>
#include<algorithm>
#include<vector>
#include<iostream>
#include<string>
#include<utility>
#include<stack>
#include "graph.h"
using namespace std;

Graph::Graph(int N,bool DEBUG){
	debug = DEBUG;
	size = N;
	MST.resize(size);
	Adj.resize(size);
	distance.resize(size);
	visited.resize(size);
	parents.resize(size);
	for (int i = 0; i < size; i++)
	{
		distance[i] = INT_MAX;
		parents[i] = i;
		visited[i] = false;
	}
	
}//default

void Graph::addEdge(int u, int v, int weight){
	int x = u;
	if(u > v)  
	{
		u = v;
		v = x;
		edge E(u,v,weight);
		Adj[x].push_back(E);
	}
	else
	{
		edge E(u,v,weight);
		EdgeList.push_back(E);
		Adj[x].push_back(E);
	}
}

void Graph::printGraph(){
	cout<<endl<<"MST: ";
	for(int i =0;i <(int)MST.size(); i++)
	{
		cout<<endl<<i<<": ";
		for(int j =0;j <(int)MST[i].size(); j++)
		{
			cout<<"("<<MST[i][j].u<<" , "<<MST[i][j].v<<") "<<MST[i][j].w<<" ";
		}
	}
}//printGraph

void Graph::Christofides()
{
	MakeMST();
	perfectMatching();
	Euelerianpath(0);
	Hamiltonpath();
	if(debug)
	{
		for(int j =0;j<(int)Hamilton.size();j++)
		{
		cout<<" "<<Hamilton[j];
		}
	}
}//Christofides

void Graph::MakeMST()
{
	sort(EdgeList.begin(),EdgeList.end());
	for (int i = 0; i < (int)EdgeList.size(); i++)
	{
		int u = EdgeList[i].u;
		int v = EdgeList[i].v;

		if(root(u) != root(v))
		{
			changeroot(u,v);
			MST[u].push_back(EdgeList[i]);
			MST[v].push_back(EdgeList[i]);
		}
	}
}//MST

int Graph::root(int x)
{
	while(parents[x] != x)
    {
        parents[x] = parents[parents[x]];
        x = parents[x];
    }
    return x;
}//root

void Graph::changeroot(int u,int v)
{
	int p = root(u);
    int q = root(v);
    parents[p] = parents[q];
}//changeroot




void Graph::perfectMatching() 
{
	makeOdds();
	int closest, length;
	bool done;
	vector<bool> added;
	for (int i = 0; i < (int)odds.size(); i++)
	{
		added.push_back(false);
	}
	
	for (int i = 0; i < (int)odds.size(); i++)
	{
		edge* tmp;
		int first = odds[i];
    	length = INT_MAX;
        done = false;
		for (int j = 0; j<(int)odds.size(); j++) 
		{
			int second = odds[j];
			tmp = new edge(findedge(first,second));
      		if (tmp->w < length && notadded(*tmp,first) && !added[second]) 
			{
				length = tmp->w;
        		closest = second;
				done = true;
      		}
    	}
    	if(done)
		{	
			tmp =new edge(findedge(first,closest));
			added[first] = true;
    		MST[first].push_back(*tmp);
			added[closest] = true;
    		MST[closest].push_back(*tmp);
		}
	}
}



void Graph::makeOdds()
{
	vector<int>::iterator tmp, first;
	for (int i = 0; i < size; i++) 
	{
    	if ((MST[i].size() % 2) != 0) 
		{
      		odds.push_back(i);
		}
	}
}

bool Graph::notadded(const edge &E,int i)
{
	for(int j =0;j<(int)MST[i].size();j++)
	{
		if(E.w == MST[i][j].w && E.v == MST[i][j].v && E.u == MST[i][j].u)
		{
			return false;
		}
	}

	return true;
}

edge Graph::findedge(int u,int v)
{
	if(u > v)  
	{
		int temp = u;
		u = v;
		v = temp;
	}
	for(int i =0;i < (int)Adj[u].size();i++)
	{
		if(Adj[u][i].v == v)
		{
			return Adj[u][i];
		}
	}
	return Adj[u][0];//to remove warning
}


void Graph::Euelerianpath(int src )
{
	stack<int> S;
	int pos = src;
	while(!S.empty() || MST[pos].size() > 0)
	{
		if(MST[pos].empty())
		{
			
			Euler.push_back(pos);
			pos = S.top();
			S.pop();
		}
		else
		{
			S.push(pos);
			int neighbor;
			
			edge tmp = MST[pos].back();
			if(pos != tmp.u)
			{
				
				neighbor = tmp.u;
			}
			else neighbor = tmp.v;
			MST[pos].pop_back();
			vector<int> indexes;
			for(auto it = MST[neighbor].begin() ; it != MST[neighbor].end(); ++it)
			{
				if(pos == it->v || pos == it->u)
				{
					MST[neighbor].erase(it);
					it = MST[neighbor].end() - 1;
				}
			}
			pos = neighbor;
		}
		
	}
	Euler.push_back(pos);
}

void Graph::Hamiltonpath()
{
	vector<bool> done(size,false);
	int i = 0;
	int src = Euler[i];
	tot_cost = 0;
	int last = -1;
	for (int i = 0; i < (int)Euler.size(); i++)
	{
		if(!done[Euler[i]])
		{
			done[Euler[i]] = true;
			Hamilton.push_back(Euler[i]);
			last = Euler[i];
			if(i > 0)
			{
				tot_cost += findedge(last,Euler[i]).w;
			}
		}
	}
	if(Hamilton.back() != src)
	{
		Hamilton.push_back(src);
		tot_cost += findedge(src,Hamilton.back()).w;
	}
	cout<<tot_cost<<endl;
}

