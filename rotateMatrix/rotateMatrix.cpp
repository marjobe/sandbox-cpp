#include <iostream>

/** @brief Matrix definition. */
template <class T, size_t ROW, size_t COL>
using Matrix = T[ROW][COL];

/**
 * @brief Prints a matrix
 * @param[in] matrix The matrix to print.
 */
template <class T, size_t ROW, size_t COL>
void print(const Matrix<T, ROW, COL>& matrix)
{
    for (unsigned int i = 0u; i < ROW; ++i)
    {
        for (unsigned int j = 0u; j < COL; ++j)
        {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

/** Square matrix definition. */
template <class T, size_t N>
using SquareMatrix = Matrix<T, N, N>;

/**
 * @brief Rotates 90 degress CCW the four values starting with a given position.
 * @param[in,out] matrix The matrix to make changes.
 * @param[in] i Row position of the starting position.
 * @param[in] j Column position of the starting position.
 */
template <class T, size_t N>
void doFourChanges(SquareMatrix<T, N>& matrix, unsigned int origI, unsigned int origJ)
{
    T temp(matrix[origI][origJ]);

    unsigned int i(origI);
    unsigned int j(origJ);
    for (unsigned int op = 0u; op < 3u; ++op)
    {
        unsigned int a(j);
        unsigned int b(N - 1 - i);

        matrix[i][j] = matrix[a][b];
        i = a;
        j = b;
    }
    matrix[i][j] = temp;
}

/**
 * @brief Rotates a matrix 90 degrees CCW.
 * @param matrix The matrix to rotate.
 */
template <class T, size_t N>
void rotate90CCW(SquareMatrix<T, N>& matrix)
{
    unsigned int d(0u);
    for (unsigned int i = 0u; i < N/2u; ++i)
    {
        for (unsigned int j = d; j < N - 1u - d; ++j)
        {
            doFourChanges(matrix, i, j);
        }
        d++;
    }
}

int main()
{
    //SquareMatrix<int, 2> sqMatrix = {1, 2, 3, 4};
    //SquareMatrix<int, 3> sqMatrix = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    //SquareMatrix<int, 4> sqMatrix = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    SquareMatrix<int, 5> sqMatrix = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
    print(sqMatrix);

    std::cout << std::endl;

    rotate90CCW(sqMatrix);
    print(sqMatrix);

    return 0;
}
