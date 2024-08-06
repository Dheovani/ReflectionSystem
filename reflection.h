#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <variant>
#include <typeinfo>
#include <algorithm>

#include "for_each.h"

#define TName(v) typeid(v).name()

#define DeclT(t) decltype(&type::t)

#define Stringify(x) #x

#define Pair(v) { #v, &type::v }

#define PAssert(parent) \
	static_assert(std::is_class_v<parent>, #parent " is not a valid class.");

#define Parents(...) ForEach(PAssert, __VA_ARGS__)

#define AAssert(attrib) \
	static_assert(reflection::is_attribute<decltype(&type::attrib)>, #attrib " is not an attribute.");

#define Attributes(...) \
	ForEach(AAssert, __VA_ARGS__) \
	using attrib_types = std::variant<ForEachWS(DeclT, __VA_ARGS__)>; \
public: \
	attrib_types GetAttribute(const std::string& name) const { \
		for (const auto& pair : GetAttributes()) { if (pair.first == name) return pair.second; } \
		throw std::runtime_error("Attribute not found"); } \
	inline static reflection::map<std::string, attrib_types> GetAttributes() noexcept { \
		return reflection::map<std::string, attrib_types>{ ForEachWS(Pair, __VA_ARGS__) }; } \
	inline static bool HasAttribute(const std::string& name) noexcept { \
		const reflection::map<std::string, attrib_types> attrs = GetAttributes(); \
		return std::find_if(attrs.begin(), attrs.end(), [&name](const auto& elm) { return elm.first == name; }) != attrs.end(); }

#define MAssert(method) \
	static_assert(reflection::is_function<decltype(&type::method)>, #method " is not a function.");

#define Methods(...) \
	ForEach(MAssert, __VA_ARGS__) \
	using method_types = std::variant<ForEachWS(DeclT, __VA_ARGS__)>; \
public: \
	method_types GetMethod(const std::string& name) const { \
		for (const auto& pair : GetMethods()) { if (pair.first == name) return pair.second; } \
		throw std::runtime_error("Method not found"); } \
	inline static reflection::map<std::string, method_types> GetMethods() noexcept { \
		return reflection::map<std::string, method_types>{ ForEachWS(Pair, __VA_ARGS__) }; } \
	inline static bool HasMethod(const std::string& name) noexcept { \
		const reflection::map<std::string, method_types> meths = GetMethods(); \
		return std::find_if(meths.begin(), meths.end(), [&name](const auto& elm) { return elm.first == name; }) != meths.end(); }

#define UseReflectionTrait(t, a, m, p) \
	using type = t; a m p \
public: \
	inline static t GetInstance() noexcept { return t(); } \
	template <typename... Args> \
	inline static t GetInstance(Args... args) noexcept { return t(args...); } \
	inline static constexpr size_t Size() noexcept { return sizeof(t); } \
	inline static constexpr std::string Classname() noexcept { return reflection::Clear(TName(t), { "class", "struct" }); }

namespace reflection
{
	typedef unsigned long long hash;

	template <typename _K, typename _V>
	using map = std::vector<std::pair<_K, _V>>;

	template <typename _Base, typename _Derived>
	constexpr bool instance_of = std::is_base_of_v<_Base, std::remove_pointer_t<_Derived>>;

	template <typename _Ty>
	constexpr bool is_attribute = std::is_member_object_pointer_v<_Ty> || std::is_object_v<std::remove_pointer_t<_Ty>>;

	template <typename _Ty>
	constexpr bool is_function = std::is_member_function_pointer_v<_Ty> || std::is_function_v<std::remove_pointer_t<_Ty>>;

	template <typename _Var, typename _Ty, size_t _Idx>
	struct variant_index;

	template <typename _Var, typename _Ty, size_t _Idx = 0>
	struct variant_index {
		static_assert(_Idx < std::variant_size_v<_Var>, "Unknown variant type");
		static constexpr size_t value = std::is_same_v<std::variant_alternative_t<_Idx, _Var>, _Ty>
			? _Idx
			: variant_index<_Var, _Ty, _Idx + 1>::value;
	};

	template <typename _Var, typename _Ty, size_t _Idx = 0>
	constexpr size_t variant_index_v = variant_index<_Var, _Ty, _Idx>::value;

	template <typename _Ty, class _Class>
	struct remove_class_pointer {
		using type = _Ty;
	};

	template <typename _Ty, class _Class>
	struct remove_class_pointer<_Ty _Class::*, _Class> {
		using type = _Ty;
	};

	template <typename _Ty, class _Class>
	using remove_class_pointer_t = typename remove_class_pointer<_Ty, _Class>::type;

	template <class _Ty1, class _Ty2>
	concept parent_concept = instance_of<_Ty1, _Ty2>;

	constexpr std::string Clear(std::string token, const std::vector<std::string>& substrs) noexcept;

	constexpr std::string Normalize(const std::string& name, const std::string& sign) noexcept;

	constexpr hash HashCode(const char* key) noexcept(true);

	constexpr hash HashCode(const std::string& key) noexcept(true);
}