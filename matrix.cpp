#include <iostream>
#include <vector>
#include <thread>
#include <ctime>

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
    for (int i = 0; i < firstMatrix.size(); i++) {
        for (int j = 0; j < secondMatrix[0].size(); j++) {
            for (int r = 0; r < secondMatrix.size(); r++) {
                resultMatrix[i][j] += firstMatrix[i][r] * secondMatrix[r][j];
            }
        }
    }
}

void MultiplyMatrixMT(std::vector<std::vector<int>> firstMatrix, std::vector<std::vector<int>> secondMatrix,
                      std::vector<std::vector<int>>& resultMatrix, int start_pos, int end_pos) {
    int num_cols = resultMatrix[0].size();
    for (int i = start_pos; i <= end_pos; i++) {
        int row = i / num_cols;
        int col = i % num_cols;
        resultMatrix[row][col] = 0;
        for (int j = 0; j < secondMatrix.size(); j++)
            resultMatrix[row][col] += firstMatrix[row][j] * secondMatrix[j][col];
    }
}

void MTThread(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2,
              std::vector<std::vector<int>>& resultMatrix, int rows1, int cols2) {
    int matrix_size = rows1 * cols2;
    int threads_quantity;
    std::cout << "Enter quantity of threads: " << std::endl;
    std::cin >> threads_quantity;
    std::vector<std::thread> threads;
    int start = clock();
    for (int i = 0; i <= matrix_size - threads_quantity; i+= matrix_size / threads_quantity) 
        threads.push_back(std::thread(&MultiplyMatrixMT, matrix1, matrix2, std::ref(resultMatrix), i, i + matrix_size / threads_quantity));
    for (int i = 0; i < threads.size(); i++)
        threads[i].join();
    printMatrix(resultMatrix);
    int end = clock();
    std::cout << end - start << std::endl;

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
    generateZeroMatrix(result_matrix, rows1, cols2);
    int start = clock();
    multiplyMatrix(matrix1, matrix2, result_matrix);
    printMatrix(result_matrix);
    int end = clock();
    std::cout << end - start << std::endl;

    MTThread(matrix1, matrix2, std::ref(result_matrix), rows1, rows2);


}