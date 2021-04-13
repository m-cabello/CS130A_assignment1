#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <openssl/sha.h>
# include <iostream>
# include <sstream>
# include <ctype.h>
# include <cstdlib> // for rand()
#include <iomanip>
#include <string>
using namespace std;

class Transaction{
public:
    Transaction();
    ~Transaction();
    Transaction(int a, string s, string r, Transaction *p);

    int getAmount();
    string getNonce();
    string getHash();
    string getSender();
    string getReceiver();
    Transaction *getPrevious();

private:
    Transaction *prev; 
    string sender;
    string receiver;
    int amount;
    string nonce;
    string hash;
};

class Blockchain{
public:
    Blockchain();
    ~Blockchain();
    void add(int amount, string sender, string receiver);  //adds new transaction to chain
    int getBalance(string person); // returns balance of a specific person
    void printChain(); //prints chain
    void printChainHelper(Transaction *n);
private:
    Transaction *last;
};

#endif