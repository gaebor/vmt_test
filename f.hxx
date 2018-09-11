#ifdef _MSC_VER
#define EXPORTSYMBOL __declspec(dllexport)
#else 
#define EXPORTSYMBOL __attribute__ ((dllexport))
#endif

class EXPORTSYMBOL F
{
public:
    F();
    virtual ~F();
    virtual double operator()(double x) const = 0;
};

class EXPORTSYMBOL F1 : public F
{
public:
    F1();
    virtual ~F1();
    double operator()(double x)const;
};

class EXPORTSYMBOL F2 : public F
{
public:
    F2();
    virtual ~F2();
    double operator()(double x)const;
};

extern "C" EXPORTSYMBOL double fxx(const F* s, double x);
