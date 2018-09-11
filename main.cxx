#include "f.h"
#include "f.hxx"

#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <cmath>

typedef std::chrono::high_resolution_clock myclock;

template<class Type, template<class, class> typename Container, typename Allocator>
Type mean(const Container<Type, Allocator>& v)
{
    return std::accumulate(v.begin(), v.end(), (Type)0) / v.size();
}

template<class Type, template<class, class> typename Container, typename Allocator>
Type stddev(const Container<Type, Allocator>& v)
{
    const auto m = mean(v);
    return sqrt(std::accumulate(v.begin(), v.end(), (Type)0, [&](Type prev, Type x) {return prev + (x - m)*(x - m); }) / (v.size() - 1));
}

int main(int argc, char* argv[])
{
    int N = 0, n = 0;
    if (argc > 1)
        N = atoi(argv[1]);
    if (N <= 0)
        N = 1000000;
    if (argc > 2)
        n = atoi(argv[2]);
    if (n <= 0)
        n = 10;

    double* x = new double[N];
    std::vector<double> f0_time, f1_time, f2_time, f3_time, fxx_time;
    double result = 0.0;
    auto start = myclock::now();
    F** arraycpp = new F*[N];
    for (int i = 0; i < N; ++i)
        arraycpp[i] = (i % 2 == 0) ? static_cast<F*>(new F1()) : static_cast<F*>(new F2());

    s* arrayc = new s[N];
 
    for (int i = 0; i < N; ++i)
    {
        arrayc[i].c = (i % 2 == 0);
        x[i] = (double)i;
    }

#define measurec(FF, arg) start = myclock::now();\
                   for (int i = 0; i < N; ++i)\
                       result = FF(arg, x[i]);\
                   FF##_time.push_back(std::chrono::duration<double>(myclock::now() - start).count()); \
                   std::cout << FF##_time.back() << "\t";\
                   std::cout.flush()

    std::cout << "C++\tC_1\tC_2\tC_3\tbaseline" << std::endl;
    
    for (int j = 0; j < n; ++j)
    {
        measurec(fxx, arraycpp[i]);
        measurec(f1, arrayc[i]);
        measurec(f2, arrayc[i]);
        measurec(f3, arrayc[i].c);
        
        start = myclock::now();
        for (int i = 0; i < N; ++i)
            result = f0(x[i]);
        f0_time.push_back(std::chrono::duration<double>(myclock::now() - start).count());
        std::cout << f0_time.back() << "\t";
        std::cout.flush();

        std::cout << std::endl;
    }

    for (int i = 0; i < N; ++i)
    {
        delete arraycpp[i];
    }
    delete[] arraycpp;
    delete[] arrayc;
    delete[] x;

    const auto baseline = mean(f0_time)/N;
    for (auto v : { &fxx_time, &f1_time, &f2_time, &f3_time })
        printf("baseline%+.3fns\t", 1000000000 * (mean(*v) / N - baseline));
    printf("%.3fns/call\n", 1000000000 * baseline);
    for (auto v : { &fxx_time, &f1_time, &f2_time, &f3_time, &f0_time })
        printf("+/-%.3f%%\t", 100 * stddev(*v) / mean(*v));
    printf("\n");
    return result == 0;
}
