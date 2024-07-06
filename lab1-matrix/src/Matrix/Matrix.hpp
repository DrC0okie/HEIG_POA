#pragma once

#include "ostream"
#include "../Operators/Operator.h"

/**
 * @class Matrix
 * @brief Represents a mathematical matrix with elements stored modulo n.
 * @authors Slimani Walid, Van Hove Timothée
 * The Matrix class supports addition, subtraction, and multiplication operations performed modulo n.
 */
class Matrix {
private:
    // region Fields
    unsigned **data;
    unsigned rows, columns, modulo;
    const unsigned EMPTY_CASE = 0;
    // endregion

    // region Private methods

    /**
    * @brief Applies a specified operation to the current matrix with another matrix.
    * @param other The other matrix to operate with.
    * @param op The operation to apply.
    */
    void applyOperator(const Matrix &other, const Operator &op);

    /**
     * @brief Frees the memory allocated for a 2D array and resets its dimensions.
     * @note The pointer to the 2D array is set to nullptr and the dimensions are reset to 0.
     * @param dataToFree A reference to the pointer to the 2D array that needs to be freed.
     * @param dataRows A reference to the variable holding the number of rows in the 2D array.
     * @param dataCols A reference to the variable holding the number of columns in the 2D array.
     */
    static void freeMemory(unsigned** &dataToFree, unsigned& dataRows, unsigned& dataCols) ;

    /**
    * @brief Checks the bounds of the matrix and retrieves the value at the specified indices.
    * @param rowIndex The row index.
    * @param columnIndex The column index.
    * @return The value at the specified indices or EMPTY_CASE if out of bounds.
    */
    [[nodiscard]] unsigned checkBounds(unsigned rowIndex, unsigned columnIndex) const;

    /**
     * @brief Copies the data from another matrix to the current matrix.
     * @param other The matrix to copy from.
     * @return A pointer to the new data array.
     */
    [[nodiscard]] unsigned** copyData(const Matrix &other);

    // endregion

public:
    // region Ctors and Destructor
    Matrix() = delete;

    /**
    * @brief Constructs a Matrix filled with random numbers in the range [0, modulo).
    * @param rows Number of rows in the matrix.
    * @param columns Number of columns in the matrix.
    * @param modulo The modulo value for matrix operations.
    */
    Matrix(unsigned rows, unsigned columns, unsigned modulo);

    /**
    * @brief Copy constructor.
    * @param other The Matrix object to copy from.
    */
    Matrix(const Matrix &other);

    /**
    * @brief Move constructor.
    * @param other The Matrix object to move from, leaving it in an unusable state.
    */
    Matrix(Matrix &&other) noexcept; // Copy ctor by moving

    /** @brief Destructor that frees allocated memory. */
    ~Matrix();
    // endregion

    // region Public methods

    /**
     * @brief Adds another matrix to this matrix in-place.
     * @param other The matrix to be added to this matrix.
     * @return A reference to this matrix after the addition.
     */
    Matrix &add(const Matrix &other);

    /**
     * @brief Creates a new matrix that is the result of adding another matrix to this matrix.
     * Does not modify the current matrix. Instead, returns a new Matrix instance that is the result of the addition.
     * @param other The matrix to be added to this matrix.
     * @return A new Matrix instance that is the result of the addition.
     */
    [[nodiscard]] Matrix addStatic(const Matrix &other) const;

    /**
     * @brief Dynamically allocates a new matrix that is the result of adding another matrix to this matrix.
     * Does not modify the current matrix, but allocates a new Matrix instance on the heap and returns a pointer to it.
     * @note It's the caller's responsibility to manage the memory of the returned Matrix pointer.
     * @param other The matrix to be added to this matrix.
     * @return A pointer to a new Matrix instance that is the result of the addition.
     */
    [[nodiscard]] Matrix *addDynamic(const Matrix &other) const;

    /**
     * @brief Subtracts another matrix to this matrix in-place.
     * @param other The matrix to be subtracted to this matrix.
     * @return A reference to this matrix after the subtraction.
     */
    Matrix &sub(const Matrix &other);

    /**
     * @brief Creates a new matrix that is the result of subtracting another matrix to this matrix.
     * Does not modify the current matrix. Instead, returns a new Matrix instance that is the result of the subtraction.
     * @param other The matrix to be subtracted to this matrix.
     * @return A new Matrix instance that is the result of the subtraction.
     */
    [[nodiscard]] Matrix subStatic(const Matrix &other) const;

    /**
     * @brief Dynamically allocates a new matrix that is the result of subtracting another matrix to this matrix.
     * Does not modify the current matrix, but allocates a new Matrix instance on the heap and returns a pointer to it.
     * @note It's the caller's responsibility to manage the memory of the returned Matrix pointer.
     * @param other The matrix to be subtracted to this matrix.
     * @return A pointer to a new Matrix instance that is the result of the subtraction.
     */
    [[nodiscard]] Matrix *subDynamic(const Matrix &other) const;

    /**
     * @brief Multiplies another matrix to this matrix in-place.
     * @param other The matrix to be multiplied to this matrix.
     * @return A reference to this matrix after the multiplication.
     */
    Matrix &multiply(const Matrix &other);

    /**
     * @brief Creates a new matrix that is the result of multiplying another matrix to this matrix.
     * Does not modify the current matrix. Instead, returns a new Matrix instance that is the result of the multiplication.
     * @param other The matrix to be multiplied to this matrix.
     * @return A new Matrix instance that is the result of the multiplication.
     */
    [[nodiscard]] Matrix multiplyStatic(const Matrix &other) const;

    /**
     * @brief Dynamically allocates a new matrix that is the result of multiplying another matrix to this matrix.
     * Does not modify the current matrix, but allocates a new Matrix instance on the heap and returns a pointer to it.
     * @note It's the caller's responsibility to manage the memory of the returned Matrix pointer.
     * @param other The matrix to be multiplied to this matrix.
     * @return A pointer to a new Matrix instance that is the result of the multiplication.
     */
    [[nodiscard]] Matrix *multiplyDynamic(const Matrix &other) const;

    // endregion

    // region Operators

    /**
     * @brief Copy assignment operator.
     * @note The copy-and-swap idiom is used to provide the strong exception guarantee.
     * @param other The Matrix object to copy from.
     * @return A reference to the current object.
    */
    Matrix &operator=(const Matrix &other);

    /**
    * @brief Move assignment operator.
    * @param other The Matrix object to move from.
    * @return A reference to the current object.
    */
    Matrix &operator=(Matrix &&other) noexcept;

    /**
    * @brief Stream insertion operator for Matrix class.
    * @param os The output stream to insert into.
    * @param matrix The Matrix object to insert into the stream.
    * @return A reference to the modified output stream.
    */
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
    // endregion
};

/**
 * @brief Adds two matrices.
 * @param lhs The left-hand side matrix.
 * @param rhs The right-hand side matrix.
 * @return A new matrix that is the result of adding the two matrices.
 */
Matrix operator+(const Matrix &lhs, const Matrix &rhs);

/**
 * @brief Subtracts two matrices.
 * @param lhs The left-hand side matrix.
 * @param rhs The right-hand side matrix.
 * @return A new matrix that is the result of subtracting the two matrices.
 */
Matrix operator-(const Matrix &lhs, const Matrix &rhs);

/**
 * @brief Multiplies two matrices.
 * @param lhs The left-hand side matrix.
 * @param rhs The right-hand side matrix.
 * @return A new matrix that is the result of multiplying the two matrices.
 */
Matrix operator*(const Matrix &lhs, const Matrix &rhs);
