#include "Wallet.h" 
#include <iostream>

std::unordered_map<std::string,double> Wallet::user;


Wallet::Wallet(){

}

void Wallet::AddMoney(std::string mony, double amount){
    user[mony] = user[mony] > 0 ? user[mony]+amount : amount ; 
    std::cout<<"Amount of "<<amount <<" was added to "<<mony<<" token"<<std::endl;
    
   // if (user[mony]){
   //     user[mony]+=amount;
   // }
   // else {
   //     user[mony]=0;
   //     user[mony]+=amount;
   // }
}

void Wallet::WithdMoney(std::string mony, double amount){
    
    if(checkWallet(mony,amount)){
        user[mony] -= amount;
        std::cout<<"Amount of " << amount<< " was deducted from "<< mony<<" token"<<std::endl;
    }
    else{
        throw std::exception{};
        //std::cout<<"Insufficient Funds please check the wallet again "<<std::endl;
    }

}

void Wallet::PrintWallet(){
    std::cout<<"-------Wallet-------"<<std::endl;
    for(std::pair<const std::string , double>& i : user){  // key cant be modified so const should be there
        if(i.second==0) continue;
        std::cout<<i.first<<" : "<<i.second<<std::endl;   
    }
    std::cout<<"--------------------"<<std::endl;

}

bool Wallet::checkWallet(std::string mony, double amount){
    
    return user[mony]>=amount ? 1 : 0 ;
}