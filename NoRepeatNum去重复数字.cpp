#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

int main()
{
	std::vector<int> v((std::istream_iterator<int>(std::cin)), (std::istream_iterator<int>())); // �������ݵ����飨��Ctrl+Z������
	std::sort(v.begin(), v.end()); // ����
	std::unique_copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " ")); // �Ƴ��ظ���Ŀ˳�����

	//v.erase(std::unique(v.begin(), v.end()), v.end()); // �ѷ��ظ���Ŀ�ƶ�������ǰ�ˣ�Ȼ��Ѻ�˲�����unique-erase���÷���
	//std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " ")); // �������������
}
