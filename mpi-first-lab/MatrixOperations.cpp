#include "MatrixOperations.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int CalculateRow(vector<int>& row, vector<int>& column) {
	int result = 0;
	for (std::vector<int>::size_type i = 0; i != column.size(); i++) {
		result += row[i] * column[i];
	}
	return result;
}


vector<int> ConvertToIntArray(string line) {
	int length = strlen(line.c_str());
	vector<int> row;

	for (unsigned int i = 0; i < length; i++) {
		row.push_back(line.c_str()[i] - '0');
	}

	return row;
}

vector<vector<int> > ReadMatrix(fstream& file) {

	int lineLimit = 1, lineCounter = 0;
	vector<vector<int> > matrix;

	string line;

	while (lineCounter < lineLimit) {
		getline(file, line);
		if (matrix.size() == 0) {
			lineLimit = ConvertToIntArray(line).size();
		}
		vector<int> row = ConvertToIntArray(line);
		matrix.push_back(ConvertToIntArray(line));
		lineCounter++;
	}

	return matrix;
}



vector<int> GetColumn(vector<vector<int> > matrix, int n_column) {

	vector<int> result;

	for (size_t i = 0; i != matrix.size(); i++) {

		result.push_back(matrix[i][n_column]);
	}
	return result;
}

vector<vector<int> > ResultMatrix(vector<vector<int> > first_matrix, vector<vector<int> > second_matrix) {
	vector<vector<int> > result;
	vector<int> row_result;


	for (size_t i = 0; i != first_matrix.size(); i++) {
		for (size_t j = 0; j != second_matrix[0].size(); j++) {
			vector<int> column = GetColumn(second_matrix, j);
			int result_row = CalculateRow(first_matrix[i], column);

		}
		result.push_back(row_result);
		row_result.clear();
	}
	return result;
}
vector<vector<int> > ReadMatrixSpec(fstream& file) {
	int lineLimit = 1, lineCounter = 0;
	vector<vector<int> > matrix;

	string line;

	while (lineCounter < lineLimit) {
		getline(file, line);
		if (matrix.size() == 0) {
			if (ConvertToIntArray(line).size() == 5) {
				lineLimit = 8;
			} else {
				lineLimit = 5;
			}
			
		}
		vector<int> row = ConvertToIntArray(line);
		matrix.push_back(ConvertToIntArray(line));
		lineCounter++;
	}

	return matrix;
}