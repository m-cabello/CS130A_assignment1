# include <iostream>
# include <sstream>
# include "blockchain.h"
using namespace std;

int main(){
   Blockchain a;
    while(true){
        string question;
        int answer;
        question = "Welcome to the transaction-chain application....\n1) Add a transaction to the chain.\n2) Find balance of a person.\n3) Print the chain.\n4) Exit.\nWhich operation do you want to make? (1,2,3,4):";
        cout << question << endl << flush;
        cin >> answer;
        if (answer == 1){
            cout << "Integer amount of money:"<< endl;
            int amount;
            cin >> amount;
            cout << "Sender name"<< endl;
            string sender;
            cin >> sender;
            cout << "Receiver name" << endl;
            string receiver;
            cin >> receiver;
            a.add(amount, sender, receiver);
        }else if (answer == 2){
            cout << "Person name" << endl;
            string person;
            cin >> person;
            int balance = a.getBalance(person);
            cout << balance << endl;
        }else if(answer == 3){
            a.printChain();
        }else if(answer == 4){
            break;
        }else{
            cout << "wrong operation!"<< endl;
        }
    }
    return 0;
}