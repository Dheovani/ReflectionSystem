#pragma once

#include <any>
#include <string>
#include <vector>
#include <sstream>
#include <variant>
#include <typeinfo>

#include "for_each.h"

#define ID(v) typeid(v).name()

#define ASSERTATION(parent) \
	static_assert(std::is_class_v<parent>, #parent " is not a valid class."); \
	static_assert(reflection_system::instance_of<parent, This>, #parent " class is not extended by this class.");

#define PARENT_CLASSES(...) \
protected: \
	using Parents = std::variant<__VA_ARGS__>; \
	inline void __class_specific_assertations__() const noexcept(false) override { FOR_EACH(ASSERTATION, __VA_ARGS__) } \
	inline const std::vector<std::string> GetParentNames() const noexcept(true) override { return { FOR_EACH(STRINGIFY, __VA_ARGS__) }; }\
public: \
	template <reflection_system::parent_concept<This> _Ty> auto GetParent() const noexcept { \
		Parents parents = _Ty{}; \
		return std::get<_Ty>(parents); \
	}

#define ATTRIBUTE(attrib) \
{ \
	static_assert(reflection_system::is_attribute<decltype(&This::attrib)>, #attrib " is not an attribute."); \
	std::string name = #attrib; \
	name.erase(name.begin(), std::find_if(name.begin(), name.end(), [](int ch) { return !std::isspace(ch) && (char)ch != '&'; })); \
	AddAttribute(reflection_system::HashCode(name.c_str()), reflection_system::Normalize(name, ID(&This::attrib)), \
		!std::is_member_pointer_v<decltype(&This::attrib)>, &This::attrib); \
}

#define ATTRIBUTES(...) \
protected: void FillMethodList() const noexcept override { FOR_EACH(ATTRIBUTE, __VA_ARGS__) } \
public: \
	template <typename _Ty> _Ty GetAttribute(const std::string& name) const noexcept(false) { \
		if (GetAttributes().empty()) FillAttribList(); \
		const hash key = reflection_system::HashCode(name.c_str()); \
		for (const auto& attrib : GetAttributes()) { \
			if (attrib.key == key) { \
				if (attrib.isStatic) return *(std::any_cast<_Ty*>(attrib.value)); \
				else return this->*(std::any_cast<_Ty This::*>(attrib.value)); \
			} \
		} \
		throw std::runtime_error("Attribute not found"); \
	}

#define METHOD(method) \
{ \
	static_assert(reflection_system::is_function<decltype(&This::method)>, #method " is not a function."); \
	std::string name = #method; \
	name.erase(name.begin(), std::find_if(name.begin(), name.end(), [](int ch) { return !std::isspace(ch) && (char)ch != '&'; })); \
	AddMethod(reflection_system::HashCode(name.c_str()), reflection_system::Normalize(name, ID(&This::method)), \
		!std::is_member_pointer_v<decltype(&This::method)>, &This::method); \
}

#define METHODS(...) \
protected: \
	void FillAttribList() const noexcept override { FOR_EACH(METHOD, __VA_ARGS__) }

typedef unsigned long long hash;

namespace reflection_system
{
	class Serializer; // See serializer.h

	template <typename>
	class Reflective;

	template <typename _Ty>
	struct Method
	{
		const hash key;
		const std::string sign;
		const bool isStatic;
		const _Ty value;

		Method(const hash& k, const std::string& s, const bool& st, const _Ty& v)
			: key(k), sign(s), isStatic(st), value(v)
		{}

		bool operator==(const Method& other) const
		{
			return key == other.key;
		}

		bool operator==(const hash& key) const
		{
			return this->key == key;
		}
	};

	template <typename _Ty>
	struct Attribute
	{
		const hash key;
		const std::string name;
		const bool isStatic;
		const _Ty value;

		Attribute(const hash& k, const std::string& n, const bool& st, const _Ty& v)
			: key(k), name(n), isStatic(st), value(v)
		{}

		bool operator==(const Attribute& other) const
		{
			return key == other.key;
		}

		bool operator==(const hash& key) const
		{
			return this->key == key;
		}
	};

	template <typename _Base, typename _Derived>
	constexpr bool instance_of = std::is_base_of_v<_Base, std::remove_pointer_t<_Derived>>;

	template <typename _Ty>
	constexpr bool is_attribute = std::is_member_object_pointer_v<_Ty> || std::is_object_v<std::remove_pointer_t<_Ty>>;

	template <typename _Ty>
	constexpr bool is_function = std::is_member_function_pointer_v<_Ty> || std::is_function_v<std::remove_pointer_t<_Ty>>;

	template<class _Ty1, class _Ty2>
	concept parent_concept = instance_of<_Ty1, _Ty2>;

	constexpr const std::string Clear(std::string token, const std::vector<std::string>& substrs) noexcept
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

	constexpr const std::string Normalize(const std::string& name, const std::string& sign) noexcept
	{
		std::string token = std::string{ name + ": " + sign };
		std::vector<std::string> substrs = { "__ptr64", "__cdecl" };

		return Clear(token, substrs);
	}

	constexpr const hash HashCode(const char* key) noexcept(true)
	{
		hash value = 0;
		size_t len = 0;
		while (key[len] != '\0')
			++len;

		for (unsigned int i = 0; i < len; i++) {
			value = value * 37 + key[i];
		}

		return value;
	}

	template <typename _Class>
	class Reflective
	{
		const size_t size = sizeof(_Class);
		const std::string classname = ID(_Class);

		mutable std::string cache;
		mutable std::vector<Method<std::any>> methods = {};
		mutable std::vector<Attribute<std::any>> attributes = {};

	protected:
		Reflective() { __class_specific_assertations__(); }

		virtual inline const std::vector<std::string> GetParentNames() const noexcept(true) { return {}; }
		virtual inline void __class_specific_assertations__() const noexcept(false) {}
		virtual void FillAttribList() const noexcept {}
		virtual void FillMethodList() const noexcept {}

	public:
		~Reflective() = default;

		operator const char* () const
		{
			if (GetMethods().empty() || GetAttributes().empty()) {
				FillAttribList();
				FillMethodList();
			}
			
			std::stringstream ss;
			ss << GetClassname(true);

			auto parents = GetParentNames();
			for (size_t i = 0; i < parents.size(); ++i)
				ss << (i == 0 ? " : " : "") << parents[i] << (i + 1 < parents.size() ? ", " : "");

			ss << std::endl << "{\n\tSize: " << size << std::endl << "Attributes:" << std::endl;
			for (const Attribute<std::any>& attr : attributes)
				ss << "\t" << (attr.isStatic ? "static " : "") << attr.name << std::endl;

			ss << "Methods:" << std::endl;
			for (const Method<std::any>& method : methods)
				ss << "\t" << (method.isStatic ? "static " : "") << method.sign << std::endl;

			ss << "}" << std::endl;
			return (cache = ss.str()).c_str();
		}

		template <typename... Args>
		inline _Class GetInstance(Args... args) const noexcept(true) { return _Class(args...); }

		inline _Class GetInstance(void) const noexcept(true) { return _Class(); }

		constexpr std::string GetClassname(bool ignoreType = false) const noexcept
		{
			std::string cname = classname;
			const std::string substrs[] = { "class", "struct" };

			if (ignoreType)
				return cname;

			for (const std::string& substr : substrs) {
				size_t pos = cname.find(substr);
				size_t length = substr.length();

				if (cname.length() > pos + length && std::isspace(cname.at(pos + length)))
					++length;

				while (pos != std::string::npos) {
					cname.erase(pos, length);
					pos = cname.find(substr);
				}
			}

			return cname;
		}

		inline constexpr size_t GetSize() const noexcept(true) { return size; }

		template <typename _Ty>
		inline void AddMethod(const hash& key, const std::string& sign, const bool& isStatic, const _Ty& value) const noexcept
		{
			if (HasMethod(key))
				return;

			methods.push_back(Method<std::any>{ key, sign, isStatic, std::make_any<_Ty>(value) });
		}

		template <typename _Ty>
		inline void AddAttribute(const hash& key, const std::string& name, const bool& isStatic, const _Ty& value) const noexcept
		{
			if (HasAttribute(key))
				return;

			attributes.push_back(Attribute<std::any>{ key, name, isStatic, std::make_any<_Ty>(value) });
		}

		template <typename _Ty>
		_Ty GetMethod(const std::string& name) const noexcept(false)
		{
			if (GetMethods().empty()) FillMethodList();

			const hash key = HashCode(name.c_str());
			for (const auto& method : GetMethods()) {
				if (method.key == key) return std::any_cast<_Ty>(method.value);
			}

			throw std::runtime_error("Method not found");
		}

		inline constexpr bool HasMethod(const std::string& name) const noexcept
		{
			const hash methodHash = HashCode(name.c_str());
			return std::find(methods.begin(), methods.end(), methodHash) != methods.end();
		}

		inline constexpr bool HasMethod(const hash& key) const noexcept
		{
			return std::find(methods.begin(), methods.end(), key) != methods.end();
		}

		inline constexpr bool HasAttribute(const std::string& name) const noexcept
		{
			const hash attrHash = HashCode(name.c_str());
			return std::find(attributes.begin(), attributes.end(), attrHash) != attributes.end();
		}

		inline constexpr bool HasAttribute(const hash& key) const noexcept
		{
			return std::find(attributes.begin(), attributes.end(), key) != attributes.end();
		}

		inline const std::vector<Method<std::any>>& GetMethods() const noexcept(true) { return methods; }

		inline const std::vector<Attribute<std::any>>& GetAttributes() const noexcept(true) { return attributes; }

	protected:
		using This = _Class;

		friend class Serializer;
	};
}