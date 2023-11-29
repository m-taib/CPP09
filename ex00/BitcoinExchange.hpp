#ifndef BITCOINEXCHANE_HPP
#define BITCOINEXCHANE_HPP

#include <iostream>
#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>
#include <cstring>

class BitcoinExchange
{   
    public :
        BitcoinExchange(std::string fileName);
        BitcoinExchange(const BitcoinExchange& rhs);
        BitcoinExchange&    operator=(const BitcoinExchange& rhs);
        ~BitcoinExchange();

        void    extract_data(std::string file);
        void    validDate(const std::string& value) const;
        void    checkYear(const std::string& value) const;
        void    checkMonth(const std::string& value) const;
        void    checkDay(const std::string& value) const;
    //extract data
    //parse
    //print_data
    private:   
        BitcoinExchange();
        std::map<std::string, float> dictionary;
};

#endif