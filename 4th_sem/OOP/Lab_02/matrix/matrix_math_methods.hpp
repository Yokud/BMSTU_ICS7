template <typename T>
Matrix<T> Matrix<T>::AddMatrix(const Matrix &matrix) const
{
    checkSizes(matrix);

    Matrix<T> result(this->rows, this->cols);

    for (size_t i = 0; i < result.rows; i++)
        for (size_t j = 0; j < result.cols; j++)
            result[i][j] = this->data[i][j] + matrix.data[i][j];

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::SubMatrix(const Matrix &matrix) const
{
    checkSizes(matrix);

    Matrix<T> result(this->rows, this->cols);

    for (size_t i = 0; i < result.rows; i++)
        for (size_t j = 0; j < result.cols; j++)
            result[i][j] = this->data[i][j] - matrix.data[i][j];

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::MulMatrix(const Matrix &matrix) const
{
    checkMultSizes(matrix);

    Matrix<T> result(this->rows, matrix.cols);

    for (size_t i = 0; i < this->rows; i++)
            for (size_t j = 0; j < matrix.cols; j++)
            {
                result[i][j] = 0;
                for (size_t k = 0; k < this->cols; k++)
                    result[i][j] += this->data[i][k] * matrix[k][j];
            }

    return result;
}

template <typename T>
void Matrix<T>::AddEqMatrix(const Matrix &matrix)
{
    checkSizes(matrix);

    for (size_t i = 0; i < this->rows; i++)
        for (size_t j = 0; j < this->cols; j++)
            this->data[i][j] += matrix.data[i][j];
}

template <typename T>
void Matrix<T>::SubEqMatrix(const Matrix &matrix)
{
    checkSizes(matrix);

    for (size_t i = 0; i < this->rows; i++)
        for (size_t j = 0; j < this->cols; j++)
            this->data[i][j] -= matrix.data[i][j];
}

template <typename T>
void Matrix<T>::MulEqMatrix(const Matrix &matrix)
{
    checkMultSizes(matrix);

    Matrix<T> result(this->rows, matrix.cols);

    for (size_t i = 0; i < this->rows; ++i)
            for (size_t j = 0; j < matrix.cols; ++j)
            {
                result[i][j] = 0;
                for (size_t k = 0; k < this->cols; ++k)
                    result[i][j] += this->data[i][k] * matrix[k][j];
            }

    *this = result;
}

template <typename T>
Matrix<T> Matrix<T>::AddElem(const T &elem) const
{
    Matrix<T> result(this->rows, this->cols);

    for (size_t i = 0; i < result.rows; i++)
        for (size_t j = 0; j < result.cols; j++)
            result[i][j] = this->data[i][j] + elem;

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::SubElem(const T &elem) const
{
    Matrix<T> result(this->rows, this->cols);

    for (size_t i = 0; i < result.rows; i++)
        for (size_t j = 0; j < result.cols; j++)
            result[i][j] = this->data[i][j] - elem;

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::MulElem(const T &elem) const
{
    Matrix<T> result(this->rows, this->cols);

    for (size_t i = 0; i < result.rows; i++)
        for (size_t j = 0; j < result.cols; j++)
            result[i][j] = this->data[i][j] * elem;

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::DivElem(const T &elem) const
{
    if (elem == 0)
        throw InvalidArgument(__TIME__, __FILE__, __LINE__, "Zero division");

    Matrix<T> result(this->rows, this->cols);

    for (size_t i = 0; i < result.rows; i++)
        for (size_t j = 0; j < result.cols; j++)
            result[i][j] = this->data[i][j] / elem;

    return result;
}

template <typename T>
void Matrix<T>::AddEqElem(const T &elem)
{
    for (size_t i = 0; i < this->rows; i++)
        for (size_t j = 0; j < this->cols; j++)
            this->data[i][j] += elem;
}

template <typename T>
void Matrix<T>::SubEqElem(const T &elem)
{
    for (size_t i = 0; i < this->rows; i++)
        for (size_t j = 0; j < this->cols; j++)
            this->data[i][j] -= elem;
}

template <typename T>
void Matrix<T>::MulEqElem(const T &elem)
{
    for (size_t i = 0; i < this->rows; i++)
        for (size_t j = 0; j < this->cols; j++)
            this->data[i][j] *= elem;
}

template <typename T>
void Matrix<T>::DivEqElem(const T &elem)
{
    if (elem == 0)
        throw InvalidArgument(__TIME__, __FILE__, __LINE__, "Zero division");

    for (size_t i = 0; i < this->rows; i++)
        for (size_t j = 0; j < this->cols; j++)
            this->data[i][j] /= elem;
}

template <typename T>
Matrix<T> Matrix<T>::Neg()
{
    Matrix<T> result(this->rows, this->cols);

    for (size_t i = 0; i < result.rows; i++)
        for (size_t j = 0; j < result.cols; j++)
            result[i][j] = -this->data[i][j];

    return result;
}

template <typename T>
T Matrix<T>::Determinant() const
{
    if (!IsSquare())
        throw InvalidArgument(__TIME__, __FILE__, __LINE__, "Matrix should be square to get determinant");

    if (rows == 1)
    {
        T det = data[0][0];
        return det;
    }
    else if (rows == 2)
    {
        T det = data[0][0] * data[1][1] - data[0][1] * data[1][0];
        return det;
    }

    T det = 0;
    int sig = 1;
    for (size_t i = 0; i < rows; ++i)
    {
        Matrix<T> temp = this->SubMatrix(0, i);
        det += sig * data[0][i] * temp.Determinant();
        sig *= -1;
    }

    return det;
}

template <typename T>
Matrix<T> Matrix<T>::Transpose() const
{
    Matrix<T> result(this->cols, this->rows);

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            result[j][i] = this->data[i][j];

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::SubMatrix(size_t cross_row, size_t cross_col) const
{
    if (cross_row >= rows || cross_col >= cols)
        throw InvalidArgument(__TIME__, __FILE__, __LINE__, "impossible to make operation: position is out of range");

    Matrix<T> sub_matrix = Matrix<T>{rows - 1, cols - 1};

    for (size_t i = 0, p = 0; i < rows; ++i, ++p)
    {
        if (i == cross_row)
        {
            --p;
            continue;
        }

        for (size_t j = 0, k = 0; j < rows; ++j, ++k)
        {
            if (j == cross_col)
            {
                --k;
                continue;
            }
            sub_matrix[p][k] = data[i][j];
        }
    }

    return sub_matrix;
}

template <typename T>
Matrix<T> Matrix<T>::Adjoint() const
{
    if (!IsSquare())
        throw InvalidArgument(__TIME__, __FILE__, __LINE__, "Matrix should be square to get determinant");

    Matrix<T> res{*this};

    if (cols == 1)
    {
        res[0][0] = 1.0;
        return res;
    }

    Matrix<T> copy {*this};
    T val;
    int sig;
    for (size_t i = 0; i < rows; i++)
    {
        sig = i % 2 == 0 ? 1 : -1;

        for (size_t j = 0; j < cols; j++)
        {
            Matrix<T> tmp = this->SubMatrix(i, j);
            val = tmp.Determinant();
            res[j][i] = val * sig;
            sig *= -1;
        }
    }
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::Inverse() const
{
    T det = Determinant();

    if (!det)
        throw InvalidArgument(__TIME__, __FILE__, __LINE__, "Matrix should have non-zero determinant");

    Matrix<T> result{*this};
    result = result.Adjoint();
    result /= det;

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::DivMatrix(const Matrix &matrix) const
{
    return MulMatrix(matrix.Inverse());
}

template <typename T>
void Matrix<T>::DivEqMatrix(const Matrix &matrix)
{
    MulEqMatrix(matrix.Inverse());
}
