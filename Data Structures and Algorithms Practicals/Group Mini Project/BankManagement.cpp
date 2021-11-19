#include<iostream>
#include<fstream>
#include<cstring>
#include<string.h>
#include<algorithm>
#include<ctime>
#include<stdlib.h>
using namespace std;


// File Structure:
// Bank_Accounts File (Sequential File with Details of all acounts)
// Every Bank Account will have its own transaction file which will maintain the transactions of
// That particular bank account.
// To access these transaction files we will use a hash code
// the hash code is a 12 digit code generated using account holder credentials like:
// 1. Aadhar Number
// 2. NAME
// 3. Email
// Name convention used for transaction files is "hashcode"+"transactions.data"



// Example the Bank has 3 accounts
// Bank_Accounts.data:
// person1-info / person2-info / person3-info
// AccountNumber == HashCode Generated using person details
// 3 Separate files will be created named
// AccountNumberPerson1transaction.data / AccountNumberPerson2transaction.data / AccountNumberPerson3transaction.data
// These files will have info of every transaction made by that account holder form opening
// the account till the account is deleted. This will help in keeping record of all transactions
// the time stamp will help user in authenticating the transaction


// Class Bank 
// Will contain accounts of all people
class Bank{
    // Struct account details will store personal info of customer as well as the pin
    struct Account_Details{
        string account_number;
        string account_holder_name;
        string account_holder_email;
        string address;
        string gender;
        int age;
        int pin;
        long long int aadhar_number;
    }acc;

    // Struct Account_Transactions will store data related to transactions along with the pin
    struct Account_Transactions{
        int balance;
        int withdrawn;
        int deposited;
        string time_stamp;
        int pin;
    }trans;

    // Stores the total number of accounts in the bank
    int total_accounts;
    public:

    Bank(){
        // initialize total_accounts to 0
        total_accounts = 0;
    }

    string hash_key(long long int, string, string);
    string time_stamps();
    void withdraw();
    void deposit();
    void add_new_account();
    void delete_account();
    void modify_account_details();
    void search_account();
};

// Return time stamp at which a transaction has occured such as witdrawal and deposit
string Bank::time_stamps(){
    // Header file <ctime> required
    time_t now = time(0);
    tm *current_time = localtime(&now);
    // tm_year returns years from 1900 so we add 1900 to years
    int year = 1900 + current_time->tm_year;
    // Months are 0 based indexed so we add 1
    int month = 1 + current_time->tm_mon;
    int day = current_time->tm_mday;
    int hours = current_time->tm_hour;
    int mins = current_time->tm_min;
    int sec = current_time->tm_sec;

    return to_string(year)+"/"+to_string(month)+"/"+to_string(day)+" "+to_string(hours)+":"+to_string(mins)+":"+to_string(sec);
}

// Modify details of a account
// All details cannot be modified
// Only Age, Gender, Address fields can be changed
void Bank::modify_account_details(){
    string acc_number, gender, address; 
    int pin;
    int option, flag_1 = 1, flag_2=0, age;
    int a_flag=0, g_flag=0, ad_flag = 0;
    cout<<"Enter the Account Number: ";
    cin>>acc_number;
    cout<<"Enter your pin: ";
    cin>>pin;
    
    int counter = 0;
    // Take input for required changes
    while(true){
        cout<<"Menu: "<<endl;
        cout<<"1. Age"<<endl;
        cout<<"2. Gender"<<endl;
        cout<<"3. Address"<<endl;
        cout<<"Enter your choice: ";
        cin>>option;
        switch(option){
            case 1:{
                cout<<"Enter Age: ";
                cin>>age;
                a_flag = 1;
                break;
            }
            case 2:{
                cout<<"Enter Gender: ";
                cin>>gender;
                g_flag = 1;
                break;
            }
            case 3:{
                cout<<"Enter Address: ";
                cin>>address;
                ad_flag = 1;
                break;
            }
            default:{
                cout<<"Invalid Option!"<<endl;
                break;
            }
        }
        cout<<"Do you want to modify any other field? ";
        cin>>flag_1;
        if(!flag_1){
            break;
        }
    }
    
    fstream file;
    // open file in input mode
    file.open("Bank_Accounts.data", ios::in|ios::binary);
    
    while(file.read((char *)&acc, sizeof(acc))){
        if(acc_number == acc.account_number){
            // if account number matches check the pin and if pin matches
            // Proceed with the changes 
            // Else break 
            if (acc.pin == pin){
                file.close();
                cout<<counter;
                // Open file in write mode
                file.open("Bank_Accounts.data", ios::out|ios::binary);
                // file pointer should point record to be updated;
                file.seekp(sizeof(acc)*(counter), ios::beg);
                cout<<"Account Found"<<endl;
                cout<<"Changes Successfully applied!"<<endl;
                // Whichever flag is set thse records will be changed
                if(a_flag)
                acc.age=age;
                if(g_flag)
                acc.gender=gender;
                if(ad_flag)
                acc.address=address;
                file.write((char *)&acc, sizeof(acc));
                file.close();
                flag_2=1;
                break;
            }
            else{
                cout<<"Wrong PIN!"<<endl;
                file.close();
                break;
            }
            
        }
        counter++;  
    }
    if(!flag_2){
        cout<<"Account not found!"<<endl;
    }
    cout<<endl;
}

