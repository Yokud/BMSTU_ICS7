template <typename T>
void Matrix<T>::InsertRow(size_t pos, const T &filler)
{
    if (pos > rows)
        throw IndexError(__TIME__, __FILE__, __LINE__, "Impossible to make operation: position is out of range");

    Matrix<T> tmp(rows + 1, cols);
    for (size_t i = 0; i < rows + 1; i++)
        for (size_t j = 0; j < cols; j++)
        {
            if (i < pos)
                tmp[i][j] = (*this)[i][j];
            if (i == pos)
                tmp[i][j] = filler;
            if (i > pos)
                tmp[i][j] = (*this)[i - 1][j];
        }
    (*this) = tmp;
}

template <typename T>
void Matrix<T>::InsertCol(size_t pos, const T &filler)
{
    if (pos > cols)
        throw IndexError(__TIME__, __FILE__, __LINE__, "Impossible to make operation: position is out of range");

    Matrix<T> tmp(rows, cols + 1);
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols + 1; j++)
        {
            if (j < pos)
                tmp[i][j] = (*this)[i][j];
            if (j == pos)
                tmp[i][j] = filler;
            if (j > pos)
                tmp[i][j] = (*this)[i][j - 1];
        }
    (*this) = tmp;
}

template <typename T>
void Matrix<T>::DeleteRow(size_t pos)
{
    if (pos >= rows)
        throw IndexError(__TIME__, __FILE__, __LINE__, "Impossible to make operation: position is out of range");

    Matrix<T> tmp(rows - 1, cols);
    for (size_t i = 0; i < rows - 1; i++)
        for (size_t j = 0; j < cols; j++)
        {
            if (i < pos)
                tmp[i][j] = (*this)[i][j];
            if (i >= pos)
                tmp[i][j] = (*this)[i + 1][j];
        }
    (*this) = tmp;
}

template <typename T>
void Matrix<T>::DeleteCol(size_t pos)
{
    if (pos >= cols)
        throw IndexError(__TIME__, __FILE__, __LINE__, "Impossible to make operation: position is out of range");

    Matrix<T> tmp(rows, cols - 1);
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols - 1; j++)
        {
            if (j < pos)
                tmp[i][j] = (*this)[i][j];
            if (j >= pos)
                tmp[i][j] = (*this)[i][j + 1];
        }
    (*this) = tmp;
}
