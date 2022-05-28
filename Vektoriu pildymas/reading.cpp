#include <vector>
#include <iostream>
#include <chrono>
#include "vector.h"

void measure (unsigned int sz, bool std) {

    using hrClock = std::chrono::high_resolution_clock;
    hrClock::time_point start, end;
    std::chrono::duration<double> time;

    std::vector<int> premade;
    Vector<int> homemade;

    int reallocCount = 0, capacity;
    bool didReallocate = false;

    std::cout << (std ? "std::vector\n" : "vector\n");

    start = hrClock::now();
    if (std) {
        for (int i = 1; i <= sz; ++i) {
            if (premade.size() == premade.capacity()) {
                reallocCount++; 
                didReallocate = true;
            }
            premade.push_back(i);
            if (didReallocate) {
                capacity = premade.capacity();
                didReallocate = false;
            }
        }
    } else {
        for (int i = 1; i <= sz; ++i) {
        if (homemade.size()== homemade.capacity()) {
            reallocCount++; 
            didReallocate = true;
        }
        homemade.push_back(i);
        if (didReallocate) {
            capacity = homemade.capacity();
            didReallocate = false;
        }
    }
    }
    end = hrClock::now();
    time = end - start;
    std::cout << "time: " << time.count() << std::endl;
    std::cout << "reallocated: " << reallocCount << " times " <<std::endl;
    std::cout << std::endl;
}

int main() {
    unsigned int sz = 1000000000;
    measure(sz, true);
    measure(sz, false);
    return 0;
}