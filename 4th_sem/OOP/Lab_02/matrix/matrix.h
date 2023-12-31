#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <memory>
#include <iterator>

#include "absmatrix.h"
#include "../exceptions/exceptions.h"
#include "../const_iterator/const_iterator.h"
#include "../iterator/iterator.h"

template<typename T>
class Matrix: public AbsMatrix
{
public:
    class MatrixRow;

    explicit Matrix(size_t rows = 0, size_t cols = 0);
    Matrix(size_t rows, size_t cols, const T &filler);
    Matrix(size_t rows, size_t cols, const T **matrix);
    Matrix(std::initializer_list<std::initializer_list<T> > init_list);

    explicit Matrix(const Matrix& matrix);
    Matrix(Matrix &&matrix);

    virtual ~Matrix() = default;

    Matrix<T>& operator=(const Matrix &matrix);
    Matrix<T>& operator=(Matrix &&matrix);
    Matrix<T>& operator=(std::initializer_list<std::initializer_list<T>> init_list);


// Compare methods and operators
    bool operator==(const Matrix &matrix) const;
    bool Equals(const Matrix &matrix) const;

    bool operator!=(const Matrix &matrix) const;
    bool Nequals(const Matrix &matrix) const;


// Addition matrix and element
    Matrix<T> operator+(const Matrix &matrix) const;
    Matrix<T> AddMatrix(const Matrix &matrix) const;

    void operator+=(const Matrix &matrix);
    void AddEqMatrix(const Matrix &matrix);

    Matrix<T> operator+(const T &elem) const;
    Matrix<T> AddElem(const T &elem) const;

    void operator+=(const T &elem);
    void AddEqElem(const T &elem);


// Substraction matrix and element
    Matrix<T> operator-(const Matrix &matrix) const;
    Matrix<T> SubMatrix(const Matrix &matrix) const;

    void operator-=(const Matrix &matrix);
    void SubEqMatrix(const Matrix &matrix);

    Matrix<T> operator-(const T &elem) const;
    Matrix<T> SubElem(const T &elem) const;

    void operator-=(const T &elem);
    void SubEqElem(const T &elem);


// Multiplication matrix and element
    Matrix<T> operator*(const Matrix &matrix) const;
    Matrix<T> MulMatrix(const Matrix &matrix) const;

    void operator*=(const Matrix &matrix);
    void MulEqMatrix(const Matrix &matrix);

    Matrix<T> operator*(const T &elem) const;
    Matrix<T> MulElem(const T &elem) const;

    void operator*=(const T &elem);
    void MulEqElem(const T &elem);


// Division matrix and element
    Matrix<T> operator/(const Matrix &matrix) const;
    Matrix<T> DivMatrix(const Matrix &matrix) const;

    void operator/=(const Matrix &matrix);
    void DivEqMatrix(const Matrix &matrix);

    Matrix<T> operator/(const T &elem) const;
    Matrix<T> DivElem(const T &elem) const;

    void operator/=(const T &elem);
    void DivEqElem(const T &elem);


// Negative Matrix
    Matrix<T> operator-();
    Matrix<T> Neg();


// Math methods
    T Determinant() const;

    Matrix<T> Transpose() const;
    Matrix<T> operator!() const;

    Matrix<T> Adjoint() const;

    Matrix<T> Inverse() const;
    Matrix<T> operator~() const;

    Matrix<T> SubMatrix(size_t cross_row, size_t cross_col) const;
    bool IsSquare() const;


// Insert and delete rows and collumns
    void InsertRow(size_t pos, const T &filler);
    void InsertCol(size_t pos, const T &filler);

    void DeleteRow(size_t pos);
    void DeleteCol(size_t pos);

// [][]
    MatrixRow &operator[](size_t row);
    const MatrixRow &operator[](size_t row) const;

// Iterators
    Iterator<T> begin();
    Iterator<T> end();
    ConstIterator<T> begin() const;
    ConstIterator<T> end() const;
    ConstIterator<T> cbegin() const;
    ConstIterator<T> cend() const;

private:
    std::shared_ptr<MatrixRow[]> data { nullptr };
    std::shared_ptr<MatrixRow[]> AllocMatrix(size_t rows, size_t cols);
    void checkIndex(size_t pos, size_t limit) const;
    void checkSizes(const Matrix &matrix) const;
    void checkMultSizes(const Matrix &matrix) const;
    void checkPtr(T *ptr);

public:
    class MatrixRow
    {
    private:
        std::shared_ptr<T[]> row = nullptr;
        size_t len = 0;
    public:
        MatrixRow(): row(nullptr), len(0) {}
        MatrixRow(T *data, const size_t size): row(data), len(size) {}
        MatrixRow(const size_t size);

        T &operator[](size_t index);
        const T &operator[](size_t index) const;
        void reset(T *row, const size_t size);
        void reset();
    };
};

#include "matrix_bool_methods.hpp"
#include "matrix_constrs.hpp"
#include "matrix_ins_del.hpp"
#include "matrix_iterator.hpp"
#include "matrix_math_methods.hpp"
#include "matrix_operators.hpp"
#include "matrix_private.hpp"
#include "matrix_row.hpp"

#endif // MATRIX_H
