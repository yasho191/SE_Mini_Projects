#include<iostream>// standard i/o
#include<fstream>//Files
#include<cstring>//string comparator;
#include<conio.h>
#include<string>// string operations
#include<algorithm>
#include<lexical_cast.h> // used for type casting
#include<stdlib.h>//Alternative to clrscr();
#include<iomanip>// string padding

using namespace std;


//main class 
class phoneBook{
	
	// Node
	// Creating a DLL to store the data in the program
	// Considered fields (Name/ Phone Number/ Telephone Number)
	struct details{
		details *next;
		details *prev;
		long long int phone_number;
		long long int telephone_number;
		char name[100];
	}*start, *end;
	
	//Delcaring variables for File Operations
	ofstream output;
	ifstream input;
	
	public:
		//Default Constructor
		phoneBook(){
			start = NULL;
			end = NULL;
		}
		
		// Different methods of Phone Book
		
		void new_contact();// Add ne contact
		void update_contact();// Update Existing Contact
		void search_contact_by_name();// Search Contact using Name
		void search_contact_by_number();// Search Contact using Number
		void del_contact();// Delete Existing Contact
		void display();//Display all the contacts in the Phone Book
		void get_data();
		void feed_data();
		void summary();// Statistics
		bool validate_phone(long long int);// Validates a Phone Number
		void sort();
		void partial_name_search(); //Searches for names starting wit particular sequence of characters
		void partial_number_search();// Searches for numbers starting with particular sequence of numbers
};


//Time complexity O(n^2)
// Sorts the Directory in Alphabetical Order
// Bubble Sort
void phoneBook::sort(){
	int count = 0;
	details *temp, *curr, *t;
	t = new details;
	t->next = NULL;
	t->prev = NULL;
	
	// Counting the total elements in the directory
	temp = start;
	while(temp->next!=NULL){
		count++;
		temp = temp->next;
	}
	
	// Bubble Sort Logic
	for(int i = 0; i < count; i++){
		temp = start;
		temp = temp->next;
		curr = temp->prev;
		for(int j = 0; j < count-i; j++){
			if(strcmp(curr->name, temp->name) > 0){
				// Swap
				// Copy String
				strcpy(t->name, curr->name); 
				t->phone_number = curr->phone_number;
				t->telephone_number = curr->telephone_number;
				
				strcpy(curr->name, temp->name);
				curr->phone_number = temp->phone_number;
				curr->telephone_number = temp->telephone_number;
				
				strcpy(temp->name, t->name);
				temp->phone_number = t->phone_number;
				temp->telephone_number = t->telephone_number;
			}
			curr = temp;
			temp = temp->next;
		}
	}
	
	
}


//Time Complexity O(n)
// Checks if there is a Number similar to that of entered Number
void phoneBook::partial_number_search(){
	char str[100];
	int counter = 0;
	
	
	cout<<"Enter the name of the Person :";
	cin.ignore();
	cin.getline(str, 100);
	cout<<endl;
	
	details *temp;
	temp = start;
	
	while(temp!=NULL){
		// type casting the phone number and telephone number
		string phone_num = boost::lexical_cast<string>(temp->phone_number);
		string tele_num = boost::lexical_cast<string>(temp->telephone_number);
		
		// comparing the numbers with entered number sequence
		if(strncmp(phone_num.c_str(), str, strlen(str))==0 || strncmp(tele_num.c_str(), str, strlen(str))==0){
			counter ++;
			string t_num = boost::lexical_cast<string>(temp->telephone_number);
			cout<<"\t\t\t\t\t\t\t\t----------------------------------------------"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Name             :"<<string (temp->name).insert(strlen(temp->name), 25 - strlen(temp->name), ' ')<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Phone Number     :"<<temp->phone_number<<setw(16)<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Telephone Number :"<<t_num.insert(t_num.length(), 25 - t_num.length(), ' ')<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t----------------------------------------------"<<endl;
			cout<<endl;
		}
		temp = temp->next;
	}
	
	// If no contacts start with the mentioned string then:
	if (counter == 0){
		cout<<"No entry found..."<<endl;
	}
	else{
		cout<<"Total entries found in the directory are :"<<counter<<endl;
	}
}


