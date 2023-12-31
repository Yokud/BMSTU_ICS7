from ctypes import *
from os.path import join
import tkinter as tk
import tkinter.messagebox as mbox

try:
    lib = CDLL(join('dll', 'arr_lib.dll'))
except:
    root = tk.Tk()
    root.withdraw()
    mbox.showerror(title="Ошибка", message="Нет необходимой библиотеки")
    raise SystemExit

_fill_arr = lib.fill_arr_with_prime_nums
_fill_arr.argtypes = (POINTER(c_long), c_long)
_fill_arr.restype = None

def fill_array_by_prime_nums(n):
    if n <= 0:
        return list()
    
    arr = (c_long * n)()
    _fill_arr(arr, n)

    return list(arr)

_filter = lib.take_elems_after_even
_filter.argtypes = (POINTER(c_long), c_long, POINTER(c_long), POINTER(c_long))
_filter.restype = c_int

def create_array_with_elems_after_even(nums):
    arr_len = len(nums)
    arr = (c_long * arr_len)(*nums)

    n_res = c_long(0)
    rc = _filter(arr, arr_len, None, n_res)
    if rc:
        res = (c_long * n_res.value)()

        rc = _filter(arr, arr_len, res, n_res)

        return list(res)
    else:
        return list()
