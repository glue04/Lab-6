#include <iostream>
#include <fstream>

using namespace std;

void readMatrixFromFile(const char* filename, int** matrixA, int** matrixB, int rows, int cols) {
/*was having a problem where the code would read the first 3 lines of the input file twice, so while not very elegant, it fixed the problem :)*/
    ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!(file >> matrixA[i][j])) {
                    cerr << "Error reading matrix element at (" << i << ", " << j << ")." << endl;
                    exit(1);
                }
            }
        }
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!(file >> matrixB[i][j])) {
                    cerr << "Error reading matrix element at (" << i << ", " << j << ")." << endl;
                    exit(1);
                }
            }
        }
        file.close();
    } else {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }
}

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void addMatrices(int** A, int** B, int** result, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrices(int** A, int** B, int** result, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

void multiplyMatrices(int** A, int** B, int** result, int rowsA, int colsA, int colsB) {
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < colsA; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


int main() {
    const char* filename = "input.txt";
    int rows;
    int cols;
    cout << "Rows in each matrix: ";
    scanf("%d", &rows);
    cout << "Collumns in each matrix: ";
    scanf("%d", &cols);

    int** matrixA = new int*[rows];
    int** matrixB = new int*[rows];
    int** sum = new int*[rows];
    int** difference = new int*[rows];
    int** product = new int*[rows];

    for (int i = 0; i < rows; ++i) {
        matrixA[i] = new int[cols];
        matrixB[i] = new int[cols];
        sum[i] = new int[cols];
        difference[i] = new int[cols];
        product[i] = new int[cols];
    }

    readMatrixFromFile(filename, matrixA, matrixB, rows, cols);

    cout << "Matrix A:" << endl;
    printMatrix(matrixA, rows, cols);
    cout << endl;

    cout << "Matrix B:" << endl;
    printMatrix(matrixB, rows, cols);
    cout << endl;

    cout << "Sum of A and B:" << endl;
    addMatrices(matrixA, matrixB, sum, rows, cols);
    printMatrix(sum, rows, cols);
    cout << endl;

    cout << "Difference of A and B:" << endl;
    subtractMatrices(matrixA, matrixB, difference, rows, cols);
    printMatrix(difference, rows, cols);
    cout << endl;

    if(rows == cols){
    	cout << "Product of A and B:" << endl;
    	multiplyMatrices(matrixA, matrixB, product, rows, cols, cols);
    	printMatrix(product, rows, cols);
    	cout << endl;
    }
    else{
	cout << "Multiplication impossible, rows and collumns not equivalent.";
	/*I really hope this is true, because I was getting errors when multiplying together matrices that were not squares*/
	cout << endl;
    }
    return 0;
}
