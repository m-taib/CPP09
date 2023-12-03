#include "RPN.hpp"
#include <cctype>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <string>

Rpn::Rpn()
{

}

Rpn::Rpn(const Rpn& rhs)
{
    (void)rhs;
}

Rpn&    Rpn::operator=(const Rpn& rhs)
{
    calcStack = rhs.calcStack;
    return (*this);
}

bool	Rpn::isOperator(const std::string& op)
{
    std::string ops = "+-*/";
	
	if (op.length() == 1 && (int)ops.find(op[0]) != -1)
		return (true);	
	return (false);
}

void	Rpn::performOp(std::stack<int>& s, const std::string& op)
{
	int	lval;
	int	rval;
	int	res;
	
		
	rval = s.top();
	s.pop();
	lval = s.top();
	s.pop();
	if (op[0] == '+')
		res = lval + rval;
    else if (op[0] == '-')
		res = lval - rval;
    else if (op[0] == '/')
	{
        if (!rval)
            throw std::invalid_argument("Error: Impossible division");
		res = lval / rval;
	}
    else 
		res = lval * rval;
    s.push(res);
}

int    Rpn::is_alnum(const char *av)
{
    while (*av)
    {
        if (!std::isalnum(*av))
            throw std::invalid_argument("Error");
        av++;
    }
    return (1);
}

int     Rpn::checkSep(const std::string value)
{
    std::cout << value << std::endl;
    if ((int)value.find(' ') != -1)
        return (value.find(' ') + 1);
    return (value.length());
}
void    Rpn::stackManip(char *av)
{
    
    char * value;

    value = std::strtok(av, " ");
	while (value)
	{
		if (calcStack.size() >= 2 && isOperator(value))
        {
            performOp(calcStack, value);
        }
        else if (is_alnum(value))
            calcStack.push(std::atoi(value));
        else
            throw std::invalid_argument("Error");
        value = strtok(NULL, " ");
	}
    if (calcStack.size() == 2)
        throw std::invalid_argument("Error");
	std::cout << calcStack.top() << std::endl;
}

Rpn::~Rpn()
{
    
}