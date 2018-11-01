#include <iostream>
#include <vector>
#include <unordered_set>
#include <iterator>

using namespace std;
int main()
{
    // 读数据(ctrl+z停止)
    vector<int> v ((istream_iterator<int>(cin)), (istream_iterator<int>()));
    // 输出有没有相同数据
    cout << (unordered_set<int>(v.begin(), v.end()).size() != v.size()) << endl;
}