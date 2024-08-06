#include "reflection.h"

using namespace reflection;

constexpr std::string reflection::Clear(std::string token, const std::vector<std::string>& substrs) noexcept
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

constexpr std::string reflection::Normalize(const std::string& name, const std::string& sign) noexcept
{
	std::string token = std::string{ name + ": " + sign };
	std::vector<std::string> substrs = { "__ptr64", "__cdecl" };

	return reflection::Clear(token, substrs);
}

constexpr hash reflection::HashCode(const char* key) noexcept(true)
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

constexpr hash reflection::HashCode(const std::string& key) noexcept(true)
{
	hash value = 0;

	for (uint64_t i = 0; i < key.size(); ++i)
		value = value * 37 + key.at(i);

	return value;
}
