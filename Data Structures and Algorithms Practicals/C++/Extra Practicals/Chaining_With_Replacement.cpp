#include<iostream>

using namespace std;

class chain_with_replacement{
	// private members 
	int ele_arr[10];
	int chain_arr[10];
	int n;
	
	public:
		
		// Constructor
		// Initialize element array and chain array with -1
		// Set size of Hashmap = 10
		chain_with_replacement(){
			for (int i = 0; i < n; i++){
				ele_arr[i] = -1;
				chain_arr[i] = -1;
			}
			n = 10;
		}
		
		// Hash Function
		int hash(int element){
			return element % n;
		}
		
		// Display Chain array
		void show_chain(){
			cout<<"The current chaning array is:"<<endl;
			for(int i = 0; i < n; i++){
				cout<<chain_arr[i]<<" ";
			}
		}
		
		// Display element array
		void show_map(){
			cout<<"The current Hashmap is :"<<endl;
			for (int i = 0; i < n; i++){
				cout<<ele_arr[i]<<" ";
			}
		}
		
		// Inserting Elements
		// 3 Conditions
		void map_ele(int element){
			// get hash code for element
			int code = hash(element);
			
			// case 1
			// if the ele_arr[code] is -1 directly set the element to that position
			// chain array will not be modified
			if (ele_arr[code] == -1){
				ele_arr[code] = element;
			}
			// Case 2
			else{
				// set flag for checking if element was successfully inserted or not
				int flag1 = 0;
				int flag2 = 0;
				// sec_code is the hash code of data at ele_arr[code] where collision has occured
				int sec_code = hash(ele_arr[code]);
				// maintain next variable for iterating the chain
				int next;
				
				// Case 2a
				// if the hash code do not match 
				if (sec_code != code){
					// in this case we will set ele_arr[code] to correct value
					// the value we are replacing must be taken care of
					// store this value in varible called removed_ele
					int removed_ele = ele_arr[code];
					ele_arr[code] = element;
					flag1 = 1;
					int prev;
					// next step is to break previous link and form new link
					// iterate through the chain array if we get the link
					// set that to the chain array data stored at previous location 
					for(int i = 0; i < n; i++){
						if (chain_arr[i] == code){
							prev = chain_arr[i-1];
							chain_arr[i] = chain_arr[code];
							break;
						}
					}	
					// save the chain array data in next
					// now we will use this next to iterate through the chain
					if(chain_arr[code] != -1){
						next = chain_arr[code];
					}
					else{
						next = prev;
					}
					// set the current chain array location to -1 as now links are currently formed
					chain_arr[code] = -1;
					
					// the next step is to find a postion for the removed element
					// this will require the following steps
					// find the end of the chain
					// linear search for next vacant spot
					// assigning the data to position found
					// creating a link with the last chain position
					while(chain_arr[next] != -1){
						next = chain_arr[next];
						cout<<next<<endl;
					}
					
					
					for (int j = next; j < next+n; j++){
						if(ele_arr[j%n] == -1){
							ele_arr[j%n] = removed_ele;
							chain_arr[next] = j%n;
							flag2 = 1;
							break;
						}
					}
					
					// if the element array gets full the removed element would be left out
					if(flag2 == 0){
						cout<<removed_ele<<" could not be inserted into the hash map"<<endl;
					}
				}
				else{
					// case 2b
					// if the hashcodes match, the procedure will be same as chaining without replacement
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
							ele_arr[i % n] = element;
							chain_arr[code] = i % n;
							flag = -1;
							break;
						}
					}
					
					if (flag == 0){
						cout<<element<<" could not be inserted into the hash map as the has map is full!"<<endl;
					}
				}
				
			}
		}
		
		// find hash code of element to be found
		int get_element(int element){
			int to_be_found = element;
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
					i = chain_arr[i];
					if(ele_arr[i] == to_be_found){
						cout<<"Element found at position: "<<i;
						flag = 1;
						return i;
					}		
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
			int index = get_element(element);
			
			// if element is not found don't do anything
			if (index != -1){
				// linear search to find out the location at which the current element
				// address was stored 
				// once that position is found set that position to the data 
				// stored at chain_arr[index]
				// then set both ele_arr[index] and chain_arr[index] = -1
				if(chain_arr[index] != -1){
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

int main(){
	chain_with_replacement map;
	int element, members;
	cout<<"Enter the number of members:";
	cin>>members;
	for(int i = 0; i < members; i++){
		cout<<"Enter the element: ";
		cin>>element;
		map.map_ele(element);
	}
	
	map.show_map();
	cout<<endl;
	map.show_chain();
	cout<<endl;
	map.get_element(10);
	cout<<endl;
	map.del_ele(11);
	cout<<endl;
	map.show_map();
	cout<<endl;
	map.show_chain();
	cout<<endl;
	map.map_ele(42);
	cout<<endl;
	map.show_map();
	cout<<endl;
	map.show_chain();
}
