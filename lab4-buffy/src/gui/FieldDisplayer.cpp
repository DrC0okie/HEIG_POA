#include <iostream>
#include "src/gui/FieldDisplayer.hpp"

char getBorderChar(unsigned row, unsigned column, unsigned width, unsigned height) {
    if ((!row && (!column || column == width - 1)) || (row == height - 1 && (column == 0 || column == width - 1)))
        return CORNER;
    else if (!row || row == height - 1)
        return HORIZONTAL;
    else if (column == 0 || column == width - 1)
        return VERTICAL;
    else
        return '\0'; // Not a border
}

void FieldDisplayer::display(const Field& field) {
    const std::vector<Humanoid*>& humanoids = field.getHumanoid2DVector();

    const unsigned width = field.getWidth() + 2;
    const unsigned height = field.getHeight() + 2;

    for (unsigned row = 0; row < height; ++row) {
        for (unsigned column = 0; column < width; ++column) {
            char borderChar = getBorderChar(row, column, width, height);
            if (borderChar != '\0') {
                std::cout << borderChar;
            } else {
                const unsigned x = column - 1;
                const unsigned y = row - 1;
                if (x < field.getWidth() && y < field.getHeight()) {  // Ensure we are within the field bounds
                    Humanoid* humanoid = humanoids[x + y * field.getWidth()];
                    if (humanoid != nullptr)
                        std::cout << *humanoid;
                    else
                        std::cout << EMPTY;
                } else {
                    std::cout << EMPTY;  // Print empty for out-of-bounds areas
                }
            }
        }
        std::cout << std::endl;
    }
}
