#include <iostream>
#include <cmath>

int** allocateMatrix(int dim) {
	if (dim <= 0) {
		throw std::invalid_argument("Matrix size <= 0");
	}

	int** matrix = new int* [dim] {};

	try {
		for (int i = 0; i < dim; i++) {
			matrix[i] = new int[dim] {};
		}
	}
	catch (...) {
		// Если что-то упало - освобождаем всё, что успели выделить
		for (int i = 0; i < dim; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		throw; // пробрасываем исключения дальше
	}

	return matrix;

}
void freeMatrix(int** matrix, int dim) {

	for (int i = 0; i < dim; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

void fillMatrix(int** matrix, int dim) {
	if (matrix == nullptr) {
		throw std::invalid_argument("Matrix is nullptr");
	}

	if (dim <= 0) {
		throw std::invalid_argument("Matrix size <= 0");
	}
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			std::cin >> matrix[i][j];

			if (std::cin.fail()) 
				throw std::invalid_argument("Incorrect input");
			}
		}
	}

void printMatrix(int** matrix, int dim) {

	std::cout << "\n";

	if (matrix == nullptr) {
		throw std::invalid_argument("Matrix is nullptr");
	}

	if (dim <= 0) {
		throw std::invalid_argument("Matrix size <= 0");
	}

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

int diagonalMatrix(int** matrix, int dim) {
	if (matrix == nullptr) {
		throw std::invalid_argument("Matrix is nullptr");
	}

	if (dim <= 0) {
		throw std::invalid_argument("Matrix size <= 0");
	}

	if (dim % 2 == 0) {
		throw std::invalid_argument("Invalid matrix size");
	}

	int mainDiag = 0;
	int pobochDiag = 0;
	

	for (int i = 0; i < dim; i++) {
		mainDiag += abs(matrix[i][i]);
		pobochDiag += abs(matrix[dim - i - 1][i]);
	}
	return mainDiag + pobochDiag - abs(matrix[(dim - 1) / 2][(dim - 1) / 2]);
}

bool isOderedArray(int* arr, int dim) {
	
	if (arr == nullptr) {
		throw std::invalid_argument("Matrix is nullptr");
	}

	if (dim <= 0) {
		throw std::invalid_argument("Matrix size <= 0");
	}

	for (int i = 0; i < dim - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			return false;
		}
	}
	return true;
}

int getNumberOfOrderedRows(int** matrix, int rows, int cols) {
	if (matrix == nullptr) {
		throw std::invalid_argument("Matrix is nullptr");
	}

	if (rows <= 0 || cols <= 0) {
		throw std::invalid_argument("Matrix size <= 0");
	}
	int counterRows = 0;
	for (int i = 0; i < rows; i++) {
		if (isOderedArray(matrix[i], cols)) {
			counterRows++;
		}
	}
	return counterRows;
}

void additionOfRectangularMatrices(int** matrixOne, int rows int colsmatrixOne, int  int** matrixTwo) {
	int** matrixOutcome = nullptr;
	try {
		matrixOutcome = allocateMatrix
	}
 }



int main()
{
	int dim = 0;
	int** original = nullptr;
	std::cout << "Enter matrix dim";
	std::cin >> dim;
	if (std::cin.fail()) {
		std::cerr << "ERROR: Wrong input!!!";
		return 1;
	}

	try {
		original = allocateMatrix(dim);
		fillMatrix(original, dim);
		printMatrix(original, dim);
		std::cout << getNumberOfOrderedRows(original, dim, dim);
	}

	catch (const std::invalid_argument& e) {
		std::cerr << "INVALID ARGUMENT ERROR: " << e.what() << "\n";
		return 2;
	}
	catch (const std::exception& e) {
		std::cerr << "STD EXCEPTION: " << e.what() << "\n";
		freeMatrix(original, dim);
		return 3;
	}
	freeMatrix(original, dim);
	return 0;
}
