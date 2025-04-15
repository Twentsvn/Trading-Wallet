#include "OrderBook.h"
#include <algorithm>

// if not defined the program will not compile
std::vector<OrderBookEntry> OrderBook::orders = CSVreader::ReadCSV("Data.csv"); 
std::string OrderBook::curtime=" ";  
// need to define the two
OrderBook::OrderBook(){

}

int OrderBook::getAsk(std::string prod){
    int ask=0;
    for (OrderBookEntry& e : orders){
        if(e.product==prod and e.timeStamp==curtime and e.orderType==OrderBookType::ask){
            ++ask;
        }
    }
    return ask;
}

int OrderBook::getBid(std::string prod){
    int bid=0;
    for (OrderBookEntry& e : orders){
        if(e.product==prod and e.timeStamp==curtime and e.orderType==OrderBookType::bid){
            ++bid;
        }
    }
    return bid;
}
/** go to the next time step and it goes in circle */
void OrderBook::nextTimestamp(){
    std::string temp = curtime;
    for (OrderBookEntry& e : orders){
        if(e.timeStamp>curtime) {
            curtime=e.timeStamp;
            break;
        } 
    }    
    if(temp==curtime) curtime=orders[0].timeStamp;
    
}

void OrderBook::max_min(std::string product){
    double max_ask=0;
    double max_bid=0;
    for(OrderBookEntry& e: orders){
        if(e.timeStamp==curtime and e.product==product){
            if(e.orderType==OrderBookType::ask and e.price>max_ask) max_ask=e.price;
            else if(e.orderType==OrderBookType::bid and e.price>max_bid) max_bid=e.price;
        }
    }
    std::cout<<"Max bid for the poduct: "<<product<<" :- "<<max_bid<<std::endl;
    std::cout<<"Max ask for the poduct: "<<product<<" :- "<<max_ask<<std::endl;
    
}

std::vector <std::string> OrderBook::productType(){
    std::vector <std::string> v;
    std::unordered_map <std::string,bool> mp;
    for(OrderBookEntry& e : orders){
        mp[e.product]=1;
    }
    std::cout<<"-- Prdoct orders of type --"<<std::endl;
    for (auto s: mp){
        v.push_back(s.first);
        std::cout<<s.first<<std::endl;
    }
    return v;
}

void OrderBook::getCurtime(){
    std::cout<<"Time: "<<curtime<<std::endl;
}

void OrderBook::loadtime(){
  //  orders= CSVreader::ReadCSV("Data.csv");
    curtime = orders[0].timeStamp;
}

OrderBookEntry OrderBook::intoOBE(OrderBookType obetype,std::string line){
    std::vector <std::string> v,temp; // product , price , amount
    double price{0} , amount{0};
    temp = CSVreader::tokenizer(line,',');
    // EXCEPTION handling
    if(temp.size() >= 3){
    for (std::string& i : temp){
        if(i.length()!=0){
            v.push_back(i);
        }
    }
    if(v.size()!=3){
        std::cout<<" Bad Input by user in placing order"<< line <<std::endl;
        throw std::exception() ;
    }
    
    }
    else{
        std::cout<<" Bad Input by user in placing order : "<< line <<std::endl;
        throw std::exception() ;
    }
    temp.clear();
    try {
        price = std::stod(v[1]);
        amount = std::stod(v[2]);
    }
    catch(std::exception& e){
        std::cout<<" Bad Price/Amount by user in placing order : "<< line <<std::endl;
        throw std::exception() ;
    }

 try{
    OrderBookEntry obe {curtime,v[0],obetype,price,amount};
    return obe;
 }
 catch(...){
    std::cout<<"There was some error in forming the object"<<std::endl;
    throw std::exception();
 }
    
}
 // this is a very simple matching engine and it behaves as i like and want
