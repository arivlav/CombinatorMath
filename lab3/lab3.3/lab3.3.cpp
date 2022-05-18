#include <iostream>
#include <optional>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

constexpr int MAX_MATRIX_SIZE = 100;

struct Args
{
	string inputFileName;
};

typedef vector<vector<int>> IntMatrix;
typedef vector<vector<float>> FloatMatrix;

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid argument count\n";
		cout << "Use lab3.3.exe <matrix fileName>\n";
		return nullopt;
	}

	Args args;
	args.inputFileName = argv[1];

	return args;
}

int ReadMatrixFromStream(std::ifstream& input, IntMatrix& field, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			input >> field[i][j];
		}
	}
	return 0;
}


int GetKirchhoffMatrix(const IntMatrix& inputMatrix, FloatMatrix& kirchhoffMatrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		float countPoints = 0.0f;
		for (int j = 0; j < size; j++)
		{
			if (inputMatrix[i][j] > 0)
			{
				countPoints++;
				kirchhoffMatrix[i][j] = -1.0;
			}
			else
			{
				kirchhoffMatrix[i][j] = 0.0;
			}
		}
		if (countPoints == 0)
		{
			return 0;
		}
		kirchhoffMatrix[i][i] = countPoints;
	}
	return 1;
}

void PrintMatrix(IntMatrix& field, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << field[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	ifstream input(args->inputFileName);
	if (!input.is_open())
	{
		cout << "Failed to open input file for reading\n";
		return 1;
	}

	int matrixSize;
	input >> matrixSize;

	if (matrixSize <= 0 || matrixSize > MAX_MATRIX_SIZE)
	{
		cout << "Invalid matrix size\n";
		return 1;
	}

	IntMatrix inputMatrix(matrixSize, vector<int>(matrixSize, 0));
	ReadMatrixFromStream(input, inputMatrix, matrixSize);

	FloatMatrix kirchhoffMatrix(matrixSize, vector<float>(matrixSize, 0));
	if (GetKirchhoffMatrix(inputMatrix, kirchhoffMatrix, matrixSize) != 0) {

	}

	return 0;
}