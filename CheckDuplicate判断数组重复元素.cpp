#include <iostream>
#include <vector>
#include <unordered_set>
#include <iterator>

using namespace std;
int main()
{
    // ������(ctrl+zֹͣ)
    vector<int> v ((istream_iterator<int>(cin)), (istream_iterator<int>()));
    // �����û����ͬ����
    cout << (unordered_set<int>(v.begin(), v.end()).size() != v.size()) << endl;
}