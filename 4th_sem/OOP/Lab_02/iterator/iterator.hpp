template <typename T>
void Iterator<T>::checkIndex(const string hint)
{
    if (index < rows * cols)
        return;

    throw IndexError(__TIME__, __FILE__, __LINE__, hint);
}

template <typename T>
void Iterator<T>::checkValid(const string hint) const
{
    if (!isValid())
        throw MemoryError(__TIME__, __FILE__, __LINE__, hint);
}

template <typename T>
bool Iterator<T>::operator!=(Iterator const& other) const
{
    return index != other.index;
}

template <typename T>
bool Iterator<T>::operator==(Iterator const& other) const
{
    return index == other.index;
}

template <typename T>
T& Iterator<T>::operator*()
{
    checkValid("Iterator points on nullptr");
    checkIndex("Iterator doens't in data bounds, while executing operator*");
    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = data.lock();
    return data_ptr[index / cols][index % cols];
}

template <typename T>
T& Iterator<T>::value()
{
    return operator*();
}

template <typename T>
const T& Iterator<T>::operator*() const
{
    checkValid("Iterator points on nullptr");
    checkIndex("Iterator doens't in data bounds, while executing const operator*");
    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = data.lock();
    return data_ptr[index / cols][index % cols];
}

template <typename T>
const T& Iterator<T>::value() const
{
    return operator*();
}

template <typename T>
T* Iterator<T>::operator->()
{
    checkValid("Iterator points on nullptr");
    checkIndex("Iterator doens't in data bounds, while executing operator->");

    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = data.lock();
    return data_ptr[index / cols].getAddr() + (index % cols);
}

template <typename T>
const T* Iterator<T>::operator->() const
{
    checkValid("Iterator points on nullptr");
    checkIndex("Iterator doens't in data bounds, while executing const operator->");

    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = data.lock();
    return data_ptr[index / cols].getAddr() + (index % cols);
}

template <typename T>
Iterator<T>& Iterator<T>::operator++()
{
    if (index < cols * rows)
        ++index;
    return *this;
}

template <typename T>
Iterator<T>& Iterator<T>::next()
{
    return operator++();
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int)
{
    Iterator<T> it(*this);
    ++(*this);
    return it;
}

template <typename T>
bool Iterator<T>::operator<(Iterator const& other) const
{
    return index < other.index;
}

template <typename T>
bool Iterator<T>::operator>(Iterator const& other) const
{
    return index > other.index;
}

template <typename T>
bool Iterator<T>::isEnd() const
{
    return index == rows * cols;
}

template <typename T>
Iterator<T>::operator bool() const
{
    return data.expired();
}

template <typename T>
bool Iterator<T>::isValid() const
{
    return !data.expired();
}

template <typename T>
Iterator<T> Iterator<T>::operator+(const int value) const
{
    Iterator<T> it(*this);
    if (value < 0 && it.index < static_cast<size_t>(-value))
        it.index = 0;
    else
        it.index += value;

    if (it.index < 0)
        it.index = 0;
    else if (it.index > rows * cols)
        it.index = rows * cols;

    return it;
}

template <typename T>
Iterator<T> Iterator<T>::operator-(const int value) const
{
    return operator+(-value);
}

template <typename T>
Iterator<T> &Iterator<T>::operator+=(const int value)
{
    index += value;
    return *this;
}

template <typename T>
Iterator<T> &Iterator<T>::operator=(const Iterator<T> &it)
{
    data = it.data, index = it.index, rows = it.rows, cols = it.cols;
    return *this;
}
