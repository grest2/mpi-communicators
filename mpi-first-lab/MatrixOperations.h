#include <string>
#include <vector>
using namespace std;
#pragma once
int CalculateRow(vector<int>& row, vector<int>& column);
vector<int> ConvertToIntArray(string line);
vector<vector<int> > ReadMatrix(fstream& file);
vector<int> GetColumn(vector<vector<int> > matrix, int n_column);
vector<vector<int> > ResultMatrix(vector<vector<int> > first_matrix, vector<vector<int> > second_matrix);
vector<vector<int> > ReadMatrixSpec(fstream& file);