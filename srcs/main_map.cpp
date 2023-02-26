#ifdef USING_STD
    #include <map>

    using std::map;
    using std::pair;
#else
    #include "../map.hpp"

    using ft::map;
    using ft::pair;
#endif

#include <iostream>

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp {
    bool operator()(const char &lhs, const char &rhs) const { return lhs < rhs; }
};

int main() {

#ifdef USING_STD
    std::cout << "Using std::map" << std::endl;
#else
    std::cout << "Using map" << std::endl;
#endif

    std::cout << "-------------TEST CONSTRUCTOR------------" << std::endl;
    {
        map<char, int> first;
        first['a'] = 10;
        first['b'] = 30;
        first['c'] = 50;
        first['d'] = 70;
        for (map<char, int>::iterator it = first.begin(); it != first.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        map<char, int> second(first.begin(), first.end());

        map<char, int> third(second);

        map<char, int, classcomp> fourth;                 // class as Compare

        bool (*fn_pt)(char, char) = fncomp;
        map<char, int, bool (*)(char, char)> fifth(fn_pt); // function pointer as Compare
    }


    {
        map<char, int> mymap;

        mymap['x'] = 100;
        mymap['y'] = 200;
        mymap['z'] = 300;

        // show content:
        map<char, int>::reverse_iterator rit;
        for (rit = mymap.rbegin(); rit != mymap.rend(); ++rit)
            std::cout << rit->first << " => " << rit->second << '\n';

    }
    std::cout << "-------------TEST SIZE------------" << std::endl;
    {

        // accessing mapped values
        map<char, std::string> mymap;

        mymap['a'] = "an element";
        mymap['b'] = "another element";
        mymap['c'] = mymap['b'];

        std::cout << "mymap['a'] is " << mymap['a'] << '\n';
        std::cout << "mymap['b'] is " << mymap['b'] << '\n';
        std::cout << "mymap['c'] is " << mymap['c'] << '\n';
        std::cout << "mymap['d'] is " << mymap['d'] << '\n';

        std::cout << "mymap now contains " << mymap.size() << " elements.\n";

    }
    std::cout << "-------------TEST SIZE_MAX------------" << std::endl;
    {
        int i;
        map<int, int> mymap;

        if (mymap.max_size() > 1000) {
            for (i = 0; i < 1000; i++) mymap[i] = 0;
            std::cout << "The map contains 1000 elements.\n";
        } else std::cout << "The map could not hold 1000 elements.\n";

    }

    std::cout << "-------------TEST EMPTY------------" << std::endl;

    {
        // map::empty
        map<char, int> mymap;

        mymap['a'] = 10;
        mymap['b'] = 20;
        mymap['c'] = 30;

        while (!mymap.empty()) {
            std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
            mymap.erase(mymap.begin());
        }


    }
    std::cout << "-------------TEST INSERT------------" << std::endl;
    {
        map<char, int> mymap;

        // first insert function version (single parameter):
        mymap.insert(pair<char, int>('a', 100));
        mymap.insert(pair<char, int>('z', 200));

        map<char, int>::iterator itt = mymap.begin();
        mymap.insert(pair<char, int>('z', 500));
        for (; itt != mymap.end(); ++itt)
            std::cout << itt->first << " => " << itt->second << '\n';


        // second insert function version (with hint position):
        map<char, int>::iterator it = mymap.begin();
        mymap.insert(it, pair<char, int>('b', 300));  // max efficiency inserting
        mymap.insert(it, pair<char, int>('c', 400));  // no max efficiency inserting

        // third insert function version (range insertion):
        map<char, int> anothermap;
        anothermap.insert(mymap.begin(), mymap.find('c'));

        // showing contents:
        std::cout << "mymap contains:\n";
        for (it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << "anothermap contains:\n";
        for (it = anothermap.begin(); it != anothermap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';


    }
    std::cout << "-------------TEST ERASE------------" << std::endl;
    {
        map<char, int> mymap;
        map<char, int>::iterator it;

        // insert some values:
        mymap['a'] = 10;
        mymap['b'] = 20;
        mymap['c'] = 30;
        mymap['d'] = 40;
        mymap['e'] = 50;
        mymap['f'] = 60;

        it = mymap.find('b');
        mymap.erase(it);                   // erasing by iterator

        mymap.erase('c');                  // erasing by key

        it = mymap.find('e');
        mymap.erase(it, mymap.end());    // erasing by range

        // show content:
        for (it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';


    }
    std::cout << "-------------TEST SWAP------------" << std::endl;

    {
        map<char, int> foo, bar;

        foo['x'] = 100;
        foo['y'] = 200;

        bar['a'] = 11;
        bar['b'] = 22;
        bar['c'] = 33;

        foo.swap(bar);

        std::cout << "foo contains:\n";
        for (map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << "bar contains:\n";
        for (map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';


    }
    std::cout << "-------------TEST CLEAR------------" << std::endl;
    {
        map<char, int> mymap;

        mymap['x'] = 100;
        mymap['y'] = 200;
        mymap['z'] = 300;

        std::cout << "mymap contains:\n";
        for (map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        mymap.clear();
        mymap['a'] = 1101;
        mymap['b'] = 2202;

        std::cout << "mymap contains:\n";
        for (map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';


    }
    std::cout << "-------------TEST KEY_COMP------------" << std::endl;
    {
        map<char, int> mymap;

        map<char, int>::key_compare mycomp = mymap.key_comp();

        mymap['a'] = 100;
        mymap['b'] = 200;
        mymap['c'] = 300;

        std::cout << "mymap contains:\n";

        char highest = mymap.rbegin()->first;     // key value of last element

        map<char, int>::iterator it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << '\n';
        } while (mycomp((*it++).first, highest));

    }
    std::cout << "-------------TEST VALUE_COMP------------" << std::endl;
    {
        map<char, int> mymap;

        mymap['x'] = 1001;
        mymap['y'] = 2002;
        mymap['z'] = 3003;

        std::cout << "mymap contains:\n";

        pair<char, int> highest = *mymap.rbegin();          // last element

        map<char, int>::iterator it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << '\n';
        } while (mymap.value_comp()(*it++, highest));


    }
    std::cout << "-------------TEST FIND------------" << std::endl;
    {
        map<char, int> mymap;
        map<char, int>::iterator it;

        mymap['a'] = 50;
        mymap['b'] = 100;
        mymap['c'] = 150;
        mymap['d'] = 200;

        it = mymap.find('b');
        if (it != mymap.end())
            mymap.erase(it);

        // print content:
        std::cout << "elements in mymap:" << '\n';
        std::cout << "a => " << mymap.find('a')->second << '\n';
        std::cout << "c => " << mymap.find('c')->second << '\n';
        std::cout << "d => " << mymap.find('d')->second << '\n';


    }
    std::cout << "-------------TEST COUNT------------" << std::endl;
    {
        map<char, int> mymap;
        char c;

        mymap['a'] = 101;
        mymap['c'] = 202;
        mymap['f'] = 303;

        for (c = 'a'; c < 'h'; c++) {
            std::cout << c;
            if (mymap.count(c) > 0)
                std::cout << " is an element of mymap.\n";
            else
                std::cout << " is not an element of mymap.\n";
        }


    }
    std::cout << "-------------TEST UPPER_BOUND/LOWER_BOUND------------" << std::endl;
    {
        map<char, int> mymap;
        map<char, int>::iterator itlow, itup;

        mymap['a'] = 20;
        mymap['b'] = 40;
        mymap['c'] = 60;
        mymap['d'] = 80;
        mymap['e'] = 100;

        itlow = mymap.lower_bound('b');  // itlow points to b
        itup = mymap.upper_bound('d');   // itup points to e (not d!)

        mymap.erase(itlow, itup);        // erases [itlow,itup)

        // print content:
        for (map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

    }
    std::cout << "-------------TEST EQUAL_RANGE------------" << std::endl;
    {
        map<char, int> mymap;

        mymap['a'] = 10;
        mymap['b'] = 20;
        mymap['c'] = 30;

        pair<map<char, int>::iterator, map<char, int>::iterator> ret;
        ret = mymap.equal_range('b');

        std::cout << "lower bound points to: ";
        std::cout << ret.first->first << " => " << ret.first->second << '\n';

        std::cout << "upper bound points to: ";
        std::cout << ret.second->first << " => " << ret.second->second << '\n';


    }
    std::cout << "-------------TEST GET_ALLOCATOR------------" << std::endl;
    {
        int psize;
        map<char, int> mymap;
        pair<const char, int> *p;

        // allocate an array of 5 elements using mymap's allocator:
        p = mymap.get_allocator().allocate(5);

        // assign some values to array
        psize = sizeof(map<char, int>::value_type) * 5;

        std::cout << "The allocated array has a size of " << psize << " bytes.\n";

        mymap.get_allocator().deallocate(p, 5);


    }
    return 0;
}