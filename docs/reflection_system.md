# Documentation for reflection_system.h

## Macros

- ID(v)
Macro that returns the type identifier name of the variable v.

- ASSERTATION(parent)
Macro that performs compile-time assertions to ensure that parent is a valid class type extended by the current class (This).

- PARENT_CLASSES(...)
Macro for defining parent classes of the current class (This). It includes compile-time assertions for each parent class and provides methods to access parent class instances.

- ATTRIBUTE(attrib)
Macro that verifies if attrib is a valid attribute and adds it to the list of attributes for the current class (This).

- ATTRIBUTES(...)
Macro that populates the list of attributes for the current class (This) using the ATTRIBUTE macro for each attribute.

- METHOD(method)
Macro that verifies if method is a valid function and adds it to the list of methods for the current class (This).

- METHODS(...)
Macro that populates the list of methods for the current class (This) using the METHOD macro for each method.

## Types and Functions

- hash
(8 bytes) Typedef for unsigned long long, used as a hash value for various purposes in the reflection system.

## Namespace reflection_system

- struct Method
Template struct representing a method of a reflective class. Stores its key (hash), signature, static status, and value.

- struct Attribute
Template struct representing an attribute of a reflective class. Stores its key (hash), name, static status, and value.

- template <typename _Base, typename _Derived> constexpr bool instance_of
Check if _Derived is an instance of _Base.

- template <typename _Ty> constexpr bool is_attribute
Check if _Ty is a valid attribute type.

- template <typename _Ty> constexpr bool is_function
Check if _Ty is a valid function type.

- template <class _Ty1, class _Ty2> concept parent_concept
Concept to verify if _Ty1 is a parent class of _Ty2.

- constexpr const std::string Clear(std::string token, const std::vectorstd::string& substrs)
Function that clears substrings from token based on substrs.

- constexpr const std::string Normalize(const std::string& name, const std::string& sign)
Function that normalizes name with sign for consistent formatting.

- constexpr const hash HashCode(const char key)*
Function that computes a hash code for key.

- template <typename _Class> class Reflective
Main class template providing reflection capabilities for _Class.

## Class Reflective' methods and members:

- size_t size: Size of _Class.
- std::string classname: Name of _Class.
- std::string cache: Cached string representation.
- std::vector<Method<std::any>> methods: List of methods.
- std::vector<Attribute<std::any>> attributes: List of attributes.

### Constructors and Operators:

- Reflective(): Constructor that performs class-specific assertions.

### Member Functions:

- operator const char* () const: Converts _Class to a string representation.
- template <typename... Args> _Class GetInstance(Args... args) const: Creates an instance of _Class.
- const _Class* GetClass() const: Returns a pointer to _Class.
- std::string GetClassname(bool ignoreType = false) const: Returns the name of _Class.
- size_t GetSize() const: Returns the size of _Class.
- template <typename _Ty> void AddMethod(...) const: Adds a method to _Class.
- template <typename _Ty> void AddAttribute(...) const: Adds an attribute to _Class.
- template <typename _Ty> _Ty GetMethod(const std::string& name) const: Retrieves a method of _Class.
- template <typename _Ty> _Ty GetAttribute(const std::string& name) const: Retrieves an attribute of _Class.
- bool HasMethod(const std::string& name) const: Checks if _Class has a method.
- bool HasMethod(const hash& key) const: Checks if _Class has a method with a key.
- bool HasAttribute(const std::string& name) const: Checks if _Class has an attribute.
- bool HasAttribute(const hash& key) const: Checks if _Class has an attribute with a key.
- const std::vector<Method<std::any>>& GetMethods() const: Returns the list of methods of _Class.
- const std::vector<Attribute<std::any>>& GetAttributes() const: Returns the list of attributes of _Class.