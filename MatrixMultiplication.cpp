#include "MatrixMultiplication.h"
#include<omp.h>

vector<vector<int>>MatrixMultiplication(vector<vector<int>>matrixA, vector<vector<int>>matrixB,string type) {
	vector<vector<int>>result(matrixA.size(),vector<int>(matrixB[0].size(),0));
	if (type == "sequential") {
		for (int i = 0; i < matrixA.size();i++) { //rows of A
			for (int j = 0; j < matrixB[0].size(); j++) {//columns of B
				for (int k = 0; k < matrixA[0].size(); k++){//columns of A or rows of B
					result[i][j] += matrixA[i][k] * matrixB[k][j]; //iterate over rows of a and columns of b and sum the multiplication 
				}
			}
		}
	}
	else {
		# pragma omp parallel for 
		for (int i = 0; i < matrixA.size(); i++) { //rows of A
			for (int j = 0; j < matrixB[0].size(); j++) {//columns of B
				for (int k = 0; k < matrixA[0].size(); k++) {//columns of A or rows of B
					result[i][j] += matrixA[i][k] * matrixB[k][j]; //iterate over rows of a and columns of b and sum the multiplication 
				}
			}
		}
	}

	return result;

}

void PrintMatrix(vector<vector<int>> matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		cout << "\t\t";
		for (int j = 0; j < matrix[i].size(); j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}