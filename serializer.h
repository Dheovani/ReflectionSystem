#pragma once

#include <fstream>
#include <iostream>
#include <tinyxml2.h>
#include <json/json.h>
#include <yaml-cpp/yaml.h>

#include "reflection.h"

namespace reflection
{
	template <typename _Ty>
	struct has_serializable_methods {
	private:
		template <typename> static std::false_type size(...);
		template <typename> static std::false_type name(...);
		template <typename> static std::false_type parents(...);
		template <typename> static std::false_type methods(...);
		template <typename> static std::false_type attributes(...);
		template <typename _Cl> static auto size(int) -> decltype(_Cl::Size(), std::true_type());
		template <typename _Cl> static auto name(int) -> decltype(_Cl::Classname(), std::true_type());
		template <typename _Cl> static auto parents(int) -> decltype(_Cl::GetParents(), std::true_type());
		template <typename _Cl> static auto methods(int) -> decltype(_Cl::GetMethods(), std::true_type());
		template <typename _Cl> static auto attributes(int) -> decltype(_Cl::GetAttributes(), std::true_type());
	public:
		static constexpr bool value = decltype(size<_Ty>(0))::value &&
									  decltype(name<_Ty>(0))::value &&
									  decltype(parents<_Ty>(0))::value &&
									  decltype(methods<_Ty>(0))::value &&
									  decltype(attributes<_Ty>(0))::value;
	};

	template <class _Ty>
	constexpr bool is_serializable = has_serializable_methods<_Ty>::value;

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