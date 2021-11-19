#include<iostream>
#include<string.h>

using namespace std;

class BST{
    struct node{
        string key;
        string value;
        node *left;
        node *right;
    } * root;

    public:

    BST(){
        root = NULL;
    }

    node *get_root(){
        return root;
    }

    void insert();
    void search();
    void modify();

    void inorder(node *temp){
        if(temp!=NULL){
            inorder(temp->left);
            cout<<"Key: "<<temp->key<<"  Value: "<<temp->value<<endl;
            inorder(temp->right);
        }
        cout<<endl;
    }

    void postorder(node *temp){
        if(temp!=NULL){
            postorder(temp->left);            
            postorder(temp->right);
            cout<<"Key: "<<temp->key<<"  Value: "<<temp->value<<endl;
        }
        cout<<endl;
    }

    node *delete_node(node *root, string key){
        node* temp;
        // base case
        if (root == NULL)
            return root;
    
        // If the key to be deleted is
        // smaller than the root's
        // key, then it lies in left subtree
        if (key < root->key)
            root->left = delete_node(root->left, key);
    
        // If the key to be deleted is
        // greater than the root's
        // key, then it lies in right subtree
        else if (key > root->key)
            root->right = delete_node(root->right, key);
    
        // if key is same as root's key, then This is the node
        // to be deleted
        else {
            // node has no child
            if (root->left==NULL and root->right==NULL){
                return NULL;
            }
            // node with only one child or no child
            else if (root->left == NULL) {
                temp = root->right;
                free(root);
                return temp;
            }
            else if (root->right == NULL) {
                temp = root->left;
                free(root);
                return temp;
            }
    
            // node with two children: Get the inorder successor
            // (smallest in the right subtree)
            temp = root->right;
            while (temp && temp->left != NULL)
                temp = temp->left;

            // Copy the inorder successor's content to this node
            root->key = temp->key;
    
            // Delete the inorder successor
            root->right = delete_node(root->right, temp->key);
        }
        return root;
    }

};

void BST::insert(){
    node *temp, *parent, *child;

    temp = new node;
    temp->left = NULL;
    temp->right = NULL;
    cout<<"Enter key: ";
    cin>>temp->key;
    cout<<"Enter value: ";
    cin>>temp->value;

    parent = root;
    child = root;

    if (root==NULL){
        root = temp;
    }
    else{

        while(child != NULL){
            if (temp->key < child->key){
                parent = child;
                child = child->left;
            }
            else if(temp->key > child->key){
                parent = child;
                child = child->right;
            }
        }

        if(temp->key > parent->key){
            parent->right = temp;
        }
        else{
            parent->left = temp;
        }
    }

}

void BST::modify(){
    string key;
    int flag=0;
    cout<<"Enter the key you want to modify: ";
    cin>>key;

    node *temp = root;

    if(temp==NULL){
        cout<<"Tree is empty"<<endl;
        return;
    }
    else{
        while(temp!=NULL){
            if(temp->key > key){
                temp = temp->left;
            }
            else if(temp->key < key){
                temp = temp->right;
            }
            else{
                flag = 1;
                cout<<"Enter the value you want to assign the key: ";
                cin>>temp->value;
                break;
            }
        }
        if(!flag){
            cout<<"No such key exists! "<<endl;
        }
    }
}

void BST::search(){
    string key;
    int flag=0;
    cout<<"Enter the key you want to search: ";
    cin>>key;

    node *temp = root;

    if(temp==NULL){
        cout<<"Tree is empty"<<endl;
        return;
    }
    else{
        while(temp!=NULL){
            if(temp->key > key){
                temp = temp->left;
            }
            else if(temp->key < key){
                temp = temp->right;
            }
            else{
                flag = 1;
                cout<<"Key found!"<<endl;
                cout<<"Key: "<<temp->key<<"  Value: "<<temp->value<<endl;
                break;
            }
        }
        if(!flag){
            cout<<"No such key exists! "<<endl;
        }
    }
}



int main(){
    BST dict;
    int option, flag;
    flag = 1;
    while(true){
        cout<<"Menu"<<endl;
        cout<<"1. Insert pair"<<endl;
        cout<<"2. Delete pair"<<endl;
        cout<<"3. Ascending Order"<<endl;
        cout<<"4. Descending Order"<<endl;
        cout<<"5. Search"<<endl;
        cout<<"6. Modify"<<endl;
        cout<<"7. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>option;

        switch (option)
        {
        case 1:{
            dict.insert();
            break;
        }
        case 2:{
            string key;
            cout<<"Enter the element you want to delete: ";
            cin>>key;
            dict.delete_node(dict.get_root(), key);
            break;
        }
        case 3:{
            dict.inorder(dict.get_root());
            break;
        }
        case 4:{
            dict.postorder(dict.get_root());
            break;
        }
        case 5:{
            dict.search();
            break;
        }
        case 6:{
            dict.modify();
            break;
        }  
        case 7:{
            flag = 0;
            break;
        } 
        default:{
            cout<<"Invalid Option!"<<endl;
            break;
        }
        }
        if(!flag){
            cout<<"Program Exited"<<endl;
            break;
        }
    }
}