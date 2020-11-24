#ifndef __SudokuSolver__
#define __SudokuSolver__

#include "Cell.h"

class SudokuSolver
{
private:
    int m_example[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    bool m_solved;
public:
    SudokuSolver() { m_solved = false; };
    bool solve(Cell grid[9][9], int totalNumberOfEmptyCells, int checkCout);
    void setExample(Cell grid[9][9]);
    void clearBoard(Cell grid[9][9]);
    bool isPlaceAble(Cell grid[9][9], int row, int coloum, int number);
    int countNumberOfEmptyCells(Cell grid[9][9]);
    bool checkValidity(Cell grid[9][9]);
};

#endif
