# C++ Reflection System

Welcome to the C++ Reflection Library! This library provides a powerful and flexible way to add reflection capabilities to your C++ classes. With this library, you can easily introspect classes, their attributes, and methods at runtime. 🚀

## 🌟 Features

- Reflect on class attributes and methods.
- Generate human-readable class information.
- Easily extendable and customizable.
- Minimal overhead and easy integration.

## 📚 Installation

1. Clone the repository:

```sh
git clone https://github.com/Dheovani/ReflectionSystem.git
```

2. Include the header files in your project:

```cpp
#include "reflection_system.h"
```

## 🚀 Usage
Here's a quick example to get you started:

```cpp
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
};

int main(void)
{
    auto derived = Derived::GetInstance();
    std::cout << Derived::Classname() << std::endl;
    std::cout << Derived::Size() << std::endl;

    return 0;
}
```

## 📝 TODO

Here are some tasks and improvements planned for the C++ Introspection System:

- [x] 🛠️ **Add Support for Parent Classes**: Implement introspection for parents, allowing dynamic data gathering.
- [x] 📚 **Documentation**: Expand the documentation with detailed usage examples and best practices.
- [x] 🧪 **Testing**: Increase unit test coverage to ensure the robustness and reliability of the system.
- [x] 🌐 **Multi-format Serialization Support**: Implement support for additional serialization formats, such as JSON.
- [ ] 🔒 **Access Modifiers**: Find a way to verify if methods are either private, protected or public.

Feel free to contribute to any of these tasks or suggest new features and improvements!

## 🎓 Contributing
Contributions are welcome! Please feel free to submit a pull request or open an issue.

## 📄 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details.

## 🙏 Acknowledgments
Special thanks to the following projects for their inspiration and contributions to the C++ community:
- [JsonCpp](https://github.com/open-source-parsers/jsoncpp)
- [yaml-cpp](https://github.com/jbeder/yaml-cpp)
- [tinyxml2](https://github.com/leethomason/tinyxml2)
- [GoogleTest](https://github.com/google/googletest)

Happy Coding! 😊