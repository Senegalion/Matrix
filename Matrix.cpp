#include "Matrix.h"

struct Matrix::matrix {
    double **matrixData;
    int rows;
    int columns;
    int referenceCounting;

    matrix(int rows, int columns) {
        referenceCounting = 1;
        this->rows = rows;
        this->columns = columns;
        matrixData = new double*[rows];
        for (int i = 0; i < rows; i++) {
            matrixData[i] = new double[columns];
            for (int j = 0; j < columns; j++) {
                matrixData[i][j] = 0.0;
            }
        }
    }

    matrix(int rows, int columns, double** oldMatrixData) {
        referenceCounting = 1;
        this->rows = rows;
        this->columns = columns;
        matrixData = new double*[rows];
        for (int i = 0; i < rows; i++) {
            matrixData[i] = new double[columns];
            for (int j = 0; j < columns; j++) {
                matrixData[i][j] = oldMatrixData[i][j];
            }
        }
    };

    ~matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] matrixData[i];
        }

        delete[] matrixData;
    };

    matrix* detach() {
        if (referenceCounting <= 1) {
        return this;
        }
        matrix* newData = new matrix(rows, columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                newData->matrixData[i][j] = matrixData[i][j];
            }
        }
        referenceCounting--;
        return newData;
    };

private:
    matrix(const matrix&);
    matrix& operator=(const matrix&);
};

Matrix::Matrix() {
    data = new matrix(0, 0);
}

Matrix::Matrix(int rows, int columns) {
    data = new matrix(rows, columns);
}

Matrix::Matrix(const Matrix& otherMatrix) {
    otherMatrix.data->referenceCounting++;
    data = otherMatrix.data;
}

Matrix::~Matrix() {
    if (--data->referenceCounting == 0) {
        delete data;
    }
}

Matrix& Matrix::operator=(const Matrix& otherMatrix) {
    otherMatrix.data->referenceCounting++;
    if (--data->referenceCounting == 0)
        delete data;
    data = otherMatrix.data;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    if (matrix.data == nullptr) {
        os << "Matrix is empty";
    } else {
        for (int i = 0; i < matrix.data->rows; i++) {
            for (int j = 0; j < matrix.data->columns; j++) {
                os << matrix(i, j) << " ";
            }
            os << std::endl;
        }
    }
    return os;
}

Matrix Matrix::operator+(const Matrix& otherMatrix) {
    if (data->rows != otherMatrix.data->rows || data->columns != otherMatrix.data->columns) {
        throw DimensionMismatchException();
    }

    Matrix resultMatrix(data->rows, data->columns);
    for (int i = 0; i < data->rows; i++) {
        for (int j = 0; j < data->columns; j++) {
            resultMatrix(i, j) = (*this)(i, j) + otherMatrix(i, j);
        }
    }
    return resultMatrix;
}

Matrix Matrix::operator-(const Matrix& otherMatrix) {
    if (data->rows != otherMatrix.data->rows || data->columns != otherMatrix.data->columns) {
        throw DimensionMismatchException();
    }

    Matrix resultMatrix(data->rows, data->columns);
    for (int i = 0; i < data->rows; i++) {
        for (int j = 0; j < data->columns; j++) {
            resultMatrix(i, j) = (*this)(i, j) - otherMatrix(i, j);
        }
    }
    return resultMatrix;
}

Matrix Matrix::operator*(const Matrix& otherMatrix) {
    if (data->columns != otherMatrix.data->rows) {
        throw DimensionMismatchException();
    }

    Matrix result(data->rows, otherMatrix.data->columns);
    for (int i = 0; i < data->rows; i++) {
        for (int j = 0; j < otherMatrix.data->columns; j++) {
            double sum = 0.0;
            for (int k = 0; k < data->columns; k++) {
                sum += (*this)(i, k) * otherMatrix(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

Matrix& Matrix::operator+=(const Matrix& otherMatrix) {
    if (data->rows != otherMatrix.data->rows || data->columns != otherMatrix.data->columns) {
        throw DimensionMismatchException();
    }
    data = data->detach();

    for (int i = 0; i < data->rows; i++) {
        for (int j = 0; j < data->columns; j++) {
            (*this)(i, j) += otherMatrix(i, j);
        }
    }

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& otherMatrix) {
    if (data->rows != otherMatrix.data->rows || data->columns != otherMatrix.data->columns) {
        throw DimensionMismatchException();
    }
    data = data->detach();

    for (int i = 0; i < data->rows; i++) {
        for (int j = 0; j < data->columns; j++) {
            (*this)(i, j) -= otherMatrix(i, j);
        }
    }

    return *this;
}

Matrix& Matrix::operator*=(const Matrix& otherMatrix) {
    if (data->columns != otherMatrix.data->rows) {
        throw DimensionMismatchException();
    }
    data = data->detach();

    Matrix result(data->rows, otherMatrix.data->columns);

    for (int i = 0; i < data->rows; i++) {
        for (int j = 0; j < otherMatrix.data->columns; j++) {
            double sum = 0.0;
            for (int k = 0; k < data->columns; k++) {
                sum += (*this)(i, k) * otherMatrix(k, j);
            }
            result(i, j) = sum;
        }
    }

    *this = result;

    return *this;
}

bool operator==(const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.data->rows != matrix2.data->rows || matrix1.data->columns != matrix2.data->columns) {
        return false;
    }

    for (int i = 0; i < matrix1.data->rows; i++) {
        for (int j = 0; j < matrix1.data->columns; j++) {
            if (matrix1.data->matrixData[i][j] != matrix2.data->matrixData[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix& matrix1, const Matrix& matrix2) {
    return !(matrix1 == matrix2);
}

double Matrix::read(int row, int column) const {
    if (row < 0 || row >= data->rows || column < 0 || column >= data->columns) {
        throw IndexOutOfRangeException();
    }
    return data->matrixData[row][column];
}

void Matrix::write(int row, int column, double number) {
    data = data->detach();
    if (row < 0 || row >= data->rows || column < 0 || column >= data->columns) {
        throw IndexOutOfRangeException();
    }
    data->matrixData[row][column] = number;
}

double Matrix::operator()(int row, int column) const {
    if (row < 0 || row >= data->rows || column < 0 || column >= data->columns) {
        throw IndexOutOfRangeException();
    }
    return data->matrixData[row][column];
}

Matrix::Cref Matrix::operator()(int row, int column) {
    if (row < 0 || row >= data->rows || column < 0 || column >= data->columns) {
        throw IndexOutOfRangeException();
    }
    return Cref(*this, row, column);
}

Matrix& Matrix::readMatrixFromTextFile(const std::string fileName) {
    std::ifstream inputFile(fileName);
    data = data->detach();

    if (!inputFile.is_open()) {
        throw Matrix::ReadFromFileException();
    }

    int rows, columns;
    inputFile >> rows >> columns;

    Matrix temp(rows, columns);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            double value;
            inputFile >> value;
            temp.data->matrixData[i][j] = value;
        }
    }

    inputFile.close();

    *this = temp;

    return *this;
}

int Matrix::getReferenceCount() const
{
    return data->referenceCounting;
}
