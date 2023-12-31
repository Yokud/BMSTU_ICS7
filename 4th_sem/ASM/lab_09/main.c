#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stddef.h>
#include <limits.h>

#define REAPEATS 100000000

#ifdef X87
#ifdef ASM
void get_32_bit_sum_asm(float a, float b, long repeats)
{
	float c;
	for (long i = 0; i < repeats; i++)
    {
		__asm__(
            "fld %1\n\t"
			"fld %2\n\t"
			"faddp\n\t"
			"fstp %0\n\t"
			:"=m"(c)
			:"m"(a), "m"(b)
            );
    }
}
#endif

#ifdef ASM
void get_64_bit_sum_asm(double a, double b, long repeats)
{
	double c;
	for (long i = 0; i < repeats; i++)
    {
		__asm__(
            "fld %1\n\t"
			"fld %2\n\t"
			"faddp\n\t"
			"fstp %0\n\t"
			:"=m"(c)
			:"m"(a), "m"(b)
            );
    }
}
#endif



#ifdef ASM
#ifndef MNO
void get_80_bit_sum_asm(long double a, long double b, long repeats)
{
	long double c;
	for (long i = 0; i < repeats; i++)
    {
		__asm__(
            "fld %1\n\t"
			"fld %2\n\t"
			"faddp\n\t"
			"fstp %0\n\t"
			:"=m"(c)
			:"m"(a), "m"(b)
            );
    }
}
#endif
#endif

#ifdef ASM
void get_32_bit_mul_asm(float a, float b, long repeats)
{
	float c;
	for (long i = 0; i < repeats; i++)
    {
		__asm__(
            "fld %1\n\t"
			"fld %2\n\t"
			"fmulp\n\t"
			"fstp %0\n\t"
			:"=m"(c)
			:"m"(a), "m"(b)
            );
    }
}
#endif

#ifdef ASM
void get_64_bit_mul_asm(double a, double b, long repeats)
{
	double c;
	for (long i = 0; i < repeats; i++)
    {
		__asm__(
            "fld %1\n\t"
			"fld %2\n\t"
			"fmulp\n\t"
			"fstp %0\n\t"
			:"=m"(c)
			:"m"(a), "m"(b)
            );
    }
}
#endif



#ifdef ASM
#ifndef MNO
void get_80_bit_mul_asm(long double a, long double b, long repeats)
{
	long double c;
	for (long i = 0; i < repeats; i++)
    {
		__asm__(
            "fld %1\n\t"
			"fld %2\n\t"
			"fmulp\n\t"
			"fstp %0\n\t"
			:"=m"(c)
			:"m"(a), "m"(b)
            );
    }
}
#endif
#endif

void get_64_bit_sum(double a, double b, long repeats)
{
	double c;
	for (long i = 0; i < repeats; i++)
        c = a + b;
}

#ifndef MNO
void get_80_bit_sum(long double a, long double b, long repeats)
{
	long double c;
	for (long i = 0; i < repeats; i++)
        c = a + b;
}
#endif

void get_32_bit_sum(float a, float b, long repeats)
{
	float c;
	for (long i = 0; i < repeats; i++)
        c = a + b;
}


void get_64_bit_mul(double a, double b, long repeats)
{
	double c;
	for (long i = 0; i < repeats; i++)
        c = a * b;
}

#ifndef MNO
void get_80_bit_mul(long double a, long double b, long repeats)
{
	long double c;
	for (long i = 0; i < repeats; i++)
        c = a * b;
}
#endif

void get_32_bit_mul(float a, float b, long repeats)
{
	float c;
	for (long i = 0; i < repeats; i++)
        c = a * b;
}
#endif

