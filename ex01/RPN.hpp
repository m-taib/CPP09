
#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <exception>

class Rpn
{
    public :
        Rpn();
        Rpn(const Rpn& rhs);
        Rpn&    operator=(const Rpn& rhs);
        ~Rpn();

        bool	isOperator(const std::string& op);
        void	performOp(std::stack<int>& s, const std::string& op);
        void    stackManip(char *av);
        int     is_alnum(const char *av);
        int     checkSep(const std::string value);
    
    private:
        std::stack<int> calcStack;

};

#endif