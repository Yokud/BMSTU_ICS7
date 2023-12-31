import sys
sys.path.append('py/')
from arr_lib import *
import unittest

class TestArrayLibrary(unittest.TestCase):

    def test_fill_array_usual(self):
        self.assertEqual(fill_array_by_prime_nums(5), [2, 3, 5, 7, 11])

    def test_fill_array_zero_len(self):
        self.assertEqual(fill_array_by_prime_nums(0), [])

    def test_fill_array_neg_len(self):
        self.assertEqual(fill_array_by_prime_nums(-1), [])

    def test_create_array_usual(self):
        self.assertEqual(create_array_with_elems_after_even([1, 2, 3, 4, 5]),
                                                             [3, 5])

    def test_create_array_void_list(self):
        self.assertEqual(create_array_with_elems_after_even([]), [])


if __name__ == '__main__':
    unittest.main(verbosity=2)
