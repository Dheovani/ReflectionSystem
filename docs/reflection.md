# Documentation for reflection.h

## Macros

- TName(v)
Gets the type name of a variable v using typeid.

- DeclT(t)
Gets the declared type of a member t of the class type.

- Stringify(x)
Converts a token to a string.

- Pair(v)
Creates a pair of a string and a pointer to the member v.

- PAssert(parent)
Static assertion to check if a parent type is a valid class.

- Parents(...)
Macro to validate the parents of a class and provide a method to get their names.

- AAssert(attrib)
Static assertion to check if a member is an attribute.

- Attributes(...)
Macro to define attributes of a class and provide methods to access them.

- MAssert(method)
Static assertion to check if a member is a method.

- Methods(...)
Macro to define methods of a class and provide methods to access them.

- UseReflectionTrait(t, a, m, p)
Macro to define a class with reflection traits, including attributes, methods, and parents.

## Types and Functions

- hash
(8 bytes) Typedef for unsigned long long, used as a hash value for various purposes in the reflection system.

- template <typename _K, typename _V> map
Translates to std::vector<std::pair<_K, _V>>

## Namespace reflection_system

- template <typename _Base, typename _Derived> constexpr bool instance_of
Check if _Derived is an instance of _Base.

- template <typename _Ty> constexpr bool is_attribute
Check if _Ty is a valid attribute type.

- template <typename _Ty> constexpr bool is_function
Check if _Ty is a valid function type.

- template <typename _Ty, typename _Var, size_t _Idx = 0> constexpr size_t get_variant_index
Gets the index of a determined type (_Ty) in a std::variant (_Var) instance

- template <typename _Ty, typename _Var> constexpr bool holds_variant_option
Verifies if a giver std::variant (_Var) instance holds a determined type (_Ty)

- template <typename _Ty, class _Class> struct remove_class_pointer
Removes a class pointer from a given type (_Ty)

- template <typename _Ty, class _Class> struct remove_class_pointer<_Ty _Class::*, _Class>
Specialization of the above struct to remove a class pointer from a given type (_Ty)

- template <class _Ty1, class _Ty2> concept parent_concept
Concept to verify if _Ty1 is a parent class of _Ty2.

- constexpr const std::string Clear(std::string token, const std::vectorstd::string& substrs)
Function that clears substrings from token based on substrs.

- constexpr const std::string Normalize(const std::string& name, const std::string& sign)
Function that normalizes name with sign for consistent formatting.

- constexpr const hash HashCode(const char* key | const std::string& key)
Function that computes a hash code for key.

- template <typename _Ty, typename _Var, size_t _Idx = 0> constexpr size_t GetVariantIndex()
Gets the index of a determined type (_Ty) in a std::variant (_Var) instance

## Member Functions:

- inline static t GetInstance() noexcept
Creates an instance of the class.

- template <typename... Args> inline static t GetInstance(Args... args) noexcept
Creates an instance of the class given a set of args.

- inline static constexpr std::string Classname() noexcept
Returns the name of the classs.

- inline static constexpr size_t Size() noexcept
Returns the size of the class.

- method_types GetMethod(const std::string& name) const
Returns a method class pointer (converted to a std::variant instance) given it's name

- template <typename _Ty> _Ty GetMethod(const std::string& name) const
Returns a method class pointer converted to a given type (_Ty)

- attrib_types GetAttribute(const std::string& name) const
Returns an attribute class pointer (converted to a std::variant instance) given it's name

- template <typename _Ty> _Ty GetAttribute(const std::string& name) const
Returns an attribute class pointer converted to a given type (_Ty)

- inline static reflection::map<std::string, method_types> GetMethods() noexcept
Returns a map (vector of pairs) of the names and pointers to the methods

- inline static reflection::map<std::string, attrib_types> GetAttributes() noexcept
Returns a map (vector of pairs) of the names and pointers to the attributes

- inline static bool HasMethod(const std::string& name) noexcept
Verifies if a class contains a method

- inline static bool HasAttribute(const std::string& name) noexcept
Verifies if a class contains an attribute