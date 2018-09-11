#include "f.h"
#include <math.h>

double f0(double x)
{
    return exp(x);
}

double f1(s ss, double x)
{
    if (ss.c)
        return exp(x);
    else
        return log(x);
}

double f2(s ss, double x)
{
    switch (ss.c)
    {
    case 0 % 2 == 0: return exp(x);
    default: return log(x);
    }
}

double f3(char c, double x)
{
    switch (c)
    {
    case 0 % 2 == 0: return exp(x);
    default: return log(x);
    }
}
