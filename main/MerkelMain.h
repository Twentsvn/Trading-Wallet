#pragma once // programs throws error when the file is included twice to solve that we include it once 
// header file
// specification file
#include <vector>
#include "OrderBookEntry.h"

class MerkelMain{
    public:
    MerkelMain();
    /** Call this to start the sim */
    void init();
private:
    void printMenu();
    int getuserOption();
    void printHelp();
    void printMarketstats();
    void enterOffer();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    void processOpertation(int userOption);

    

};