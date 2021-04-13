# include "blockchain.h"
using namespace std;

// Sha256 Implementation
string sha256(const string str){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}
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
string Transaction::getReceiver(){
    return this->receiver;
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
    receiver = r;
    amount = a;

    int found = 0;
    // While loop will be used to find nonce
    while(found == 0){
        char first = char(rand() % 26 + 97); 
        char second = char(rand() % 26 + 97); 
        string am = to_string(this->amount);
        string nonceGenerated = to_string(first + second);
        string hashGenerated = sha256(am + this->sender + this->receiver + nonceGenerated);
        if(hashGenerated.back() == '0'){
            found = 1;
            this->nonce = nonceGenerated;
        }
    }
    // hash will be calciulated using the previous transaction's data
    if(p){
        this->hash = sha256(to_string(p->getAmount()) + p->getSender() + p->getReceiver() + p->getNonce());
    }else{
        hash = "NULL";
    }
}

// Blockchain Methods
Blockchain::Blockchain(){ 
    last = NULL;
}
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
void Blockchain::add(int amount, string sender, string receiver){
    Transaction *new1 = new Transaction(amount, sender, receiver, this->last);
    last = new1;
}
int Blockchain::getBalance(string person){
    //initial Balance
    int total = 50;
    Transaction *p = last;
    while( p != NULL){
        if(p->getSender() == person){
            total = total - p->getAmount();
        }else if(p->getReceiver() == person){
            total = total + p->getAmount();
        }
        p = p->getPrevious();
    }
    return total;
}

void Blockchain::printChain(){
    Transaction *p = last;
    printChainHelper(p);
}

void Blockchain::printChainHelper(Transaction *n){
    if (n == NULL){
        return;
    }
        printChainHelper(n->getPrevious());
        cout << "Amount: " << n->getAmount() << endl;
        cout << "Sender: " << n->getSender() << endl;
        cout << "Receiver: " << n->getReceiver() << endl;
        cout << "Nonce: " << n->getNonce() << endl;
        cout << "Hash: " << n->getHash() << endl;
}