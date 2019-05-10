#include <iostream>
#include <tuple>

using namespace std;

template<class...Args> struct hash<tuple<Args...>>
{
	template<std::size_t...I>
	std::size_t hash_impl(const tuple<Args...>& t, std::index_sequence<I...>) const
	{
		return (hash<Args>()(std::get<I>(t)) ^ ...);
	}
	std::size_t operator()(const tuple<Args...>& t) const
	{
		return hash_impl(t, std::index_sequence_for<Args...>());
	}
};

int main()
{
	auto t = std::make_tuple(123, 456);
	auto t2 = std::make_tuple(123, 456);
	std::cout << hash<decltype(t)>()(t) << std::endl;
	std::cout << hash<decltype(t)>()(t2) << std::endl;
}