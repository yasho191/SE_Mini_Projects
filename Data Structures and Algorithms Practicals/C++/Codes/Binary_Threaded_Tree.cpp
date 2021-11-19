#include<stack>
#include<iostream>

using namespace std;

class BTT{
	struct node{
		int data;
		int left_flag;
		int right_flag;
		node *left;
		node *right;
	}*root, *header;
	
	public:
		BTT(){
			root = NULL;
		}
		
		node *get_root(){
			return root;
		}
		
		void create();
		void inorder(node *);
		void preorder(node *);
		void postorder(node *);
};


void BTT::create(){
	int ans = 1;
	
	header = new node;
	header->data = -999;
	header->left = root;
	header->right = header;
	header->left_flag = 0;
	header->right_flag = 1;
	
	while(ans == 1){
		
		node *temp;
		temp = new node;
		cout<<"Enter the data in the node: ";
		cin>>temp->data;
		temp->left = NULL;
		temp->right = NULL;
		temp->left_flag = 0;
		temp->right_flag = 0;
		
		
		if(root == NULL){
			root = temp;
			root->left = header;
			root->right = header;
		}
		else{
			node *curr;
			curr = root;
			int flag = 0;
			
			while(!flag){
				// following rules of BST
				if (curr->data > temp->data){
					if(curr->left_flag == 0){
						// treading the new node
						temp->left = curr->left;
						temp->right = curr;
						
						// linking new node and parent node
						curr->left_flag = 1;
						curr->left = temp;
						flag = 1;
					}
					else{
						// move to left of current node
						curr = curr->left;
					}
				}
				else{
					if(curr->right_flag == 0){
						// treading the new node
						temp->right = curr->right;
						temp->left = curr;
						
						// linking new node and parent node
						curr->right_flag = 1;
						curr->right = temp;
						flag = 1;
					}
					else{
						// move to right of current node
						curr = curr->right;
					}
				}
			}
			
		}
		cout<<"Do you want to insert a new node?"<<endl;
		cin>>ans;
	}
	
}

void BTT::inorder(node *temp){
	
	// find leftmost node
	while(temp->left_flag != 0){
		temp = temp->left;
	}
	
	// till our node is not header
	while(temp != header){
		// print node data
		cout<<temp->data<<" ";
		
		//if node has right child
		if(temp->right_flag == 1){
			// move to right node
			temp = temp->right;
			
			// find leftmodes node of this node
			while(temp->left_flag != 0){
				temp = temp->left;
			}
		}
		// if right child not present move to successor node
		else{
			temp = temp->right;
		}
		
		//cout<<temp->data<<endl;
		//cout<<"right_flag"<<temp->right_flag<<<endl;
		//cout<<"left_flag"<<temp->left_flag<<<endl;	
		
	}
		
}

void BTT::preorder(node *temp){
	
	while(temp != header){
		cout<<temp->data<<" ";
		
		if (temp->left_flag != 0){
			temp = temp->left;
		}
		//if node has right child
		else if(temp->right_flag == 1){
			// move to right node
			temp = temp->right;
			
			// find leftmodes node of this node
			while(temp->left_flag != 0){
				temp = temp->left;
			}
		}
		// if left & right child not present move to successor node until it has a right child node
		else{
			while(temp->right_flag != 1){
				temp = temp->right;	
			}
			temp = temp->right;
			
		}
	}
    
}


void BTT::postorder(node *temp){
	stack<int> s;
	// the root should be the last node so push that on to the stack
	s.push(temp->data);	
	while(temp != header){
		// move to rightmost node
		// while doing that store the values in stack;
		if (temp->right_flag == 1){
			while(temp->right_flag == 1){
				temp = temp->right;
				s.push(temp->data);					
			}
			if(s.top()!= temp->data){
				s.push(temp->data);	
			}
			
		}
		//if node has left child
		else if(temp->left_flag == 1){
			// move to left node
			temp = temp->left;
			s.push(temp->data);
			
			
		}
		// if left and right child not present move to predecessor node until it has a left child node
		else{
			while(temp->left_flag != 1){
				if (temp != header){
					temp = temp->left;
				}
				else{
					break;
				}	
			}
			
			temp = temp->left;
			s.push(temp->data);
					
		}
	}
	// the top will have value of header node so pop it
	s.pop();
	while(!s.empty()){
		int x = s.top();
		cout<<x<<" ";
		s.pop();
	}
	
}

int main(){
	BTT obj;
	obj.create();
	obj.inorder(obj.get_root());
	cout<<endl;
	obj.preorder(obj.get_root());
	cout<<endl;
	obj.postorder(obj.get_root());
}
