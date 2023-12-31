#include "unit_tests/unittests.h"

int main(void)
{
    UnitTests unit;

    unit.TestDet();
    unit.TestTranspose();
    unit.TestInverse();

    unit.TestSum();
    unit.TestSumEq();
    unit.TestSub();
    unit.TestSubEq();
    unit.TestMult();
    unit.TestMultEq();
    unit.TestDiv();
    unit.TestDivEq();

    unit.TestSumElem();
    unit.TestSumElemEq();
    unit.TestSubElem();
    unit.TestSubElemEq();
    unit.TestMulElem();
    unit.TestMulElemEq();
    unit.TestDivElem();
    unit.TestDivElemEq();
    unit.TestNeg();

    unit.TestEq();
    unit.TestNeq();

    unit.TestInsertRow();
    unit.TestInsertCol();
    unit.TestDeleteRow();
    unit.TestDeleteCol();

    return 0;
}
