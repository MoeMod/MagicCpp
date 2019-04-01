#include <iostream>

template<class T>
struct identity
{
	using type = T;
};

template<class c, class x, class y>
struct replace_type : identity<c> {};

template<class x, class y>
struct replace_type<x, x, y> : identity<y> {};

// functions with x
template<class x, class y, class Return, class...Args>
struct replace_type<Return(Args...), x, y>
{
	using type = typename replace_type<Return, x, y>::type(typename replace_type<Args, x, y>::type...);
};

// C++17
#if __cplusplus >= 201703L
template<class x, class y, class Return, class...Args>
struct replace_type<Return(*)(Args...) noexcept, x, y>
{
	using type = typename replace_type<Return, x, y>::type (*) (typename replace_type<Args, x, y>::type...) noexcept;
};
#endif

// template class with x
template<class x, class y, template<class...A> class obj, class...Args>
struct replace_type<obj<Args...>, x, y>
{
	using type =  obj<typename replace_type<Args, x, y>::type...>;
};

template<class c, class x, class y, size_t i>
struct replace_type<c [i], x, y>
{
	using type = typename replace_type<c, x, y>::type [i];
};

template<class c, class x, class y>
struct replace_type<const c, x, y> : identity<const typename replace_type<c, x, y>::type> {};

template<class c, class x, class y>
struct replace_type<c *, x, y> : identity<typename replace_type<c, x, y>::type *> {};

template<class c, class x, class y>
struct replace_type<c &, x, y> : identity<typename replace_type<c, x, y>::type &> {};

template<class c, class x, class y>
struct replace_type<c &&, x, y> : identity<typename replace_type<c, x, y>::type &&> {};

int main()
{
	std::cout << typeid(replace_type<int (*)(), int, float> ::type).name() << std::endl;
}