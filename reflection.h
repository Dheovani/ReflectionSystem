#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <variant>
#include <typeinfo>
#include <algorithm>

#include "utils.h"

#define PAssert(parent) \
	static_assert(std::is_class_v<parent>, #parent " is not a valid class.");

#define AAssert(attrib) \
	static_assert(reflection::is_attribute<decltype(&type::attrib)>, #attrib " is not an attribute.");

#define MAssert(method) \
	static_assert(reflection::is_function<decltype(&type::method)>, #method " is not a function.");

#define Parents(...) ForEach(PAssert, __VA_ARGS__) \
	inline static std::vector<std::string> GetParents() noexcept { return { ForEachWS(Stringify, __VA_ARGS__) }; }

#define Attributes(...) ForEach(AAssert, __VA_ARGS__) \
	using attrib_types = std::variant<ForEachWS(DeclT, __VA_ARGS__)>; \
	attrib_types GetAttribute(const std::string& name) const { \
		for (const auto& pair : GetAttributes()) { if (pair.first == name) return pair.second; } \
		throw std::runtime_error("Attribute not found"); } \
	template <typename _Ty> _Ty GetAttribute(const std::string& name) const { return std::get<_Ty>(this->GetAttribute(name)); } \
	inline static reflection::map<std::string, attrib_types> GetAttributes() noexcept { return { ForEachWS(Pair, __VA_ARGS__) }; } \
	inline static bool HasAttribute(const std::string& name) noexcept { \
		const reflection::map<std::string, attrib_types> attrs = GetAttributes(); \
		return std::find_if(attrs.begin(), attrs.end(), [&name](const auto& elm) { return elm.first == name; }) != attrs.end(); }

#define Methods(...) ForEach(MAssert, __VA_ARGS__) \
	using method_types = std::variant<ForEachWS(DeclT, __VA_ARGS__)>; \
	method_types GetMethod(const std::string& name) const { \
		for (const auto& pair : GetMethods()) { if (pair.first == name) return pair.second; } \
		throw std::runtime_error("Method not found"); } \
	template <typename _Ty> _Ty GetMethod(const std::string& name) const { return std::get<_Ty>(this->GetMethod(name)); } \
	inline static reflection::map<std::string, method_types> GetMethods() noexcept { return { ForEachWS(Pair, __VA_ARGS__) }; } \
	inline static bool HasMethod(const std::string& name) noexcept { \
		const reflection::map<std::string, method_types> meths = GetMethods(); \
		return std::find_if(meths.begin(), meths.end(), [&name](const auto& elm) { return elm.first == name; }) != meths.end(); }

#define UseReflectionTrait(t, a, m, p) \
public: using type = t; a m p \
	inline static t GetInstance() noexcept { return t(); } \
	template <typename... Args> inline static t GetInstance(Args... args) noexcept { return t(args...); } \
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
	constexpr bool is_function = std::is_member_function_pointer_v<_Ty> || std::is_function_v<std::remove_pointer_t<_Ty>>;

	template <typename _Ty>
	constexpr bool is_attribute = !is_function<_Ty> && (std::is_member_object_pointer_v<_Ty> || std::is_object_v<std::remove_pointer_t<_Ty>>);

	template <typename, typename, size_t> constexpr size_t GetVariantIndex();

	template <typename _Ty, typename _Var, size_t _Idx = 0>
	constexpr size_t get_variant_index = GetVariantIndex<_Ty, _Var, _Idx + 1>();

	template <typename _Ty, typename _Var>
	constexpr bool holds_variant_option = get_variant_index<_Ty, _Var> != std::variant_npos;

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

	template <typename _Base, typename _Derived>
	concept parent_concept = instance_of<_Base, _Derived>;

	constexpr std::string Clear(std::string token, const std::vector<std::string>& substrs) noexcept
	{
		for (const std::string& substr : substrs) {
			size_t pos = token.find(substr);
			size_t length = substr.length();

			// Delete whitespaces
			if (token.length() > pos + length && std::isspace(token.at(pos + length)))
				++length;

			while (pos != std::string::npos) {
				token.erase(pos, length);
				pos = token.find(substr);
			}
		}

		return token;
	}

	constexpr std::string Normalize(const std::string& name, const std::string& sign) noexcept
	{
		std::string token = std::string{ name + ": " + sign };
		std::vector<std::string> substrs = { "__ptr64", "__cdecl" };

		return reflection::Clear(token, substrs);
	}

	constexpr hash HashCode(const char* key) noexcept(true)
	{
		hash value = 0;
		size_t len = 0;
		while (key[len] != '\0')
			++len;

		for (uint64_t i = 0; i < len; ++i) {
			value = value * 37 + key[i];
		}

		return value;
	}

	constexpr hash HashCode(const std::string& key) noexcept(true)
	{
		hash value = 0;

		for (uint64_t i = 0; i < key.size(); ++i)
			value = value * 37 + key.at(i);

		return value;
	}

	template <typename _Ty, typename _Var, size_t _Idx = 0>
	constexpr size_t GetVariantIndex()
	{
		if constexpr (_Idx >= std::variant_size_v<_Var>)
			return std::variant_npos;
		else if constexpr (std::is_same_v<std::variant_alternative_t<_Idx, _Var>, _Ty>)
			return _Idx;
		else
			return reflection::GetVariantIndex<_Ty, _Var, _Idx + 1>();
	}
}