//Time Complexity O(n)
// Checks if there is a Name similar to that of entered string
void phoneBook::partial_name_search(){
	char str[100];
	int counter = 0;
	
	cout<<"Enter the name of the Person :";
	cin.ignore();
	cin.getline(str, 100);
	cout<<endl;
	
	details *temp;
	temp = start;
	
	while(temp!=NULL){
		// Finds if the word starts with the entered squence of charachters
		if (strncmp(temp->name, str, strlen(str)) == 0){
			counter ++;
			string t_num = boost::lexical_cast<string>(temp->telephone_number);
			cout<<"\t\t\t\t\t\t\t\t----------------------------------------------"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Name             :"<<string (temp->name).insert(strlen(temp->name), 25 - strlen(temp->name), ' ')<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Phone Number     :"<<temp->phone_number<<setw(16)<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Telephone Number :"<<t_num.insert(t_num.length(), 25 - t_num.length(), ' ')<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t----------------------------------------------"<<endl;
			cout<<endl;
		}
		temp = temp->next;
	}
	
	// If no contacts start with the mentioned string then:
	if (counter == 0){
		cout<<"No entry found..."<<endl;
	}
	else{
		cout<<"Total entries found in the directory are :"<<counter<<endl;
	}
	
}


//Time Complexity O(1)
// Checks validity of the entered phone number
bool phoneBook::validate_phone(long long int number){
	int valid = 10;
	string s1 = boost::lexical_cast<string>(number);
	int len = s1.length();
	
	if (len == valid){
		return true;
	}
	else{
		cout<<"Entered number is invalid!"<<endl;
		return false;
	}
}

//Function Definition
//Time Complexity )=O(1)
void phoneBook::new_contact(){
	int ans;
	details *temp;
	temp = new details;
	temp->next = NULL;
	temp->prev = NULL;
	// Getting the input fields
	cout<<"Enter the name of the Person: ";
	cin.ignore();//Important to use before every cin.getline() call
	cin.getline(temp->name, 100);
	
	// Check if the entered number is valid
	// If number not valid ask user to enter the number
	// Loop continues till user inputs 10 digit Number
	bool check = false;
	while (check == false){
		cout<<"Enter the contact number of the Person: ";
		cin>>temp->phone_number;
		check = validate_phone(temp->phone_number);
	}
	
	//Optional Telephone Number
	cout<<"Do you want to enter a Telephone Number? Press 1 for yes: ";
	cin>>ans;
	
	if(ans == 1){
		cout<<"Enter the Telephone Number: ";
		cin>>temp->telephone_number;
	}
	else{
		temp->telephone_number = 0;
	}
	
	if (start == NULL){
		start = temp;
		end = temp;
	}
	else{
		temp->prev = end;
		end->next = temp;
		end = temp;
	}
	cin.ignore();
}


//Time Complexity O(n)
void phoneBook::search_contact_by_name(){
	//Creating Local variables for getting the data
	char person[100];
	int counter = 0;
	
	cout<<"Enter the name of the Person :";
	cin.ignore();
	cin.getline(person, 100);
	cout<<endl;
	//cout<<person;
	
	details *temp;
	temp = start;
	
	//DLL Traversal
	while(temp != NULL){
		//Comparing strings to get a match
		if(strcmp(temp->name, person) == 0){
			counter ++;
			cout<<"Details :"<<endl;
			string t_num = boost::lexical_cast<string>(temp->telephone_number);
			cout<<"\t\t\t\t\t\t\t\t----------------------------------------------"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Name             :"<<string (temp->name).insert(strlen(temp->name), 25 - strlen(temp->name), ' ')<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Phone Number     :"<<temp->phone_number<<setw(16)<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Telephone Number :"<<t_num.insert(t_num.length(), 25 - t_num.length(), ' ')<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t----------------------------------------------"<<endl;
			cout<<endl;
		}
		temp = temp->next;
	}
	//If counter == 0 (No records found)
	if (counter == 0){
		cout<<"No entry found..."<<endl;
	}
	else{
		cout<<endl;
		if (counter > 1){
			cout<<"Alert!"<<endl;
			cout<<"Multiple records with same name found!"<<endl;
		}
		cout<<"Total entries found :"<<counter<<endl;
	}
	
	//cout<<&temp;
}


