#include <iostream>
#include <tuple>

template<class Tuple1, class Tuple2>
constexpr auto cart_impl(Tuple1&& lhs, Tuple2&& rhs, std::index_sequence<0>, 
	typename std::enable_if<(std::tuple_size<typename std::decay<Tuple1>::type>::value == std::tuple_size<typename std::decay<Tuple2>::type>::value == 1)>::type * = nullptr)
{
	using T1 = typename std::tuple_element<0, typename std::decay<Tuple1>::type >::type;
	using T2 = typename std::tuple_element<0, typename std::decay<Tuple2>::type >::type;
	return std::tuple<std::pair<T1, T2>>(std::pair<T1, T2>(std::get<0>(std::forward<Tuple1>(lhs)), std::get<0>(std::forward<Tuple2>(rhs))));
}

template<class T, class Tuple2, std::size_t...I2>
constexpr auto cart_impl(const std::tuple<T>& lhs, Tuple2&& rhs, std::index_sequence<I2...>, 
	typename std::enable_if<std::tuple_size<typename std::decay<Tuple2>::type>::value != 1>::type * = nullptr)
{
	return std::tuple_cat(cart_impl(
		lhs, 
		std::tuple<typename std::tuple_element<I2, typename std::decay<Tuple2>::type>::type>(std::get<I2>(std::forward<Tuple2>(rhs))), 
		std::index_sequence<0>()
	)...);
}

template<class Tuple1, class Tuple2, std::size_t...I1>
constexpr auto cart_impl(Tuple1&& lhs, Tuple2&& rhs, std::index_sequence<I1...>, 
	typename std::enable_if<std::tuple_size<typename std::decay<Tuple1>::type>::value != 1>::type * = nullptr)
{
	return std::tuple_cat(cart_impl(
		std::tuple<typename std::tuple_element<I1, typename std::decay<Tuple1>::type>::type>(std::get<I1>(std::forward<Tuple1>(lhs))), 
		rhs, 
		std::make_index_sequence<std::tuple_size< typename std::decay<Tuple2>::type >::value>()
	)...);
}

template<class Tuple1, class Tuple2>
constexpr auto cart(Tuple1&& lhs, Tuple2&& rhs)
{
	return cart_impl(std::forward<Tuple1>(lhs), std::forward<Tuple2>(rhs), std::make_index_sequence<std::tuple_size< typename std::decay<Tuple1>::type >::value>());
}

int main()
{
	int x = 1, y = 2, z = 3;
	auto tuple1 = std::tie(x, y, z);
	auto tuple2 = std::make_tuple("a", "b");
	auto tuple3 = cart(tuple2, tuple1);
	std::cout << typeid(tuple3).name() << std::endl;
	return 0;
}