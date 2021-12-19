#include <algorithm>
#include <iostream>
#include <list>
#include <random>
#include <sys/time.h>

using std::cout; using std::endl;
using std::list; using std::vector;


float time_diff(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

const int MIN = 1;
const int MAX = 100;
const int CAPASITY = 100000;

int main() {
    struct timeval start{};
    struct timeval end{};

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> distr(MIN, MAX);

    vector<int> vec1;
    list<int> list1;

    vec1.reserve(CAPASITY);
    for (int i = 0; i < CAPASITY; ++i) {
        if (i % 39999 == 0) {
            vec1.push_back(111);
            continue;
        }
        vec1.push_back(distr(eng));
    }

    for (int i = 0; i < CAPASITY; ++i) {
        if (i % 39999 == 0) {
            list1.push_back(111);
            continue;
        }
        list1.push_back(distr(eng));
    }

    auto iter = std::find(vec1.begin(), vec1.end(), 111);
    gettimeofday(&start, nullptr);
    vec1.insert(iter, 1111);
    gettimeofday(&end, nullptr);
    printf("insert vector: %0.8f sec\n", time_diff(&start, &end));


    auto iter2 = std::find(list1.begin(), list1.end(), 111);
    gettimeofday(&start, nullptr);
    list1.insert(iter2, 1111);
    gettimeofday(&end, nullptr);
    printf("insert list  : %0.8f sec\n", time_diff(&start, &end));

    return EXIT_SUCCESS;
}
