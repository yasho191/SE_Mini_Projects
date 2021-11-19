#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstring>
# define MAX 1000
using namespace std;

class seq_file{
    struct record{
        int student_id;
        char student_name[30];
        char student_department[30];
    }r;

    int deleted_records[MAX];
    int deleted_records_counter;

    public:

    seq_file(){
        for (int i = 0; i < MAX; i++){
            deleted_records[i] = -1;
        }
        deleted_records_counter = 0;
    }

    void insert_record();
    void search_record();
    void modify_record();
    void delete_record_physically();
    void delete_record_logically();
};

void seq_file::insert_record(){
    ofstream out;
    int flag = 1;

    out.open("student_records.data", ios::app|ios::binary);
    out.seekp(0, ios::end);
    while(true){
        cout<<"Enter the student id: ";
        cin>>r.student_id;
        cout<<"Enter the name of the student: ";
        cin>>r.student_name;
        cout<<"Enter the department of the student";
        cin>>r.student_department;
        out.write((char *)&r, sizeof(r));

        cout<<"Do you want to add another record?";
        cin>>flag;

        if (!flag){
            break;
        }
    }
    out.close();
}

void seq_file::search_record(){
    int id;
    cout<<"Enter the student ID of the employee: ";
    cin>>id;
    for (int i = 0; i<deleted_records_counter; i++){
        if(deleted_records[i] == id){
            cout<<"Record not found!"<<endl;
            return;
        }
    }
    int flag = 0;
    ifstream in;
    in.open("student_records.data", ios::in | ios::binary);
    while(in.read((char *)&r, sizeof(r))){
        if(r.student_id == id){
            cout<<endl;
            cout<<"Record found!"<<endl;
            cout<<"ID: "<<r.student_id<<endl;
            cout<<"Name: "<<r.student_name<<endl;
            cout<<"Department: "<<r.student_department<<endl;
            cout<<endl;
            flag = 1;
            break;
        }
    }
    if(!flag){
        cout<<"Record not found!"<<endl;
    }
    in.close();
}

void seq_file::modify_record(){
    int id, flag=0, counter=0;
    char student_name[30], student_department[30];
    cout<<"Enter the ID of the student: ";
    cin>>id;
    cout<<"Enter new student Name";
    cin>>student_name;
    cout<<"Enter new department";
    cin>>student_department;

    for (int i = 0; i<deleted_records_counter; i++){
        if(deleted_records[i] == id){
            cout<<"Record not found!"<<endl;
            return;
        }
    }

    fstream file;
    file.open("student_records.data", ios::in|ios::out|ios::binary);
    while (file.read((char *)&r, sizeof(r)))
    {
        if (r.student_id == id){
            cout<<"Record found!";
            file.seekp(sizeof(r)*counter, ios::beg);
            r.student_id =id;
            strcpy(r.student_name, student_name);
            strcpy(r.student_department, student_department);
            file.write((char *)&r, sizeof(r));
            flag = 1;
            break;
        }
        counter++;
    }
    if(!flag){
        cout<<"Record not found"<<endl;
    }
    file.close();  
}

void seq_file::delete_record_physically(){
    int id, flag=0;
    cout<<"Enter the empoyee id: ";
    cin>>id;

    ifstream file1;
    ofstream file2;
    file1.open("student_records.data", ios::in | ios::binary);
    file2.open("new_student_records.data", ios::out | ios::binary);

    while(file1.read((char *)&r, sizeof(r))){
        
        if(r.student_id != id){
            file2.write((char *)&r, sizeof(r));
        }
    }
    file1.close();
    file2.close();

    remove("student_records.data");
    rename("new_student_records.data", "student_records.data");
    
    cout<<"Record successfully deleted!"<<endl;
}

void seq_file::delete_record_logically(){
    int id, flag = 0;
    cout<<"Enter thestudent id: ";
    cin>>id;
    
    ifstream in;
    in.open("student_records.data", ios::in | ios::binary);
    while(in.read((char *)&r, sizeof(r))){
        if(r.student_id == id){
            deleted_records[deleted_records_counter] = id;
            deleted_records_counter++;
            flag = 1;
            break;
        }
    }
    if(!flag){
        cout<<"The record has been deleted!"<<endl;
    }
    in.close();
}

int main(){
    seq_file obj;
    int option, cont=0;

    while(true){
        cout<<endl;
        cout<<"Menu: "<<endl;
        cout<<"1. Insert record"<<endl;
        cout<<"2. Modify record"<<endl;
        cout<<"3. Search record"<<endl;
        cout<<"4. Delete record physically"<<endl;
        cout<<"5. Delete record logically"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<"Select one option:";
        cin>>option;
        cout<<endl;

        switch (option)
        {
            case 1:{
                obj.insert_record();
                break;
            }
            case 2:{
                obj.modify_record();
                break;
            }
            case 3:{
                obj.search_record();
                break;
            }
            case 4:{
                obj.delete_record_physically();
                break;
            }
            case 5:{
                obj.delete_record_logically();
                break;
            }  
            case 6:{
                cont = 1;
                break;
            } 
            default:{
                cout<<"Invalid Option!"<<endl;
                break;
            }
             
        }
        if(cont){
            break;
        } 
    }
    
}