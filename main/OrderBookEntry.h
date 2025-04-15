#pragma once
// header file
// specification file
#include <string>

        // enumeration is datatype which relates strings to numerals here automatically bid will be assign 0 if i dont specify it and be used for further comparison since we can only compare numbers 
enum class OrderBookType {bid , ask , bidsale , asksale , unknown};


class OrderBookEntry {
    
            // attributes which can be accessed outside of the class
    public:

            // attributes
    std::string timeStamp ;
    std::string product ;
    OrderBookType orderType ;
            // proper storage container need to be used for price and amount since slight error can cause problems and error increase with number of operation so we need to keep that in mind
    double price ;  
    double amount ;
    std::string user;

    //constructor only defining there would be such function i other file will be its implimentation 
    OrderBookEntry(std::string atimeStamp , std::string aproduct , OrderBookType aorderType , double aprice , double aamount, std::string auser = "OrdBook");
    static OrderBookType string_to_obtype(std::string line);    

    
};
