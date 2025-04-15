#include <iostream>
#include <string>
#include <vector>
#include <fstream> // file reading 
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVreader.h"
#include "Wallet.h"

int main(){
     Wallet::AddMoney("BTC",20);
    Wallet::AddMoney("BTC",20);
    Wallet::AddMoney("ETH",10);
    
    MerkelMain app{};
    app.init();

   /*                 // we need vector for storing all the data
    std::vector<OrderBookEntry> order;
                    // we can also make an object OrderBookEntry order1("2020/03/17 17:01:24.884492","BTC/USDT",OrderBookType::ask,1000,0.5) 
                    // and then push it the vector but if we have a lot of data then this can not be done 
                    // so this way is better 
    order.push_back( OrderBookEntry("2020/03/17 17:01:24.884492","BTC/USDT",OrderBookType::ask,1000,0.5) ) ;
    order.push_back( OrderBookEntry("2020/03/17 17:02:24.884492","BTC/USDT",OrderBookType::ask,12340,1.5) ) ;
    
                    // we can extract info from the vector in many ways
    std::cout<<"The price is : "<<order[1].price<<std::endl;
                            /*
                            //  this is one way
                            for(auto i : order){
                                std::cout<<i.price<<std::endl;
                            }
                            /*
                            //   no copy is created in this way
                            
                            for ( OrderBookEntry& i : order){
                                std::cout<<i.price<<std::endl;
                            }
                            
                            // copy is created in this way
                            
                            for ( OrderBookEntry i : order){
                                std::cout<<i.price<<std::endl;
                            }
                            
                            // indexing style           ++i is used rather than i++ as the after one creats copy which uses space and we dont want that
                            for (int i =0 ; i<order.size(); ++i){
                                std::cout<<order[i].price<<std::endl;
                                std::cout<<order.at(i).price<<std::endl; // class use of vector since vector is a class
                            }
                            */

  //  Wallet::AddMoney("BTC",20);
  //  Wallet::AddMoney("BTC",20);
  //  Wallet::AddMoney("ETH",10);
  //  Wallet::WithdMoney("ETH",5);
  //  Wallet::WithdMoney("ETH",100);
  //  Wallet::WithdMoney("abc",0);
  //  Wallet::PrintWallet();
    


    return 0;
}
