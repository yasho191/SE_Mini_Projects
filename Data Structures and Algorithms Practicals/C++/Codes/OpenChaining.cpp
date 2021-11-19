#include<iostream>
#include<string.h>

# define max 10

using namespace std;

class OpenHash{
	// node will store the key value pairs
	// declare an array of nodes for the hash map
	// size of array = 10
	struct node{
		int key;
		string value;
		node *next;
	}*hash_table[max];
	
	public:
		// Constructor
		// set all the node pointers in table to zero
		OpenHash(){
			for(int i = 0; i < max; i++){
				hash_table[i] = NULL;
			}
		}
		
		// return hash value of the key
		int hash(int key){
			return key % max;
		}
		
		// inserting key value pair in the hashmap
		void insert(){
			// initialize a temp node
			// user input data will be stored here
			node *temp;
			temp = new node;
			temp->next = NULL;
			cout<<"Enter the key: ";
			cin>>temp->key;
			cout<<"Enter the value of the key: ";
			cin>>temp->value;
			
			// find the hash code of the key
			int code = hash(temp->key);
			
			// if the linked list at that position has zero elements
			// directly assign the temp to hash_table[code]
			if(hash_table[code] == NULL){
				hash_table[code] = temp;
			}
			// else iterate to the last node and perform standard element append
			else{
				node *curr;
				curr = hash_table[code];
				while(curr->next != NULL){
					curr = curr->next;
				}
				curr->next = temp;
			}
		}
		
		// searching an element
		void search(){
			//declare temp node pointer 
			// it will point to the starting node of linked lists in the hash table
			node *temp;
			int key;
			// indicator if the search operation fails
			int flag = 0;
			cout<<"Enter the key you want to find: ";
			cin>>key;
			int code = hash(key);
			
			temp = hash_table[code];
			while(temp != NULL){
				if(temp->key == key){
					cout<<"Key found!"<<endl;
					cout<<"Key: "<<temp->key<<endl;
					cout<<"Value: "<<temp->value<<endl;
					flag = 1;
					break;
				}
			}
			
			if(flag == 0){
				cout<<"Key does not exist!"<<endl;
			}
		}
		
		// delete a key value pair
		void del(){
			node *temp, *prev;
			int key;
			cout<<"Enter the key you want to delete: ";
			cin>>key;
			int code = hash(key);
			temp = hash_table[code];
			
			// if the element to be deleted is the first element 
			if(temp->key == key){
				hash_table[code] = temp->next;
				delete temp;
			}
			// if the element to be deleted is not the first element
			else{
				while(temp!=NULL){
					if(temp->key == key){
						// element fount but it is the last element in the linked list
						if(temp->next == NULL){
							prev->next = NULL;
							delete temp;
							break;
						}
						// element found but is not the last element in the list
						else{
							prev->next = temp->next;
							delete temp;
							break;
						}
						
					}
					prev = temp;
					temp = temp->next;
					
				}	
			}
			
			
		}
		
		// Display the Hash Table
		void display(){
			// set temp node
			// loop 1 - iterate over the whole hash table
			// loop 2 - iterate over the linked lists at every position
			node *temp;
			
			cout<<"The current Hash table is:"<<endl;
			cout<<"{";
			for (int i = 0; i < max; i++){
				temp = hash_table[i];
				while(temp != NULL){
					cout<<temp->key<<": ";
					cout<<temp->value<<", ";
					
					temp = temp->next;
				}
			}
			cout<<"}"<<endl;
		}
};

// test functions
int main(){
	OpenHash dict;
	dict.insert();
	dict.insert();
	dict.insert();
	dict.insert();
	dict.display();
	dict.del();
	dict.display();
	dict.del();
	dict.display();
}
