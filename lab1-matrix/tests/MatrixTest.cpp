
/**
* @file MatrixTest.cpp
 * @brief This file is the test file for the Matrix class
*/
#include "gtest/gtest.h"
#include "../src/Matrix/Matrix.hpp"
#include "../src/Utils/Utils.h"
#include "../src/Operators/Sub/Sub.h"
#include "../src/Operators/Add/Add.h"
#include "../src/Operators/Multiply/Multiply.h"
#include <string>
#include <vector>
using Vector2D = std::vector<std::vector<unsigned>>;
/**
 * @brief Extracts the matrix inner data and returns it as a 2D vector.
 *
 * This function parses the string representation of a Matrix object to reconstruct
 * and return its internal data as a 2D vector.
 *
 * @param matrix The Matrix object whose data is to be extracted.
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 * @return A 2D vector containing a copy of the matrix's internal data.
 * @note The function assumes that the formatting of the matrix's string representation
 * (provided by `operator<<`) is consistent and correctly represents the matrix's internal structure.
 */
Vector2D getInnerData(const Matrix &matrix, unsigned rows, unsigned cols) {
    std::stringstream s;
    s << matrix;

    // Create the 2d vector
    std::vector<std::vector<unsigned>> data(rows, std::vector<unsigned>(cols));
    std::string line;

    // Parse each element and populate the vector
    for (unsigned i = 0; i < rows && std::getline(s, line); ++i) {
        std::istringstream lineStream(line);
        for (unsigned j = 0; j < cols; ++j) {
            lineStream >> data[i][j];
        }
    }
    return data;
}

/**
 * Verifies that the operator has been correctly applied to the inner values of the result matrix
 * @param m1 The first matrix
 * @param m2 The second matrix
 * @param mRes The result matrix
 * @param rows The number of rows
 * @param cols The number of columns
 * @param mod The modulo to apply
 * @param op The operator to apply
 * @return true if the inner value of the result matrix is correct according to the operator, false otherwise
 */
bool isOperationValid(Matrix &m1, Matrix &m2, Matrix &mRes ,unsigned rows, unsigned cols, unsigned mod, const Operator &op){
    auto dataM1 = getInnerData(m1, rows, cols);
    auto dataM2 = getInnerData(m2, rows, cols);
    auto dataRes = getInnerData(mRes, rows, cols);
    for (unsigned i = 0; i < rows; ++i) {
        for (unsigned j = 0; j < cols; ++j) {
            // Adjust left value to prevent underflow for sub. This has no effect on add/mult
            auto res = op.apply(dataM1.at(i).at(j) + mod, dataM2.at(i).at(j)) % mod;
            if(dataRes.at(i).at(j) != res){
                return false;
            }
        }
    }
    return true;
}

// Function pointer type for member functions of Matrix that return Matrix& (in-place operations)
using MatrixOpMemberFunction = Matrix& (Matrix::*)(const Matrix&);

// Function pointer type for member functions of Matrix that return Matrix* (dynamic operations)
using MatrixOpDynamicFunction = Matrix* (Matrix::*)(const Matrix&) const;

// Helper function to test in-place operations
void testInPlaceOperation(MatrixOpMemberFunction opFunc, const Operator& op) {
    // Get random number of rows, columns and modulo
    const unsigned ROWS = Utils::getRandom(20) + 1, COLS = Utils::getRandom(20) + 1, MOD = Utils::getRandom(20) + 1;

    Matrix m1(ROWS, COLS, MOD), m2(ROWS, COLS, MOD);

    // get a copy before the in-place operation
    auto m1Copy = m1;

    // Execute the operation
    Matrix& mRes = (m1.*opFunc)(m2);

    EXPECT_EQ(&mRes, &m1);  // The returned matrix and m1 must be the same object
    EXPECT_TRUE(isOperationValid(m1Copy, m2, mRes, ROWS, COLS, MOD, op));
}

// Helper function to test dynamic operations
void testDynamicOperation(MatrixOpDynamicFunction opFunc, const Operator& op) {
    // Get random number of rows, columns and modulo
    const unsigned ROWS = Utils::getRandom(20) + 1, COLS = Utils::getRandom(20) + 1, MOD = Utils::getRandom(20) + 1;

    Matrix m1(ROWS, COLS, MOD), m2(ROWS, COLS, MOD);
    std::unique_ptr<Matrix> mRes((m1.*opFunc)(m2));
    EXPECT_NE(mRes.get(), &m1);  // The returned matrix and m1 must be different objects
    EXPECT_NE(mRes.get(), &m2);  // The returned matrix and m2 must be different objects
    EXPECT_TRUE(isOperationValid(m1, m2, *mRes, ROWS, COLS, MOD, op));
}

