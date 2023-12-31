template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
{
    this->data = AllocMatrix(rows, cols);
    this->rows = rows;
    this->cols = cols;
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T &filler)
{
    this->data = AllocMatrix(rows, cols);
    this->rows = rows;
    this->cols = cols;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            data[i][j] = filler;
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T **matrix)
{
    checkPtr(matrix);
    this->data = AllocMatrix(rows, cols);
    this->rows = rows;
    this->cols = cols;

    for (size_t i = 0; i < rows; i++)
    {
        checkPtr(matrix[i]);
        for (size_t j = 0; j < cols; j++)
            data[i][j] = matrix[i][j];
    }
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init_list)
{
    size_t rows = init_list.size();
    auto it = init_list.begin();
    size_t cols = it->size();

    for (const auto &ilist: init_list)
        if (ilist.size() != cols)
            throw InvalidArgument(__TIME__, __FILE__, __LINE__, "Bad initializer list");

    this->data = AllocMatrix(rows, cols);
    this->rows = rows;
    this->cols = cols;

    std::size_t i = 0;
    for (const auto &ilist: init_list)
        for (const auto &elem: ilist)
        {
            data[i / cols][i % cols] = elem;
            ++i;
        }
}

template <typename T>
Matrix<T>::Matrix(const Matrix& matrix) : AbsMatrix(matrix.get_rows(), matrix.get_cols())
{
    this->data = AllocMatrix(matrix.get_rows(), matrix.get_cols());
    this->rows = matrix.get_rows();
    this->cols = matrix.get_cols();

    for (std::size_t i = 0; i < rows; i++)
        for (std::size_t j = 0; j < cols; j++)
            data[i][j] = matrix[i][j];
}

template <typename T>
Matrix<T>::Matrix(Matrix &&matrix) : AbsMatrix(matrix.get_rows(), matrix.get_cols())
{
    this->data = matrix.data;
    this->rows = matrix.get_rows();
    this->cols = matrix.get_cols();
}
