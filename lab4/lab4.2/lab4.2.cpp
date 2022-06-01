#include <iostream>
#include <optional>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

const int NO_MATCH = -1;
const int MAX_SIZE = 100;

struct Args
{
	string inputFileName;
};

typedef vector<vector<int>> Matrix;

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid argument count\n";
		cout << "Use lab4.2.exe <matrix fileName>\n";
		return nullopt;
	}

	Args args;
	args.inputFileName = argv[1];

	return args;
}

int ReadMatrixFromStream(ifstream& input, Matrix& field, int size)
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

void PrintMatrix(Matrix& field, int size)
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

bool TryKuhn(int v, vector<bool>& used, vector<int>& matchingList, Matrix& ribsList)
{
	if (used[v])  return false;
	used[v] = true;
	for (int i = 0; i < ribsList[v].size(); ++i) {
		int to = ribsList[v][i];
		if (matchingList[to] == NO_MATCH || TryKuhn(matchingList[to], used, matchingList, ribsList)) {
			matchingList[to] = v;
			return true;
		}
	}
	return false;
}

vector<int> FindCompleteMatching(Matrix& arr, int size)
{
	Matrix ribsList(size);
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (arr[i][j] == 1)
			{
				ribsList[i].push_back(j);
			}
		}
	}

	vector<int> matchingList(size, NO_MATCH);
	vector<bool> used;

	for (int v = 0; v < size; ++v) {
		used.assign(size, false);
		TryKuhn(v, used, matchingList, ribsList);
	}

	return matchingList;
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

	int matrixSize, rowSize;
	input >> matrixSize;
	input >> rowSize;

	if (matrixSize <= 0 || matrixSize > MAX_SIZE)
	{
		cout << "Invalid matrix size\n";
		return 1;
	}

	if (rowSize <= 0 || rowSize > MAX_SIZE)
	{
		cout << "Invalid row size\n";
		return 1;
	}

	Matrix inputMatrix(matrixSize, vector<int>(matrixSize, 0));
	ReadMatrixFromStream(input, inputMatrix, matrixSize);

	vector<int> result = FindCompleteMatching(inputMatrix, matrixSize);

	if (find(result.begin(), result.end(), NO_MATCH) != result.end()) {
		cout << "No\n";
	}
	else {
		cout << "Yes\n";
		for (int i = 0; i < matrixSize; ++i)
		{
			cout << result[i] << ", " << i << endl;
		}
	}
}