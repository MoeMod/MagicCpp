#include <iostream>

class A {
private:
    int val = 0;
public:
    virtual int get() const {
        return val;
    }
};

constexpr int A::* get_private();
template <int A::* Ptr> struct hack_a {
    friend constexpr int A::* get_private() { return Ptr; }
};
template struct hack_a<&A::val>;

int main() {
    A a;
    constexpr int A::* p = get_private();
    std::cout << a.get() << std::endl;
    a.*p = 233;
    std::cout << a.get() << std::endl;
}