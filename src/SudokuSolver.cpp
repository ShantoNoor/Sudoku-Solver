#include "SudokuSolver.h"
#include "Window.h"
#include <unordered_map>
#include <iostream>
#include "Sound.h"

SudokuSolver::SudokuSolver()
{
    m_solved = false;
    srand(time(0)); // for random number generator
}

bool SudokuSolver::solve(Cell grid[9][9], int totalNumberOfEmptyCells, int checkCout)
{
    if(totalNumberOfEmptyCells == 0)
    {
        Sound::get()->playMusicFX("solved");
        m_solved = true;
        Window::get()->setIsSolving(false);
        Window::get()->update();
        return true;
    }

    for(int row = 0; row < 9; row++)
    {
        for(int coloum = 0; coloum < 9; coloum++)
        {
            if(grid[row][coloum].getNumberId() == 0)
            {
                for(int number = 1; number <= 9; number++)
                {
                    if(isPlaceAble(grid, row, coloum, number))
                    {
                        grid[row][coloum].setNumberId(number);
                        grid[row][coloum].done();
                        Window::get()->update();
                        if(solve(grid, totalNumberOfEmptyCells-1, checkCout+1)) return true;
                        grid[row][coloum].setNumberId(0);
                        grid[row][coloum].backed();
                        Window::get()->update();
                    }
                }
                if(checkCout == 0)
                {
                    Sound::get()->playMusicFX("error");
                    Window::get()->setUnable(true);
                    Window::get()->setIsSolving(false);
                    Window::get()->update();
                }
                return false;
            }
        }
    }

    return true;
}

void SudokuSolver::setExample(Cell grid[9][9])
{
    clearBoard(grid);
    m_solved = false;
    int r = rand()%BOARD_COUNT;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            grid[i][j].setNumberId(m_example[r][i][j]);
        }
    }
}

bool SudokuSolver::isPlaceAble(Cell grid[9][9], int row, int coloum, int number)
{
    for(int i = 0; i < 9; i++)
    {
        if(grid[row][i].getNumberId() == number) return false;
    }
    for(int i = 0; i < 9; i++)
    {
        if(grid[i][coloum].getNumberId() == number) return false;
    }
    row = (row/3)*3;
    coloum = (coloum/3)*3;
    for(int i = row; i < row+3; i++)
    {
        for(int j = coloum; j < coloum+3; j++)
        {
            if(grid[i][j].getNumberId() == number) return false;
        }
    }
    return true;
}
int SudokuSolver::countNumberOfEmptyCells(Cell grid[9][9])
{
    int counter = 0;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(grid[i][j].getNumberId() == 0) counter++;
        }
    }
    return counter;
}
void SudokuSolver::clearBoard(Cell grid[9][9])
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            grid[i][j].setNumberId(0);
            grid[i][j].notDone();
        }
    }
}
bool SudokuSolver::checkValidity(Cell grid[9][9])
{
    std::unordered_map<int, int> umap;
    //checking all rows
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            umap[grid[i][j].getNumberId()]++;
        }
        for(auto x : umap)
        {
            if(x.first != 0 && x.second != 1) return false;
        }
        umap.clear();
    }
    //checking all column
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            umap[grid[j][i].getNumberId()]++;
        }
        for(auto x : umap)
        {
            if(x.first != 0 && x.second != 1) return false;
        }
        umap.clear();
    }
    //checking all grids
    for(int k = 0; k < 3; k++)
    {
        for(int m = 0; m < 3; m++)
        {
            for(int i = k*3; i < k*3+3; i++)
            {
                for(int j = m*3; j < m*3+3; j++) umap[grid[i][j].getNumberId()]++;
            }
            for(auto x : umap)
            {
                if(x.first != 0 && x.second != 1) return false;
            }
            umap.clear();
        }
    }
    return true;
}
