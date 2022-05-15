#include <iostream>
#include <vector>
#include <boost/timer.hpp>

using namespace std;

int main()
{
    const int k = 5, n = 25; //10 20;
    vector<size_t> v;

    boost::timer t;
    t.restart();
    v.push_back(-1);
    for (int i = 1; i <= k; ++i)
    {
        v.push_back(i);
    }
    int m = 1;
    while (m != 0)
    {
        copy(v.begin() + 1, v.begin() + 1 + k, ostream_iterator<size_t>(cout, " "));
        cout << endl;
        m = k;
        while (v[m] == n - k + m)
        {
            m--;
        }
        v[m]++;
        for (int i = m + 1; i <= k; i++)
        {
            v[i] = v[i - 1] + 1;
        }
    }
    double duration = t.elapsed();
    cout << duration << endl;
}