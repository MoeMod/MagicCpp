#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <set>

int main()
{
	// ����1 : ����
	/*
	std::vector<int> v((std::istream_iterator<int>(std::cin)), (std::istream_iterator<int>())); // �������ݵ����飨��Ctrl+Z������
	std::sort(v.begin(), v.end()); // ����
	v.erase(std::unique(v.begin(), v.end()), v.end()); // �ѷ��ظ���Ŀ�ƶ�������ǰ�ˣ�Ȼ��Ѻ�˲�����unique-erase���÷���
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " ")); // �������������
	*/
	
	// ����2 : ���顢�򻯸���
	/*
	std::vector<int> v((std::istream_iterator<int>(std::cin)), (std::istream_iterator<int>())); // �������ݵ����飨��Ctrl+Z������
	std::sort(v.begin(), v.end()); // ����
	std::unique_copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " ")); // �Ƴ��ظ���Ŀ˳�����
	*/
	
	// ����3 : ֱ����set������
	std::set<int> v((std::istream_iterator<int>(std::cin)), (std::istream_iterator<int>())); // �������ݵ����飨��Ctrl+Z������
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " ")); // ���
	
}
