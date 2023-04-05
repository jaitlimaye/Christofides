#include<string>
#include<iostream>


using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

struct edge{
	int u; 
	int v;
	int w; 
	edge(int u, int v,int w){
		this->u = u;
		this->v = v;
		this->w = w;
	};
	edge(const edge &x){
		this->u = x.u;
		this->v = x.v;
		this->w = x.w;
	};
	bool operator ==(const edge& a)	
	{
		return this->w == a.w;
	};
	bool operator >(const edge& a)	
	{
		return this->w > a.w;
	};
	bool operator <(const edge& a)	
	{
		return this->w < a.w;
	};
};

class Graph{
public:
	Graph(int N,bool DEBUG);
	void printGraph();
	void addEdge(int u, int v, int weight);
	void Christofides();
	
private:
	int size;
	int tot_cost;
	int filled_size;
	bool debug;

	vector<edge> EdgeList; 
	vector<vector<edge>> Adj;
	vector<vector<edge>> MST;
	vector<int> distance;
	vector<int> parents;
	vector<int> odds;
	vector<bool> added;
	vector<bool> visited;
	vector<int> Euler;
	vector<int> Hamilton;

	edge findedge(int u,int v);
	void MakeMST();
	int root(int x);
	void changeroot(int u,int v);
	void perfectMatching();
	void makeOdds();
	bool notadded(const edge &E,int i);
	void Euelerianpath(int src);
	void Hamiltonpath();
	
};

#endif
