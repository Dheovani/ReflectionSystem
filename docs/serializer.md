# Documentation for serialize.h

## Namespace reflection_system

### Types and Functions

- template <typename _Ty> constexpr bool is_reflective
Check if _Ty is reflective.

- template <typename _Ty> concept reflective_concept
Concept to verify if _Ty is reflective.

### Class Serializer

Class providing serialization functionalities for reflective classes.

#### Methods:

- template <reflective_concept _Ty> Json::Value ToJson(const Reflective<_Ty>& item) const: Converts a reflective _Ty instance to JSON.
- template <reflective_concept _Ty> YAML::Node ToYaml(const Reflective<_Ty>& item) const: Converts a reflective _Ty instance to YAML.
- template <reflective_concept _Ty> void ToXml(const Reflective<_Ty>& item) const: Converts a reflective _Ty instance to XML.
- template <reflective_concept _Ty> std::string ToString(const Reflective<_Ty>& item) const: Converts a reflective _Ty instance to a string representation.