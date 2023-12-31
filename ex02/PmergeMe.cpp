#include "PmergeMe.hpp"
#include <cctype>
#include <stdexcept>


int     comp_num;

PmergeMe::PmergeMe()
{
    _num_of_elements = 1;
    comp_num = 0;
}
PmergeMe::PmergeMe(const PmergeMe& rhs)
{
    *this = rhs;
}

PmergeMe&   PmergeMe::operator=(const PmergeMe& rhs)
{
    _num_of_elements = rhs._num_of_elements;
    _v = rhs._v;
    _list = rhs._list;
    _vec_main_chain = rhs._vec_main_chain;
    _vec_pend = rhs._vec_pend;
    _list_main_chain = rhs._list_main_chain;
    _list_pend = rhs._list_pend;
    return (*this);
}

void      print_pairs(std::vector<vect_int >& v)
{
    std::vector<vect_int >::iterator begin = v.begin();
    std::vector<vect_int >::iterator end = v.end();
    vect_int::iterator it;

    while (begin != end)
    {
        it = (begin->begin());
        while (it != (begin->end()))
        {
            std::cout << *it << " ";
            it++;
        }
        std::cout << std::endl;
        begin++;
    }
}
std::vector<vect_int> PmergeMe::make_pairs(vect_int& data)
{
    std::vector<vect_int > v;
    vect_int v2;
    vect_int::iterator begin = data.begin();
    vect_int::iterator end = data.end();
    int     i;
    
    while (begin != end)
    {
        v2.clear();
        i = -1;
        while (begin != end && ++i < _num_of_elements)
        {
            v2.push_back(*begin);
            begin++;
        }
        v.push_back(v2);
    }
    return (v);
}

void    PmergeMe::sort_each_pair(std::vector<vect_int>& v)
{
    vect_int tmp;
    std::vector<vect_int>::iterator it;
    std::vector<vect_int>::iterator begin = v.begin();
    std::vector<vect_int>::iterator end = v.end();

    while (begin != end)
    {
	    if (begin + 1 == end)
		    break ;
	    it = begin;
	    ++it;
        if ((int)it->size() !=_num_of_elements)
            break ;
	    if (it->back() < begin->back())
	    {
            tmp = *begin;
            *begin = *it;
            *it = tmp;
	    }
        comp_num++;
        begin += 2;
    }

}
void    PmergeMe::copy_elements_to_data(vect_int& data, std::vector<vect_int>& v)
{
	std::vector<vect_int>::iterator begin = v.begin();
	vect_int::iterator data_begin = data.begin();
	vect_int::iterator it;
    
    int i = -1;
    int j = -1;

	while (++i < (int)v.size())
	{
		it = begin->begin();
        j = -1;
		while (++j < (int)begin->size())
		{
			*data_begin = *it;
			it++;
			data_begin++;
		}
		begin++;
	}
}

bool    compare(const vect_int& main_chain, const vect_int& pend) 
{
    comp_num++;
    return (main_chain.back() <= pend.back());
}

void    PmergeMe::update_iterators(pend_vec::iterator begin, std::vector<vect_int>::iterator pos)
{
    pend_vec::iterator end = _vec_pend.end();

    while (begin != end)
    {
        if (begin->second >= pos)
        {
            begin->second++;
        }
        begin++;
    }
}

void    PmergeMe::insert_pend_to_chain()
{
    pend_vec::iterator begin = _vec_pend.begin();
    std::vector<vect_int>::iterator it;
    int		i = 0;
    long int     jacob_sthal[] = { 
	   2, 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366,
        2730, 5462, 10922, 21846, 43690, 87382, 174762, 349526, 699050,
        1398102, 2796202, 5592406, 11184810, 22369622, 44739242, 89478486,
        178956970, 357913942, 715827882, 1431655766, 2863311530, 5726623062,
        11453246122, 22906492246, 45812984490 };

    while (_vec_pend.size())
    {  
        begin = _vec_pend.begin();
        begin += (jacob_sthal[i] - 1);
        if (begin >= _vec_pend.end())
            begin = _vec_pend.end() - 1;
        while (true)
        {
            it = std::lower_bound(_vec_main_chain.begin(), begin->second, 
                begin->first, compare);
            _vec_main_chain.insert(it, begin->first);
             _vec_pend.erase(begin);
            update_iterators(_vec_pend.begin(), it);
           
            if (begin == _vec_pend.begin())
                break ;
            begin--;
        }
        i++;
    }

}


int     PmergeMe::getComparisonsNum() const
{
    return (comp_num);
}

// void    PmergeMe::insert_pend_to_chain()
// {
//     pend_vec::iterator begin = _vec_pend.begin();
//     pend_vec::iterator end = _vec_pend.end();
//     std::vector<vect_int>::iterator it;
    
