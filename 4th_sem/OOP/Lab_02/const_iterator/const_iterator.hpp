template <typename T>
void ConstIterator<T>::checkIndex(const string hint) const {
    if (index < rows * cols)
        return;

    throw IndexError(__TIME__, __FILE__, __LINE__, hint);
}

template <typename T>
void ConstIterator<T>::checkValid(const string hint) const {
    if (!isValid())
        throw MemoryError(__TIME__, __FILE__, __LINE__, hint);
}

template <typename T>
bool ConstIterator<T>::operator!=(ConstIterator const& other) const {
    return index != other.index;
}

template <typename T>
bool ConstIterator<T>::operator==(ConstIterator const& other) const {
    return index == other.index;
}

template <typename T>
const T& ConstIterator<T>::operator*() const {
    checkValid("Iterator points on nullptr");
    checkIndex("ConstIterator doens't in data bounds, while executing const operator*");
    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = data.lock();
    return data_ptr[index / cols][index % cols];
}

template <typename T>
const T& ConstIterator<T>::value() const {
    return operator*();
}

template <typename T>
const T* ConstIterator<T>::operator->() const {
    checkValid("Iterator points on nullptr");
    checkIndex("ConstIterator doens't in data bounds, while executing const operator->");
    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = data.lock();
    return data_ptr[index / cols].getAddr() + (index % cols);
}

template <typename T>
const ConstIterator<T>& ConstIterator<T>::operator++() const {
    if (index < cols * rows)
        ++index;
    return *this;
}

template <typename T>
ConstIterator<T>& ConstIterator<T>::next() const {
    return operator++();
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator++(int) const {
    ConstIterator<T> it(*this);
    ++(*this);
    return it;
}

template <typename T>
bool ConstIterator<T>::operator<(ConstIterator const& other) const {
    return index < other.index;
}

template <typename T>
bool ConstIterator<T>::operator>(ConstIterator const& other) const {
    return index > other.index;
}

template <typename T>
bool ConstIterator<T>::isEnd() const {
    return index == rows * cols;
}

template <typename T>
ConstIterator<T>::operator bool() const {
    return data.expired();
}

template <typename T>
bool ConstIterator<T>::isValid() const {
    return !data.expired();
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator+(const int value) const {
    ConstIterator<T> it(*this);
    if (value < 0 && it._index < static_cast<size_t>(-value))
        it._index = 0;
    else
        it._index += value;

    if (it._index > rows * cols)
        it._index = rows * cols;

    return it;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator-(const int value) const {
    return operator+(-value);
}

template <typename T>
ConstIterator<T> &ConstIterator<T>::operator+=(const int value) const {
    index += value;
    return *this;
}
