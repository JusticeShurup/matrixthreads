#include <iostream>
#include <vector>
#include <thread>

void printMatrix(std::vector<std::vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void generateMatrix(std::vector<std::vector<int>> &matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        std::vector<int> matr;
        for (int j = 0; j < cols; j++) {
            matr.push_back(rand() % 10);
        }
        matrix.push_back(matr);
    }
}
void generateZeroMatrix(std::vector<std::vector<int>> &matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        std::vector<int> matr;
        for (int j = 0; j < cols; j++) {
            matr.push_back(0);
        }
        matrix.push_back(matr);
    }
}
void multiplyMatrix(std::vector<std::vector<int>> firstMatrix, std::vector<std::vector<int>> secondMatrix,
                    std::vector<std::vector<int>> &resultMatrix) {
    generateZeroMatrix(resultMatrix, firstMatrix.size(), secondMatrix[0].size());
    for (int i = 0; i < resultMatrix.size(); i++) {
        for (int j = 0; j < resultMatrix[0].size(); j++) {
            for (int r = 0; r < secondMatrix.size(); r++) {
                resultMatrix[i][j] += firstMatrix[i][r] * secondMatrix[r][j];
            }
        }
    }
}

int main()
{
    int rows1;
    int cols1;
    int rows2;
    int cols2;
    while (true) {
        std::cout << "Enter row and col for matrix1: ";
        std::cin >> rows1 >> cols1;
        std::cout << "Enter row and col for matrix2: ";
        std::cin >> rows2 >> cols2;
        if (rows2 != cols1)
            std::cout << "Incorrect values, try again" << std::endl;
        else
            break;
    }
    std::vector<std::vector<int>> matrix1;
    std::vector<std::vector<int>> matrix2;
    std::vector<std::vector<int>> result_matrix;
    generateMatrix(matrix1, rows1, cols1);
    generateMatrix(matrix2, rows2, cols2);
    printMatrix(matrix1);
    printMatrix(matrix2);
    multiplyMatrix(matrix1, matrix2, result_matrix);
    printMatrix(result_matrix);


    std::vector<std::thread> threads;
    threads.push_back(std::thread(&generateMatrix, matrix1, rows1, cols1));
    threads.push_back(std::thread(&generateMatrix, matrix2, rows2, cols2));
    threads.push_back(std::thread(&printMatrix, matrix1));
    threads.push_back(std::thread(&printMatrix, matrix2));
    threads.push_back(std::thread(&multiplyMatrix, matrix1, matrix2, result_matrix));
    threads.push_back(std::thread(&printMatrix, result_matrix));

    for (int i = 0; i < threads.size(); i++)
        threads[0].join();


}