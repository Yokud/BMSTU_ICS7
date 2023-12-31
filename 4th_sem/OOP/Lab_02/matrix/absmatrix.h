#ifndef ABSMATRIX_H
#define ABSMATRIX_H

#include <iostream>

class AbsMatrix
{
protected:
    size_t rows = 0, cols = 0;

public:
    AbsMatrix(size_t rows = 0, size_t cols = 0): rows(rows), cols(cols) {}

    virtual size_t get_rows() const noexcept { return rows;}
    virtual size_t get_cols() const noexcept { return cols;}

    virtual operator bool() const noexcept { return rows && cols;}

    virtual ~AbsMatrix() = 0;
};

#endif // ABSMATRIX_H
