#pragma once

#include <fstream>
#include <iostream>
#include <tinyxml2.h>
#include <json/json.h>
#include <yaml-cpp/yaml.h>

#include "reflection.h"

#define MethodExists(method) \
	template <class _Ty> \
	struct has_##method { \
	private: \
		template<typename U> \
		static auto check(int) -> decltype(U::##method(), std::true_type()); \
		template<typename> static std::false_type check(...); \
	public: \
		static constexpr bool value = decltype(check<_Ty>(0))::value; \
	};


namespace reflection
{
	MethodExists(Classname)

	MethodExists(Size)

	MethodExists(GetParents)

	MethodExists(GetAttributes)

	MethodExists(GetMethods)

	template <class _Ty>
	constexpr bool is_serializable = has_Size<_Ty>::value		&&
									 has_Classname<_Ty>::value  &&
									 has_GetParents<_Ty>::value &&
									 has_GetMethods<_Ty>::value &&
									 has_GetAttributes<_Ty>::value;

	template <class _Ty>
	concept serializable = is_serializable<_Ty>;

	class Serializer
	{
	public:
		template <serializable _Ty>
		Json::Value ToJson() const noexcept(true)
		{
			const std::string filename = std::string{ _Ty::Classname() + ".json" };
			std::fstream fileStream(filename, std::ios::in | std::ios::out | std::ios::trunc);

			Json::StreamWriterBuilder writer;
			Json::Value objectJson;

			objectJson["name"] = _Ty::Classname();
			objectJson["size"] = _Ty::Size();

			for (const std::string& parentName: _Ty::GetParents())
				objectJson["parents"].append(parentName);

			for (const auto& attribute : _Ty::GetAttributes())
				objectJson["attributes"].append(attribute.first);

			for (const auto& method : _Ty::GetMethods())
				objectJson["methods"].append(method.first);

			if (fileStream.is_open())
				fileStream << Json::writeString(writer, objectJson) << std::endl;
			else
				std::cerr << "Failed opening file!";

			return objectJson;
		}

		template <serializable _Ty>
		YAML::Node ToYaml() const noexcept(true)
		{
			const std::string filename = std::string{ _Ty::Classname() + ".yaml" };
			std::fstream fileStream(filename, std::ios::in | std::ios::out | std::ios::trunc);

			YAML::Node objectYaml;
			objectYaml["name"] = _Ty::Classname();
			objectYaml["size"] = _Ty::Size();

			for (const std::string& parentName : _Ty::GetParents())
				objectYaml["parents"].push_back(parentName);

			for (const auto& attribute : _Ty::GetAttributes())
				objectYaml["attributes"].push_back(attribute.first);

			for (const auto& method : _Ty::GetMethods())
				objectYaml["methods"].push_back(method.first);

			if (fileStream.is_open())
				fileStream << objectYaml << std::endl;
			else
				std::cerr << "Failed opening file!";

			return objectYaml;
		}

		template <serializable _Ty>
		std::string ToString() const noexcept(true)
		{
			std::stringstream str;
			str << _Ty::Classname();

			std::vector<std::string> parents = _Ty::GetParents();
			for (size_t i = 0; i < parents.size(); ++i)
				str << (i == 0 ? " : " : "") << parents[i] << (i + 1 < parents.size() ? ", " : "");

			str << std::endl << "{"
				<< std::endl << "\tSize: " << _Ty::Size()
				<< std::endl << "Attributes:"
				<< std::endl;

			for (const auto& attr: _Ty::GetAttributes())
				str << "\t" << attr.first << std::endl;

			str << "Methods:" << std::endl;
			for (const auto& method: _Ty::GetMethods())
				str << "\t" << method.first << std::endl;

			str << "}" << std::endl;
			return std::string{ str.str() };
		}

		template <serializable _Ty>
		void ToXml() const noexcept(true)
		{
			tinyxml2::XMLDocument doc;
			tinyxml2::XMLElement* root = doc.NewElement("item");
			doc.InsertFirstChild(root);

			tinyxml2::XMLElement* nameElement = doc.NewElement("name");
			nameElement->SetText(_Ty::Classname().c_str());
			root->InsertEndChild(nameElement);

			tinyxml2::XMLElement* sizeElement = doc.NewElement("size");
			sizeElement->SetText(_Ty::Size());
			root->InsertEndChild(sizeElement);

			tinyxml2::XMLElement* parentsElement = doc.NewElement("parents");
			for (const std::string& parentName: _Ty::GetParents()) {
				tinyxml2::XMLElement* parentElement = doc.NewElement("parent");
				parentElement->SetText(parentName.c_str());
				parentsElement->InsertEndChild(parentElement);
			}
			root->InsertEndChild(parentsElement);

			tinyxml2::XMLElement* attributesElement = doc.NewElement("attributes");
			for (const auto& attribute: _Ty::GetAttributes()) {
				tinyxml2::XMLElement* attributeElement = doc.NewElement("attribute");
				attributeElement->SetText(attribute.first.c_str());
				attributesElement->InsertEndChild(attributeElement);
			}
			root->InsertEndChild(attributesElement);

			tinyxml2::XMLElement* methodsElement = doc.NewElement("methods");
			for (const auto& method: _Ty::GetMethods()) {
				tinyxml2::XMLElement* methodElement = doc.NewElement("method");
				methodElement->SetText(method.first.c_str());
				methodsElement->InsertEndChild(methodElement);
			}
			root->InsertEndChild(methodsElement);

			const std::string filename = std::string{ _Ty::Classname() + ".xml" };
			doc.SaveFile(filename.c_str());
		}
	};
}