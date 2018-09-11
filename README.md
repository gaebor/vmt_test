# vmt_test
C++ virtual method table (VMT) performance compared to C function call

see https://stackoverflow.com/questions/449827/virtual-functions-and-performance-c

## Experiment setup

            virtual double F::operator()(double x) const = 0;
                          /  \
                         /    \
                        /      \
       virtual double F1::operator()(double x){return exp(x);}
                                 \
                                  \
                                   \
                     virtual double F2::operator()(double x){return log(x);}

In C implementation the baseline is a plain `exp` function call.
I imitated the dynamic polymorphism in C with a `swith`, something like that:

    double f(char what_to_do, double x)
    {
        switch (what_to_do)
        {
            case one:     return exp(x);
            case another: return log(x);
        }
    }
## Run
### Linux
    cmake . && make && ./vmt_test_dynamic
### Windows
    cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release . && nmake && vmt_test_dynamic.exe

## Options
You can set the array size, which is the number of function calls in one experiment (default 1M).
And you can set the repetition of experiment (default 10).

    vmt_test_dynamic <array size in one experiment> <repetition of the experiment>

You can try `vmt_test_static` which is linked statically, but I couldn't see any performance gain.

## Results
Performed each call on an arry of length 1M, repeated 10 times:

| C++                  | C_1                   | C_2                   | C_3                   | baseline              |
|----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
| baseline+19.770ns    | baseline+11.024ns     | baseline+10.887ns     | baseline+11.042ns     | 34.580ns/call         |
| +/-1.177%            | +/-3.122%             | +/-2.153%             | +/-2.284%             | +/-2.075%             |
