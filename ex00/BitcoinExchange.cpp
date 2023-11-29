#include "BitcoinExchange.hpp"
#include <string>

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(std::string fileName)
{
    std::fstream    file;
    std::string     line;

    file.open(fileName, std::ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line[0] == 'd')
                continue ;      
            dictionary.insert(std::make_pair(strtok((char *)line.c_str(), ","), strtod(strtok(NULL, ","), NULL)));
        }
        std::map<std::string, float>::iterator begin = dictionary.begin();
        std::map<std::string, float>::iterator end = dictionary.end();
        while (begin != end)
        {
            std::cout << begin->first << "\t" << begin->second << std::endl;
            begin++;
        }
        file.close();
    }
    else 
        throw  "File cannot be opened";
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& rhs)
{
    *this = rhs;
}

BitcoinExchange&  BitcoinExchange::operator=(const BitcoinExchange& rhs)
{
    this->dictionary = rhs.dictionary;
    return(*this);
}

void    BitcoinExchange::checkYear(const std::string& value) const
{
    if (value.length() == 4 && )
    else
        throw "Error: not a valid date.";
}
void    BitcoinExchange::checkMonth(const std::string& value) const
{
    throw "Error: not a valid date.";
}
void    BitcoinExchange::checkDay(const std::string& value) const
{
    throw "Error: not a valid date.";
}
void    BitcoinExchange::validDate(const std::string& value) const
{
    static int  i;
    typedef  void    (BitcoinExchange::*funPtr)(const std::string&) const;
    funPtr  ptr[3];

    ptr[0] = &BitcoinExchange::checkYear;
    ptr[1] = &BitcoinExchange::checkMonth;
    ptr[2] = &BitcoinExchange::checkDay;
    (this->*ptr[i++])(value);
}

void    BitcoinExchange::extract_data(std::string fileName)
{
    //check record if is correct
        //check date if has a alpha char
        //check date format : year = 4 digit  month = 2 digit and if its between month 1-12, day = range of month , 
            //  31 for odd 30 for even, except february
        //
    std::fstream    file;
    std::string     line;
    int     i;
    std::string value;

    file.open(fileName, std::ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {   
            i = 0;
            while (!line.empty())
            {
                i = line.find('-');
                if (i == -1)
                    i = line.length();
                value +=  line.substr(0, i);
                validDate(value);
                if (i != line.length())
                    value += "-";
                line.erase(0, i + 1 - (i == line.length()));
            }
        }
        file.close();
    }
    else 
        throw  "File cannot be opened";
    
}

BitcoinExchange::~BitcoinExchange()
{

}
    // std::pair<std::string, int> p;
    // std::map<std::string, int> m;
    // m.insert(std::pair<std::string, int>("1", 5));
    // m.insert(std::pair<std::string, int>("2", 5));
    // m.insert(std::pair<std::string, int>("4", 5));
    // std::map<std::string, int>::iterator itlow;
    // std::map<std::string, int>::iterator itup;
    // itlow = m.lower_bound("3");
    // itup  = m.upper_bound("3");
    // std::cout << (--itlow)->first << std::endl;