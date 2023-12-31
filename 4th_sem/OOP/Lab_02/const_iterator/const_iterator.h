#ifndef CONSTITERATOR_H
#define CONSTITERATOR_H

#include <memory>
#include <string>

#include "../exceptions/exceptions.h"

template <typename T>
class Matrix;

template <typename T>
class ConstIterator: public std::iterator<std::forward_iterator_tag, T> {
public:
    ConstIterator(const ConstIterator& it) = default;
    ConstIterator(const std::shared_ptr<typename Matrix<T>::MatrixRow[]>& matrix_ptr, size_t rows, size_t cols, size_t ind = 0):
        data(matrix_ptr), rows(rows), cols(cols), index(ind) {}

    bool operator!=(ConstIterator const& other) const;
    bool operator==(ConstIterator const& other) const;
    bool operator<(ConstIterator const& other) const;
    bool operator>(ConstIterator const& other) const;

    operator bool() const;
    bool isEnd() const;
    bool isValid() const;

    ConstIterator<T> operator+(const int value) const;
    ConstIterator<T> &operator+=(const int value) const;
    ConstIterator<T> operator-(const int value) const;

    const T& operator*() const;
    const T& value() const;

    const T* operator->() const;

    const ConstIterator<T>& operator++() const;
    ConstIterator<T>& next() const;
    ConstIterator<T> operator++(int) const;

private:
    void checkIndex(const string hint = "") const;
    void checkValid(const string hint = "") const;
    std::weak_ptr<typename Matrix<T>::MatrixRow[]> data = nullptr;
    mutable size_t index = 0;
    size_t rows = 0;
    size_t cols = 0;
};

#include "const_iterator.hpp"

#endif // CONSTITERATOR_H
