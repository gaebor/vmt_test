#include "f.hxx"
#include <math.h>

F1::F1() {}

F1::~F1() {}

double F1::operator()(double x)const
{
    return exp(x);
}

F2::F2() {}

F2::~F2() {}

double F2::operator()(double x)const
{
    return log(x);
}

double fxx(const F* s, double x)
{
    return (*s)(x);
}

F::F() {}

F::~F() {}
