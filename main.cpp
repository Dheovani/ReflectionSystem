#include <iostream>
#include "reflection_system.h"

using reflection_system::Reflective;

class Base {};

struct BaseStruct {};

class Derived : public Reflective<Derived>, public Base, public BaseStruct
{
    std::string str = "string";
    static const long long fl = 5;

    void func1() { std::cout << "func1" << std::endl; }
    int func2() { return 0; }

public:
    Derived() = default;

    Derived(const std::string& s, const long long& f) : str(s)
    {}

    static void StaticMethod(void) { std::cout << "In the static method" << std::endl; }

    void SetStr(const std::string& s) { this->str = s; }

    void PrintMethods() const {
        FillMethodList();
        for (auto& method : GetMethods())
            std::cout << method.sign << std::endl;
    }

    PARENT_CLASSES(Reflective<Derived>, Base, BaseStruct)
    ATTRIBUTES(str, fl)
    METHODS(func1, func2, StaticMethod, PrintMethods)
};

int main(int argc, char** argv)
{
    Derived derived;
    std::cout << derived << std::endl;

    (*(derived.GetMethod<void(*)(void)>("StaticMethod")))();

    auto method = derived.GetMethod<void(Derived::*)(void)const>("PrintMethods");
    (derived.*method)();

    std::cout << derived.GetAttribute<long long const>("fl") << std::endl;
    std::cout << derived.GetAttribute<std::string>("str") << std::endl;
    derived.SetStr("Other string");
    std::cout << derived.GetAttribute<std::string>("str") << std::endl;

    return 0;
}
