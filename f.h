
#ifdef _MSC_VER
#define EXPORTSYMBOL __declspec(dllexport)
#else 
#define EXPORTSYMBOL __attribute__ ((dllexport))
#endif

#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{
    char c;
} s;

EXPORTSYMBOL double f0(double);
EXPORTSYMBOL double f1(s, double);
EXPORTSYMBOL double f2(s, double);
EXPORTSYMBOL double f3(char, double);

#ifdef __cplusplus
}
#endif