//     while (begin != end)
//     {   
//         it = std::lower_bound(_vec_main_chain.begin(), begin->second, begin->first, compare);
//         _vec_main_chain.insert(it, begin->first);
//         update_iterators(begin + 1, it);
//         begin++;
//     }

// }
    
void    PmergeMe::insertion_sort(vect_int& data)
{
    std::vector<vect_int> v;
    vect_int temp;
    std::vector<vect_int>::iterator it;
    std::vector<vect_int>::iterator tmp;
    int     i = -1;
    
    v = make_pairs(data);
    _vec_main_chain.clear();
    _vec_pend.clear();
    _vec_main_chain.reserve(v.size());
    temp.clear();
    if ((int)v.back().size() !=_num_of_elements)
    {
        temp = v.back();
        v.pop_back();
    }
    it = v.begin();

    while (it != v.end() && ++i < 2)
        _vec_main_chain.push_back(*(it++));
    while (it != v.end())
    {
        if (it + 1 == v.end())
        {
            _vec_pend.push_back(make_pair(*(it), _vec_main_chain.end())); 
            break ; 
        }
        tmp = _vec_main_chain.insert(_vec_main_chain.end(), *(it + 1));
        _vec_pend.push_back(make_pair(*(it), tmp));  
        it += 2;
    }
    insert_pend_to_chain();
    
    if (temp.size())
        _vec_main_chain.insert(_vec_main_chain.end(), temp);
    copy_elements_to_data(data, _vec_main_chain);
    _num_of_elements /= 2;
}

void    PmergeMe::merge_sort(vect_int& data)
{
    std::vector<vect_int> v;
    
    v = make_pairs(data);
    sort_each_pair(v);
    copy_elements_to_data(data, v);
    if (v.size() >= 4 && (int)v[3].size() ==_num_of_elements) 
    {
        _num_of_elements *= 2;
        merge_sort(data);
    }
    insertion_sort(data);
   
}

/*************** LIST IMPLEMENTATION ***************/

void      print_pairs(std::list<list_int >& lst)
{
    std::list<list_int >::iterator begin = lst.begin();
    std::list<list_int >::iterator end = lst.end();
    list_int::iterator it;

    while (begin != end)
    {
        it = (begin->begin());
        while (it != (begin->end()))
        {
            std::cout << *it << " ";
            it++;
        }
        std::cout << std::endl;
        begin++;
    }
}
std::list<list_int> PmergeMe::make_pairs(list_int& data)
{
    std::list<list_int > lst;
    list_int lst_element;
    list_int::iterator begin = data.begin();
    list_int::iterator end = data.end();
    int     i;
    
    while (begin != end)
    {
        lst_element.clear();
        i = -1;
        while (begin != end && ++i < _num_of_elements)
        {
            lst_element.push_back(*begin);
            begin++;
        }
        lst.push_back(lst_element);
    }
    return (lst);
}

void    PmergeMe::sort_each_pair(std::list<list_int>& lst)
{
    list_int tmp;
    std::list<list_int>::iterator it;
    std::list<list_int>::iterator begin = lst.begin();
    std::list<list_int>::iterator end = lst.end();
    std::list<list_int>::iterator tmp_it;
    int     j;

    while (begin != end)
    {
        j = -1;
        tmp_it = begin;
        tmp_it++;
	    if ((int)tmp_it->size() != _num_of_elements)
		    break ;
	    it = begin;
	    ++it;
        comp_num++;
	    if (it->back() < begin->back())
	    {
            tmp = *begin;
            *begin = *it;
            *it = tmp;
	    }
        while (++j < 2)
           begin++;
    }
}
void    PmergeMe::copy_elements_to_data(list_int& data, std::list<list_int>& lst)
{
	std::list<list_int>::iterator begin = lst.begin();
	list_int::iterator data_begin = data.begin();
	list_int::iterator it;
    
    int i = -1;
    int j = -1;

	while (++i < (int)lst.size())
	{
		it = begin->begin();
        j = -1;
		while (++j < (int)begin->size())
		{
			*data_begin = *it;
			it++;
			data_begin++;
		}
		begin++;
	}
}

bool    compare_list(const list_int& main_chain, const list_int& pend) 
{
    comp_num++;
    return (main_chain.back() <= pend.back());
}


