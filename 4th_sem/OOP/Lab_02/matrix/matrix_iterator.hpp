template <typename T>
Iterator<T> Matrix<T>::begin()
{
    return Iterator<T>(data, rows, cols, 0);
}

template <typename T>
Iterator<T> Matrix<T>::end()
{
    return Iterator<T>(data, rows, cols, cols * rows);
}

template <typename T>
ConstIterator<T> Matrix<T>::begin() const
{
    return ConstIterator<T>(data, rows, cols, 0);
}

template <typename T>
ConstIterator<T> Matrix<T>::end() const
{
    return ConstIterator<T>(data, rows, cols, cols * rows);
}

template <typename T>
ConstIterator<T> Matrix<T>::cbegin() const
{
    return ConstIterator<T>(data, rows, cols, 0);
}

template <typename T>
ConstIterator<T> Matrix<T>::cend() const
{
    return ConstIterator<T>(data, rows, cols, cols * rows);
}
