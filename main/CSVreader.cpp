#include "CSVreader.h"

std::vector <std::string> CSVreader::tokenizer(std::string s , char c){
    std::vector <std::string> v;
    int start=0,end=0;
    std::string temp;
    for (auto i : s){
        if (i==c){
            temp = s.substr(start,end-start);
            if (temp.size())
            v.push_back(temp);
            ++end;
            start=end;
        }
        else {
                
                ++end;
                if(end==s.length()){
                     temp = s.substr(start,end-start);
                     v.push_back(temp);
                }
        }
    }
    return v;
}

std::vector<OrderBookEntry> CSVreader::ReadCSV(std::string filename){
        std::ifstream  CSVfile;
        std::string line;
        std::vector <OrderBookEntry> entries;
         
        CSVfile.open(filename);
        if (CSVfile.is_open()){
            std::cout<<"File was opened with no error"<<std::endl;
            while(std::getline(CSVfile,line)){
            std::vector <std::string> token;
            token=tokenizer(line , ',');
             try{
                OrderBookEntry obe = token_to_OBE(token);
                entries.push_back(obe);
             }
             catch(const std::exception& e){
                std::cout<<"CSVreader::readcsv error"<<std::endl;
             }
            }
        }
        else{
            std::cout<<"there was some problem in opening the file"<<std::endl;
        }
            CSVfile.close();
            std::cout<<entries.size()<<std::endl;
            return entries;            
    }

OrderBookEntry CSVreader::token_to_OBE(std::vector <std::string> token){
    if(token.size()!=5){
                std::cout<<"Input data Wrong"<<std::endl;
                throw std::exception{};
            }
            /** Input will be 5 exactly */
            double price,amount;   
    // exception handling
        try{
        price = std::stod(token[3]);
        amount = std::stod(token[4]);  
        
        }
        catch(std::exception& e){
            std::cout<<" Bad line "<<std::endl;
            throw e; //throwing std::exception
        }
    OrderBookEntry obe{token[0],token[1],OrderBookEntry::string_to_obtype(token[2]),price,amount};
    return obe;
};

    