void OrderBook::MatchingEngine(){ // i dont have to think of product since BTC/ETH of ask should match for BTC/ETH bid as 
                                  // ask - i have btc give me eth
                                  // bid - i want btc i have eth 
    // match the current time bids to asks
    std::vector<std::pair<OrderBookEntry,double>> asks;
    std::vector<std::pair<OrderBookEntry,double>> bids;
    for (OrderBookEntry& i : orders ){
        if(i.timeStamp == curtime){
            if(i.orderType==OrderBookType::ask){
                asks.push_back(std::pair{i,i.price/i.amount});
            }
            else if(i.orderType == OrderBookType::bid){
                bids.push_back(std::pair{i,i.price/i.amount});
            }

        }
    }
    
    std::sort(asks.begin(),asks.end(), compfunc_a);   // comfunction descending ask - asceind
    std::sort(bids.begin(),bids.end(), compfunc_d);   // descending
    // ask and bid vectors contain the asks and bid of a certain time instant 
    /*
                HOW MATCHING HAPPENS
        since i am providing the platform i want max profit so "higest bid" will match to "min ask" so that i get diff.
        if amount does not match then what these all be handled dont worry.
        
       * Partial Orders will  be matched 

    */
   Sale sui;
   int sasu=0;
   for (std::pair<OrderBookEntry,double>& ask : asks){
        for(std::pair<OrderBookEntry,double>& bid : bids){
            
                    // we could stop one by one by making grps of product but it will use space and time to make in order and we dont need that because it will take my brain
            if(ask.first.amount==0){break;}
            if(bid.first.price==0){continue;}
            // asker has some left
             
            if(bid.first.orderType == OrderBookType::bid and bid.first.product == ask.first.product){
                
                // now product is same we have to decide what to do now 
                // ask BTC/ETH 23, 12 ; bid BTC/ETH 23,12  
                // ask : i will give 12 BTC if you will give me 23 ETH rate : 1 BTC = 23 (ETH) /12 
                // bid : i will give 23 ETH if you will give me 12 BTC rate : 1 BTC = 23 (ETH) /12  
                if(bid.second >= ask.second){
                 ++sasu;   
                    // 5eth for 1 btc bid 1btc 2 eth ask
                    // 3 eth with me and bidder got 1 btc and asker got 2 eth
                    double want = bid.first.amount ; // want BTC  ---> bidder
                    double give = ask.first.amount ; // give (Real) BTC ---> ask
                 

                                if(want >= give){ // bidder want is more than the asker can give 
                                    // i have more than ask bidder will have some left and ask with nothing hahahha
                                    bid.first.amount -= give; // this much trade done 
                                    bid.first.price -= give*bid.second ; // this much eth gone from bidder to me 
                                    ask.first.amount=0; // ask has no more asking capacity boom
                                    ask.first.price = 0; // give*ask.second which i will give it to ask
                                    // how much i got ashiki*bid.second eth gonne and taken by asker is ask.second*ashiki
                                    // i will make profit on give
                                    std::vector<std::string> money = CSVreader::tokenizer(bid.first.product,'/');    
                                        // sale updated 
                                        // i will be gaining eth the difference of i get minus i gave to ask which will be give*ask.second = ask.first.price
                                    if(sui.sale[money[1]]){
                                        sui.sale[money[1]] += (bid.second-ask.second)*give; 
                                    }
                                    else {
                                        sui.sale[money[1]] = (bid.second-ask.second)*give;
                                    }
                                                    if(ask.first.user=="simuser"){
                                                         Wallet::AddMoney(money[1],give*ask.second);   
                                                    }
                                                    else if(bid.first.user=="simuser"){
                                                        Wallet::AddMoney(money[0],give);
                                                    }
                                             // function call to update wallet if order was by simuser need to be written
                                
                                }


                    else if(give > want){  //  i can not have all btc of asker but my all eth will be gone
                        
                        double temp = bid.first.price;
                        bid.first.price = 0; // nothing left for bidder
                        bid.first.amount = 0; // i get what i wanted = want

                        ask.first.amount -= want  ; // this much btc of asker is gone
                        ask.first.price -= want*ask.second; // this much i gae him 
                        
                        std::vector<std::string> money = CSVreader::tokenizer(bid.first.product,'/');
                         // i will be gaining eth
                         
                         if(sui.sale[money[1]]){
                            
                            sui.sale[money[1]] += temp-want*ask.second;
                        }
                        else {
                            sui.sale[money[1]] = temp-want*ask.second;
                        }  
                            if(ask.first.user=="simuser"){
                                Wallet::AddMoney(money[1],want*ask.second);
                            }
                            else if(bid.first.user=="simuser"){
                                Wallet::AddMoney(money[0],want);
                            }
                                             // wallet update need to be done
                    
                    }
                    else{
                        std::cout<<"WHAT the hell"<<std::endl;
                    }

                }

                 // no trade
                 
            }
            // product did not matched or bider as no more to give 
        } 
   }
    std::cout<<"Succussful Trads : "<<sasu<<std::endl;
    std::cout<<"----------SALES---------"<<std::endl;
    for(auto& i: sui.sale){
        std::cout<<i.first<<" : "<<i.second<<std::endl;
    }


}
 // matching engine end


bool OrderBook::compfunc_d(std::pair<OrderBookEntry,double>& obe1 , std::pair<OrderBookEntry,double>& obe2){
     return obe1.first.price > obe2.first.price ;
}

bool OrderBook::compfunc_a(std::pair<OrderBookEntry,double>& obe1 , std::pair<OrderBookEntry,double>& obe2){
    return obe1.first.price < obe2.first.price ;
}

void OrderBook::insertOrder(OrderBookEntry& obe){
    orders.push_back(obe);
}