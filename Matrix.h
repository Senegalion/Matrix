#ifndef _MATRIX_H_
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

class Matrix {
private:
    struct matrix;
    matrix* data;

public:
    class Cref;
    Matrix();
    Matrix(int rows, int columns);
    Matrix(const Matrix& otherMatrix);
    ~Matrix();
    Matrix& operator=(const Matrix& otherMatrix);
    friend std::ostream& operator>>(std::ostream& os, const Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend bool operator==(const Matrix& matrix1, const Matrix& matrix2);
    friend bool operator!=(const Matrix& matrix1, const Matrix& matrix2);
    Matrix operator+(const Matrix& otherMatrix);
    Matrix operator-(const Matrix& otherMatrix);
    Matrix operator*(const Matrix& otherMatrix);
    Matrix& operator+=(const Matrix& otherMatrix);
    Matrix& operator-=(const Matrix& otherMatrix);
    Matrix& operator*=(const Matrix& otherMatrix);
    Matrix& readMatrixFromTextFile(const std::string fileName);
    double read(int row, int column) const;
    void write(int row, int column, double number);
    double operator()(int row, int column) const;
    Cref operator()(int row, int column);
    int getReferenceCount() const;

    class MatrixException : public std::exception {
    public:
        virtual const char* what() const noexcept override {
            return "Matrix Exception";
        }
    };

    class DimensionMismatchException : public MatrixException {
    public:
        const char* what() const noexcept override {
            return "Matrix Dimension Mismatch Exception";
        }
    };

    class IndexOutOfRangeException : public MatrixException {
    public:
        const char* what() const noexcept override {
            return "Matrix Index Out Of Range Exception";
        }
    };

    class ReadFromFileException : public MatrixException {
    public:
        const char* what() const noexcept override {
            return "Read From File Exception";
        }
    };
};

class Matrix::Cref {
    friend class Matrix;
    Matrix& referenceToMatrix;
    int row;
    int column;
    Cref(Matrix& referenceToMatrix, int row, int column) : referenceToMatrix(referenceToMatrix), row(row), column(column) {};

public:
    operator char() const
    {
        return referenceToMatrix.read(row, column);
    }
    Matrix::Cref& operator=(double number)
    {
        referenceToMatrix.write(row, column, number);
        return *this;
    }
    Matrix::Cref& operator=(const Cref& ref)
    {
        return operator=((char)ref);
    }

    Matrix::Cref& operator+=(double number) {
        referenceToMatrix.write(row, column, referenceToMatrix.read(row, column) + number);
        return *this;
    }
    
    Matrix::Cref& operator-=(double number) {
        referenceToMatrix.write(row, column, referenceToMatrix.read(row, column) - number);
        return *this;
    }
};

#endif