// Withdraw amount
void Bank::withdraw(){
    string account_number;
    int balance, withdraw_amount, pin;
    // input account number and pin
    cout<<"Enter your Bank Account Number: ";
    cin>>account_number;
    cout<<"Enter your pin: ";
    cin>>pin;

    fstream file;
    // Open transaction file and check for the pin
    // If pin does not match break and exit elese continue
    // Update transaction in transaction file
    string file_name = account_number+"transactions.data";
    file.open(file_name, ios::in|ios::binary);
    if(file){
        while(file.read((char *)&trans, sizeof(trans))){
            if(trans.pin != pin){
                cout<<"Wrong PIN!"<<endl;
                file.close();
                return;
            }
            balance = trans.balance;
        }
        file.close();
        
        cout<<"Your current balance is: "<<balance<<endl;
        cout<<"Enter the amount of money you would like to withdraw: ";
        cin>>withdraw_amount;
        // if withdral isgreater than balance break and print invalid transaction
        if(withdraw_amount > balance){
            cout<<"Transaction not possible due to insufficient balance!"<<endl;
        }
        else{
            file.open(file_name, ios::app|ios::binary);
            balance = balance - withdraw_amount;
            trans.balance = balance;
            trans.deposited = 0;
            trans.withdrawn = withdraw_amount;
            trans.time_stamp = time_stamps();
            file.seekp(0, ios::end);
            file.write((char *)&trans, sizeof(trans));
            file.close();
            cout<<"Withdrawal Successful..."<<endl;
            cout<<"Current balance: "<<trans.balance<<endl;
        }
    }
    else{
        cout<<"No such Account Exists!";
    }
    
}

void Bank::deposit(){
    string account_number;
    int balance, deposit_amount, pin;
    // input account number and pin
    cout<<"Enter your Bank Account Number: ";
    cin>>account_number;
    cout<<"Enter your pin: ";
    cin>>pin;

    // Open transaction file and check for the pin
    // If pin does not match break and exit elese continue
    // Update transaction in transaction file
    fstream file;
    string file_name = account_number+"transactions.data";
    file.open(file_name, ios::in|ios::binary);
    if(file){
        while(file.read((char *)&trans, sizeof(trans))){
            if(trans.pin != pin){
                cout<<"Wrong PIN!"<<endl;
                file.close();
                return;
            }
            balance = trans.balance;
        }
        file.close();
        file.open(file_name, ios::app|ios::binary);
        cout<<"Your current balance is: "<<balance<<endl;
        cout<<"Enter the amount of money you would like to deposit: ";
        cin>>deposit_amount;
        balance = balance + deposit_amount;
        trans.balance = balance;
        trans.deposited = deposit_amount;
        trans.withdrawn = 0;
        trans.time_stamp = time_stamps();
        file.seekp(0, ios::end);
        file.write((char *)&trans, sizeof(trans));
        cout<<"Money Sucessfully Deposited...."<<endl;
        cout<<"Current Account Balance: "<<balance<<endl;
        cout<<endl;
        file.close();
    }
    else{
        cout<<"No such Account Exists!";
    }
    
}

