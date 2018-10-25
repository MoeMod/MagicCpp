#include <iostream> // cin cout
#include <iterator> // istreambuf_iterator ostreambuf_iterator
#include <string> // toupper tolower
#include <algorithm> // transform

using namespace std;
int main()
{
	// 1. 利用transform和流迭代器直接处理输入输出
	// 2. 利用按位异或的性质（源字符、大写、小写之中去掉两个重复的）
	// 3. 利用lambda表达式作为处理的函数对象
	transform(istreambuf_iterator<char>(cin), istreambuf_iterator<char>(), ostreambuf_iterator<char>(cout), [](char c) { return c ^ toupper(c) ^ tolower(c); });
}