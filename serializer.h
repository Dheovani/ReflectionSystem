#pragma once

#include <fstream>
#include <tinyxml2.h>
#include <json/json.h>
#include <yaml-cpp/yaml.h>

#include "logger.h"
#include "reflection_system.h"

namespace reflection_system
{
	template <typename _Ty>
	constexpr bool is_reflective = instance_of<Reflective<_Ty>, _Ty>;

	template <typename _Ty>
	concept reflective_concept = is_reflective<_Ty>;

	class Serializer
	{
	public:
		template <reflective_concept _Ty>
		Json::Value ToJson(const Reflective<_Ty>& item) const noexcept(true)
		{
			const std::string filename = std::string{ item.GetClassname() + ".json" };
			std::fstream fileStream(filename, std::ios::in | std::ios::out | std::ios::trunc);

			Json::StreamWriterBuilder writer;
			Json::Value objectJson;
			objectJson["name"] = item.GetClassname();
			objectJson["size"] = item.GetSize();

			for (const auto& parentName : item.GetParentNames())
				objectJson["parents"].append(parentName);

			for (const auto& attribute : item.GetAttributes())
				objectJson["attributes"].append(std::string{ (attribute.isStatic ? "static " : "") + attribute.name });

			for (const auto& method : item.GetMethods())
				objectJson["methods"].append(std::string{ (method.isStatic ? "static " : "") + method.sign });

			if (fileStream.is_open())
				fileStream << Json::writeString(writer, objectJson) << std::endl;
			else
				LOGGER << "Failed opening file!";

			return objectJson;
		}

		template <reflective_concept _Ty>
		YAML::Node ToYaml(const Reflective<_Ty>& item) const noexcept(true)
		{
			const std::string filename = std::string{ item.GetClassname() + ".yaml" };
			std::fstream fileStream(filename, std::ios::in | std::ios::out | std::ios::trunc);

			YAML::Node objectYaml;
			objectYaml["name"] = item.GetClassname();
			objectYaml["size"] = item.GetSize();

			for (const auto& parentName : item.GetParentNames())
				objectYaml["parents"].push_back(parentName);

			for (const auto& attribute : item.GetAttributes())
				objectYaml["attributes"].push_back(std::string{ (attribute.isStatic ? "static " : "") + attribute.name });

			for (const auto& method : item.GetMethods())
				objectYaml["methods"].push_back(std::string{ (method.isStatic ? "static " : "") + method.sign });

			if (fileStream.is_open())
				fileStream << objectYaml << std::endl;
			else
				LOGGER << "Failed opening file!";

			return objectYaml;
		}

		template <reflective_concept _Ty>
		void ToXml(const Reflective<_Ty>& item) const noexcept(true)
		{
			tinyxml2::XMLDocument doc;
			tinyxml2::XMLElement* root = doc.NewElement("item");
			doc.InsertFirstChild(root);

			tinyxml2::XMLElement* nameElement = doc.NewElement("name");
			nameElement->SetText(item.GetClassname().c_str());
			root->InsertEndChild(nameElement);

			tinyxml2::XMLElement* sizeElement = doc.NewElement("size");
			sizeElement->SetText(item.GetSize());
			root->InsertEndChild(sizeElement);

			tinyxml2::XMLElement* parentsElement = doc.NewElement("parents");
			for (const auto& parentName : item.GetParentNames()) {
				tinyxml2::XMLElement* parentElement = doc.NewElement("parent");
				parentElement->SetText(parentName.c_str());
				parentsElement->InsertEndChild(parentElement);
			}
			root->InsertEndChild(parentsElement);

			tinyxml2::XMLElement* attributesElement = doc.NewElement("attributes");
			for (const auto& attribute : item.GetAttributes()) {
				tinyxml2::XMLElement* attributeElement = doc.NewElement("attribute");
				attributeElement->SetText(std::string{ (attribute.isStatic ? "static " : "") + attribute.name });
				attributesElement->InsertEndChild(attributeElement);
			}
			root->InsertEndChild(attributesElement);

			tinyxml2::XMLElement* methodsElement = doc.NewElement("methods");
			for (const auto& method : item.GetMethods()) {
				tinyxml2::XMLElement* methodElement = doc.NewElement("method");
				methodElement->SetText(std::string{ (method.isStatic ? "static " : "") + method.name });
				methodsElement->InsertEndChild(methodElement);
			}
			root->InsertEndChild(methodsElement);

			const std::string filename = std::string{ item.GetClassname() + ".xml" };
			doc.SaveFile(filename.c_str());
		}

		template <reflective_concept _Ty>
		std::string ToString(const Reflective<_Ty>& item) const noexcept(true)
		{
			return std::string{ (const char*)item };
		}
	};
}