void    PmergeMe::insert_list_pend_to_chain()
{
    pend_list::iterator begin;
    pend_list::iterator end;

    std::list<list_int>::iterator it;
    int		i = 0;
    int     j;
    long int     jacob_sthal[] = {
	   2, 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366,
        2730, 5462, 10922, 21846, 43690, 87382, 174762, 349526, 699050,
        1398102, 2796202, 5592406, 11184810, 22369622, 44739242, 89478486,
        178956970, 357913942, 715827882, 1431655766, 2863311530, 5726623062,
        11453246122, 22906492246, 45812984490 };

    while (_list_pend.size())
    {  
        begin = _list_pend.begin();
        end = _list_pend.begin();
        j = -1;
        end = _list_pend.begin();
        while (++j < (jacob_sthal[i] - 1) && end != _list_pend.end())
            end++;
        if (end == _list_pend.end())
            end--;
        while (true)
        {
            it = std::lower_bound(_list_main_chain.begin(), end->second, 
                            end->first, compare_list);
            _list_main_chain.insert(it, end->first);
            _list_pend.erase(end);
            if (end == begin)
                break ;
            end--;
        }
        i++;
    }

}

void    PmergeMe::insertion_sort(list_int& data)
{
    std::list<list_int> lst;
    list_int temp;
    std::list<list_int>::iterator it;
    std::list<list_int>::iterator tmp_it;
    std::list<list_int>::iterator tmp;
    int     i = -1;
    
    lst = make_pairs(data);

    _list_main_chain.clear();
    _list_pend.clear();
   
    temp.clear();
    if ((int)lst.back().size() !=_num_of_elements)
    {
        temp = lst.back();
        lst.pop_back();
    }
    it = lst.begin();

    while (it != lst.end() && ++i < 2)
        _list_main_chain.push_back(*(it++));
    
    while (it != lst.end())
    {
        i = -1;
        tmp_it = it;
        tmp_it++;
        if (tmp_it == lst.end())
        {
            _list_pend.push_back(make_pair(*(it), _list_main_chain.end())); 
            break ; 
        }
        tmp = _list_main_chain.insert(_list_main_chain.end(), *(tmp_it));
        _list_pend.push_back(make_pair(*(it), tmp));  
        while (++i < 2)
            it++;
    }
    insert_list_pend_to_chain();
    
    if (temp.size())
        _list_main_chain.insert(_list_main_chain.end(), temp);    
    copy_elements_to_data(data, _list_main_chain);
    _num_of_elements /= 2;
}

void    PmergeMe::merge_sort(list_int& data)
{
    std::list<list_int> lst;
    
  
    lst = make_pairs(data);
   

    sort_each_pair(lst);
    copy_elements_to_data(data, lst);
    if (lst.size() >= 4 || (int)lst.back().size() ==_num_of_elements) 
    {
        _num_of_elements *= 2;
        merge_sort(data);
    }  
    insertion_sort(data);
}

/*********************************************/

void    checkElemenets(char *str)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (!std::isdigit(str[i]) ||
                str[0] == '-')
        {
            throw std::invalid_argument("Error");
        }
        i++;
    }
}
void    vector_implementation(char **av)
{
    std::vector<int> v;
    int     i = 1;
    PmergeMe a;

    while (av[i])
    {
        checkElemenets(av[i]);
        v.push_back(std::atoi(av[i++]));
    }
    std::cout << "Before: " ;
    print_elements(v);
    std::cout << std::endl;
    a.merge_sort(v);
    i = -1;
    std::cout << "After : " ;
    while (++i < (int)v.size())
    {
        if (i + 1 == (int)v.size())
            break ;
	    if (v[i] > v[i + 1])
        {
                std::cout << "NOT SORTED" << std::endl;
                return ;
        }
    }
    print_elements(v);
    std::cout << "\nTime to process a range of "<< v.size() << " elements with std::[vector] : ";
    // std::cout << "\nnumber of comparisons : " << a.getComparisonsNum() << std::endl;
}
// Before: 3 5 9 7 4
// After: 3 4 5 7 9
// Time to process a range of 5 elements with std::[..] : 0.00031 us
// Time to process a range of 5 elements with std::[..] : 0.00014 us

void    list_implementation(char **av)
{
    std::list<int> lst;
    std::list<int>::iterator tmp;
    std::list<int>::iterator begin = lst.begin();
    int     i = 1;
    PmergeMe a;
    // std::cout << "Before: " ;
    while (av[i])
    {
        // std::cout << av[i] << " ";
        checkElemenets(av[i]);
        lst.push_back(std::atoi(av[i++]));
    }
    // std::cout << std::endl;
    
    a.merge_sort(lst);
    i = -1;
    // std::cout << "After : " ;
    while (begin != lst.end())
    {
        tmp = begin;
        tmp++;
        if (tmp == lst.end())
            break ;
	    if (*begin > *tmp)
        {
            std::cout << "NOT SORTED" << std::endl;
            return ;
        }
        begin++;
    }
    // print_elements(lst);
    std::cout << "Time to process a range of "<< lst.size() << " elements with std::[list] : ";
    // std::cout << "\nnumber of comparisons : " << a.getComparisonsNum() << std::endl;
}

long	gettime(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
    return (1000000 * curr_time.tv_sec + curr_time.tv_usec);
}
PmergeMe::~PmergeMe()
{
    
}
