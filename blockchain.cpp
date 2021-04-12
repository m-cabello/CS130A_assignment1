# include "blockchain.h"
# include <iostream>
# include <sstream>
# include <ctype.h>
# include <cstdlib> // for rand()
using namespace std;

//Transaction Methods
Transaction::Transaction(){

}
Transaction::~Transaction(){
    prev = NULL;
}

int Transaction::getAmount(){
    return this->amount;
}
string Transaction::getSender(){
    return this->sender;
}
string Transaction::getReciever(){
    return this->reciever;
}
Transaction* Transaction::getPrevious(){
    return this->prev;
}
string Transaction::getNonce(){
    return this->nonce;
}
string Transaction::getHash(){
    return this->hash;
}

Transaction::Transaction(int a, string s, string r, Transaction *p){
    prev = p;
    sender = s;
    reciever = r;
    amount = a;

    int found = 0;

    // While loop will be used to find nonce
    while(found == 0){
        char first = char(rand() % 26 + 97); 
        char second = char(rand() % 26 + 97); 
        string am = to_string(this->amount);
        string nonceGenerated = to_string(first + second);
        string hashGenerated = sha256(am + this->sender + this->reciever + nonceGenerated);
        if(hashGenerated.back() == '0'){
            found = 1;
            this->nonce = nonceGenerated;
        }
    }
    // hash will be calciulated using the previous transaction's data
    p = p->getPrevious();
    if(p){
        this->hash = sha256(to_string(this->amount) + this->sender + this->reciever + this->getNonce());
    }else{
        hash = "NULL";
    }
}

// Blockchain Methods
Blockchain::Blockchain(){ }
Blockchain::~Blockchain(){
    Transaction *m = last;
    while(m!= NULL){
        Transaction *n = last;
        n = n->getPrevious();
        delete m;
        m = n;
        delete n;
    }
}

// blockchain's 3 functions
void Blockchain::add(int amount, string sender, string reciever){
    Transaction *new1 = new Transaction(amount, sender, reciever, this->last);
    last = new1;
}
int Blockchain::getBalance(string person){
    //initial Balance
    int total = 50;
    Transaction *p = last;
    while( p != NULL){
        if(p->getSender() == person){
            total = total - p->getAmount();
        }else if(p->getReciever() == person){
            total = total + p->getAmount();
        }
        p = p->getPrevious();
    }
    return total;
}

void Blockchain::printChain(){
    Transaction *p = last;
    while (p != NULL){
        cout << "Amount: " << p->getAmount() << endl;
        cout << "Sender: " << p->getSender() << endl;
        cout << "Reciever: " << p->getReciever() << endl;
        cout << "Nonce: " << p->getNonce() << endl;
        cout << "Hash: " << p->getHash() << endl;
        p = p->getPrevious();
    }

}