//Time Complexity O(n)
void phoneBook::search_contact_by_number(){
	//Creating Local variables for getting the data
	int counter = 0;
	long long int number;
	
	cout<<"Enter the number of the Person :";
	cin>>number;
	//cout<<number;
	details *temp;
	temp = start;
	
	//DLL traversal
	while(temp != NULL){
		if(temp->phone_number == number){
			counter ++;
			cout<<"Details :"<<endl;
			string t_num = boost::lexical_cast<string>(temp->telephone_number);
			cout<<"\t\t\t\t\t\t\t\t----------------------------------------------"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Name             :"<<string (temp->name).insert(strlen(temp->name), 25 - strlen(temp->name), ' ')<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Phone Number     :"<<temp->phone_number<<setw(16)<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Telephone Number :"<<t_num.insert(t_num.length(), 25 - t_num.length(), ' ')<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t----------------------------------------------"<<endl;
			cout<<endl;
		}
		temp = temp->next;
	}
	if (counter == 0){
		cout<<"No entry found..."<<endl;
	}
	else{
		cout<<"Total entries found :"<<counter<<endl;
	}
	
}


//Time Complexity O(n)
void phoneBook::update_contact(){
	
	// To update a contact the two steps are:
	// Find the record
	// Access the record and ask for the new values
	// If no record found print a message "No record found"
	
	char person[100];
	int counter = 0;
	cout<<"Enter the name of the Person :";
	cin.ignore();
	cin.getline(person, 100);
	
	details *temp;
	temp = start;
	
	while(temp != NULL){
		if(strcmp(temp->name, person) == 0){
			counter ++;
			string t_num = boost::lexical_cast<string>(temp->telephone_number);
			cout<<"\t\t\t\t\t\t\t\t----------------------------------------------"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Name             :"<<string (temp->name).insert(strlen(temp->name), 25 - strlen(temp->name), ' ')<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Phone Number     :"<<temp->phone_number<<setw(16)<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Telephone Number :"<<t_num.insert(t_num.length(), 25 - t_num.length(), ' ')<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t----------------------------------------------"<<endl;
			cout<<endl;
			break;
		}
		temp = temp->next;
	}
	if (counter == 0){
		cout<<"No entry found..."<<endl;
	}
	else{
		cout<<"Total entries found :"<<counter<<endl;
		char n[100];
		int flag;
		do{
			int option;
			cout<<"Which details do you want to update?\n1. Name\n2. Phone Number\n3. Telephone Number"<<endl;
			cin>>option;
			if (option == 1){
				cout<<"Enter the new Name :";
				cin.ignore();
				cin.getline(temp->name, 100);
				cout<<"The name of the person is updated..."<<endl;
			}
			else if(option == 2){
				// Check if the entered number is valid
				// If number not valid ask user to enter the number
				// Loop continues till user inputs 10 digit Number
				bool check = false;
				while (check == false){
					cout<<"Enter the contact number of the Person: ";
					cin>>temp->phone_number;
					check = validate_phone(temp->phone_number);
				}
				cout<<"The Phone Number of the person is updated..."<<endl;
			}
			else if(option == 3){
				cout<<"Enter the new Telphone Number :";
				cin>>temp->telephone_number;
				cout<<"The Telphone Number of the person is updated..."<<endl;
			}
			else{
				cout<<"Invalid Value!"<<endl;
			}
			
			cout<<"Do you you want to update any other details? Press 1 for yes"<<endl;
			cin>>flag;
			
		}while(flag == 1);
	}
	
	//details* temp;
	//temp = search_contact_by_name();
	//cout<<temp;
	//cin.ignore();
}


