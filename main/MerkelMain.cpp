#include <iostream>
#include <vector>
#include "MerkelMain.h"
#include "CSVreader.h"
#include "OrderBook.h"
#include "OrderBookEntry.h" // this thing is added twice in our cpp programs and will generate error but we solved that using "#pragma once" command
// MerkelMain namespace function are these
MerkelMain::MerkelMain(){

}
void MerkelMain::init(){
     OrderBook::loadtime();

    while(1){   
        printMenu();
        int input;
        input = getuserOption();
        processOpertation(input);
    }
}

void MerkelMain::printMenu(){
    std::cout<<"1: Help"<<std::endl;
    std::cout<<"2: Print exchange stats"<<std::endl;
    std::cout<<"3: Make an offer"<<std::endl;
    std::cout<<"4: Make a bid"<<std::endl;
    std::cout<<"5: Print wallet"<<std::endl;
    std::cout<<"6: Continue"<<std::endl;
    std::cout<<"-------------------------------"<<std::endl;
    OrderBook::getCurtime();
}

int MerkelMain::getuserOption(){
    int userOption;
    std::cout<<"Please select an option"<<std::endl;
    std::string line;
    std::getline(std::cin,line);
    try{
        userOption=std::stoi(line);
        
    }
    catch(std::exception& e){
        std::cout<<" Invalid Input "<<std::endl;
    }
    return userOption;
}

void MerkelMain::printHelp(){
    std::cout<<"Help - Your aim is to make money and lots of ofc."<<std::endl;
}

void MerkelMain::printMarketstats(){
    std::vector<std::string> prodtype = OrderBook::productType();
    for(auto i : prodtype){
    //OrderBook::max_min(i);
    std::cout<<i<<": asks : " <<OrderBook::getAsk(i)<<std::endl;
    std::cout<<i<<": bids : " <<OrderBook::getBid(i)<<std::endl;
    }


}

void MerkelMain::enterOffer(){
    std::cout<<"Mark and offer - enter the amount"<<std::endl;
    std::string line;
    std::vector <OrderBookEntry> o;
    try{
    try{

    std::getline(std::cin, line );
    o.push_back(OrderBook::intoOBE(OrderBookType::ask,line));
    }
    catch(std::exception& e ){
        std::cout<<"MerkelMain::enteroffer error"<<std::endl;
        throw std::exception();    
    }
    std::cout<<"ASK"<<std::endl;
    std::cout<<"Product: "<<o[0].product <<std::endl;
    std::cout<<"Price: "<<o[0].price <<std::endl;
    std::cout<<"Amount: "<<o[0].amount<<std::endl;
    }
    catch(std::exception& e){

     }

    std::vector<std::string> prod = CSVreader::tokenizer(o[0].product,'/');
    try{
        Wallet::WithdMoney(prod[0],o[0].amount);
    }
    catch(std::exception& e){
        std::cout<<"Insufficient Funds"<<std::endl;
    }
    o[0].user="simuser";
     OrderBook::insertOrder(o[0]);    

}

void MerkelMain::enterBid(){
    std::cout<<"Make a bid - enter the amount"<<std::endl;
    std::string line;
    std::vector <OrderBookEntry> o;
    try{
    try{
    std::getline(std::cin, line );
    o.push_back(OrderBook::intoOBE(OrderBookType::bid,line));
    }
    catch(std::exception& e ){
        std::cout<<"MerkelMain::enteroffer error"<<std::endl;  
        throw std::exception();  
    }
    std::cout<<"BID"<<std::endl;
    std::cout<<"Product: "<<o[0].product <<std::endl;
    std::cout<<"Price: "<<o[0].price <<std::endl;
    std::cout<<"Amount: "<<o[0].amount<<std::endl;
    }
    catch(std::exception& e){

    }

    // wallet add
    std::vector<std::string> prod = CSVreader::tokenizer(o[0].product,'/');
    try{
    Wallet::WithdMoney(prod[1],o[0].price);
    }
    catch(std::exception& e){
        std::cout<<"Insufficient balance "<<std::endl;
    }
    o[0].user="simuser";
    OrderBook::insertOrder(o[0]);
}

void MerkelMain::printWallet(){
    Wallet::PrintWallet();
    
}

void MerkelMain::gotoNextTimeframe(){
    OrderBook::nextTimestamp();
}

void MerkelMain::processOpertation(int userOption){       
        switch (userOption)
        {
        case 1:
            std::cout<<"You chose: "<<userOption<<std::endl;
            printHelp();
            break;
        case 2:
            std::cout<<"You chose: "<<userOption<<std::endl;
            printMarketstats();
            break;
        case 3:
            std::cout<<"You chose: "<<userOption<<std::endl;
            enterOffer();
            break;
        case 4:
            std::cout<<"You chose: "<<userOption<<std::endl;
            enterBid();
            break;
        case 5:
            std::cout<<"You chose: "<<userOption<<std::endl;
            printWallet();
            break;
        case 6:
            std::cout<<"You chose: "<<userOption<<std::endl;
            OrderBook::MatchingEngine();
            gotoNextTimeframe();
            break;
        default:
            std::cout<<"Bad input"<<std::endl;
            break;
        }
}
