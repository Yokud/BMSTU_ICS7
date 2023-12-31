template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix &matrix)
{
    this->data = AllocMatrix(matrix.rows, matrix.cols);
    this->rows = matrix.rows;
    this->cols = matrix.cols;

    for (size_t i = 0; i < matrix.rows; i++)
        for (size_t j = 0; j < matrix.cols; j++)
            data[i][j] = matrix[i][j];

    return (*this);
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix &&matrix)
{
    this->data = matrix.data;
    this->rows = matrix.rows;
    this->cols = matrix.cols;

    return (*this);
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(std::initializer_list<std::initializer_list<T>> init_list)
{
    Matrix<T> tmp = Matrix(init_list);
    *this = tmp;

    return (*this);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix &matrix) const
{
    return AddMatrix(matrix);
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix &matrix) const
{
    return SubMatrix(matrix);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix &matrix) const
{
    return MulMatrix(matrix);
}

template <typename T>
void Matrix<T>::operator+=(const Matrix &matrix)
{
    AddEqMatrix(matrix);
}

template <typename T>
void Matrix<T>::operator-=(const Matrix &matrix)
{
    SubEqMatrix(matrix);
}

template <typename T>
void Matrix<T>::operator*=(const Matrix &matrix)
{
    MulEqMatrix(matrix);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const T &elem) const
{
    return AddElem(elem);
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const T &elem) const
{
    return SubElem(elem);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T &elem) const
{
    return MulElem(elem);
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T &elem) const
{
    return DivElem(elem);
}

template <typename T>
void Matrix<T>::operator+=(const T &elem)
{
    AddEqElem(elem);
}

template <typename T>
void Matrix<T>::operator-=(const T &elem)
{
    SubEqElem(elem);
}

template <typename T>
void Matrix<T>::operator*=(const T &elem)
{
    MulEqElem(elem);
}

template <typename T>
void Matrix<T>::operator/=(const T &elem)
{
    DivEqElem(elem);
}

template <typename T>
Matrix<T> Matrix<T>::operator-()
{
    return Neg();
}

template <typename T>
typename Matrix<T>::MatrixRow &Matrix<T>::operator[](size_t row)
{
    if (row >= rows)
        throw IndexError(__TIME__, __FILE__, __LINE__, "Incorrect row");

    return data[row];
}

template <typename T>
const typename Matrix<T>::MatrixRow &Matrix<T>::operator[](size_t row) const
{
    if (row >= rows)
        throw IndexError(__TIME__, __FILE__, __LINE__, "Incorrect row");

    return data[row];
}

template <typename Type>
std::ostream& operator<<(std::ostream& os, const Matrix<Type>& matr)
{
    size_t i = 0;
    for (ConstIterator<Type> iter = matr.cbegin(); iter != matr.cend(); iter++, i++) {
        std::cout << *iter << " ";
        if ((i + 1) % matr.get_cols() == 0)
            std::cout << std::endl;
    }
    return os;
}

template <typename Type>
std::ostream& operator<<(std::ostream& os, Matrix<Type>& matr)
{
    size_t i = 0;
    for (ConstIterator<Type> iter = matr.cbegin(); iter != matr.cend(); iter++, i++) {
        std::cout << *iter << " ";
        if ((i + 1) % matr.get_cols() == 0)
            std::cout << std::endl;
    }
    return os;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const Matrix &matrix) const
{
    return DivMatrix(matrix);
}

template <typename T>
void Matrix<T>::operator/=(const Matrix &matrix)
{
    DivEqMatrix(matrix);
}

template <typename T>
Matrix<T> Matrix<T>::operator!() const
{
    return this->Transpose();
}

template <typename T>
Matrix<T> Matrix<T>::operator~() const
{
    return this->Inverse();
}
