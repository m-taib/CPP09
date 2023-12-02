#include <iostream>
#include <stack>
#include <string>

bool	isOperator(const std::string& op)
{
	std::string ops = "+-*/";
	
	if (ops.find(op[0]) != -1)
		return (true);	
	return (false);
}

void	performOp(std::stack<int>& s, const std::string& op)
{
	int	lval;
	int	rval;
	int	res;
	
		
	lval = s.top();
	s.pop();
	rval = s.top();
	s.pop();
	if (op[0] == '+')
	{
		res = lval + rval;
		s.push(res);
	}
}

int	main(int ac, char **av)
{
	std::stack<int> calcStack;
	
	int	i;
	int	count;
	
	count = 0;
	i = 0;
	while (av[++i])
	{
		if (count == 2)
		{
			if (isOperator(av[i]))
			{
				performOp(calcStack, av[i++]);
				if (!av[i])
					break ;
			}
			count = 0;
		}
		if (av[i][0] != '+')
		{
			calcStack.push(std::atoi(av[i]));
			count++;
		}
	}
	std::cout << calcStack.top() << std::endl;
	return (0);
}
