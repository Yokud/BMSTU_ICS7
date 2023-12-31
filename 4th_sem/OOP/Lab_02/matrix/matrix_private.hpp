template <typename T>
std::shared_ptr<typename Matrix<T>::MatrixRow[]>
Matrix<T>::AllocMatrix(size_t rows, size_t cols)
{
    std::shared_ptr<MatrixRow[]> matr_ptr(new MatrixRow[rows]);
    try
    {
        for (size_t i = 0; i < rows; i++)
            matr_ptr[i].reset(new T[cols], cols);
    }
    catch (std::bad_alloc &err)
    {
        throw MemoryError(__TIME__, __FILE__, __LINE__, "memory allocation error");
    }
    return matr_ptr;
}

template <typename T>
void Matrix<T>::checkIndex(size_t pos, size_t limit) const
{
    if (pos > limit)
        throw IndexError(__TIME__, __FILE__, __LINE__, "Index is bigger than sizes");
}

template <typename T>
void Matrix<T>::checkSizes(const Matrix &matrix) const
{
    if (rows != matrix.rows || cols != matrix.cols)
        throw IncompatibleElements(__TIME__, __FILE__, __LINE__, "Different matrix sizes");
}
template <typename T>
void Matrix<T>::checkMultSizes(const Matrix &matrix) const
{
    if (cols != matrix.rows)
        throw IncompatibleElements(__TIME__, __FILE__, __LINE__, "Bad sizes of matrices for multiplication");
}

template <typename T>
void Matrix<T>::checkPtr(T *ptr)
{
    if (!ptr)
        throw InvalidArgument(__TIME__, __FILE__, __LINE__, "nullptr as a ptr of c-matrix");
}
