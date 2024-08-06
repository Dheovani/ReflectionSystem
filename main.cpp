#include <iostream>
#include "reflection.h"

class Base {};

struct BaseStruct {};

class Derived : public Base, public BaseStruct
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

    template <typename _Ty>
    _Ty GetAttribute(const std::string& name) const {
        for (const auto& pair : GetAttributes()) {
            if (pair.first == name) {
                return std::is_convertible_v<decltype(pair.first), _Ty type::*>
                    ? this->*(std::get<_Ty type::*>(pair.first))
                    : *(std::get<_Ty*>(pair.first));
            }
        }

        throw std::runtime_error("Attribute not found");
    }
};

int main(void)
{
    Derived derived = Derived::GetInstance("String nova");

    auto str = derived.GetAttribute<std::string>("str");
    //std::cout << derived.*(std::get<std::string Derived::*>(str)) << std::endl;

    auto fl = derived.GetAttribute("fl");
    std::cout << *(std::get<const long long*>(fl)) << std::endl;

    std::cout << TName(&Derived::StaticMethod) << std::endl;
    std::cout << typeid(std::remove_pointer_t<decltype(&Derived::StaticMethod)>).name() << std::endl;
    std::cout << TName(&Derived::SetStr) << std::endl;
    std::cout << typeid(reflection::remove_class_pointer_t<decltype(&Derived::SetStr), Derived>).name() << std::endl;

    return 0;
}
