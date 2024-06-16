#include <string>
#include <gtest/gtest.h>

#include "logger.h"
#include "logger.cpp"
#include "serializer.h"
#include "reflection_system.h"

class ReflectionSystemTest : public ::testing::Test {
public:
    class TestClass : public reflection_system::Reflective<TestClass> {
    public:
        int attr1 = 0;
        static const int attr2;

        TestClass() = default;

        TestClass(int attr) : attr1(attr) {}
        
        void method1() { attr1 = 1; }
        int method2() { return attr1; }

        METHODS(method1, method2)
    };

    void SetUp() override {
        obj = new TestClass();
    }

    void TearDown() override {
        delete obj;
    }

    TestClass* obj;
};

const int ReflectionSystemTest::TestClass::attr2 = 42;

// Reflective class' function tests
TEST_F(ReflectionSystemTest, GetInstanceDefault)
{
    TestClass instance = obj->GetInstance();
    EXPECT_EQ(instance.attr1, 0);
}

TEST_F(ReflectionSystemTest, GetInstanceWithParams)
{
    TestClass instance = obj->GetInstance(5);
    EXPECT_EQ(instance.attr1, 5);
}

TEST_F(ReflectionSystemTest, GetClassname)
{
    EXPECT_EQ(obj->GetClassname(), "TestClass");
}

TEST_F(ReflectionSystemTest, GetSize)
{
    EXPECT_EQ(obj->GetSize(), sizeof(TestClass));
}

TEST_F(ReflectionSystemTest, AddMethodAndGetMethod)
{
    obj->AddMethod(reflection_system::HashCode("method1"), "void method1()", false, &TestClass::method1);
    auto method = obj->GetMethod<void(TestClass::*)()>("method1");
    EXPECT_NO_THROW((obj->*method)());
}

TEST_F(ReflectionSystemTest, AddAttributeAndGetAttribute)
{
    obj->AddAttribute(reflection_system::HashCode("attr1"), "int attr1", false, &TestClass::attr1);
    auto attr = obj->GetAttribute<int>("attr1");
    EXPECT_EQ(attr, 0);
}

TEST_F(ReflectionSystemTest, HasMethod)
{
    EXPECT_FALSE(obj->HasMethod("method1"));
    obj->AddMethod(reflection_system::HashCode("method1"), "void method1()", false, &TestClass::method1);
    EXPECT_TRUE(obj->HasMethod("method1"));
}

TEST_F(ReflectionSystemTest, HasAttribute)
{
    EXPECT_FALSE(obj->HasAttribute("attr1"));
    obj->AddAttribute(reflection_system::HashCode("attr1"), "int attr1", false, &TestClass::attr1);
    EXPECT_TRUE(obj->HasAttribute("attr1"));
}

TEST_F(ReflectionSystemTest, GetMethods)
{
    obj->AddMethod(reflection_system::HashCode("method1"), "void method1()", false, &TestClass::method1);
    auto methods = obj->GetMethods();
    EXPECT_EQ(methods.size(), 1);
}

TEST_F(ReflectionSystemTest, GetAttributes)
{
    obj->AddAttribute(reflection_system::HashCode("attr1"), "int attr1", false, &TestClass::attr1);
    auto attributes = obj->GetAttributes();
    EXPECT_EQ(attributes.size(), 1);
}

// namespace reflection_system's tests
TEST(ReflectionSystemFunctions, Clear)
{
    std::string token = "example __ptr64";
    std::vector<std::string> substrs = { "__ptr64" };
    EXPECT_EQ(reflection_system::Clear(token, substrs), "example ");
}

TEST(ReflectionSystemFunctions, Normalize)
{
    std::string name = "example";
    std::string sign = "void example() __cdecl";
    EXPECT_EQ(reflection_system::Normalize(name, sign), "example: void example()");
}

TEST(ReflectionSystemFunctions, HashCode)
{
    const char* key = "example";
    EXPECT_EQ(reflection_system::HashCode(key), 738883317383ULL);
}

TEST(ReflectionSystemFunctions, is_function)
{
    EXPECT_TRUE(reflection_system::is_function<decltype(&ReflectionSystemTest::TestClass::method1)>);
}

TEST(ReflectionSystemFunctions, is_attribute)
{
    EXPECT_TRUE(reflection_system::is_attribute<decltype(&ReflectionSystemTest::TestClass::attr2)>);
}

TEST_F(ReflectionSystemTest, ToJson)
{
    TestClass mock;
    reflection_system::Serializer serializer;
    Json::Value json = serializer.ToJson(mock);

    EXPECT_EQ(json["name"].asString(), "TestClass");
    EXPECT_EQ(json["size"].asInt(), sizeof(TestClass));
    EXPECT_EQ(json["parents"].size(), 1);
    EXPECT_EQ(json["attributes"].size(), 2);
    EXPECT_EQ(json["methods"].size(), 2);
}

TEST_F(ReflectionSystemTest, ToYaml)
{
    TestClass mock;
    reflection_system::Serializer serializer;
    YAML::Node yaml = serializer.ToYaml(mock);

    EXPECT_EQ(yaml["name"].as<std::string>(), "TestClass");
    EXPECT_EQ(yaml["size"].as<int>(), sizeof(TestClass));
    EXPECT_EQ(yaml["parents"].size(), 1);
    EXPECT_EQ(yaml["attributes"].size(), 2);
    EXPECT_EQ(yaml["methods"].size(), 2);
}

TEST_F(ReflectionSystemTest, ToString)
{
    TestClass mock;
    reflection_system::Serializer serializer;
    std::string str = serializer.ToString(mock);

    EXPECT_FALSE(str.empty());
    EXPECT_TRUE(str.find("MockReflective") != std::string::npos);
    EXPECT_TRUE(str.find("42") != std::string::npos);
}
