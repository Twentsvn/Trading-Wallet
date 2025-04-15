#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "OrderBookEntry.h"
#include "MerkelMain.h"



class CSVreader{
    
    public:
    CSVreader(){

    }
    static std::vector<OrderBookEntry> ReadCSV(std::string filename);
    static std::vector<std::string> tokenizer(std::string s , char c); 
    
    private:
    static OrderBookEntry token_to_OBE(std::vector <std::string> token);
    

};