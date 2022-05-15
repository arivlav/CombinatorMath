#include <iostream>
#include <vector> 

using namespace std;

void PrintPermutation(const vector<int> v)
{
	copy(v.begin()++, v.end()--, ostream_iterator<size_t>(cout, " "));
	cout << endl;
}

void GetRandomPermutation(vector<int>& v)
{
	int randomNum;
	for (int i = 0; i < v.size(); ++i)
	{
		randomNum = rand() % v.size();
		swap(v[i], v[randomNum]);
	}
}

int main()
{
	srand(time(0));
	vector<int> identityPermutation = { 1, 2, 3, 4, 5 };

	cout << "Identity permutation:\n";
	PrintPermutation(identityPermutation);

	GetRandomPermutation(identityPermutation);
	cout << "Random permutation:\n";
	PrintPermutation(identityPermutation);
}