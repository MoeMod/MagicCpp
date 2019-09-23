#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <mutex>
using namespace std;

template<class T> class ObjectPool {
private:
    using Storage = std::pair<T, std::weak_ptr<void>>;
    std::vector<const std::shared_ptr<Storage>> v;
    std::mutex m;
public:
    std::shared_ptr<T> acquire() {
        std::lock_guard<std::mutex> l(m);
        const std::shared_ptr<std::shared_ptr<Storage>> keeper = std::make_shared<std::shared_ptr<Storage>>();
        auto iter = v.end();
        while((iter = std::find_if(v.begin(), v.end(), [](const std::shared_ptr<Storage> &s){ return s->second.lock() == nullptr; })) == v.end())
            v.push_back(std::make_shared<Storage>());
	    (*iter)->second = keeper;
	    *keeper = *iter;
        return std::shared_ptr<T>(keeper, &(*iter)->first);
    }
};

int main()
{
    std::shared_ptr<ObjectPool<std::string>> op = std::make_shared<ObjectPool<std::string>>();
    auto a = op->acquire();
    {
        auto b = op->acquire(), c = op->acquire();
        std::cout << a.get() << std::endl;
        std::cout << b.get() << std::endl;
        std::cout << c.get() << std::endl;
    }
    auto e = op->acquire();
    std::cout << e.get() << std::endl;
    *e = "still alive";
    op = nullptr;
    std::cout << *e << std::endl;
}