//Time Complexity O(n)
void phoneBook::display(){
	//Simple traversal for displaying all Phone Book Numbers.
	details* temp;
	temp = start;
	if(start == NULL){
		cout<<"The contact list is empty."<<endl;
	}
	else{
		while(temp!=NULL){
			string t_num = boost::lexical_cast<string>(temp->telephone_number);
			cout<<"\t\t\t\t\t\t\t\t----------------------------------------------"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Name             :"<<string (temp->name).insert(strlen(temp->name), 25 - strlen(temp->name), ' ')<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Phone Number     :"<<temp->phone_number<<setw(16)<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t| Telephone Number :"<<t_num.insert(t_num.length(), 25 - t_num.length(), ' ')<<"|"<<endl;
			cout<<"\t\t\t\t\t\t\t\t----------------------------------------------"<<endl;
			cout<<endl;
			temp = temp->next;
		}
	}
}


//Time Complexity O(n)
void phoneBook::del_contact(){
	char person[100];
	int counter =0;
	cin.ignore();
	cout<<"Enter the name of the Person :";
	cin.getline(person, 100);
	details *temp, *back, *front;
	temp = start;
	
	//Phone Book Empty Condition
	if(start == NULL){
		cout<<"The PhoneBook is empty!"<<endl;
	}
	else{
		//Start Searching....
		while(temp != NULL){
			if(strcmp(temp->name, person) == 0){
				counter ++;
				break;
			}
			temp = temp->next;
		}
		//No entry found condition
		if (counter == 0){
			cout<<"No entry found..."<<endl;
		}
		//Entry Found
		else{
			// Check for different conditions
			// Delete Start
			// Delete End
			// Delete Middle
			if((temp == start)&&(temp == end)){
				cout<<start->name<<" has been deleted successfully"<<endl;
				delete start;
				start = NULL;
				end = NULL;
			}
			else if(temp == start){
				temp = temp->next;
				cout<<start->name<<" has been deleted successfully"<<endl;
				delete start;
				temp->prev = NULL;
				start = temp;
			}
			else if(temp == end){
				temp = temp->prev;
				temp->next = NULL;
				cout<<end->name<<" has been deleted successfully"<<endl;
				delete end;
				end = temp;
			}
			else{
				front = temp->next;
				back = temp->prev;
				front->prev = back;
				back->next = front;
				cout<<temp->name<<" has been deleted successfully"<<endl;
				delete temp;
			}
			
		}
	}
	
}


//Extracting Data from the txt file to Our DLL
//Time Complexity O(n)
void phoneBook::get_data(){
	details *temp;
	//Open PhoneBook file
	input.open("phonebook.txt");
	
	while(input){
		temp = new phoneBook::details;
		temp->next = NULL;
		temp->prev = NULL;
		
		input.getline(temp->name, 100);
		input>>temp->phone_number;
		input>>temp->telephone_number;
		
		// Eliminate any char at the end of the line like \n or a space " "
		input.get();
		
		//Create DLL
		if(start == NULL){
			start = temp;
			end = temp;
		}
		else{
			temp->prev = end;
			end->next = temp;
			end = temp;
		}
		// If no input can be found break the loop.
		if(!input){
			break;
		}
		
	}
	//close the file
	input.close();
}


