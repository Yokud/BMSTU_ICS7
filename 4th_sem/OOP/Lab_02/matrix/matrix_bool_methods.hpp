template <typename T>
bool Matrix<T>::operator==(const Matrix &matrix) const
{
    return this->Equals(matrix);
}

template <typename T>
bool Matrix<T>::Equals(const Matrix &matrix) const
{
    if (rows != matrix.rows || cols != matrix.cols)
        return false;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            if (data[i][j] != matrix[i][j])
                return false;

    return true;
}

template <typename T>
bool Matrix<T>::Nequals(const Matrix &matrix) const
{
    return !this->Equals(matrix);
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix &matrix) const
{
    return this->Nequals(matrix);
}

template <typename T>
bool Matrix<T>::IsSquare() const
{
    return rows == cols;
}
