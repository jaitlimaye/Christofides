#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<utility>
#include<cmath>
#include "graph.h"
#include <chrono>

using namespace std;

const bool DEBUG = false; //SET THIS TO TRUE TO SHOW PATH

int main(){
	int N;
	cin >> N;

    Graph graph(N,DEBUG);
	string command;
	while(cin >> command){
		if(command == "INIT"){
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					int w;
					cin >> w;
					
					if(i != j)
					{
						graph.addEdge(i, j, w);
					}
				}
			}	
		}else if(command == "printGraph"){
			graph.printGraph();
		}
        else if(command == "christofides"){
			graph.Christofides();
		}
        else{
			cerr << "ERROR: command " << command << " is not recognized." << endl;
		}
	}//while
	
  return 0;
}
