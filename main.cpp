# include <iostream>
# include <sstream>
# include "blockchain.h"
using namespace std;

int main(){
   Blockchain *a = new Blockchain;
    while(true){
        string question;
        int answer;
        question = "Welcome to the transaction-chain application.... \n 1) Add a transaction to the chain.\n 2) Find the balance of a person.\n 3) Print the chain.\n 4) Exit. \n Which operation do you want to make? (1,2,3,4):\n" ;
        cout << question;
        cin >> answer;
        if (answer == 1){
            cout << "Integer amount of money:\n";
            int amount;
            cin >> amount;
            cout << "Sender name\n";
            string sender;
            cin >> sender;
            cout << "Reciever name\n";
            string reciever;
            cin >> reciever;
            a->add(amount, sender, reciever);

        }else if (answer == 2){
            cout << "Person name\n";
            string person;
            cin >> person;
            int balance = a->getBalance(person);
            cout << balance << endl;
        }else if(answer == 3){
            a->printChain();
        }else if(answer == 4){
            break;
        }else{
            cout << "wrong operation!";
        }
    }
    // delete *a;
    return 0;
}