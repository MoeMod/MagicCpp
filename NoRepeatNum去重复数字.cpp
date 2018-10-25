#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

int main()
{
	std::vector<int> v((std::istream_iterator<int>(std::cin)), (std::istream_iterator<int>())); // 输入数据到数组（按Ctrl+Z结束）
	std::sort(v.begin(), v.end()); // 排序
	std::unique_copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " ")); // 移除重复项目顺便输出

	//v.erase(std::unique(v.begin(), v.end()), v.end()); // 把非重复项目移动到数组前端，然后把后端擦除（unique-erase惯用法）
	//std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " ")); // 从数组输出数据
}