//Updating the data in the text file writting all the changes to the file.
//Time Complexity O(n)
void phoneBook::feed_data(){
	details *temp;
	temp = start; 
	
	//Open PhoneBook file
	output.open("phonebook.txt");
	
	if(start == NULL){
		cout<<"No data available to feed into the database..."<<endl;
	}
	else{
		while(temp!=NULL){
			if(temp == end){
				output<<temp->name<<endl;
				output<<temp->phone_number<<endl;
				output<<temp->telephone_number;
			}
			else{
				output<<temp->name<<endl;
				output<<temp->phone_number<<endl;
				output<<temp->telephone_number<<endl;
			}
			/*
			output<<temp->name<<endl;
			output<<temp->phone_number<<endl;
			output<<temp->telephone_number<<endl;
			*/
			temp = temp->next;
		}
	}
	
	//close file
	output.close();
}


//Gives total number of contacts and total contacts with telephone
void phoneBook::summary(){
	int count_arr[26] = {0};
	int count = 0;
	int t_count = 0;
	details* t=start;
	while(t != NULL){
		if (t->telephone_number){
			t_count++;
		}
		char ts = (t->name)[0];
		if (ts >=97 && ts<= 122){  //converts to lowercase
			ts = ts-32;
		}
		count_arr[ts-65]++;
		count++;
		t = t->next;
	}
	cout << "Summary"<<endl;
	cout << "Total Contacts             :" << count << endl;
	cout << "Contacts with telephone    :" << t_count << endl;
	cout << "Most frequent first letter :" << char(max_element(count_arr,count_arr+26)-count_arr+65) << endl;
}



//Driver Code
int main(){
	
	//Creating an Object of Class phoneBook
	phoneBook obj1;
	
	//Initializing DLL
	obj1.get_data();
	obj1.sort();
	
	//Menu Driven Operations
	int cont = 1;
	
	while(cont == 1){
		cout<<"\t\t\t\t\t\t\t\t\t\tPhone Directory"<<endl;
		cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t1. Display the complete Directory"<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t2. Search Contact by Name"<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t3. Search Contact by Number"<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t4. Update a Contact"<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t5. Insert a New Contact"<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t6. Delete a Contact"<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t7. Summary"<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t8. Partial Name Search"<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t9. Partial Number Search"<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t10. Exit"<<endl;
		cout<<"------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<endl;
		
		int option;
		cout<<"Enter your option :";
		cin>>option;
		
		switch(option){
			case 1:{
				cout<<endl;
				obj1.sort();
				cout<<"Displaying the current Phone Directory:"<<endl;
				obj1.display();
				break;
			}
			case 2:{
				cout<<endl;
				obj1.search_contact_by_name();
				cout<<endl;
				break;
			}
			case 3:{
				cout<<endl;
				obj1.search_contact_by_number();
				cout<<endl;
				break;
			}
			case 4:{
				cout<<endl;
				obj1.update_contact();
				cout<<endl;
				break;
			}
			case 5:{
				cout<<endl;
				obj1.new_contact();
				cout<<"The contact has been successfully added to your directory."<<endl;
				cout<<endl;
				break;
			}
			case 6:{
				cout<<endl;
				obj1.del_contact();
				cout<<endl;
				break;
			}
			case 7:{
				cout<<endl;
				obj1.summary();
				cout<<endl;
				break;
			}
			case 8:{
				cout<<endl;
				obj1.partial_name_search();
				cout<<endl;
				break;
			}
			case 9:{
				cout<<endl;
				obj1.partial_number_search();
				cout<<endl;
				break;
			}
			case 10:{
				//Update all changes to our file
				obj1.feed_data();
				cout<<"You have successfully exited the application!"<<endl;
				cout<<"All the modifications done have been successfully saved!"<<endl;
				cout<<"Thankyou!"<<endl;
				exit(1);
				break;
			}
			default:{
				cout<<endl;
				cout<<"Invalid Input!"<<endl;
				cout<<endl;
				break;
			}
			
		}
		char a;
		cout<<"Press any key to continue:";
		cin>>a;
		//Clear Screen After Every Operation.
		system("CLS");
			
	}
	
	return 0;
}


