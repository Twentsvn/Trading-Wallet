#pragma once
#include "CSVreader.h"
#include "OrderBook.h"
#include <unordered_map>
#include "Wallet.h"
struct Sale{
    std::unordered_map<std::string,double> sale;
};

class OrderBook{
    public:
    OrderBook();
    static int getAsk(std::string prod);
    static int getBid(std::string prod);
    static void nextTimestamp();
   // static void loaddata();
    static std::vector <std::string> productType();
    static void max_min(std::string product);
    static void getCurtime();
    static void loadtime();
    static OrderBookEntry intoOBE(OrderBookType obetype ,std::string line); 
    static void MatchingEngine(); 
    static bool compfunc_d(std::pair<OrderBookEntry,double>& obe1 , std::pair<OrderBookEntry,double>& obe2 );
    static bool compfunc_a(std::pair<OrderBookEntry,double>& obe1 , std::pair<OrderBookEntry,double>& obe2 );    
    static void insertOrder(OrderBookEntry& obe);

    private:
    static std::string curtime;
    static std::vector<OrderBookEntry> orders; 
    
};