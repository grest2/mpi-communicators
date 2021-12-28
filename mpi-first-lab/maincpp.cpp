//#include "stdafx.h"

#include "MatrixOperations.h"
#include "mpi.h"

#include <iostream>
#include <fstream>
#include <vector>


using namespace std;


//int main(int argc, char* argv[]) {
//
//	int rank;
//	vector<vector<int> > pointer;
//	vector<vector<int> > pointer_sec;
//	int result = 0;
//	int result2 = 0;
//
//	MPI_Status status;
//	MPI_Init(&argc, &argv);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//	
//
//
//	fstream file("D:/Github/mpi-first-lab/mpi-first-lab/matrix.txt");
//
//		while (!file.eof()) {
//
//			if (pointer.empty()) {
//				pointer = ReadMatrix(file);
//			}
//			if (pointer_sec.empty()) {
//				pointer_sec = ReadMatrix(file);
//			}
//			if (pointer.size() != pointer_sec.size()) {
//				vector<vector<int> > temporary = ReadMatrix(file);
//
//				if (temporary.size() == pointer.size()) {
//					vector<vector<int> > result_t = ResultMatrix(pointer, temporary);
//					int counter = 0;
//
//					for (size_t i = 0; i != result_t.size(); i++) {
//						for (size_t j = 0; j != result_t.size(); j++) {
//							if (rank == 0) {
//								result = result_t[i][j];
//								MPI_Send(&result, 10, MPI_INT, 1, counter, MPI_COMM_WORLD);
//								counter += 1;
//							}
//						}
//					}
//
//					pointer.clear();
//				}
//				else {
//					vector<vector<int> > result_t = ResultMatrix(pointer_sec, temporary);
//					if (rank == 0) {
//						result = 5;
//						MPI_Send(&result, 10, MPI_INT, 1, 0, MPI_COMM_WORLD);
//					}
//
//					pointer_sec.clear();
//				}
//			}
//			else if (pointer.size() == pointer_sec.size() && pointer.size() > 1) {
//				vector<vector<int> > result_t = ResultMatrix(pointer, pointer_sec);
//				int counter = 0;
//				for (size_t i = 0; i != result_t.size(); i++) {
//					for (size_t j = 0; j != result_t.size(); j++) {
//						if (rank == 0) {
//							result2 = result_t[i][j];
//							MPI_Send(&result2, 10, MPI_INT, 2, counter, MPI_COMM_WORLD);
//							counter += 1;
//						}
//					}
//				}
//				pointer.clear();
//				pointer_sec.clear();
//			}
//		}
//		file.close();
//
//	if (rank == 1) {
//		for(int i = 0; i < 12; i++)
//		{
//			MPI_Recv(&result, 10, MPI_INT, 0, i, MPI_COMM_WORLD, &status);
//			cout << "_LOG_ received value, matrix size 3x3: " << result << endl;
//		}
//	}
//
//	if(rank == 2) {
//		for(int i = 0; i < 16; i++)
//		{
//			MPI_Recv(&result2, 10, MPI_INT, 0, i, MPI_COMM_WORLD, &status);
//			cout << "_LOG_ received value, matrix size 4x4: " << result2 << endl;
//		}
//		
//	}
//	MPI_Finalize();
//	pointer_sec.clear();
//	pointer.clear();
//
//	return 0;
//}

int main(int argc, char* argv[]) {

	int rank,size;
	vector<vector<int> > pointer;
	vector<vector<int> > pointer_sec;

	vector<vector<int> > pointer_b;
	vector<vector<int> > pointer_sec_b;

	vector<vector<int> > result;
	vector<int> result_s;
	vector<int> r;
	vector<int> temporary_vec(5);
	vector<int> temporary_vec_sec(3);


	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	
	fstream file("D:/Github/mpi-first-lab/mpi-first-lab/matrix_2.txt");
	while (!file.eof()) {
		pointer = ReadMatrixSpec(file);
		pointer_sec = ReadMatrixSpec(file);
		if (pointer.size() > 1) {
			if (rank == 0) {
				for (size_t i = 0; i != pointer.size(); i++) {
					MPI_Bcast(pointer[i].data(), 5, MPI_INT, 0, MPI_COMM_WORLD);
				}
				for (size_t j = 0; j != pointer_sec.size(); j++) {
					MPI_Bcast(pointer_sec[j].data(), 3, MPI_INT, 0, MPI_COMM_WORLD);
				}
				MPI_Barrier(MPI_COMM_WORLD);
			}
			else {
				pointer_b.clear();
				pointer_sec_b.clear();
				for (int i = 0; i < 8; i++) {
					MPI_Bcast(temporary_vec.data(), 5, MPI_INT, 0, MPI_COMM_WORLD);
					pointer_b.push_back(temporary_vec);
				}
				for (int i = 0; i < 5; i++) {
					MPI_Bcast(temporary_vec_sec.data(), 3, MPI_INT, 0, MPI_COMM_WORLD);
					pointer_sec_b.push_back(temporary_vec_sec);
				}
				MPI_Barrier(MPI_COMM_WORLD);
				if (rank == 1) {
					result = ResultMatrix(pointer_b, pointer_sec);
					cout << "_LOG_ result matrix size: " << result.size() << endl;

				} 
			}
		}
	}
	file.close();
	MPI_Finalize();
	pointer_sec.clear();
	pointer.clear();

	return 0;
}

