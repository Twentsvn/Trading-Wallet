#include "OrderBookEntry.h"

OrderBookType OrderBookEntry::string_to_obtype(std::string line){
        if(line == "ask"){
                return OrderBookType::ask;
        }
        if(line=="bid"){
                return OrderBookType::bid;
        }
        else {
                return OrderBookType::unknown;
        }
}
// we can not write OrderBookEntry() like this since we have to provide the namespace
OrderBookEntry::OrderBookEntry(std::string atimeStamp , std::string aproduct , OrderBookType aorderType , double aprice , double aamount , std::string auser  ):
        timeStamp{atimeStamp} , product{aproduct} , orderType{aorderType} , price{aprice} , amount{aamount} , user{auser}
    {
                // we can construct normally also
                // timeStamp = atimeStamp 
                // this is also fine timeStamp(atimeStamp) is also correct these are just different ways to intialize
                // this->timeStamp = timeStamp when the function also passes the same name timeStamp rather than atimeStamp
                // 
    } 