void Bank::add_new_account(){
    cout<<endl;
    cout<<"New account is being created..."<<endl;
    cout<<"Enter Bank Account Holder Name: ";
    cin>>acc.account_holder_name;
    cout<<"Enter the MailID of the Account Holder: ";
    cin>>acc.account_holder_email;

    while (true){
        cout<<"Enter Aadhar Number of the Account Holder: ";
        cin>>acc.aadhar_number;
        if(to_string(acc.aadhar_number).length() == 12){
            break;
        }
    }
    
    cout<<"Enter the Age of the Account Holder: ";
    cin>>acc.age;
    cout<<"Enter the Address of the Account Holder: ";
    cin>>acc.address;
    cout<<"Enter the gender of the Account Holder: ";
    cin>>acc.gender;
    acc.account_number = hash_key(acc.aadhar_number, acc.account_holder_name, acc.account_holder_email);

    fstream file;
    file.open(acc.account_number+"transactions.data", ios::in|ios::out|ios::binary);
    if(file){
        cout<<"Account already exists!"<<endl;
        file.close();
        return;
    }
    file.close();

    cout<<"Your Bank Account Number is: "<<acc.account_number<<endl;
    cout<<"Enter the pin you want to set: ";
    cin>>trans.pin;
    acc.pin = trans.pin;
    cout<<"Enter the Amount you want to deposit into your account: ";
    cin>>trans.balance;
    trans.deposited = 0;
    trans.withdrawn = 0;
    
    trans.time_stamp = time_stamps();

    string transaction_file_name = acc.account_number + "transactions.data";
    ofstream out;
    out.open("Bank_Accounts.data", ios::app|ios::binary);
    out.seekp(0, ios::end);
    out.write((char *)&acc, sizeof(acc));
    out.close();

    out.open(transaction_file_name, ios::app|ios::binary);
    out.seekp(0, ios::end);
    out.write((char *)&trans, sizeof(trans));
    out.close();
    cout<<"Bank Account successfully created..."<<endl;
    total_accounts++;

}


// Hash Function
string Bank::hash_key(long long int number, string str1, string str2){
    long long int hash_1 = 0;
    int multiplier = 227;
    // transform both the strings to lowercase
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
    // concat the strings
    string word = str1 + str2;

    // Use formula hash = hash*multiplier + word[char]
    // word[char] will directly get typecasted as integer
    for(int i=0; i<word.length(); i++){
        hash_1 = (hash_1 * multiplier) + word[i];
    }

    // Multiply the hash value by aadhar nuber
    // Take mod of hash
    long long int hash_2 = number * hash_1;
    hash_2 = hash_2 % 100000000000;

    // we now convert the hash to string
    string hash_3 = to_string(hash_2);
    
    // now every alternate number in hash code will get replaced by a char in word
    for(int i = 0; i<word.length(); i=i+2){
        if(hash_3.length()>i){
            hash_3[i] = word[i];
        }
    }

    // After these operations if the hash length is not 12
    // Either slice the hash or add more chars depending on its length
    if(hash_3.length()>12){
        hash_3 = hash_3.substr(0, 11);
    }
    else if(hash_3.length()<12){
        string num = to_string(number);
        int i = 0;
        while(hash_3.length()<12){
            hash_3 = hash_3 + num[i];
            i++;
        }
    }

    return hash_3;   
}

