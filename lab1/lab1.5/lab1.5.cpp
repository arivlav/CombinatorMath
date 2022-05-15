#include <iostream>
#include <vector>
#include <boost/timer.hpp>

using namespace std;

void PrintVector(const vector<size_t> v)
{
    copy(v.begin()++, (v.end() - 1)--, ostream_iterator<size_t>(cout, " "));
    cout << endl;
}


int main()
{
    const int k = 5, n = 20;

    boost::timer t;
    t.restart();

    vector<size_t> v;

    for (int i = 0; i <= k; i++)
    {
        v.push_back(0);
    }

    while (v[k] != 1)
    {
        PrintVector(v);
        int i = 0;
        while (v[i] == n - 1)
        {
            v[i] = 0;
            i++;
        }
        v[i]++;
    }

    double duration = t.elapsed();
    cout << duration << endl;
}