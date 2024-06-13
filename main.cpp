#include <iostream>
#include "reflection_system.h"

using reflection_system::Reflective;

class Derived : public Reflective<Derived>
{
    std::string str = "string";
    long long fl = 5;

    void func1() { std::cout << "func1" << std::endl; }
    int func2() { return 0; }

public:
    Derived() = default;

    Derived(const std::string& s, const long long& f)
        : str(s), fl(f)
    {}

    void SetStr(const std::string& s) { this->str = s; }

    void PrintMethods() const {
        FillMemberList();
        for (auto& method : GetMethods())
            std::cout << method.sign << std::endl;
    }

    MEMBER_LIST_BEGIN
        ATTRIBUTE(str)
        ATTRIBUTE(fl)
        METHOD(func1)
        METHOD(func2)
        METHOD(PrintMethods)
    MEMBER_LIST_END
};

int main(int argc, char** argv)
{
    Derived derived;
    std::cout << derived << std::endl;
    std::cout << derived.GetSize() << std::endl;
    std::cout << derived.GetClassname() << std::endl;

    return 0;
}
