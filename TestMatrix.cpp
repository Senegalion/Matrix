#include "Matrix.h"
#include <iostream>

void testMatrixCreation() {
    Matrix matrix1(2, 3);

    cout << endl << "TEST MATRIX CREATION" << endl;
    cout << "Matrix 1:" << endl;
    cout << matrix1 << endl;
}

void testMatrixCopyConstructor() {
    Matrix matrix1(2, 3);
    Matrix matrix2(matrix1);

    cout << endl << "TEST MATRIX COPY CONSTRUCTOR" << endl;
    cout << "Matrix 1:" << endl;
    cout << matrix1 << endl;

    cout << "Matrix 2:" << endl;
    cout << matrix2 << endl;
}

void testMatrixAssignmentOperator() {
    Matrix matrix1(2, 3);
    Matrix matrix2;
    matrix2 = matrix1;

    cout << endl << "TEST MATRIX ASSIGNMENT OPERATOR" << endl;
    cout << "Matrix 1:" << endl;
    cout << matrix1 << endl;

    cout << "Matrix 2:" << endl;
    cout << matrix2 << endl;
}

void testSingleElementAccess() {
    Matrix matrix1(2, 2);
    matrix1(0, 0) = 1;
    matrix1(0, 1) = 2;
    matrix1(1, 0) = 3;
    matrix1(1, 1) = 4;

    Matrix matrix2(2, 2);
    matrix2(0, 0) = 5;
    matrix2(0, 1) = 6;
    matrix2(1, 0) = 7;
    matrix2(1, 1) = 8;

    Matrix matrixSum = matrix1 + matrix2;
    Matrix matrixDifference = matrix1 - matrix2;
    Matrix matrixProduct = matrix1 * matrix2;

    cout << endl << "TEST MATRIX SINGLE ELEMENT ACCESS" << endl;
    cout << "Matrix 1 + Matrix 2: " << endl;
    cout << matrixSum << endl;

    cout << "Matrix 1 - Matrix 2: " << endl;
    cout << matrixDifference << endl;

    cout << "Matrix 1 * Matrix 2: " << endl;
    cout << matrixProduct << endl;
}

void testMatrixAddition() {
    Matrix matrix1;
    matrix1.readMatrixFromTextFile("matrix_input1.txt");
    Matrix matrix2;
    matrix2.readMatrixFromTextFile("matrix_input2.txt");

    Matrix matrixSum = matrix1 + matrix2;
    cout << endl << "TEST MATRIX ADDITION" << endl;
    cout << "Matrix 1 + Matrix 2: " << endl;
    cout << matrixSum << endl;
}

void testAddingMatrix() {
    Matrix matrix1;
    matrix1.readMatrixFromTextFile("matrix_input1.txt");
    Matrix matrix2;
    matrix2.readMatrixFromTextFile("matrix_input2.txt");

    matrix1 = (matrix1 += matrix2);
    cout << endl << "TEST ADDING MATRIX" << endl;
    cout << "Matrix 1 += Matrix 2: " << endl;
    cout << matrix1 << endl;
}

void testMatrixSubtraction() {
    Matrix matrix1;
    matrix1.readMatrixFromTextFile("matrix_input1.txt");
    Matrix matrix2;
    matrix2.readMatrixFromTextFile("matrix_input2.txt");

    Matrix matrixDifference = matrix1 - matrix2;
    cout << endl << "TEST MATRIX SUBTRACTION" << endl;
    cout << "Matrix 1 - Matrix 2: " << endl;
    cout << matrixDifference << endl;
}

void testSubtractingMatrix() {
    Matrix matrix1;
    matrix1.readMatrixFromTextFile("matrix_input1.txt");
    Matrix matrix2;
    matrix2.readMatrixFromTextFile("matrix_input2.txt");

    matrix1 -= matrix2;
    cout << endl << "TEST SUBTRACTING MATRIX" << endl;
    cout << "Matrix 1 -= Matrix 2: " << endl;
    cout << matrix1 << endl;
}

void testMatrixMultiplication() {
    Matrix matrix1;
    matrix1.readMatrixFromTextFile("matrix_input1.txt");
    Matrix matrix2;
    matrix2.readMatrixFromTextFile("matrix_input2.txt");

    Matrix matrixProduct = matrix1 * matrix2;
    cout << endl << "TEST MATRIX MULTIPLICATION" << endl;
    cout << "Matrix 1 * Matrix 2: " << endl;
    cout << matrixProduct << endl;
}

void testMultiplyingMatrix() {
    Matrix matrix1;
    matrix1.readMatrixFromTextFile("matrix_input1.txt");
    Matrix matrix2;
    matrix2.readMatrixFromTextFile("matrix_input2.txt");

    matrix1 *= matrix2;
    cout << endl << "TEST MULTIPLYING MATRIX" << endl;
    cout << "Matrix 1 *= Matrix 2: " << endl;
    cout << matrix1 << endl;
}

void testComparisonMatrix() {
    Matrix matrix1;
    matrix1.readMatrixFromTextFile("matrix_input1.txt");
    Matrix matrix2;
    matrix2.readMatrixFromTextFile("matrix_input2.txt");

    cout << endl << "TEST COMPARISON MATRIX" << endl;
    if (matrix1 == matrix2) {
        cout << "Matrices are equal" << endl;
    }

    if (matrix1 != matrix2) {
        cout << "Matrices are not equal" << endl;
    }
}

void testExceptionHandling() {
    cout << endl << "TEST EXCEPTION HANDLING" << endl;
    try {
        Matrix matrix1;
        matrix1.readMatrixFromTextFile("matrix_input1.txt");
        Matrix matrix3;
        matrix3.readMatrixFromTextFile("matrix_input3.txt");
        Matrix matrix = matrix1 + matrix3;
    } catch (const Matrix::DimensionMismatchException& e) {
        std::cerr << "Exception caught: "<< e.what() << std::endl;
    }

    try {
        Matrix matrix1(2, 2);
        matrix1(0, 0) = 1;
        matrix1(0, 1) = 2;
        matrix1(1, 0) = 3;
        matrix1(1, 1) = 4;

        matrix1(5,7) = 5;
    } catch (const Matrix::IndexOutOfRangeException& e) {
        std::cerr << "Exception caught: "<< e.what() << std::endl;
    }
}

void testReferenceCounting() {
    cout << endl << "TEST REFERENCE COUNTING" << endl;
    Matrix matrix1(2, 2);
    if (matrix1.getReferenceCount() == 1)
    {
        Matrix matrix2(matrix1);

        if (matrix1.getReferenceCount() == 2)
        {
            Matrix matrix3;
            matrix3 = matrix1;

            if (matrix1.getReferenceCount() == 3)
            {
                matrix1 += matrix2;
                if (matrix1.getReferenceCount() == 1 && matrix2.getReferenceCount() == 2 && matrix3.getReferenceCount() == 2)
                {
                    cout << "Reference counting test passed" << endl << endl;
                    return;
                }
            }
        }
    }
    cout << "Reference counting test failed" << endl;
}

int main() {
    testMatrixCreation();
    testMatrixCopyConstructor();
    testMatrixAssignmentOperator();
    testSingleElementAccess();
    testMatrixAddition();
    testAddingMatrix();
    testMatrixSubtraction();
    testSubtractingMatrix();
    testMatrixMultiplication();
    testMultiplyingMatrix();
    testComparisonMatrix();
    testExceptionHandling();
    testReferenceCounting();
    return 0;
}
