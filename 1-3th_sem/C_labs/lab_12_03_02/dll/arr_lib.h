#ifndef ARR_LIB_H
#define ARR_LIB_H

#ifdef EXPORTS
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif

#define DECL __cdecl

#define OK 0
#define OVERFLOW -1

DLL void DECL fill_arr_with_prime_nums(long *arr, long n);
DLL int DECL take_elems_after_even(long *arr_src, long len_src, long *arr_dst, long *len_dst);

#endif