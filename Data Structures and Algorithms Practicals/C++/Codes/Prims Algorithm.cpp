#include<iostream>

using namespace std;

class und_graph{
	int graph[10][10];
	int nodes;
	int edges;
	
	public:
		und_graph(){
			cout<<"Enter the Number of nodes you want in the graph: ";
			cin>>nodes;
			
			for (int i = 0; i < nodes; i++){
				for(int j = 0; j < nodes; j++){
					graph[i][j] = 0;
				}
			}
			edges = 0;
		}
		
		void create();
		void display();
		void info();
		int min_spanning_tree();
};

void und_graph::create(){
	int ans = 1;
	int n1, n2;
	int weight = 0;
	
	do{
		cout<<"Enter the values of node1 and node2: ";
		cin>>n1>>n2;
		cout<<"Enter the weight of the edge: ";
		cin>>weight;
		if(n1 < nodes && n2 < nodes){
			graph[n1][n2] = weight;
			graph[n2][n1] = weight;
			edges++;
		}
		else{
			cout<<"Invalid Nodes!"<<endl;
		}
		cout<<"Do you want to add another node?"<<endl;
		cin>>ans;
	}while(ans == 1);
}

void und_graph::display(){
	for (int i = 0; i < nodes; i++){
		for(int j = 0; j < nodes; j++){
			cout<<graph[i][j]<<" ";
		}
		cout<<endl;
	}
}


void und_graph::info(){
	cout<<"The total nodes in the graph: "<<nodes<<endl;
	cout<<"The total edges in the graph: "<<edges<<endl;
}


int und_graph::min_spanning_tree(){
	
	int cost = 0;
	int v[nodes];
	int n, min;
	int x, y;
	
	
	
	for(int i = 0; i < nodes; i++){
		v[i] = 0;
	}
	
	cout<<"Enter a node to start with: ";
	cin>>n;
	
	v[n] = 1;
	
	for (int k = 0; k < nodes-1; k++){
		min = 999;
		for(int i = 0; i < nodes; i++){
			
			if(v[i] == 1){
				
				for (int j = 0; j < nodes; j++){
					if(v[j] != 1 && graph[i][j] != 0){
						if (min > graph[i][j]){
							min = graph[i][j];
							y = j;
							x = i;
						}
					}
				}
				
			}
			
		}
		v[y] = 1;
		v[x] = 1;
		cost = cost + min;
		// cout<<cost<<endl;
		
	}
	
	cout<<"Minimum cost is: "<<cost<<endl;
	return cost;
}


int main(){
	und_graph obj;
	obj.create();
	obj.display();
	obj.info();
	obj.min_spanning_tree();
}
