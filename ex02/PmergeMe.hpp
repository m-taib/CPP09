#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <sys/time.h>

typedef  std::vector<int> vect_int;
typedef  std::vector< std::pair<vect_int, std::vector<vect_int>::iterator> > pend_vec;

typedef  std::list<int> list_int;
typedef  std::list< std::pair<list_int, std::list<list_int>::iterator> > pend_list;

class   PmergeMe
{
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& rhs);
        PmergeMe&   operator=(const PmergeMe& rhs);
        ~PmergeMe();

        void    merge_sort(std::vector<int>& data);
        std::vector<std::vector<int> > make_pairs(std::vector<int>& data);
        void    sort_each_pair(std::vector<std::vector<int> >& v);
        void    copy_elements_to_data(std::vector<int>& data, std::vector<std::vector<int> >& v);
        void    insertion_sort(vect_int& data);
        void    insert_pend_to_chain();
        void    update_iterators(pend_vec::iterator begin, std::vector<vect_int>::iterator pos);
        void    print_pairs(std::vector<vect_int >& lst);

       

        // list
        void    merge_sort(std::list<int>& data);
        std::list<std::list<int> >     make_pairs(std::list<int>& data);
        void    sort_each_pair(std::list<std::list<int> >& v);
        void    copy_elements_to_data(std::list<int>& data, std::list<std::list<int> >& v);
        void    insertion_sort(list_int& data);
        void    insert_list_pend_to_chain();
        void    print_pairs(std::list<list_int >& lst);
        int     getComparisonsNum() const;
        
        

    private:

        int     _num_of_elements;
        std::vector<int> _v;
        std::list<int> _list;

        std::vector<vect_int> _vec_main_chain;
        pend_vec    _vec_pend;

        std::list<list_int> _list_main_chain;
        pend_list    _list_pend;


};

template<typename T>
void    print_elements(T& lst)
{
    typename T::iterator it = lst.begin();

    while (it != lst.end())
    {
        std::cout << *it << " ";
        it++;
    }
}

void    vector_implementation(char **av);
void    list_implementation(char **av);
long	gettime(void);

#endif