/*********************** Constructors *************************/

/**
 * @test The value constructor generate a matrix with the correct number of rows and columns.
 * Furthermore it must not throw any exception
 */
TEST(MatrixTest, ValueConstructorValid) {
    const unsigned ROWS = 3, COLS = 4, MOD = 11;
    Matrix m1(ROWS, COLS, MOD);
    auto m1Data = getInnerData(m1, ROWS, COLS);

    // The matrix has a number of rows equal to ROWS
    EXPECT_EQ(m1Data.size(), ROWS);

    // All row have a size of COLS
    for (unsigned i = 0; i < ROWS; ++i) {
        EXPECT_EQ(m1Data.at(i).size(), COLS);
    }
}

/**
 * @test A 1xN matrix must be possible
 */
TEST(MatrixTest, ValueConstructorWith1Row) {
    const unsigned ROWS = 1, COLS = 4, MOD = 5;
    Matrix matrix(ROWS, COLS, MOD);
    auto m1Data = getInnerData(matrix, ROWS, COLS);

    EXPECT_EQ(m1Data.size(), ROWS);

    // The first row must have a size of COLS
    EXPECT_EQ(m1Data.at(0).size(), COLS);
}

/**
 * @test A Nx1 matrix must be possible
 */
TEST(MatrixTest, ValueConstructorWith1Column) {
    const unsigned ROWS = 4, COLS = 1, MOD = 5;
    Matrix matrix(ROWS, COLS, MOD);
    auto m1Data = getInnerData(matrix, ROWS, COLS);

    EXPECT_EQ(m1Data.size(), ROWS);

    // Each row must have a size of ROW
    for (unsigned i = 0; i < ROWS; ++i) {
        EXPECT_EQ(m1Data.at(i).size(), COLS);
    }
}

/**
 * @test The value constructor must throw an exception if 0 is given as modulo
 */
TEST(MatrixTest, ValueConstructorInvalidModulo) {
    EXPECT_THROW(Matrix matrix(3, 4, 0), std::invalid_argument);
}

/**
 * @test The value constructor must throw an exception if 0 is given as number of rows
 */
TEST(MatrixTest, ValueConstructorWith0Row) {
    EXPECT_THROW(Matrix matrix(0, 4, 1), std::runtime_error);
}

/**
 * @test The value constructor must throw an exception if 0 is given as number of columns
 */
TEST(MatrixTest, ValueConstructorWith0Column) {
    EXPECT_THROW(Matrix matrix(3, 0, 1), std::runtime_error);
}

/**
 * @test It must be possible to construct a 1x1 matrix
 */
TEST(MatrixTest, MinimalValidMatrix) {
    EXPECT_NO_THROW(Matrix matrix(1, 1, 2));
}

/**
 * @test It must be possible to construct a matrix with a modulo of 1
 */
TEST(MatrixTest, SmallestValidModulo) {
    EXPECT_NO_THROW(Matrix matrix(3, 4, 1));
}

/**
 * @test Using the copy constructor, the 2 matrices must have the same values
 */
TEST(MatrixTest, CopyConstructorValid) {
    const unsigned ROWS = 3, COLS = 4, MOD = 11;
    Matrix m1(ROWS, COLS, MOD);
    auto dataM1 = getInnerData(m1, ROWS, COLS);
    Matrix m2(m1);
    auto dataM2 = getInnerData(m2, ROWS, COLS);

    // All inner elements are equal
    for (unsigned i = 0; i < ROWS; ++i) {
        for (unsigned j = 0; j < COLS; ++j) {
            EXPECT_EQ(dataM1.at(i).at(j), dataM2.at(i).at(j));
        }
    }
}

/**
 * @test Using the move constructor, the 2 matrices must have the same values
 */
TEST(MatrixTest, MoveConstructorValid) {
    const unsigned ROWS = 3, COLS = 4, MOD = 11;
    Matrix m1(ROWS, COLS, MOD);
    auto dataM1 = getInnerData(m1, ROWS, COLS);
    Matrix m2(std::move(m1));
    auto dataM2 = getInnerData(m2, ROWS, COLS);

    // All inner elements are equal (before moving them)
    for (unsigned i = 0; i < ROWS; ++i) {
        for (unsigned j = 0; j < COLS; ++j) {
            EXPECT_EQ(dataM1.at(i).at(j), dataM2.at(i).at(j));
        }
    }
}

/**
 * @test Destructor must not throw any exception
 * @note We cannot test the memory deallocation, because it is not possible to access the memory after it has been released.
 */
