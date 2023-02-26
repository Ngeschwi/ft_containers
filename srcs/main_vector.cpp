#include <iostream>

#ifdef USING_STD
#include <vector>

    using std::vector;
#else
#include "../vector.hpp"

using ft::vector;
#endif

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"		/* Reset */
#define BLUE    "\033[34m"      /* Blue */
#define CYAN    "\033[36m"      /* Cyan */
#define RED     "\033[31m"

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"		/* Reset */
#define BLUE    "\033[34m"      /* Blue */
#define CYAN    "\033[36m"      /* Cyan */
#define RED     "\033[31m"

int main() {

#ifdef USING_STD
    std::cout << "Using std::vector" << std::endl;
#else
    std::cout << "Using ft::vector" << std::endl;
#endif

    std::cout << "------------TEST CONSTRUCTOR----------" << std::endl;
    {
            vector<int> first;                                // empty vector of ints
            vector<int> second(4, 100);                       // four ints with value 100
            vector<int> third((second.begin()), (second.end()));  // iterating through second
            vector<int> fourth(third);
            // the iterator constructor can also be used to construct from arrays:
            int myints[] = {16, 2, 77, 29};
            vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
            std::cout << "The contents of fifth are:";
            for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it) {
                std::cout << ' ' << *it;
            }
            std::cout << '\n';
    }

    std::cout << "------------TEST SIZE----------" << std::endl;
    {
        {
            vector<int> myints;
            std::cout << "0. size: " << myints.size() << '\n';

            for (int i = 0; i < 10; i++) myints.push_back(i);
            std::cout << "1. size: " << myints.size() << '\n';

            myints.insert(myints.end(), 10, 100);
            std::cout << "2. size: " << myints.size() << '\n';

            myints.pop_back();
            std::cout << "3. size: " << myints.size() << '\n';
        }
    }

    std::cout << "------------TEST BEGIN/END----------" << std::endl;
    {
        {
            vector<int> myvector;
            for (int i = 1; i <= 5; i++) myvector.push_back(i);

            std::cout << "myvector contains:";
            for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
                std::cout << ' ' << *it;
            std::cout << '\n';
        }
    }
    std::cout << "------------TEST RBEGIN/REND----------" << std::endl;
    {
        {
            vector<int> myvector(5);  // 5 default-constructed ints

            int i = 0;

            vector<int>::reverse_iterator rit = myvector.rbegin();
            for (; rit != myvector.rend(); ++rit)
                *rit = ++i;

            std::cout << "myvector contains:";
            for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
                std::cout << ' ' << *it;
            std::cout << '\n';
        }
    }
    std::cout << "------------TEST MAX_SIZE----------" << std::endl;
    {
        {
            vector<int> myvector;

            // set some content in the vector:
            for (int i = 0; i < 100; i++) myvector.push_back(i);

            std::cout << "size: " << myvector.size() << "\n";
            std::cout << "capacity: " << myvector.capacity() << "\n";
            std::cout << "max_size: " << myvector.max_size() << "\n";
        }
    }
    std::cout << "------------TEST RESIZE----------" << std::endl;
    {
        {
            vector<int> myvector;

            // set some initial content:
            for (int i = 1; i < 10; i++) myvector.push_back(i);

            myvector.resize(5, 100);
            myvector.resize(8, 100);

            std::cout << "myvector contains:";
            for (unsigned long i = 0; i < myvector.size(); i++)
                std::cout << ' ' << myvector[i];
            std::cout << '\n';
        }
    }

    std::cout << "------------TEST EMPTY----------" << std::endl;
    {
        {
            vector<int> myvector;
            int sum(0);

            for (int i = 1; i <= 10; i++) myvector.push_back(i);

            while (!myvector.empty()) {
                sum += myvector.back();
                myvector.pop_back();
            }

            std::cout << "total: " << sum << '\n';
        }
    }
    std::cout << "----------------TEST RESERVE---------------" << std::endl;
    {
        {
            vector<int>::size_type sz;

            vector<int> foo;
            sz = foo.capacity();
            std::cout << "making foo grow:\n";
            for (int i = 0; i < 128; ++i) {
                foo.push_back(i);
                if (sz != foo.capacity()) {
                    sz = foo.capacity();
                    std::cout << "capacity changed: " << sz << '\n';
                }
            }

            vector<int> bar;
            sz = bar.capacity();
            bar.reserve(100);
            std::cout << bar.capacity() << std::endl;
            // this is the only difference with foo above
            std::cout << "making bar grow:\n";
            for (int i = 0; i < 100; ++i) {
                bar.push_back(i);
                if (sz != bar.capacity()) {
                    sz = bar.capacity();
                    std::cout << "capacity changed: " << sz << '\n';
                }
            }
        }
    }
    std::cout << "------------TEST PUSH_BACK/POP_BACK----------" << std::endl;
    {
        {
            vector<int> myvector;
            int sum(0);

            myvector.push_back(100);
            myvector.push_back(200);
            myvector.push_back(300);

            while (!myvector.empty()) {
                sum += myvector.back();
                myvector.pop_back();
            }

            std::cout << "The elements of myvector add up to " << sum << '\n';
        }
    }
    std::cout << "-------------TEST AT------------" << std::endl;
    {
        {
            vector<int> myvector(10);   // 10 zero-initialized ints

            // assign some values:
            for (unsigned i = 0; i < myvector.size(); i++)
                myvector.at(i) = i;

            std::cout << "myvector contains:";
            for (unsigned i = 0; i < myvector.size(); i++)
                std::cout << ' ' << myvector.at(i);
            std::cout << '\n';
        }
    }
    std::cout << "-------------TEST FRONT/BACK------------" << std::endl;
    {
        {
            vector<int> myvector;

            myvector.push_back(78);
            myvector.push_back(16);

            // now front equals 78, and back 16
            std::cout << "myvector.front() is " << myvector.front() << '\n';
            myvector.front() -= myvector.back();

            std::cout << "myvector.front() is now " << myvector.front() << '\n';
        }
    }

    std::cout << "-------------TEST INSERT------------" << std::endl;
    {
        {
            vector<int> myvector(3, 100);
            vector<int>::iterator it;

            it = myvector.begin();
            it = myvector.insert(it, 200);

            myvector.insert(it, 2, 300);

            // "it" no longer valid, get a new one:
            it = myvector.begin();

            vector<int> anothervector(2, 400);
            myvector.insert(it + 2, anothervector.begin(), anothervector.end());

            int myarray[] = {501, 502, 503};
            myvector.insert(myvector.begin(), myarray, myarray + 3);

            std::cout << "myvector contains:";
            for (it = myvector.begin(); it < myvector.end(); it++)
                std::cout << ' ' << *it;
            std::cout << '\n';
        }
    }
    std::cout << "-------------TEST ASSIGN------------" << std::endl;
    {
        {
            vector<int> first;
            vector<int> second;
            vector<int> third;

            first.assign(7, 100);             // 7 ints with a value of 100

            vector<int>::iterator it;
            it = first.begin() + 1;

            second.assign(it, first.end() - 1); // the 5 central values of first

            int myints[] = {1776, 7, 4};
            third.assign(myints, myints + 3);   // assigning from array.

            std::cout << "Size of first: " << int(first.size()) << '\n';
            std::cout << "Size of second: " << int(second.size()) << '\n';
            std::cout << "Size of third: " << int(third.size()) << '\n';
        }
    }
    std::cout << "------------TEST ERASE----------" << std::endl;
    {
        {
            vector<int> myvector;

            // set some values (from 1 to 10)
            for (int i = 1; i <= 10; i++) myvector.push_back(i);

            // erase the 6th element
            myvector.erase(myvector.begin() + 5);

            // erase the first 3 elements:
            myvector.erase(myvector.begin(), myvector.begin() + 3);

            std::cout << "myvector contains:";
            for (unsigned i = 0; i < myvector.size(); ++i)
                std::cout << ' ' << myvector[i];
            std::cout << '\n';
        }
    }
    std::cout << "------------TEST SWAP----------" << std::endl;
    {
        {
            vector<int> foo(3, 100);   // three ints with a value of 100
            vector<int> bar(5, 200);   // five ints with a value of 200

            foo.swap(bar);

            std::cout << "foo contains:";
            for (unsigned i = 0; i < foo.size(); i++)
                std::cout << ' ' << foo[i];
            std::cout << '\n';

            std::cout << "bar contains:";
            for (unsigned i = 0; i < bar.size(); i++)
                std::cout << ' ' << bar[i];
            std::cout << '\n';
        }
    }
    std::cout << "------------TEST CLEAR----------" << std::endl;
    {
        {
            vector<int> myvector;
            myvector.push_back(100);
            myvector.push_back(200);
            myvector.push_back(300);

            std::cout << "myvector contains:";
            for (unsigned i = 0; i < myvector.size(); i++)
                std::cout << ' ' << myvector[i];
            std::cout << '\n';

            myvector.clear();
            myvector.push_back(1101);
            myvector.push_back(2202);

            std::cout << "myvector contains:";
            for (unsigned i = 0; i < myvector.size(); i++)
                std::cout << ' ' << myvector[i];
            std::cout << '\n';
        }
    }
    std::cout << "------------TEST GET_ALLOCATOR----------" << std::endl;
    {
        {
            vector<int> myvector;
            int *p;
            unsigned int i;

            // allocate an array with space for 5 elements using vector's allocator:
            p = myvector.get_allocator().allocate(5);

            // construct values in-place on the array:
            for (i = 0; i < 5; i++) myvector.get_allocator().construct(&p[i], i);

            std::cout << "The allocated array contains:";
            for (i = 0; i < 5; i++) std::cout << ' ' << p[i];
            std::cout << '\n';

            // destroy and deallocate:
            for (i = 0; i < 5; i++) myvector.get_allocator().destroy(&p[i]);
            myvector.get_allocator().deallocate(p, 5);
        }
    }
    std::cout << "------------TEST OPERATION BOOL----------" << std::endl;
    {
        {
            vector<int> foo(3, 100);   // three ints with a value of 100
            vector<int> bar(2, 200);   // two ints with a value of 200

            if (foo == bar) std::cout << "foo and bar are equal\n";
            if (foo != bar) std::cout << "foo and bar are not equal\n";
            if (foo < bar) std::cout << "foo is less than bar\n";
            if (foo > bar) std::cout << "foo is greater than bar\n";
            if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
            if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
        }
    }
    std::cout << "------------TEST SWAP OVERLOAD----------" << std::endl;
    {
        {
            vector<int> foo(3, 100);   // three ints with a value of 100
            vector<int> bar(5, 200);   // five ints with a value of 200

            foo.swap(bar);

            std::cout << "foo contains:";
            for (unsigned i = 0; i < foo.size(); i++)
                std::cout << ' ' << foo[i];
            std::cout << '\n';

            std::cout << "bar contains:";
            for (unsigned i = 0; i < bar.size(); i++)
                std::cout << ' ' << bar[i];
            std::cout << '\n';
        }
    }
    return (0);
}
