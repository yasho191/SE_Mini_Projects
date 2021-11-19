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
};

void und_graph::create(){
	int ans = 1;
	int n1, n2, distance;
	do{
		cout<<"Enter the values of node1 and node2: ";
		cin>>n1>>n2;
		cout<<"Enter the distance between two node: ";
		cin>>distance;
		if(n1 < nodes && n2 < nodes){
			graph[n1][n2] = distance;
			graph[n2][n1] = distance;
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


int main(){
	und_graph obj;
	obj.create();
	obj.display();
	obj.info();
}