TEST(MatrixTest, DestructorIsValid) {
    EXPECT_NO_THROW(delete new Matrix(3, 4, 11));
}

/*********************** Overloaded operators *************************/

/**
 * @test Addition with different modulo must throw an exception
 */
TEST(MatrixTest, AddWithDifferentModulo) {
    EXPECT_THROW(Matrix(4, 5, 8) + Matrix(4, 5, 9), std::invalid_argument);
}

/**
 * @test Addition with same modulo must be valid and return the right sum
 */
TEST(MatrixTest, AddIsValidWithSameModulo) {
    const unsigned ROWS = 2, COLS = 3, MOD = 4;
    static Add op;

    Matrix m1(ROWS, COLS, MOD), m2(ROWS, COLS, MOD);
    auto mRes = m1 + m2;
    EXPECT_TRUE(isOperationValid(m1, m2, mRes, ROWS, COLS, MOD, op));
}

/**
 * @test Chain operation must be possible and return the right sum
 */
TEST(MatrixTest, ChainAddIsValidWithSameModulo) {
    const unsigned ROWS = 2, COLS = 3, MOD = 4;
    Matrix m1(ROWS, COLS, MOD);
    auto m1Data = getInnerData(m1, ROWS, COLS);
    auto m2 = m1;
    auto m3 = m2;
    auto m4 = m3;

    // Must be able to chain sum itself
    auto result = m1 + m2 + m3 + m4;
    auto resultData = getInnerData(result, ROWS, COLS);

    for (unsigned i = 0; i < ROWS; ++i) {
        for (unsigned j = 0; j < COLS; ++j) {
            auto beforeAdd = m1Data.at(i).at(j);
            auto afterAdd = resultData.at(i).at(j);

            // All elements must have been multiplied by 4
            EXPECT_EQ(afterAdd, beforeAdd * 4 % MOD);
        }
    }
}

/**
 * @test A matrix must be able to add itself
 */
TEST(MatrixTest, AddItself) {
    const unsigned ROWS = 3, COLS = 4, MOD = 11;

    Matrix m1(ROWS, COLS, MOD);
    auto m1DataBeforeAdd = getInnerData(m1, ROWS, COLS);

    // Should be able to assign the new value after adding itself
    m1 = m1 + m1;

    auto m1DataAfterAdd = getInnerData(m1, ROWS, COLS);

    for (unsigned i = 0; i < ROWS; ++i) {
        for (unsigned j = 0; j < COLS; ++j) {
            // All elements must have doubled after adding themselves to themselves
            auto beforeAdd = m1DataBeforeAdd.at(i).at(j);
            auto afterAdd = m1DataAfterAdd.at(i).at(j);
            EXPECT_EQ(afterAdd, beforeAdd * 2 % MOD);
        }
    }
}

/**
 * @test Subtraction with different modulo must throw an exception
 */
TEST(MatrixTest, SubWithDifferentModulo) {
    EXPECT_THROW(Matrix(4, 5, 8) - Matrix(4, 5, 9), std::invalid_argument);
}

/**
 * @test Subtraction with same modulo must be valid and return the right difference
 */
TEST(MatrixTest, SubIsValidWithSameModulo) {
    const unsigned ROWS = 2, COLS = 3, MOD = 4;
    static Sub op;

    Matrix m1(ROWS, COLS, MOD), m2(ROWS, COLS, MOD);
    auto mRes = m1 - m2;
    EXPECT_TRUE(isOperationValid(m1, m2, mRes, ROWS, COLS, MOD, op));
}

/**
 * @test A matrix must be able to subtract itself and the difference is 0 for each element
 */
TEST(MatrixTest, SubtractItself) {
    const unsigned ROWS = 3, COLS = 4, MOD = 11;
    Matrix m1(ROWS, COLS, MOD);
    m1 = m1 - m1;
    auto m1Data = getInnerData(m1, ROWS, COLS);

    for (unsigned i = 0; i < ROWS; ++i) {
        for (unsigned j = 0; j < COLS; ++j) {
            // All elements must be 0
            EXPECT_EQ(m1Data.at(i).at(j), 0);
        }
    }
}

/**
 * @test Multiplication with different modulo must throw an exception
 */
TEST(MatrixTest, MultWithDifferentModulo) {
    EXPECT_THROW(Matrix(4, 5, 8) * Matrix(4, 5, 9), std::invalid_argument);
}

/**
 * @test Multiplication with same modulo must be valid and return the right product
 */
