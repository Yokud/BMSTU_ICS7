#include "unittests.h"

void UnitTests::TestDet()
{
    Matrix<int> matr = { { 1, 2, 6, 9 },
                         {4, 5, -1, 4},
                         {0, 6, 1, 3},
                         {-1, 0, 2, 0}};

    int a = matr.Determinant();
    bool res = a == -227;

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestTranspose()
{
    Matrix<int> matr = { {1, 2, 3},
                         {4, 5, 6}};

    Matrix<int> check_matr = { {1, 4},
                               {2, 5},
                               {3, 6}};

    matr = matr.Transpose();

    bool res = true;
    Iterator<int> iter = matr.begin();
    Iterator<int> check_iter = check_matr.begin();
    for (; iter != matr.end(); ++iter, ++check_iter)
        if (*iter != *check_iter)
            res = false;

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestInverse()
{
    Matrix<double> matr = {{2,  6, 5},
                        {-1, 9, 8},
                        {8,  0, 2}
    };

    Matrix<double> matr_copy = {{2,  6, 5},
                           {-1, 9, 8},
                           {8,  0, 2}
    };

    Matrix<double> check_matr = {{1, 0,	0},
                                 {0, 1, 0},
                                 {0, 0, 1}
    };

    matr = matr.Inverse();
    matr *= matr_copy;

    bool res = true;
    Iterator<double> iter = matr.begin();
    Iterator<double> check_iter = check_matr.begin();
    for (; iter != matr.end(); iter++, check_iter++)
    {
        if (std::abs(*iter - *check_iter) > 1e-5)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestSum()
{
    Matrix<int> matr_1 = {{2,  6, 5},
                           {-1, 9, 8},
                           {8,  0, 2}
    };
    Matrix<int> matr_2 = {{1,  1, 5},
                             {2, 3, 1},
                             {4,  5, 1}
    };
    Matrix<int> res_check = {{3,  7, 10},
                             {1, 12, 9},
                             {12,  5, 3}
    };
    Matrix<int> res_matr = matr_1 + matr_2;

    bool res = true;
    Iterator<int> iter = res_matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
             res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestSumEq()
{
    Matrix<int> res_matr = {{2,  6, 5},
                          {-1, 9, 8},
                          {8,  0, 2}
    };
    Matrix<int> matr = {{1,  1, 5},
                          {2, 3, 1},
                          {4,  5, 1}
    };
    Matrix<int> res_check = {{3,  7, 10},
                             {1, 12, 9},
                             {12,  5, 3}
    };

    res_matr += matr;

    bool res = true;
    Iterator<int> iter = res_matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestSub()
{
    Matrix<int> matr_1 = {{2,  6, 5},
                          {-1, 9, 8},
                          {8,  0, 2}
    };
    Matrix<int> matr_2 = {{1,  1, 5},
                          {2, 3, 1},
                          {4,  5, 1}
    };
    Matrix<int> res_check = {{1,  5, 0},
                             {-3, 6, 7},
                             {4,  -5, 1}
    };
    Matrix<int> res_matr = matr_1 - matr_2;

    bool res = true;
    Iterator<int> iter = res_matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestSubEq()
{
    Matrix<int> res_matr = {{2,  6, 5},
                       {-1, 9, 8},
                       {8,  0, 2}
    };
    Matrix<int> matr = {{1,  1, 5},
                        {2, 3, 1},
                        {4,  5, 1}
    };
    Matrix<int> res_check = {{1,  5, 0},
                             {-3, 6, 7},
                             {4,  -5, 1}
    };
    res_matr -= matr;

    bool res = true;
    Iterator<int> iter = res_matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestMult()
{
    Matrix<int> matr_1 = {{1, 2, 6, 7},
                          {3, 1, 2, 16},
                          {31, 7, 28, 1}
    };
    Matrix<int> matr_2 = {{8, 13},
                          {5, 6},
                          {3, 9},
                          {11, 5}
    };
    Matrix<int> res_check = {{113, 114},
                             {211, 143},
                             {378, 702}
    };
    Matrix<int> res_matr = matr_1 * matr_2;

    bool res = true;
    Iterator<int> iter = res_matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestMultEq()
{
    Matrix<int> res_matr = {{1, 2, 6, 7},
                          {3, 1, 2, 16},
                          {31, 7, 28, 1}
    };
    Matrix<int> matr = {{8, 13},
                          {5, 6},
                          {3, 9},
                          {11, 5}
    };
    Matrix<int> res_check = {{113, 114},
                             {211, 143},
                             {378, 702}
    };
    res_matr *= matr;

    bool res = true;
    Iterator<int> iter = res_matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestDiv()
{
    Matrix<double> matr_a = {{1, 2, 3},
                             {4, 5, 6},
                             {7, 8, 9}};
    Matrix<double> matr_b = {{1, 0, 0},
                             {0, 1, 0},
                             {0, 0, 1}};
    Matrix<double> res_check{matr_a};

    Matrix<double> res_matr = matr_a / matr_b;

    bool res = true;
    Iterator<double> iter = res_matr.begin();
    Iterator<double> check_iter = res_check.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestDivEq()
{
    Matrix<double> matr_a = {{1, 2, 3},
                             {4, 5, 6},
                             {7, 8, 9}};
    Matrix<double> matr_b = {{1, 0, 0},
                             {0, 1, 0},
                             {0, 0, 1}};
    Matrix<double> res_check(matr_a);

    matr_a /= matr_b;

    bool res = true;
    Iterator<double> iter = matr_a.begin();
    Iterator<double> check_iter = res_check.begin();
    for (; iter != matr_a.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestSumElem()
{
    Matrix<int> matr = {{8, 13},
                          {5, 6},
                          {3, 9},
                          {11, 5}};

    Matrix<int> res_check = {{13, 18},
                             {10, 11},
                             {8, 14},
                             {16, 10}};

    Matrix<int> res_matr = matr + 5;

    bool res = true;
    Iterator<int> iter = res_matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestSumElemEq()
{
    Matrix<int> res_matr = {{8, 13},
                          {5, 6},
                          {3, 9},
                          {11, 5}};

    Matrix<int> res_check = {{13, 18},
                             {10, 11},
                             {8, 14},
                             {16, 10}};
    res_matr += 5;

    bool res = true;
    Iterator<int> iter = res_matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestSubElem()
{
    Matrix<int> matr = {{8, 13},
                          {5, 6},
                          {3, 9},
                          {11, 5}
    };
    Matrix<int> res_check = {{3, 8},
                             {0, 1},
                             {-2, 4},
                             {6, 0}
    };
    Matrix<int> res_matr = matr - 5;

    bool res = true;
    Iterator<int> iter = res_matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestSubElemEq()
{
    Matrix<int> res_matr = {{8, 13},
                          {5, 6},
                          {3, 9},
                          {11, 5}
    };
    Matrix<int> res_check = {{3, 8},
                             {0, 1},
                             {-2, 4},
                             {6, 0}
    };
    res_matr -= 5;

    bool res = true;
    Iterator<int> iter = res_matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestMulElem()
{
    Matrix<int> matr = {{1, 2, 6},
                          {3, 1, 2},
    };

    Matrix<int> res_check = {{2, 4, 12},
                             {6, 2, 4}
    };
    Matrix<int> res_matr = matr * 2;

    bool res = true;
    Iterator<int> iter = res_matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestMulElemEq()
{
    Matrix<int> res_matr = {{1, 2, 6},
                          {3, 1, 2},
    };

    Matrix<int> res_check = {{2, 4, 12},
                             {6, 2, 4}
    };
    res_matr *= 2;

    bool res = true;
    Iterator<int> iter = res_matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestDivElem()
{
    Matrix<double> matr_1 = {{11, 14, 38},
                          {21, 13, 70}
    };
    Matrix<double> matr_2 = {{5.5, 7, 19},
                          {10.5, 6.5, 35},
    };
    Matrix<double> res_matr = matr_1 / 2.0;

    bool res = true;
    Iterator<double> iter = res_matr.begin();
    Iterator<double> check_iter = matr_2.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (std::abs(*iter - *check_iter) > 1e-6)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestDivElemEq()
{
    Matrix<double> res_matr = {{11, 14, 38},
                          {21, 13, 70}
    };
    Matrix<double> matr_2 = {{5.5, 7, 19},
                          {10.5, 6.5, 35},
    };
    res_matr /= 2.0;

    bool res = true;
    Iterator<double> iter = res_matr.begin();
    Iterator<double> check_iter = matr_2.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (std::abs(*iter - *check_iter) > 1e-6)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestNeg()
{
    Matrix<int> res_matr = {{2, 4, -12},
                       {6, -2, 4}
    };
    Matrix<int> res_check = {{-2, -4, 12},
                             {-6, 2, -4}
    };
    res_matr = -res_matr;

    bool res = true;
    Iterator<int> iter = res_matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != res_matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestEq()
{
    Matrix<int> matr = {{2, 4, -12},
                       {6, -2, 4}
    };
    Matrix<int> res_check = {{2, 4, -12},
                             {6, -2, 4}
    };
    bool res = matr == res_check;

    std::cout << __func__;

    if (res)
        std::cout << ": \tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestNeq()
{
    Matrix<int> matr = {{2, 4, -12},
                       {6, -2, 4}
    };
    Matrix<int> res_check = {{2, 4, -12},
                             {6, 2, 4}
    };
    bool res = matr != res_check;

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestInsertRow()
{
    Matrix<int> matr = {{1, 2, 3},
                       {4, 5, 6},
                       {2, 4, -12}
    };
    Matrix<int> res_check = {{1, 2, 3},
                             {4, 5, 6},
                             {2, 4, -12},
                             {1, 1, 1}
    };
    matr.InsertRow(3, 1);

    bool res = true;
    Iterator<int> iter = matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestInsertCol()
{
    Matrix<int> matr = {{1, 2, 3},
                       {4, 5, 6},
                       {2, 4, -12}
    };
    Matrix<int> res_check = {{1, 2, 3, 1},
                             {4, 5, 6, 1},
                             {2, 4, -12, 1},
    };
    matr.InsertCol(3, 1);

    bool res = true;
    Iterator<int> iter = matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestDeleteRow()
{
    Matrix<int> matr = {{1, 2, 3},
                       {4, 5, 6},
                       {2, 4, -12},
                       {3, 4, 1}
    };
    Matrix<int> res_check = {{1, 2, 3},
                             {2, 4, -12},
                             {3, 4, 1}
    };
    matr.DeleteRow(1);

    bool res = true;
    Iterator<int> iter = matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}

void UnitTests::TestDeleteCol()
{
    Matrix<int> matr = {{1, 2, 3, 3},
                       {4, 5, 6, 4},
                       {2, 4, -12, 1}
    };
    Matrix<int> res_check = {{2, 3, 3},
                             {5, 6, 4},
                             {4, -12, 1}
    };
    matr.DeleteCol(0);

    bool res = true;
    Iterator<int> iter = matr.begin();
    Iterator<int> check_iter = res_check.begin();
    for (; iter != matr.end(); ++iter, ++check_iter) {
        if (*iter != *check_iter)
            res = false;
    }

    std::cout << __func__;

    if (res)
        std::cout << ":\tpassed" << std::endl;
    else
        std::cout << ":\tfailed" << std::endl;
}
