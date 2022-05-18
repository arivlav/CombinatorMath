#include <iostream>
#include <optional>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

constexpr int MAX_MATRIX_SIZE = 400;

struct Args
{
	string inputFileName;
};

typedef vector<vector<int>> Matrix;

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid argument count\n";
		cout << "Use lab2.5.exe <matrix fileName>\n";
		return nullopt;
	}

	Args args;
	args.inputFileName = argv[1];

	return args;
}

int ReadMatrixFromStream(std::ifstream& input, Matrix& field, int size)
{
	int elementVal;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			input >> elementVal;
			field[i][j] = (elementVal > 0 || i == j) ? 1 : 0;
		}
	}
	return 0;
}

void GetVectorOfZero(vector<int> &vector)
{
	transform(vector.begin(), vector.end(), vector.begin(), [](int element) {
		return 0;
	});
}

int GetNumberOfPaintPoint(vector<int>& colorArr) 
{
	int i = 0;
	while (i != colorArr.size())
	{
		if (colorArr[i] == 0)
			break;
		i++;
	}
	return i;
}

bool IsGrafStar(Matrix& matrix, int size, int firstPoint, int secondPoint)
{
	bool isStar = true;
	if (firstPoint < size && secondPoint < size)
	{
		for (int j = 0; j < size; j++)
		{
			matrix[firstPoint][j] |= matrix[secondPoint][j];
			if (matrix[firstPoint][j] == 0)
				isStar = false;
		}
	}
	return isStar;
}

void PrintVector(const vector<int>& vector)
{
	for (auto i = 0; i != vector.size(); ++i)
		cout << i + 1 << " " << vector[i] << endl;
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

	Matrix matrix(matrixSize, vector<int>(matrixSize, 0));
	ReadMatrixFromStream(input, matrix, matrixSize);
	
	vector<int> colorArr(matrixSize); 
	GetVectorOfZero(colorArr);


	int color = 0, numberOfPoint = GetNumberOfPaintPoint(colorArr);

	while (numberOfPoint < matrixSize)
	{
		color++;
		// красим вершину
		colorArr[numberOfPoint] = color;		
		// проходим по вершинам окрестности 1-го порядка
		bool isStar = false;
		while (!isStar)
		{
			int j;
			for (j = 0; j < matrixSize; j++)
			{
				if (numberOfPoint != j && matrix[numberOfPoint][j] == 1)
				{
					// ищем вершины окрестности 2-го порядка и красим их
					for (int k = 0; k < matrixSize; k++)
					{
						bool isPointR2 = (k != j && matrix[j][k] == 1 && matrix[numberOfPoint][k] == 0);
						// Если вершина является веришиной окрестности второго порядка и непокрашена
						// красим её и склеиваем с текушей вершиной
						if (isPointR2 && colorArr[k] == 0)
						{
							colorArr[k] = color;
							isStar = IsGrafStar(matrix, matrixSize, numberOfPoint, k);
							break;
						}
					}
				}
				if (isStar)
					break;
			}
			isStar = (isStar || !(j < matrixSize));
		}
		numberOfPoint = GetNumberOfPaintPoint(colorArr);
	}

	PrintVector(colorArr);

	return 0;
}