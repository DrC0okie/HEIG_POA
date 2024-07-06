#include "Matrix.hpp"
#include <cstring>
#include <utility>
#include "../Utils/Utils.h"
#include "../Operators/Add/Add.h"
#include "../Operators/Sub/Sub.h"
#include "../Operators/Multiply/Multiply.h"

// region Constructors and Destructor

Matrix::Matrix(unsigned rows, unsigned columns, unsigned modulo) : rows(rows), columns(columns),
                                                                   modulo(modulo) {
    if (modulo < 1) {
        throw std::invalid_argument("modulo cannot be zero or less");
    }

    if (rows < 1) {
        throw std::runtime_error("rows cannot be less than 1");
    }

    if (columns < 1) {
        throw std::runtime_error("columns cannot be less than 1");
    }

    try {
        data = new unsigned *[rows];
        for (unsigned i = 0; i < rows; ++i) {
            data[i] = new unsigned[columns];
            for (unsigned j = 0; j < columns; ++j) {
                data[i][j] = Utils::getRandom(modulo);
            }
        }
    } catch (...) {
        freeMemory(data, this->rows, this->columns);
        throw;
    }
}

Matrix::Matrix(const Matrix &other) : rows(other.rows), columns(other.columns),
                                      modulo(other.modulo) {

    data = copyData(other);
}

Matrix::Matrix(Matrix &&other) noexcept:
        data{std::exchange(other.data, nullptr)},
        rows{std::exchange(other.rows, 0)},
        columns{std::exchange(other.columns, 0)},
        modulo{std::exchange(other.modulo, 0)} {}

Matrix::~Matrix() {
    freeMemory(data, rows, columns);
}

unsigned **Matrix::copyData(const Matrix &other) {
    unsigned** result;
    try{
        result = new unsigned *[rows];
        for (unsigned i = 0; i < rows; ++i) {
            result[i] = new unsigned[columns];
            std::memcpy(result[i], other.data[i], columns * sizeof(unsigned));
        }
    } catch (...) {
        freeMemory(result, rows, columns);
        throw;
    }

    return result;
}
// endregion

// region Public Methods
// region Add
Matrix &Matrix::add(const Matrix &other) {
    static Add op;
    applyOperator(other, op);
    return *this;
}

Matrix Matrix::addStatic(const Matrix &other) const {
    Matrix result(*this);
    result.add(other);
    return result;
}

Matrix *Matrix::addDynamic(const Matrix &other) const {
    auto *result = new Matrix(*this);
    result->add(other);
    return result;
}
// endregion

// region Sub
Matrix &Matrix::sub(const Matrix &other) {
    static Sub op;
    applyOperator(other, op);
    return *this;
}

Matrix Matrix::subStatic(const Matrix &other) const {
    Matrix result(*this);
    result.sub(other);
    return result;
}

Matrix *Matrix::subDynamic(const Matrix &other) const {
    auto *result = new Matrix(*this);
    result->sub(other);
    return result;
}
// endregion

// region Multiply
Matrix &Matrix::multiply(const Matrix &other) {
    static Multiply op;
    applyOperator(other, op);
    return *this;
}

Matrix Matrix::multiplyStatic(const Matrix &other) const {
    Matrix result(*this);
    result.multiply(other);
    return result;
}

Matrix *Matrix::multiplyDynamic(const Matrix &other) const {
    auto *result = new Matrix(*this);
    result->multiply(other);
    return result;
}
// endregion
// endregion

// region Operators

Matrix &Matrix::operator=(const Matrix &other) {
    // Check auto-affectation
    if (this != &other) {
        freeMemory(data, rows, columns);

        // Get the resources from the other object
        rows = other.rows;
        columns = other.columns;
        modulo = other.modulo;

        // Allocate new resources and copy the data if not null
        if (other.data != nullptr) {
            data = copyData(other);
        }
    }
    return *this;
}

Matrix &Matrix::operator=(Matrix &&other) noexcept {
    // Check auto-affectation
    if (this != &other) {
        freeMemory(data, rows, columns);

        // Get the resources from the other object
        data = std::exchange(other.data, nullptr);
        rows = std::exchange(other.rows, 0);
        columns = std::exchange(other.columns, 0);
        modulo = std::exchange(other.modulo, 0);
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    for (unsigned i = 0; i < matrix.rows; ++i) {
        for (unsigned j = 0; j < matrix.columns; ++j) {
            os << matrix.data[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}
// endregion

// region Private Methods

void Matrix::freeMemory(unsigned** &dataToFree, unsigned& dataRows, unsigned& dataCols) {
    for (unsigned i = 0; i < dataRows; ++i) {
        delete[] dataToFree[i];
    }
    delete[] dataToFree;
    dataToFree = nullptr;
    dataRows = 0;
    dataCols = 0;
}

void Matrix::applyOperator(const Matrix &other, const Operator &op) {
    if (other.modulo != modulo) {
        throw std::invalid_argument(
                "The modulo of the 2 matrices must be identical");
    }

    if (other.data == nullptr) {
        throw std::runtime_error("Inner data of the matrix is null!");
    }

    if(data == nullptr){
        throw std::runtime_error("Inner data of the matrix is null!");
    }

    unsigned maxRows = std::max(rows, other.rows);
    unsigned maxColumns = std::max(columns, other.columns);
    unsigned **result;

    try {
        result = new unsigned *[maxRows];
        for (unsigned i = 0; i < maxRows; ++i) {
            result[i] = new unsigned[maxColumns];
            for (unsigned j = 0; j < maxColumns; ++j) {
                unsigned valM1 = checkBounds(i, j);
                unsigned valM2 = other.checkBounds(i, j);

                // Adjust valM1 to prevent underflow for sub.
                // This has no effect on addition/multiplication
                valM1 += modulo;
                result[i][j] = op.apply(valM1 + modulo, valM2) % modulo;
            }
            if (i < rows) {
                // Delete the old row after its contents have been used
                delete[] data[i];
            }
        }

        // Delete the top-level array of the old data
        delete[] data;

    } catch (...) {
        freeMemory(result, maxRows, maxColumns);
        throw;
    }

    // Update the matrix to use the new data
    data = result;
    rows = maxRows;
    columns = maxColumns;
}

unsigned Matrix::checkBounds(unsigned rowIndex, unsigned columnIndex) const {
    // Check if the given indices are within the bounds of the matrix
    if (rowIndex < rows && columnIndex < columns) {
        return data[rowIndex][columnIndex];
    }
    // Return predefined value if the indices are out of bounds
    return EMPTY_CASE;
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
    return lhs.addStatic(rhs);
}

Matrix operator-(const Matrix &lhs, const Matrix &rhs) {
    return lhs.subStatic(rhs);
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
    return lhs.multiplyStatic(rhs);
}
// endregion