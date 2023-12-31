#ifndef ITERATOR_H
#define ITERATOR_H

#include <memory>
#include <string>
#include "../exceptions/exceptions.h"

template <typename T>
class Matrix;

template <typename T>
class Iterator: public std::iterator<std::forward_iterator_tag, T> {
public:
    Iterator(const Iterator& it) = default;
    Iterator(const std::shared_ptr<typename Matrix<T>::MatrixRow[]>& matrix_ptr, size_t rows, size_t cols, size_t ind = 0):
        data(matrix_ptr), rows(rows), cols(cols), index(ind) {}

    bool operator!=(Iterator const& other) const;
    bool operator==(Iterator const& other) const;
    bool operator<(Iterator const& other) const;
    bool operator>(Iterator const& other) const;

    operator bool() const;
    bool isEnd() const;
    bool isValid() const;

    Iterator<T> operator+(const int value) const;
    Iterator<T> operator-(const int value) const;
    Iterator<T> &operator+=(const int value);
    Iterator<T> &operator=(const Iterator<T> &it);

    T& operator*();
    const T& operator*() const;
    T& value();
    const T& value() const;

    T* operator->();
    const T* operator->() const;

    Iterator<T>& operator++();
    Iterator<T>& next();
    Iterator<T> operator++(int);

private:
    void checkIndex(const string hint = "");
    void checkValid(const string hint = "") const;
    std::weak_ptr<typename Matrix<T>::MatrixRow[]> data;
    size_t rows, cols, index;
};

#include "iterator.hpp"

#endif // ITERATOR_H
