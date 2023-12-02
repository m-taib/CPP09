#include "BitcoinExchange.hpp"
#include <string>

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(std::string fileName)
{
    std::fstream    file;
    std::string     line;
    file.open(fileName.c_str(), std::ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line[0] == 'd')
                continue ;      
            dictionary.insert(std::make_pair(strtok((char *)line.c_str(), ",")
			    , std::atof(&line.c_str()[line.find(",") + 1])));	 
	}
        /*std::map<std::string, float>::iterator begin = dictionary.begin();
        std::map<std::string, float>::iterator end = dictionary.end();
        while (begin != end)
        {
            std::cout << begin->first << "\t" << begin->second << std::endl;
            begin++;
        }*/
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

tm	*BitcoinExchange::getTime() const
{
	static	tm*	ltm;

	if (ltm)
		return (ltm);	
	
	time_t now;
	now = time(0);
	ltm = localtime(&now);
	return (ltm);
}

int	BitcoinExchange::checkYear(int& year) const
{	
	if (year < 2009 
		|| year > 1900 + getTime()->tm_year)
		return (0);
	return (1);
}

int	BitcoinExchange::checkMonth(int& year, int& month) const
{
	if ((year == getTime()->tm_year 
			&& month > 1 + getTime()->tm_mon)
			|| month < 1 || month > 12)
		return (0);		
	return (1);

}

int	BitcoinExchange::checkDay(int& year, int& month, int& day) const
{
	if ((year == getTime()->tm_year 
			&& month == 1 + getTime()->tm_mon
				&& day > getTime()->tm_mday) || day < 1)
		return (0);
	if((month == 2)  
		&& (year % 400 == 0 || (year % 100 != 0 && year % 4==0)))
	{
		if (day > 29)
		 	  return (0);
	}
   	else if (month == 2)
	{
	       	if (day > 28)
		 	  return (0);
	}
    	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
			   return (0);
	}
	else if (day > 31)
	     return (0);	
	return (1);

}

std::string BitcoinExchange::badInput(std::string& value) const
{
	std::string	errorMsg;

	errorMsg = "Error: bad input => ";
	errorMsg += std::strtok((char *)value.c_str(), "|");
	return (errorMsg);
}

int	BitcoinExchange::checkDateValue(int& year, int& month, int& day) const
{
	//check if the date greater than the creation time
	if (checkYear(year))
		if (checkMonth(year, month))
			if (checkDay(year, month, day))
				return (1);
	return (0);
}

std::pair<std::string, float>   BitcoinExchange::checkData(std::string value) const
{
	int	year;
	int	month;
	int	day;
	float	price;
	int	count;
	
	count = std::sscanf(value.c_str(), "%d-%d-%d | %f", 
			&year, &month, &day, &price);
	if (count != 4)
	{
		if (count < 3)
			throw badInput(value);
		else
			throw std::invalid_argument("Error: bad input =>" + value);
	}
	else if (price < 0)
		throw std::invalid_argument("Error: not a positive number");
	else if (price == 0)
		throw std::invalid_argument("Error: too small number");
	else if (price >= 1000)
		throw std::invalid_argument("Error: too large number");
	if (checkDateValue(year, month, day))
		return (std::make_pair(strtok((char *)value.c_str(), " ")
                            , std::atof(&value.c_str()[value.find("|") + 2])));
	throw std::invalid_argument(badInput(value));
}

void    BitcoinExchange::printRecord(const std::pair<std::string, float>& p) 
{
	std::map<std::string, float>::iterator it;
	std::string date = p.first;
	
	if (p.first.length() != 10)
		throw std::invalid_argument(badInput(date));

	it = min_element(dictionary.begin(), dictionary.end());
	if (p.first < it->first)
		throw std::invalid_argument(badInput(date));
	std::cout << p.first << " => " << p.second << " = ";

	if (dictionary.find(p.first) != dictionary.end())
		std::cout << p.second * dictionary.at(p.first) << std::endl;
	else
	{
		it = dictionary.upper_bound(p.first);
		std::cout << p.second * (--it)->second << std::endl;
	}
}

void    BitcoinExchange::extract_data(std::string fileName)
{
    //check record if is correct
        //check date if has a alpha char
        //check date format : year = 4 digit  month = 2 digit and if its between month 1-12, day = range of month , 
            //  31 for odd 30 for even, except february
        //value : 0-1000
    std::fstream    file;
    std::string     line;
    
    file.open(fileName.c_str(), std::ios::in);
    if (file.is_open())
    {
	if (!getline(file, line))
		throw std::invalid_argument("Error: Empty file");
        while (!file.eof())
	{
		try
		{
	      		printRecord(checkData(line));
		}
		catch (const std::exception& exp)
		{
			std::cout << exp.what() << std::endl;
		}
		getline(file, line);
        }
        file.close();
    }
    else 
      	throw  std::invalid_argument("Error: File cannot be opened");
    
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