#include<iostream>
using namespace std;

class Graph
{
	
	int n;
	int graph[3][3];
	public:
		Graph()
		{
			cout<<"Enter no of vertices.. ";
			cin>>n;
			for(int i=1;i<n+1;i++)
			{
				for(int j=1;j<n+1;j++)
				{
					graph[i][j]=0;
				}
			}
		}
		void create();
		void display();
		void all_pairs_shortest_path();
};

void Graph::create()
{
	int x,y,wt,ans;
	do
	{
		cout<<"\nEnter 1st Vertex- ";
		cin>>x;
		cout<<"Enter 2nd Vertex- ";
		cin>>y;
		cout<<"\n\nEnter Weight of edge- ";
		cin>>wt;
		
		graph[x][y]=wt;
		
		
		cout<<"\n\n\n Do you want to add another vertex? (yes-1;no-0)  ";
		cin>>ans;
	}
	while(ans==1);
	if(ans==0)
	{
		
		for(int i=1;i<n+1;i++)
		{
			for(int j=1;j<n+1;j++)
			{
				if(graph[i][j]==0 && i!=j)
				{
					graph[i][j]= 999;
					
				}
			}
		}
	}
}

void Graph::display()
{
	cout<<endl<<endl;
	
	
	for(int i=1;i<n+1;i++)
	{   
		for(int j=1;j<n+1;j++)
		{
			cout<<"  "<<graph[i][j]<<"  ";
		}
		cout<<endl;
	}
	
}

void Graph::all_pairs_shortest_path()
{
	for(int k=1;k<n+1;k++)
	{
		for (int i=1;i<n+1;i++)
		{
			for(int j=1;j<n+1;j++)
			{
				if( (graph[i][k]+graph[k][j]) < (graph[i][j]) )
				{
					graph[i][j] = (graph[i][k]+graph[k][j]);
				}
			}
		}
	}
}


int main()
{
	Graph obj;
	obj.create();
	obj.display();
    obj.all_pairs_shortest_path();
	obj.display();
}