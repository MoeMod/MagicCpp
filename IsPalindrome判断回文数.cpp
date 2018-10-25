#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

// https://leetcode-cn.com/problems/palindrome-number/

bool isPalindrome(int x)
{
	auto str = std::to_string(x);
	return std::mismatch(str.cbegin(), str.cend(), str.crbegin()).first == str.cend();
}

int main()
{
	uint32_t n = *istream_iterator<uint32_t>(cin);
	cout << isPalindrome(n) << endl;
}