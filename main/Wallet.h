#pragma once
#include <string> 
#include <unordered_map>
class Wallet{
    public:
        Wallet(); //constructor
        static void AddMoney(std::string mony, double amount );
        static void WithdMoney(std::string mony, double amount);
        static void PrintWallet();
        static bool checkWallet(std::string mony, double amount);
    private:
        static std::unordered_map <std::string,double > user;  // need to be static to be used by static function
};