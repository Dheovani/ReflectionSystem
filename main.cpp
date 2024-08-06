#include <iostream>
#include "reflection.h"

namespace refl = reflection;

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
    _Ty GetAttribute(const std::string& name) const
    {
        for (const auto& pair : GetAttributes()) {
            if (pair.first == name) {
                return _Ty{};
                //return std::is_convertible_v<decltype(pair.second), _Ty type::*>
                    //? this->*(std::get<_Ty type::*>(pair.second))
                    //: *(std::get<_Ty*>(pair.second));
            }
        }

        throw std::runtime_error("Attribute not found"); 
    }
};

int main(void)
{
    using type = std::variant<int, char, std::string, long long, double>;
    std::cout << refl::get_variant_index_v<char, type> << std::endl;

    return 0;
}
