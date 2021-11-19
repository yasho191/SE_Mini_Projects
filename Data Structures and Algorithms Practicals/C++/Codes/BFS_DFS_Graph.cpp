#include<iostream>
#include<stack>
#include<queue>

using namespace std;

class und_graph{
	struct node{
		int data;
		node *next;
	}*graph[10];
	
	int nodes, edges;
	
	public:
		und_graph(){
			for (int i = 0; i < 10; i++){
				graph[i] = NULL;
			}
			edges = 0;
			nodes = 0;
		}
		
		void create();
		void display();
		void info();
		void dfs();
		void bfs();
};

void und_graph::create(){
	cout<<"Enter the number of nodes you want: ";
	cin>>nodes;
	int n1, n2;
	int ans = 1;
	do{
		cout<<"Enter the values of node 1 and node 2: ";
		cin>>n1>>n2;
		
		node *temp1, *temp2;
		temp1 = new node;
		temp2 = new node;
		temp1->data = n2;
		temp1->next = NULL;
		temp2->data = n1;
		temp2->next = NULL;
		
		
		
		if(graph[n1] == NULL){
			graph[n1] = temp1;
		}
		else{
			node *t;
			t = graph[n1];
			while(t->next != NULL){
				t = t->next;
			}
			t->next = temp1;
		}
		
		if(graph[n2] == NULL){
			graph[n2] = temp2;
		}
		else{
			node *t;
			t = graph[n2];
			while(t->next != NULL){
				t = t->next;
			}
			t->next = temp2;
		}
		
		edges++;
		
		cout<<"Do you want to add another node? "<<endl;
		cin>>ans;
	}while(ans==1);
}


void und_graph::display(){
	for (int i = 0; i < nodes; i++){
		cout<<i<<"---> ";
		node *temp;
		temp = graph[i];
		while(temp != NULL){
			cout<<temp->data<<" ";
			temp = temp->next;
		}
		cout<<endl;
	}
}


void und_graph::info(){
	cout<<"The total nodes in the graph: "<<nodes<<endl;
	cout<<"The total edges in the graph: "<<edges<<endl;
}

void und_graph::dfs(){
	stack<int> s;
	int num, visited[nodes], start_node;
	
	for(int i = 0; i < nodes; i++){
		visited[i] = 0;
	}
	
	node *temp;
	
	cout<<"Enter the starting node: ";
	cin>>start_node;
	
	s.push(start_node);
	visited[start_node] = 1;
	
	while(!s.empty()){
		num = s.top();
		s.pop();
		
		if(visited[num] == 1){
			cout<<num<<" ";
		}
		temp = graph[num];
		
		while(temp != NULL){
			if(visited[temp->data] == 0){
				s.push(temp->data);
				visited[temp->data] = 1;
			}
			temp = temp->next;
		}
	}
}


void und_graph::bfs(){
	queue<int> q;
	int num, visited[nodes], start_node;
	
	for(int i = 0; i < nodes; i++){
		visited[i] = 0;
	}
	
	node *temp;
	
	cout<<"Enter the starting node: ";
	cin>>start_node;
	
	q.push(start_node);
	visited[start_node] = 1;
	
	while(!q.empty()){
		num = q.front();
		q.pop();
		
		if(visited[num] == 1){
			cout<<num<<" ";
		}
		temp = graph[num];
		
		while(temp != NULL){
			if(visited[temp->data] == 0){
				q.push(temp->data);
				visited[temp->data] = 1;
			}
			temp = temp->next;
		}
	}
}


int main(){
	und_graph obj;
	obj.create();
	obj.display();
	obj.info();
	obj.dfs();
	cout<<endl;
	obj.bfs();
}
