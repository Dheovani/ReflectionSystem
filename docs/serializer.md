# Documentation for serializer.h

## Namespace reflection

### Types and Functions

- template <class _Ty> struct has_Size
Verifies if a _Ty class contains the "Size" method

- template <class _Ty> struct has_Classname
Verifies if a _Ty class contains the "Classname" method

- template <class _Ty> struct has_GetParents
Verifies if a _Ty class contains the "GetParents" method

- template <class _Ty> struct has_GetMethods
Verifies if a _Ty class contains the "GetMethods" method

- template <class _Ty> struct has_GetAttributes
Verifies if a _Ty class contains the "GetAttributes" method

- template <class _Ty> constexpr bool is_serializable
Check if _Ty is a valid class for serialization.

- template <class _Ty> concept serializable
Concept to verify if _Ty is serializable.

### Class Serializer

Class providing serialization functionalities for reflective classes.

#### Methods:

- template <serializable _Ty> Json::Value ToJson() const noexcept(true)
Converts a reflective _Ty instance to JSON.

- template <serializable _Ty> YAML::Node ToYaml() const noexcept(true)
Converts a reflective _Ty instance to YAML.

- template <serializable _Ty> void ToXml() const noexcept(true)
Converts a reflective _Ty instance to XML.

- template <serializable _Ty> std::string ToString() const noexcept(true)
Converts a reflective _Ty instance to a string representation.