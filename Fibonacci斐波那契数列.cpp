#include <iostream>
#include <array>
#include <type_traits>

// 使用模板计算0~92的斐波那契数
template<size_t N> struct F : std::integral_constant<long long, F<N - 1>::value + F<N - 2>::value> {};
template<> struct F<0> : std::integral_constant<long long, 0ll> {};
template<> struct F<1> : std::integral_constant<long long, 1ll> {};

// 将结果填充至数组
template<size_t...I>
constexpr std::array<long long, sizeof...(I)> buildArray(std::index_sequence<I...>)
{
	return { F<I>::value... };
}
auto arr = buildArray(std::make_index_sequence<93>());

int main()
{
	using namespace std;
	int i = 0;
	cin >> i;
	cout << arr[i] << endl;
}