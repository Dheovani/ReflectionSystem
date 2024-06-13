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
#include "reflection_system.h_"
```

## 🚀 Usage
Here's a quick example to get you started:

```cpp
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
```

## 📝 TODO

Here are some tasks and improvements planned for the C++ Introspection System:

- [ ] 🛠️ **Add Support for Parent Classes**: Implement introspection for parents, allowing dynamic data gathering.
- [ ] 📚 **Documentation**: Expand the documentation with detailed usage examples and best practices.
- [ ] 🧪 **Testing**: Increase unit test coverage to ensure the robustness and reliability of the system.
- [ ] 🌐 **Multi-format Serialization Support**: Implement support for additional serialization formats, such as JSON.
- [ ] 🔒 **Access Modifiers**: Find a way to verify if methods are either private, protected or public.

Feel free to contribute to any of these tasks or suggest new features and improvements!


## 🎓 Contributing
Contributions are welcome! Please feel free to submit a pull request or open an issue.

## 📄 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details.

Happy Coding! 😊