void Bank::delete_account(){
    string account_number;
    cout<<"Enter your Bank Account Number: ";
    cin>>account_number;
    
    int flag=0;
    
    ifstream file1;
    ofstream file2;
    file1.open("Bank_Accounts.data", ios::in | ios::binary);
    file2.open("New_Bank_Accounts.data", ios::out | ios::binary);

    while(file1.read((char *)&acc, sizeof(acc))){
        
        if(acc.account_number != account_number){
            file2.write((char *)&acc, sizeof(acc));
        }
        else{
            flag = 1;
        }
    }
    file1.close();
    file2.close();

    string transaction_file_name = account_number + "transactions.data";
    char char_arr[300];
    remove("Bank_Accounts.data");
    rename("New_Bank_Accounts.data", "Bank_Accounts.data");
    strcpy(char_arr, transaction_file_name.c_str());
    remove(char_arr);
    
    if (flag){
        cout<<"Record successfully deleted!"<<endl;
        total_accounts--;
    }
    else{
        cout<<"Account with provided credentials not found!"<<endl;
    }  
}

// Search will display the personal records and will also have an option to
// See the transactions of the account holder
void Bank::search_account(){
    string account_number;
    
    // Input pn and account number
    cout<<"Enter your Bank Account Number: ";
    cin>>account_number;
    int flag=0, t_details = 0, current_balance = 0;
    int pin;
    cout<<"Enter ypur pin: ";
    cin>>pin;

    ifstream in_1, in_2;
    in_1.open("Bank_Accounts.data", ios::in|ios::binary);
    while(in_1.read((char *)&acc, sizeof(acc))){
        // if account number and the pin both match the record show the data
        // Personal data will be followed by transaction data 
        if(account_number == acc.account_number && acc.pin == pin){
            cout<<"Account Found: "<<endl;
            cout<<"Account Details are as following: "<<endl;
            cout<<"Account Number: "<<acc.account_number<<endl;
            cout<<"Account Holder Name: "<<acc.account_holder_name<<endl;
            cout<<"Account Holder Email: "<<acc.account_holder_email<<endl;
            cout<<"Account Holder Gender: "<<acc.gender<<endl;
            cout<<"Account Holder Age: "<<acc.age<<endl;
            cout<<"Account Holder Address: "<<acc.address<<endl;
            cout<<"Account Holder Aadhar Number: "<<acc.aadhar_number<<endl;

            cout<<"Do you want to look at the transaction details? (Yes:1 | No:0)";
            cin>>t_details;
            if(t_details){
                cout<<"Displaying Transaction details: "<<endl;
                string trans_file = account_number+"transactions.data";
                in_2.open(trans_file, ios::in|ios::binary);
                while(in_2.read((char *)&trans, sizeof(trans))){
                    cout<<endl;
                    current_balance = trans.balance;
                    cout<<"Balance: "<<trans.balance<<endl;
                    cout<<"Deposited: "<<trans.deposited<<endl;
                    cout<<"Withdrawn: "<<trans.withdrawn<<endl;
                    cout<<"Time-Stamp: "<<trans.time_stamp;
                    cout<<endl;
                }
                cout<<"Your current Balance is: "<<current_balance<<endl;
            }
            else{
                cout<<"Details are as above"<<endl;
            }
            flag = 1;
        }
    }
    // If record is not found display essage 
    if(!flag){
        cout<<"No account was found! or you entered wrong pin...."<<endl;
    }
    // close both the files
    in_1.close();
    in_2.close();
}

int main(){
    Bank bank;
    int option, flag = 1;
    while(true){
        cout<<"Menu:"<<endl;
        cout<<"1. Create New Account"<<endl;
        cout<<"2. Delete Account"<<endl;
        cout<<"3. Search Account"<<endl;
        cout<<"4. Deposit Money"<<endl;
        cout<<"5. Withdraw Money"<<endl;
        cout<<"6. Change Account Details"<<endl;
        cout<<"7. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>option;

        switch(option){
            case 1:{
                bank.add_new_account();
                break;
            }
            case 2:{
                bank.delete_account();
                break;
            }
            case 3:{
                bank.search_account();
                break;
            }
            case 4:{
                bank.deposit();
                break;
            }
            case 5:{
                bank.withdraw();
                break;
            }
            case 6:{
                bank.modify_account_details();
                break;
            }
            case 7:{
                flag=0;
                break;
            }
            default:{
                cout<<"Invalid Option!"<<endl;
                break;
            }
        }
        if(!flag){
            break;
        }
    }
}