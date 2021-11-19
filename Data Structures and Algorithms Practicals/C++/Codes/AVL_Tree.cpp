#include<iostream>
#include<string.h>
#include<cstring>
#include<stack>

using namespace std;

class AVL{
    struct node{
        string key;
        string value;
        node *left;
        node *right;
        int height;
    };

    stack<string> descending_order;

    public:
    node *root;

    AVL(){
        root = NULL;
    }

    node *insert(node *temp, string key, string value){
        if (temp == NULL){
            temp = new node;
            temp->left=NULL;
            temp->right=NULL;
            temp->key = key;
            temp->value = value;
            
        }
        else if(temp->key != key){
            if (temp->key > key){
                temp->left = insert(temp->left, key, value);
                if(balance_factor(temp) == 2){
                    if (temp->left->key > key){
                        temp = LL(temp);
                    }
                    else{
                        temp = LR(temp);
                    }
                }
            }
            else if(temp->key < key){
                temp->right = insert(temp->right, key, value);
                if(balance_factor(temp)==-2){
                    if(temp->right->key > key){
                        temp = RR(temp);
                    }
                    else{
                        temp = RL(temp);
                    }
                }
            }
        }
        else{
            cout<<"Operation not possible!"<<endl;
        }
        temp->height = height_of_node(temp);
        return temp;
    }

    node *LL(node *curr){
        curr = right_rotate(curr);
        return curr;
    }

    node *RR(node *curr){
        curr = left_rotate(curr);
        return curr;
    }

    node *LR(node *curr){
        curr->left = left_rotate(curr->left);
        curr = right_rotate(curr);
        return curr;
    }

    node *RL(node *curr){
        curr->right = right_rotate(curr->right);
        curr = left_rotate(curr);
        return curr;
    }

    node *right_rotate(node *curr){
        node *temp;
        temp=curr->left;
        curr->left=temp->right;
        temp->left=curr;

        temp->height = height_of_node(temp);
        curr->height = height_of_node(curr);

        return temp;
    }

    node *left_rotate(node *curr){
        node *temp;
        temp=curr->right;
        curr->right=temp->left;
        temp->left=curr;

        temp->height = height_of_node(temp);
        curr->height = height_of_node(curr);

        return temp;
    }

    node *delete_node(node *curr, string key){
        node *temp;
        if (curr==NULL){
            return 0;
        }
        else{
            if(curr->key < key){
                curr->right = delete_node(curr->right, key);
                if(balance_factor(curr)==2){
                    if(balance_factor(curr->left)>=0){
                        curr = LL(curr);
                    }
                    else{
                        curr = LR(curr);
                    }
                }

            }
            else if(curr->key > key){
                curr->left = delete_node(curr->left, key);
                if(balance_factor(curr)==-2){
                    if(balance_factor(curr->right) <= 0){
                        curr = RR(curr);
                    }
                    else{
                        curr = RL(curr);
                    }
                }
            }
            else{
                if(curr->right!=NULL)
		        {
                    temp=curr->right;
                    while(temp->left!=NULL){
                        temp=temp->left;
                    }
                    
                    curr->key = temp->key;
                    curr->right=delete_node(curr->right,temp->key);

                    if(balance_factor(curr)==2){
                        if(balance_factor(curr->left)>=0){
                            curr=LL(curr);
                        }   
                        else{
                            curr=LR(curr);
                        }
                    }
                    
                        
                }
                else{
                    return(curr->left);
                }
                
            }
        }
        curr->height = height_of_node(curr);
        if(curr==NULL){
            cout<<"Element not found!";
        }
        else{
            cout<<"Deletion Sucessful";
        }
        return curr;
    }

    int balance_factor(node *);
    int height_of_node(node *);
    void create(node *);
    void search();
    void ascending(node *);
    void descending(node *);
    void show_descending_order();
};

void AVL::search(){
    node *temp;
	temp = root;
	string data; 
    int flag;
	flag = 0;
	cout<<"Enter the data you want to find: ";
	cin>>data;
	
	while(temp!=NULL){
		if(data > temp->key){
			temp = temp->right;
		}
		else if(data == temp->key){
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


int AVL::balance_factor(node *curr){
    int left_height, right_height;

    if (curr == NULL){
        return 0;
    }
    else{
        if (curr->left == NULL){
            left_height = 0;
        }
        else{
            left_height = 1 + curr->left->height;
        }

        if(curr->right == NULL){
            right_height = 0;
        }
        else{
            right_height = 1 + curr->right->height;
        }

        return (left_height-right_height);
    }
}

int AVL::height_of_node(node *curr){
    int left_height, right_height;
    
    if (curr==NULL){
        return 0;
    }
    else if(curr->right == NULL && curr->left == NULL){
        return 0;
    }
    else{
        left_height = left_height + height_of_node(curr->left);
        right_height = right_height + height_of_node(curr->right);

        if (left_height>right_height){
            return left_height+1;
        }else{
            return right_height+1;
        }
    }
}

void AVL::ascending(node *temp){
    if(temp!=NULL){
        ascending(temp->left);
        cout<<temp->key<<" : "<<temp->value<<endl;
        ascending(temp->right);
    }
    
}

void AVL::descending(node *temp){
    if(temp!=NULL){
        descending(temp->left);
        descending(temp->right);
        cout<<temp->key<<" : "<<temp->value<<endl;
    }
}


void AVL::show_descending_order(){
    while(!descending_order.empty()){
        cout<<descending_order.top()<<endl;
        descending_order.pop();
    }
} 


int main(){
    AVL tree;
    int option;
    string key, value;
    int flag = 1;

    while(true){
        cout<<"Menu"<<endl;
        cout<<"1. Insert"<<endl;
        cout<<"2. Delete"<<endl;
        cout<<"3. Display in Ascending Order"<<endl;
        cout<<"4. Display in Descending Order"<<endl;
        cout<<"5. Search"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<"Enter your choice: "<<endl;
        cin>>option;

        switch(option){
            case 1:{
                
                cout<<"Enter the key: ";
                cin>>key;
                cout<<"Enter the value: ";
                cin>>value;
                tree.root = tree.insert(tree.root, key, value);
                break;
            }
            case 2:{
                cout<<"Enter the key you want to delete: ";
                cin>>key;
                tree.delete_node(tree.root, key);
                break;
            }
            case 3:{
                cout<<"Displaying Keys in ascending order: "<<endl;
                tree.ascending(tree.root);
                break;
            }
            case 4:{
                cout<<"Displaying Keys in Descending Order: "<<endl;
                tree.descending(tree.root);
                break;
            }
            case 5:{
                tree.search();
                break;
            }
            case 6:{
                flag = 0;
                break;
            }
            default:{
                cout<<"Invalid Input!"<<endl;
            }
        }
        if (!flag){
            cout<<"Program Exited!"<<endl;
            break;
        }
    }
    return 0;
}
