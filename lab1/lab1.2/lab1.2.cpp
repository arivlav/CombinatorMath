#include <iostream>
#include <vector>
#include <boost/timer.hpp>

using namespace std;

void PrintPermutation(const vector<int>& v)
{
    copy(++v.begin(), --v.end(), ostream_iterator<size_t>(cout, " "));
    cout << endl;
}

int main()
{
    const int n = 15;
    vector<int> pi, p, d;
    for (int i = 0; i <= n + 1; i++)
    {
        pi.push_back(i);
        p.push_back(i);
        d.push_back(-1);
    }
    d[1] = 0;
    int m = pi[0] = n + 1;
    boost::timer t;
    t.restart();
    while (m != 1)
    {
        //PrintPermutation(pi);
        m = n;
        while (pi[p[m] + d[m]] > m)
        {
            d[m] = (-1) * d[m];
            m = m - 1;
        }
        swap(pi[p[m]], pi[p[m] + d[m]]);
        swap(p[pi[p[m]]], p[m]);
    }
    double duration = t.elapsed();
    cout << duration << endl;
    return 0;
}