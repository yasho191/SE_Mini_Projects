#include<iostream>

using namespace std;

class chain_without_replacement{
	int ele_arr[10];
	int chain_arr[10];
	int n;
	
	public:
		// Constructor
		// Initialize element array and chain array with -1
		// Set size of Hashmap = 10
		chain_without_replacement(){
			for (int i = 0; i < n; i++){
				ele_arr[i] = -1;
				chain_arr[i] = -1;
			}
			n = 10;
		}
		
		// Display chain array
		void show_chain(){
			cout<<"The current chaning array is:"<<endl;
			for(int i = 0; i < n; i++){
				cout<<chain_arr[i]<<" ";
			}
		}
		
		// hash function
		int hash(int element){
			return element%n;
		}
		
		// Insert all elements into the hashmap
		// 2 conditions
		void map_element(int element){
			int curr_ele = element;
			int code = hash(element);
			
			// case 1
			// if the ele_arr[code] is -1 directly set the element to that position
			// chain array will not be modified
			if (ele_arr[code] == -1){
				ele_arr[code] = curr_ele;
			}
			else{
				// case 2
				// collision occurs 
				// iterate till the end of the chain
				// linear search for an empty position
				// place new element there
				// form a chain between new element and last element
				int flag = 0;
				if (chain_arr[code] != -1){
					while (chain_arr[code] != -1){
						code = chain_arr[code];
					}
				}
				for (int i = code; i < code + n; i++){
					if (ele_arr[i % n] == -1){
						ele_arr[i % n] = curr_ele;
						chain_arr[code] = i % n;
						flag = 1;
						break;
					}
				}
				
				// if the element array gets full the new element would be left out
				if (flag == 0){
					cout<<curr_ele<<" could not be inserted into the hash map as the has map is full!"<<endl;
				}
			}
		}
		
		// Display the element array
		void show_map(){
			cout<<"The current Hashmap is :"<<endl;
			for (int i = 0; i < n; i++){
				cout<<ele_arr[i]<<" ";
			}
		}
		
		// Search Function
		int get_ele(int element){
			int to_be_found = element;
			int chain;
			// find hash code of element to be found
			int code = hash(to_be_found);
			
			// check the element at pos code in element array if it matches return the code
			if (ele_arr[code] == to_be_found){
				cout<<"Element found at position: "<<code;
				return code;
			}
			// if it does not match follow the cain and iterate through it
			// compare to_be_found to the chain positions 
			// during iteration if the element is found then return the code
			// else return that element was not found
			else{
				int i = code;
				int flag = 0;
				while(chain_arr[i] != -1){
					chain = chain_arr[i];
					if (ele_arr[chain] == to_be_found){
						cout<<"Element found at position: "<<chain;
						flag = 1;
						return chain;
					}
					i = chain;
				}
				// if element is not found
				if(flag == 0){
					cout<<"Element not found!"<<endl;
					return -1;
				}
			}
		}
		
		// Delete an element from the hash map
		// logic is same as search function just when the element is found
		// set that postion to -1
		// take care of the chain
		void del_ele(int element){
			int index = get_ele(element);
			
			// if element is not found don't do anything
			if (index != -1){
				// if element found
				// condition 1 - if chain_arr[index] != -1 
				// this means the current element is a part of a chain
				if(chain_arr[index] != -1){
					// linear search to find out the location at which the current element
					// address was stored 
					// once that position is found set that position to the data 
					// stored at chain_arr[index]
					// then set both ele_arr[index] and chain_arr[index] = -1
					for (int i = 0; i < n; i++){
						if (chain_arr[i] == index){
							chain_arr[i] = chain_arr[index];
							chain_arr[index] = -1;
							ele_arr[index] = -1;
							break;
						}
					}
				}
				// condition 2 - if chain_arr[index] == -1
				// this means the element is not a part of any chain
				// directly set ele_arr[index] = -1
				else{
					ele_arr[index] = -1;
				}
			}
		}
};

// test functions
int main(){
	chain_without_replacement map;
	int element, members;
	cout<<"Enter the number of members:";
	cin>>members;
	for(int i = 0; i < members; i++){
		cout<<"Enter the element: ";
		cin>>element;
		map.map_element(element);
	}
	
	map.show_map();
	cout<<endl;
	map.show_chain();
	cout<<endl;
	map.get_ele(42);
	map.del_ele(21);
	cout<<endl;
	map.show_map();
	cout<<endl;
	map.show_chain();
	return 0;
}
