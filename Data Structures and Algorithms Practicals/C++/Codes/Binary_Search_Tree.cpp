//Binary Search Tree
#include<iostream>
#include<queue>

using namespace std;

class Tree{
	struct node{
		int data;
		node *left;
		node *right;
	}* root;
	
	public:
		
		Tree(){
			root = NULL;
		}
		
		node *ROOT(){
			return root;
		}
		
		node *mirror(node *N){
			node *temp;
			if(N == NULL){
				return NULL;
			}
			else{
				temp = N->left;
				N->left = mirror(N->right);
				N->right = mirror(temp);
				return N;
			}
		}
		
		void create();
		void insert();
		void search();
		int minimum();
		void preorder(node *);
		int height(node *);
		void print_leaf(node *);
		void print_normal();
		void print_mirror(node *);
};

void Tree::create(){
	int ele;
	cout<<"Enter the elements you want to insert in the BST"<<endl;
	cin>>ele;
	for (int i = 0; i < ele; i++){
		insert();
	}
}

void Tree::insert(){
	
	node *temp, *curr, *parent;
	temp = new node;
	temp->right = NULL;
	temp->left = NULL;
	cout<<"Enter data: ";
	cin>>temp->data;
	
	parent = root;
	curr = root;
	
	// Tree empty condition
	if (root == NULL){
		root = temp;
	}
	else{
		while(curr){
			if (temp->data > curr->data){
				parent = curr;
				curr = curr->right;
			}	
			else{
				parent = curr;
				curr = curr->left;
			}
		}

		if (temp->data > parent->data){
			parent->right = temp;
		}
		else{
			parent->left = temp;
		}
	}
}

void Tree::preorder(node *temp){
	
	if(temp != NULL){
		cout<<temp->data<<" ";
		preorder(temp->left);
		preorder(temp->right);
	}
}

void Tree::print_leaf(node *temp){
	
	if(temp != NULL){
		if(temp->left == NULL && temp->right == NULL){
			cout<<temp->data<<" ";
		}
		print_leaf(temp->left);
		print_leaf(temp->right);
	}
}

void Tree::search(){
	node *temp;
	temp = root;
	int data, flag;
	flag = 0;
	cout<<"Enter the data you want to find: ";
	cin>>data;
	
	while(temp!=NULL){
		if(data > temp->data){
			temp = temp->right;
		}
		else if(data == temp->data){
			flag = 1;
			break;
		}
		else{
			temp = temp->left;
		}	
	}
	if(flag){
		cout<<"Element found!"<<endl;
	}
	else{
		cout<<"Element not found!"<<endl;
	}
}

int Tree::height(node *temp){
	int lheight, rheight;
	
	if(temp == NULL){
		return 0;
	}
	else{
		int lheight = height(temp->left);
		int rheight = height(temp->right);
		
		if (lheight > rheight){
			return lheight + 1;
		}
		else{
			return rheight + 1;
		}
	}
}

int Tree::minimum(){
	node *temp;
	temp = root;
	while(temp->left != NULL){
		temp = temp->left;
	}
	return temp->data;
}

void Tree::print_normal(){
	if(root == NULL){
		return;
	}
	else{
		queue<node *> q1;
		q1.push(root);
		
		
		while(!q1.empty()){
			int node_count = q1.size();
			while(node_count > 0){
				node *temp = q1.front();
				cout<<temp->data<<" ";
				q1.pop();
				if(temp->left != NULL){
					q1.push(temp->left);
				}
				if(temp->right != NULL){
					q1.push(temp->right);
				}
				node_count--;
			}
			cout<<endl;
		}
		
	}	
}


void Tree::print_mirror(node *N){
	if(N == NULL){
		return;
	}
	else{
		queue<node *> q1;
		q1.push(N);
		
		
		while(!q1.empty()){
			int node_count = q1.size();
			while(node_count > 0){
				node *temp = q1.front();
				cout<<temp->data<<" ";
				q1.pop();
				if(temp->left != NULL){
					q1.push(temp->left);
				}
				if(temp->right != NULL){
					q1.push(temp->right);
				}
				node_count--;
			}
			cout<<endl;
		}
		
	}	
}

int main(){
	Tree t1;
	t1.create();
	cout<<"The leaf nodes in the binary tree are: "<<endl;
	t1.print_leaf(t1.ROOT());
	cout<<endl;
	cout<<"Height of the binary tree is: "<<t1.height(t1.ROOT())<<endl;
	cout<<"The minimum value in Binary tree is: "<<t1.minimum()<<endl;
	cout<<"The level wise printing of the binary tree is: "<<endl;
	t1.print_normal();
	cout<<endl;
	cout<<"Mirror: "<<endl;
	t1.print_mirror(t1.mirror(t1.ROOT()));
}