TEST(MatrixTest, MultIsValidWithSameModulo) {
    const unsigned ROWS = 2, COLS = 3, MOD = 4;
    static Multiply op;

    Matrix m1(ROWS, COLS, MOD), m2(ROWS, COLS, MOD);
    auto mRes = m1 * m2;
    EXPECT_TRUE(isOperationValid(m1, m2, mRes, ROWS, COLS, MOD, op));
}

/**
 * @test A matrix must be able to multiply itself and the product must be right
 */
TEST(MatrixTest, MultiplyItselfAndChain) {
    const unsigned ROWS = 3, COLS = 4, MOD = 11;

    Matrix m1(ROWS, COLS, MOD);
    auto m1DataBeforeMult = getInnerData(m1, ROWS, COLS);
    m1 = m1 * m1 * m1;
    auto m1DataAfterMult = getInnerData(m1, ROWS, COLS);

    for (unsigned i = 0; i < ROWS; ++i) {
        for (unsigned j = 0; j < COLS; ++j) {
            // All elements must be ^3
            auto beforeMult = m1DataBeforeMult.at(i).at(j);
            auto afterMult = m1DataAfterMult.at(i).at(j);
            EXPECT_EQ(afterMult, unsigned(pow(beforeMult, 3)) % MOD);
        }
    }
}

/**
 * @test Affectation must result in the same data but different object addresses
 */
TEST(MatrixTest, EqualOperatorValid) {
    const unsigned ROWS = 3, COLS = 4, MOD = 11;
    Matrix m1(ROWS, COLS, MOD);
    auto dataM1 = getInnerData(m1, ROWS, COLS);
    Matrix m2 = m1;
    auto dataM2 = getInnerData(m2, ROWS, COLS);

    // Both matrix must have different addresses
    EXPECT_NE(&m1, &m2);

    // Both matrix must have the same data
    for (unsigned i = 0; i < ROWS; ++i) {
        for (unsigned j = 0; j < COLS; ++j) {
            EXPECT_EQ(dataM1.at(i).at(j), dataM2.at(i).at(j));
        }
    }
}

/**
 * @test Move affectation must result in the same object data.
 */
TEST(MatrixTest, MoveEqualOperatorValid) {
    const unsigned ROWS = 3, COLS = 4, MOD = 11;
    Matrix m1(ROWS, COLS, MOD);
    auto dataM1 = getInnerData(m1, ROWS, COLS);
    Matrix m2 = std::move(m1);
    auto dataM2 = getInnerData(m2, ROWS, COLS);

    // Both matrix must have the same data (before the move)
    for (unsigned i = 0; i < ROWS; ++i) {
        for (unsigned j = 0; j < COLS; ++j) {
            EXPECT_EQ(dataM1.at(i).at(j), dataM2.at(i).at(j));
        }
    }
}

/**
 * @test ASelf assignment must be possible
 */
TEST(MatrixTest, SelfAssignment) {
    Matrix matrix(3, 4, 11);
    EXPECT_NO_THROW(matrix = matrix);
}

/**
 * @test ASelf assignment must result in the same object address
 */
TEST(MatrixTest, SelfAssignmentSameObject) {
    Matrix matrix(3, 4, 11);
    auto addr1 = &matrix;
    matrix = matrix;
    auto addr2 = &(matrix = matrix);
    EXPECT_EQ(addr1, addr2);
}

/*********************** In place operations *************************/

/**
 * @test In place addition must be valid
 */
TEST(MatrixTest, InPlaceAddIsValid) {
    static Add op;
    testInPlaceOperation(&Matrix::add, op);
}

/**
 * @test In place subtraction must be valid
 */
TEST(MatrixTest, InPlaceSubIsValid) {
    static Sub op;
    testInPlaceOperation(&Matrix::sub, op);
}

/**
 * @test In place multiplication must be valid
 */
TEST(MatrixTest, InPlaceMultIsValid) {
    static Multiply op;
    testInPlaceOperation(&Matrix::multiply, op);
}

/*********************** Dynamic operations *************************/

/**
 * @test Dynamic addition must be valid
 */
TEST(MatrixTest, DynamicAddIsValid) {
    static Add op;
    testDynamicOperation(&Matrix::addDynamic, op);
}

/**
 * @test Dynamic subtraction must be valid
 */
TEST(MatrixTest, DynamicSubIsValid) {
    static Sub op;
    testDynamicOperation(&Matrix::subDynamic, op);
}

/**
 * @test Dynamic multiplication must be valid
 */
TEST(MatrixTest, DynamicMultIsValid) {
    static Multiply op;
    testDynamicOperation(&Matrix::multiplyDynamic, op);
}