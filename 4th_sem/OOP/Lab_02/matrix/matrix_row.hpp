template <typename T>
Matrix<T>::MatrixRow::MatrixRow(const size_t size)
{
    this->row.reset(new T[size]);
    this->len = size;
}

template <typename T>
T &Matrix<T>::MatrixRow::operator[](size_t index)
{
    if (index >= len)
        throw IndexError(__TIME__, __FILE__, __LINE__, "Incorrect column");

    return row[index];
}

template <typename T>
const T &Matrix<T>::MatrixRow::operator[](size_t index) const
{
    if (index >= len)
        throw IndexError(__TIME__, __FILE__, __LINE__, "Incorrect column");

    return row[index];
}

template <typename T>
void Matrix<T>::MatrixRow::reset(T *row, const size_t size) {
    this->len = size;
    this->row.reset(row);
}

template <typename T>
void Matrix<T>::MatrixRow::reset() {
    len = 0;
    row.reset();
}
