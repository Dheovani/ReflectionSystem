#include <iostream>
#include "reflection.h"

namespace refl = reflection;

class Base {};

struct BaseStruct {};

class Derived: public Base, public BaseStruct
{
    std::string str = "string";
    static const long long fl = 5;

    void func1() { std::cout << "func1" << std::endl; }
    int func2() { return 0; }

public:
    Derived() = default;

    Derived(const std::string& s) : str(s)
    {}

    static void StaticMethod(void) { std::cout << "In the static method" << std::endl; }

    void SetStr(const std::string& s) { this->str = s; }

    UseReflectionTrait
    (
        Derived,
        Attributes(str, fl),
        Methods(func1, func2, StaticMethod, SetStr),
        Parents(Base, BaseStruct)
    )
};

int main(void)
{
    auto derived = Derived::GetInstance();
    std::cout << Derived::Classname() << std::endl;
    std::cout << Derived::Size() << std::endl;

    return 0;
}
