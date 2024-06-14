#pragma once

#include <any>
#include <string>
#include <vector>
#include <sstream>
#include <variant>
#include <typeinfo>

#include "for_each.h"

#define ID(v) typeid(v).name()

#define STRINGIFY(v) #v,

#define ASSERTATION(parent) \
	static_assert(std::is_class_v<parent>, #parent " is not a valid class."); \
	static_assert(reflection_system::instance_of<parent, This>, #parent " class is not extended by this class.");

#define PARENT_CLASSES(...) \
private: \
	using Parents = std::variant<__VA_ARGS__>; \
	template <reflection_system::parent_concept<This> _Ty> auto GetParent() const noexcept { return std::get<_Ty>(this); } \
protected: \
	inline void __classSpecificAssertations() const noexcept(false) override { FOR_EACH(ASSERTATION, __VA_ARGS__) } \
	inline const std::vector<std::string> GetParentNames() const noexcept(true) override { return { FOR_EACH(STRINGIFY, __VA_ARGS__) }; }

#define MEMBER_LIST_BEGIN \
	void FillMemberList() const noexcept(true) override {

#define ATTRIBUTE(attrib) \
{ \
	static_assert(reflection_system::is_attribute<decltype(&This::attrib)>, "Not an attribute."); \
	std::string name = #attrib; \
	name.erase(name.begin(), std::find_if(name.begin(), name.end(), [](int ch) { \
		return !std::isspace(ch) && (char)ch != '&'; \
	})); \
	AddAttribute(reflection_system::HashCode(name.c_str()), reflection_system::Normalize(name, ID(&This::attrib)), &This::attrib); \
}

#define METHOD(method) \
{ \
	static_assert(reflection_system::is_method<decltype(&This::method)>, "Not a method."); \
	std::string name = #method; \
	name.erase(name.begin(), std::find_if(name.begin(), name.end(), [](int ch) { \
		return !std::isspace(ch) && (char)ch != '&'; \
	})); \
	AddMethod(reflection_system::HashCode(name.c_str()), reflection_system::Normalize(name, ID(&This::method)), &This::method); \
}

#define MEMBER_LIST_END \
	}

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
		const _Ty value;

		Method(const hash& k, const std::string& s, const _Ty& v)
			: key(k), sign(s), value(v)
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
		const _Ty value;

		Attribute(const hash& k, const std::string& n, const _Ty& v)
			: key(k), name(n), value(v)
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
	constexpr bool is_attribute = std::is_member_object_pointer_v<_Ty>;

	template <typename _Ty>
	constexpr bool is_method = std::is_member_function_pointer_v<_Ty>;

	template <typename _Ty>
	constexpr bool is_reflective = instance_of<Reflective<_Ty>, _Ty>;

	template<class _Ty1, class _Ty2>
	concept parent_concept = instance_of<_Ty2, _Ty1>;

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
		Reflective() { __classSpecificAssertations(); }

		virtual inline const std::vector<std::string> GetParentNames() const noexcept(true) { return {}; }

		virtual inline void __classSpecificAssertations() const noexcept(false) {}

		virtual void FillMemberList() const noexcept(true) {}

	public:
		~Reflective() = default;

		operator const char* () const {
			if (GetMethods().empty() || GetAttributes().empty())
				FillMemberList();
			
			std::stringstream ss;
			ss << GetClassname(true);

			auto parents = GetParentNames();
			for (size_t i = 0; i < parents.size(); ++i)
				ss << (i == 0 ? " : " : "") << parents[i] << (i + 1 < parents.size() ? ", " : "");

			ss << std::endl << "{\n\tSize: " << size << std::endl << "Attributes:" << std::endl;
			for (const Attribute<std::any>& attr : attributes)
				ss << "\t" << attr.name << std::endl;

			ss << "Methods:" << std::endl;
			for (const Method<std::any>& method : methods)
				ss << "\t" << method.sign << std::endl;

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
		inline void AddMethod(const hash& key, const std::string& sign, const _Ty& value) const noexcept
		{
			if (HasMethod(key))
				return;

			methods.push_back(Method<std::any>{ key, sign, std::make_any<_Ty>(value) });
		}

		template <typename _Ty>
		inline void AddAttribute(const hash& key, const std::string& name, const _Ty& value) const noexcept
		{
			if (HasAttribute(key))
				return;

			attributes.push_back(Attribute<std::any>{ key, name, std::make_any<_Ty>(value) });
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