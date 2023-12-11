#ifndef BITCOINEXCHANE_HPP
#define BITCOINEXCHANE_HPP

#include <iostream>
#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <exception>
#include <ctime>

class BitcoinExchange
{   
    public :
        BitcoinExchange(std::string fileName);
        BitcoinExchange(const BitcoinExchange& rhs);
        BitcoinExchange&    operator=(const BitcoinExchange& rhs);
        ~BitcoinExchange();

        void    extract_data(std::string file);
        std::pair<std::string, float> checkData(std::string value) const;
        int     checkDateValue(int& year, int& month, int& day) const;
        int	checkYear(int& year) const;  
        int	checkMonth(int& year, int& month) const;  
        int	checkDay(int& year, int& month, int& day) const;
        std::string	badInput(std::string& value) const;
        tm      *getTime() const;
        void    printRecord(const std::pair<std::string, float>& p);	
        int		spaceNum(const std::string&	value) const;

    private:   
    
        BitcoinExchange();
        std::map<std::string, float> dictionary;
};

#endif