void print_32_bit()
{
    #ifdef X87
    float a = 2e43;
	float b = 11e53;
    printf("float type size: %zu bites\n", sizeof(float) * CHAR_BIT);
    printf("SUM:\n");
    clock_t begin = clock();
    get_32_bit_sum(a, b, REAPEATS);
    clock_t end = clock();
    printf("\tstd: %-15.3g s\n", (double)(end - begin) / REAPEATS / CLOCKS_PER_SEC);
    begin = clock();
    get_32_bit_sum_asm(a, b, REAPEATS);
    end = clock();
    printf("\tasm: %-15.3g s\n", (double)(end - begin) / REAPEATS / CLOCKS_PER_SEC);
    printf("MUL:\n");
    begin = clock();
    get_32_bit_mul(a, b, REAPEATS);
    end = clock();
    printf("\tstd: %-15.3g s\n", (double)(end - begin) / REAPEATS / CLOCKS_PER_SEC);
    begin = clock();
    get_32_bit_mul_asm(a, b, REAPEATS);
    end = clock();
    printf("\tasm: %-15.3g s\n\n", (double)(end - begin) / REAPEATS / CLOCKS_PER_SEC);

    #endif
}

void print_64_bit()
{
    #ifdef X87
    double a = 2e43;
	double b = 11e53;
    printf("double type size: %zu bites\n", sizeof(double) * CHAR_BIT);
    printf("SUM:\n");
    clock_t begin = clock();
    get_64_bit_sum(a, b, REAPEATS);
    clock_t end = clock();
    printf("\tstd: %-15.3g s\n", (double)(end - begin) / REAPEATS / CLOCKS_PER_SEC);
    begin = clock();
    get_64_bit_sum_asm(a, b, REAPEATS);
    end = clock();
    printf("\tasm: %-15.3g s\n", (double)(end - begin) / REAPEATS / CLOCKS_PER_SEC);
    printf("MUL:\n");
    begin = clock();
    get_64_bit_mul(a, b, REAPEATS);
    end = clock();
    printf("\tstd: %-15.3g s\n", (double)(end - begin) / REAPEATS / CLOCKS_PER_SEC);
    begin = clock();
    get_64_bit_mul_asm(a, b, REAPEATS);
    end = clock();
    printf("\tasm: %-15.3g s\n\n", (double)(end - begin) / REAPEATS / CLOCKS_PER_SEC);

    #endif
}

void print_80_bit()
{
    #ifdef X87
    #ifndef MNO
    long double a = 2e43;
	long double b = 11e53;
    printf("long double type size: %zu bites\n", sizeof(long double) * CHAR_BIT);
    printf("SUM:\n");
    clock_t begin = clock();
    get_80_bit_sum(a, b, REAPEATS);
    clock_t end = clock();
    printf("\tstd: %-15.3g s\n", (double)(end - begin) / REAPEATS / CLOCKS_PER_SEC);
    begin = clock();
    get_80_bit_sum_asm(a, b, REAPEATS);
    end = clock();
    printf("\tasm: %-15.3g s\n", (double)(end - begin) / REAPEATS / CLOCKS_PER_SEC);
    printf("MUL:\n");
    begin = clock();
    get_80_bit_mul(a, b, REAPEATS);
    end = clock();
    printf("\tstd: %-15.3g s\n", (double)(end - begin) / REAPEATS / CLOCKS_PER_SEC);
    begin = clock();
    get_80_bit_mul_asm(a, b, REAPEATS);
    end = clock();
    printf("\tasm: %-15.3g s\n\n", (double)(end - begin) / REAPEATS / CLOCKS_PER_SEC);
    #endif
    #endif
}

void cmp_sin()
{
    double res = 0.0;

    printf("sin(pi):\n");
    printf("pi = 3.14: %g\n", sin(3.14));
    printf("pi = 3.141596: %g\n", sin(3.141596));
    #ifdef X87
    __asm__(
            "fldpi\n\t"
			"fsin\n\t"
			"fstp %0\n\t" :"=m"(res)
            );
        printf("\nfpu sin(pi): %g\n", res);
    #endif
    printf("\nsin(pi/2):\n");
    printf("pi = 3.14 / 2: %.6g\n", sin(3.14/2));
    printf("pi = 3.141596 / 2: %.6g\n", sin(3.141596/2));

    #ifdef X87
    res = 0.0;
    double temp = 2.0;
    __asm__(
            "fldpi\n\t"
            "fld %1\n\t"
            "fdivp\n\t"
            "fsin\n\t"
			"fstp %0\n\t" :"=m"(res): "m"(temp)
            );
        printf("fpu sin(pi/2): %.6g", res);
    #endif
    
}

int main(void)
{
	print_32_bit();
    print_64_bit();
    print_80_bit();
    cmp_sin();
	return 0;
}