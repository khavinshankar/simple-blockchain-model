#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "sha256.h"
using namespace std;

void createBlock(string fromUser, string toUser, int amount);

// To create a User //

void createUser()
{
    string userName;
    string transactionKey;
    int balance = 100;

    stringstream ss;

    cout << "Enter the User Name" << endl;
    cin >> userName;
    cout << "Enter the Transaction Key" << endl;
    cin  >> transactionKey;

    ss<<userName<<".txt";
    ofstream users;
    users.open(ss.str());
    users << userName << " " << transactionKey << " " << balance;
}

struct userDetails
{
    string username;
    string transactionkey;
    int balance;
};

// To get User Details //

userDetails getUserDetails(string userName)
{

    stringstream ss;

    ss<<userName<<".txt";
    ifstream users;
    users.open(ss.str());

    string UserName;
    string transactionKey;
    int balance;

    while (users >> UserName >> transactionKey >> balance){}

    cout << endl << "User Name: " << UserName << endl << "Balance: " << balance << endl;


    userDetails userinfo;
    userinfo.username = UserName;
    userinfo.transactionkey = transactionKey;
    userinfo.balance = balance;

    return userinfo;
}

// To Add Shares //

void addShares(string username, int amount)
{
    userDetails user;
    user = getUserDetails(username);

    int newBalance = user.balance + amount;

    stringstream ss;

    ss<<username<<".txt";
    ofstream users;
    users.open(ss.str());

    users << user.username << " " << user.transactionkey << " " << newBalance;
}

// To Subract Shares //

void subShares(string username, int amount)
{
    userDetails user;
    user = getUserDetails(username);

    int newBalance = user.balance - amount;

    stringstream ss;

    ss<<username<<".txt";
    ofstream users;
    users.open(ss.str());

    users << user.username << " " << user.transactionkey << " " << newBalance;
}

// To send Shares //

void send (string fromUser, string toUser, int amount, string transactionKey)
{
    userDetails fromU;
    fromU = getUserDetails(fromUser);

    if (fromU.balance >= amount)
    {
      if (fromU.transactionkey == transactionKey)
      {
          addShares(toUser, amount);
          subShares(fromUser, amount);
          createBlock(fromUser, toUser, amount);
          cout << "Your Transaction was successful" << endl;
          getUserDetails(fromUser);
          getUserDetails(toUser);
      } else { cout << "ERROR: Transaction Key Does not Match!" << endl;}
    } else { cout << "ERROR: Not Enough Balance!" << endl;}
}

// Create a Block //

void createBlock(string fromUser, string toUser, int amount)
{
    fstream blockchainFile("blockchain.txt", ios::in | ios::out | ios::app);
    fstream blockchain("blockchain.txt", ios::in | ios::out | ios::app);

    std::stringstream ss;
    ss << fromUser << " " << toUser << " " << amount;
    std::string transaction = ss.str();

    int BlockNumber;
    string FromUser;
    string ToUser;
    int Amount;
    string BlockHash;

    while (blockchainFile >> BlockNumber >> FromUser >> ToUser >> Amount >> BlockHash) {}

    string content[] = {sha256(transaction), BlockHash};

    std::stringstream sstr;
    sstr << content[0] << " " << content[1];
    std::string contents = sstr.str();

    int blockNumber = BlockNumber + 1;
    string blockHash = sha256(contents);

    blockchain << endl << blockNumber << " " << fromUser << " " << toUser << " " << amount << " " << blockHash;
}


// Main Function //

int main()
{
    int input;
    cout << "Enter 1 to create a user" << endl << "Enter 2 to get user details" << endl << "Enter 3 to send shares" << endl << "Enter 4 to exit" << endl;

    string from;
    string to;
    int amount;
    string transkey;

    while(input != 4)
    {
       cout << "Enter 1 to 4 to continue: " << endl;
       cin >> input;
       switch(input)
       {
           case 1:
               {
                   createUser();
                   break;
               }


           case 2:
               {
                   string userName;
                   cout << "Enter the username: " << endl;
                   cin >> userName;
                   getUserDetails(userName);
                   break;
               }


           case 3:
               {
               cout << "Enter your from user: " << endl;
               cin >> from;
               cout << "Enter your payee's to user: " << endl;
               cin >> to;
               cout << "Enter the amount you want to send: " << endl;
               cin >> amount;
               cout << "Enter the transaction key: " << endl;
               cin >> transkey;
               send(from, to, amount, transkey);
               break;
               }

           case 4:
            {
                cout << "Happy Day sir/mam..." << endl;
                break;
            }

               default:
                   {
                      cout << "Please check what you have entered and Enter again correctly, " << endl;
                   }
       }
    }

}
