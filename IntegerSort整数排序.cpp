#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <set>

int main()
{
	/*std::vector<int> v((std::istream_iterator<int>(std::cin)), (std::istream_iterator<int>())); // 输入数据到数组（按Ctrl+Z结束）
	std::sort(v.begin(), v.end()); // 对数组从小到大排序*/
	
	std::set<int> v((std::istream_iterator<int>(std::cin)), (std::istream_iterator<int>())); // 利用set自动排序
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " ")); // 从数组输出数据
}
