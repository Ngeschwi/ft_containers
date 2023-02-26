#include <iostream>       // std::cout

#ifdef USING_STD
#include <stack>
#include <vector>

    using std::vector;
    using std::stack;
#else
#include "../stack.hpp"
#include "../vector.hpp"

using ft::stack;
using ft::vector;
#endif


int main() {

#ifdef USING_STD
    std::cout << "Using std::stack" << std::endl;
#else
    std::cout << "Using ft::stack" << std::endl;
#endif

    std::cout << "-------------TEST CONSTRUCTOR------------" << std::endl;
    {

//        vector v;
//
//        v.push_back(1);
//        v.push_back(2);

        stack<int> first;                    // empty stack

        stack<int> third;  // empty stack using vector

        std::cout << "size of first: " << first.size() << '\n';
        std::cout << "size of third: " << third.size() << '\n';
    }
    std::cout << "-------------TEST EMPTY------------" << std::endl;
    {
        stack<int> mystack;
        int sum(0);

        for (int i = 1; i <= 10; i++) mystack.push(i);

        while (!mystack.empty()) {
            sum += mystack.top();
            mystack.pop();
        }

        std::cout << "total: " << sum << '\n';


    }
    std::cout << "-------------TEST SIZE------------" << std::endl;
    {
        stack<int> myints;
        std::cout << "0. size: " << myints.size() << '\n';

        for (int i = 0; i < 5; i++) myints.push(i);
        std::cout << "1. size: " << myints.size() << '\n';

        myints.pop();
        std::cout << "2. size: " << myints.size() << '\n';


    }
    std::cout << "-------------TEST TOP------------" << std::endl;
    {
        stack<int> mystack;

        mystack.push(10);
        mystack.push(20);

        mystack.top() -= 5;

        std::cout << "mystack.top() is now " << mystack.top() << '\n';


    }
    std::cout << "-------------TEST PUSH/POP------------" << std::endl;
    {
        stack<int> mystack;

        for (int i = 0; i < 5; ++i) mystack.push(i);

        std::cout << "Popping out elements...";
        while (!mystack.empty()) {
            std::cout << ' ' << mystack.top();
            mystack.pop();
        }
        std::cout << '\n';


    }
    std::cout << "-------------TEST OPERATOR BOOL------------" << std::endl;
    {
        vector<int> f(3, 100);   // three ints with a value of 100
        vector<int> b(2, 200);   // two ints with a value of 200
        stack<int> foo;
        stack<int> bar;

        for (vector<int>::iterator it = f.begin(); it != f.end(); ++it)
            foo.push(*it);

        for (vector<int>::iterator it = b.begin(); it != b.end(); ++it)
            bar.push(*it);

        if (foo == bar) std::cout << "foo and bar are equal\n";
        if (foo != bar) std::cout << "foo and bar are not equal\n";
        if (foo < bar) std::cout << "foo is less than bar\n";
        if (foo > bar) std::cout << "foo is greater than bar\n";
        if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
        if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
    }
    return 0;
}