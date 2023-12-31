#ifndef UNITTESTS_H
#define UNITTESTS_H

#include <iostream>
#include "../matrix/matrix.h"

class UnitTests
{
public:
    UnitTests() = default;

    void TestDet();
    void TestTranspose();
    void TestInverse();

    void TestSum();
    void TestSumEq();
    void TestSub();
    void TestSubEq();
    void TestMult();
    void TestMultEq();
    void TestDiv();
    void TestDivEq();

    void TestSumElem();
    void TestSumElemEq();
    void TestSubElem();
    void TestSubElemEq();
    void TestMulElem();
    void TestMulElemEq();
    void TestDivElem();
    void TestDivElemEq();
    void TestNeg();

    void TestEq();
    void TestNeq();

    void TestInsertRow();
    void TestInsertCol();
    void TestDeleteRow();
    void TestDeleteCol();
};

#endif // UNITTESTS_H
