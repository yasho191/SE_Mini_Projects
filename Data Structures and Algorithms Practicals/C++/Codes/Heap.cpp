#include<iostream>
#include<string.h>
# define max 100
using namespace std;

class MaxHeap{

    int heap_arr[max];
    int last_index;

    public:

    MaxHeap(){
        for (int i = 0; i < max; i++){
            heap_arr[i] = -1;
        }
        last_index = 0;
    }

    void insert(int);
    void display();
    void get_max();

};

void MaxHeap::get_max(){
    cout<<"The maximum element in the heap is: "<<heap_arr[0]<<endl;
}

void MaxHeap::insert(int data){
    heap_arr[last_index] = data;
    // cout<<"Position assigned: "<<last_index<<endl;

    if (last_index==0){
        last_index++;
        return;
    }

    int last = last_index;
    int parent_checker = (last_index-1)/2;
    // cout<<parent_checker<<endl;
    // cout<<last<<endl;

    int flag = 0;
    int swaps = 0;

    while(flag != 1 && parent_checker >= 0){
        // cout<<"Loop entered"<<endl;
        if(heap_arr[last] <= heap_arr[parent_checker]){
            //cout<<"Loop Exited"<<endl;
            flag = 1;
            break;
        }
        else{
            int temp = heap_arr[last];
            heap_arr[last] = heap_arr[parent_checker];
            heap_arr[parent_checker] = temp;
            last = parent_checker;
            swaps++;
            parent_checker = (parent_checker-1)/2;
            // cout<<"Parent: "<<parent_checker<<endl;
            // cout<<"Last: "<<last<<endl;
        }
    }
    last_index = last_index + 1;
    // cout<<"Total Swaps: "<<swaps<<endl;
}

void MaxHeap::display(){
    for (int i = 0; i < last_index; i++){
        cout<<heap_arr[i]<<" ";
    }
    cout<<endl;
}



class MinHeap{

    int heap_arr[max];
    int last_index;

    public:

    MinHeap(){
        for (int i = 0; i < max; i++){
            heap_arr[i] = -1;
        }
        last_index = 0;
    }

    void insert(int);
    void display();
    void get_min();

};

void MinHeap::get_min(){
    cout<<"The minimum element in the heap is: "<<heap_arr[0]<<endl;
}

void MinHeap::insert(int data){
    heap_arr[last_index] = data;
    // cout<<"Position assigned: "<<last_index<<endl;

    if (last_index==0){
        last_index++;
        return;
    }

    int last = last_index;
    int parent_checker = (last_index-1)/2;
    // cout<<parent_checker<<endl;
    // cout<<last<<endl;

    int flag = 0;
    int swaps = 0;

    while(flag != 1 && parent_checker >= 0){
        // cout<<"Loop entered"<<endl;
        if(heap_arr[last] >= heap_arr[parent_checker]){
            // cout<<"Loop Exited"<<endl;
            flag = 1;
            break;
        }
        else{
            int temp = heap_arr[last];
            heap_arr[last] = heap_arr[parent_checker];
            heap_arr[parent_checker] = temp;
            last = parent_checker;
            swaps++;
            parent_checker = (parent_checker-1)/2;
            // cout<<"Parent: "<<parent_checker<<endl;
            // cout<<"Last: "<<last<<endl;
        }
    }
    last_index = last_index + 1;
    // cout<<"Total Swaps: "<<swaps<<endl;
}

void MinHeap::display(){
    for (int i = 0; i < last_index; i++){
        cout<<heap_arr[i]<<" ";
    }
    cout<<endl;
}




int main(){
    
    while (true){
        int heap;
        int uni_flag=1;
        cout<<"Heaps:"<<endl;
        cout<<"1. Min Heap"<<endl;
        cout<<"2. Max Heap"<<endl;
        cout<<"3. Exit Program"<<endl;
        cout<<"Enter the Heap you want to use: ";
        cin>>heap;
        switch (heap){
            case 1:{
                MinHeap min_h;
                int option;
                int min_flag=1;
                while(true){
                    cout<<"Menu:"<<endl;
                    cout<<"1. Insert Data"<<endl;
                    cout<<"2. Display Heap"<<endl;
                    cout<<"3. Show Minimum Element"<<endl;
                    cout<<"4. Exit Min Heap"<<endl;
                    cout<<"Enter your choice: ";
                    cin>>option;

                    switch(option){
                        case 1:{
                            int data;
                            cout<<"Enter data: ";
                            cin>>data;
                            min_h.insert(data);
                            break;
                        }
                        case 2:{
                            cout<<"Current state of heap is: "<<endl;
                            min_h.display();
                            break;
                        }
                        case 3:{
                            min_h.get_min();
                            break;
                        }
                        case 4:{
                            min_flag = 0;
                            break;
                        }
                        default:{
                            cout<<"Invalid Option!"<<endl;
                            break;
                        }
                    }
                    if (!min_flag){
                        break;
                    } 
                }
                break;
            }
            case 2:{
                MaxHeap max_h;
                int option;
                int max_flag=1;
                while(true){
                    cout<<"Menu:"<<endl;
                    cout<<"1. Insert Data"<<endl;
                    cout<<"2. Display Heap"<<endl;
                    cout<<"3. Show Maximum Element"<<endl;
                    cout<<"4. Exit Max Heap"<<endl;
                    cout<<"Enter your choice: ";
                    cin>>option;

                    switch(option){
                        case 1:{
                            int data;
                            cout<<"Enter data: ";
                            cin>>data;
                            max_h.insert(data);
                            break;
                        }
                        case 2:{
                            cout<<"Current state of heap is: "<<endl;
                            max_h.display();
                            break;
                        }
                        case 3:{
                            max_h.get_max();
                            break;
                        }
                        case 4:{
                            max_flag = 0;
                            break;
                        }
                        default:{
                            cout<<"Invalid Option!"<<endl;
                            break;
                        }
                    }
                    if (!max_flag){
                        break;
                    } 
                }
                break;

            }
            case 3:{
                uni_flag = 0;
                break;
            }
            default:{
                cout<<"Invalid Option!"<<endl;
            }
        }
        if (!uni_flag){
            break;
        }
    }

    return 0;
}
