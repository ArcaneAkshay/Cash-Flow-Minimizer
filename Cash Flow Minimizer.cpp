#include <iostream>
#include<queue>
#include<map>
using namespace std;

// Cashflow Minimization Algorithm
/*
Output - Should also show transactions
Akshay pays 50 to Aman
Aman pays 10 to Niraj
2
*/

class person_compare_max_heap{
public:
    // Return true of the person1 has less money than person2
    bool operator()(pair<string,int> p1, pair<string,int> p2){
        return p1.second < p2.second;
    }
};

class person_compare_min_heap{
    public:
    // Return true of the person1 has more money than person2
    bool operator()(pair<string,int> p1, pair<string,int> p2){
        return p1.second > p2.second;
    }
};


int main(){

    int no_of_transactions,friends;
    
    cout<<"Enter the number of transactions : ";
    cin>>no_of_transactions;
    
    cout<<"Enter the number of friends : ";
    cin>>friends;

    string x,y;
    int amount;

    map<string,int> net;

    while(no_of_transactions--){
        cin>>x>>y>>amount;
        if(net.count(x)==0){
            net[x] = 0;
        }
        if(net.count(y)==0){
            net[y] = 0;
        }
        net[x] -= amount;
        net[y] += amount;
    }

    priority_queue<pair<string,int>,vector<pair<string,int>>, person_compare_max_heap> max_heap;
    priority_queue<pair<string,int>,vector<pair<string,int>>, person_compare_min_heap> min_heap;

    for(auto p:net){
        string person = p.first;
        int amount = p.second;

        if(net[person]>0){
            max_heap.push(make_pair(person,amount));
        }
        else if(net[person]<0){
            min_heap.push(make_pair(person,amount));
        }
    }
    
    //3. settlements

    int cnt = 0;
    while(!max_heap.empty() || !min_heap.empty()){

        //Access the max and min elements from max heap and min heap respectively

        auto max_heap_top = max_heap.top();
        auto min_heap_top = min_heap.top();

        int max_giver_amt = min_heap_top.second;
        string giver = min_heap_top.first;

        int max_receiver_amt = max_heap_top.second;
        string receiver = max_heap_top.first;

        //Settle the Transaction

        int settled_amount = min(-max_giver_amt,max_receiver_amt);
        max_giver_amt += settled_amount;
        max_receiver_amt -= settled_amount;


        //Pop them out
        max_heap.pop();
        min_heap.pop();

        //Print the Transaction between people
        cout<<giver<<" will pay "<<settled_amount<<" to "<<receiver<<endl;

        // Check if the transactions are settled or not
        if(max_giver_amt<0){
            min_heap.push(make_pair(giver,max_giver_amt));
        }
        if(max_receiver_amt>0){
            max_heap.push(make_pair(receiver,max_receiver_amt));
        }
        cnt += 1;
    }
    cout << "No of steps to settle the amount : " << cnt << endl;
    
return 0;
}