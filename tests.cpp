#include <string>
#include <variant>
#include "reflection.h"
#include "serializer.h"
#include <gtest/gtest.h>

class ReflectionSystemTest: public ::testing::Test
{
public:
    class Base
    {
        int baseAttr = 5;

    public:
        int getAttr() { return baseAttr; }
    };

    class TestClass: public Base
    {
    public:
        int attr1 = 0;
        static const int attr2;

        TestClass() = default;

        TestClass(int attr) : attr1(attr) {}
        
        void method1() { attr1 = 1; }
        int method2() { return attr1; }

        UseReflectionTrait
        (
            TestClass,
            Attributes(attr1, attr2),
            Methods(method1, method2),
            Parents(Base)
        )
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

// class methods' tests
TEST_F(ReflectionSystemTest, GetInstanceDefault)
{
    TestClass instance = TestClass::GetInstance();
    EXPECT_EQ(instance.attr1, 0);
}

TEST_F(ReflectionSystemTest, GetInstanceWithParams)
{
    TestClass instance = TestClass::GetInstance(5);
    EXPECT_EQ(instance.attr1, 5);
}

TEST_F(ReflectionSystemTest, Classname)
{
    EXPECT_EQ(TestClass::Classname(), "ReflectionSystemTest::TestClass");
}

TEST_F(ReflectionSystemTest, Size)
{
    EXPECT_EQ(TestClass::Size(), sizeof(TestClass));
}

TEST_F(ReflectionSystemTest, GetMethod)
{
    auto method2 = std::get<int(TestClass::*)()>(obj->GetMethod("method2"));
    EXPECT_EQ((obj->*method2)(), 0);

    auto method1 = obj->GetMethod<void(TestClass::*)()>("method1");
    EXPECT_NO_THROW((obj->*method1)());
    EXPECT_EQ((obj->*method2)(), 1);
}

TEST_F(ReflectionSystemTest, GetAttribute)
{
    auto attr = std::get<int TestClass::*>(obj->GetAttribute("attr1"));
    EXPECT_EQ(obj->*attr, 0);
    
    obj->attr1 = 5;
    EXPECT_EQ(obj->*(obj->GetAttribute<int TestClass::*>("attr1")), 5);
}

TEST_F(ReflectionSystemTest, HasMethod)
{
    EXPECT_TRUE(obj->HasMethod("method1"));
    EXPECT_FALSE(obj->HasMethod("false_method"));
}

TEST_F(ReflectionSystemTest, HasAttribute)
{
    EXPECT_TRUE(obj->HasAttribute("attr1"));
    EXPECT_FALSE(obj->HasAttribute("false_attr"));
}

TEST_F(ReflectionSystemTest, GetMethods)
{
    auto methods = obj->GetMethods();
    EXPECT_EQ(methods.size(), 2);
}

TEST_F(ReflectionSystemTest, GetAttributes)
{
    auto attributes = obj->GetAttributes();
    EXPECT_EQ(attributes.size(), 2);
}

// namespace functions' tests
TEST(ReflectionSystemFunctions, Clear)
{
    std::string token = "example __ptr64";
    std::vector<std::string> substrs = { "__ptr64" };
    EXPECT_EQ(reflection::Clear(token, substrs), "example ");
}

TEST(ReflectionSystemFunctions, Normalize)
{
    std::string name = "example";
    std::string sign = "void example() __cdecl";
    EXPECT_EQ(reflection::Normalize(name, sign), "example: void example() ");
}

TEST(ReflectionSystemFunctions, HashCode)
{
    const char* key = "example";
    EXPECT_EQ(reflection::HashCode(key), 267647114368);

    const std::string key_str = key;
    EXPECT_EQ(reflection::HashCode(key_str), 267647114368);
}

TEST(ReflectionSystemFunctions, instance_of)
{
    EXPECT_TRUE((reflection::instance_of<ReflectionSystemTest::Base, ReflectionSystemTest::TestClass>));
    EXPECT_FALSE((reflection::instance_of<ReflectionSystemTest, ReflectionSystemTest::Base>));
}

TEST(ReflectionSystemFunctions, is_function)
{
    EXPECT_TRUE(reflection::is_function<decltype(&ReflectionSystemTest::TestClass::method1)>);
    EXPECT_FALSE(reflection::is_function<decltype(&ReflectionSystemTest::TestClass::attr2)>);
}

TEST(ReflectionSystemFunctions, is_attribute)
{
    EXPECT_TRUE(reflection::is_attribute<decltype(&ReflectionSystemTest::TestClass::attr2)>);
    EXPECT_FALSE(reflection::is_attribute<decltype(&ReflectionSystemTest::TestClass::method1)>);
}

TEST(ReflectionSystemFunctions, get_variant_index)
{
    using type = std::variant<int, char, std::string, long long, double>;

    size_t index = reflection::get_variant_index<char, type>;
    EXPECT_EQ(index, 1);

    index = reflection::get_variant_index<double, type>;
    EXPECT_EQ(index, 4);

    index = reflection::get_variant_index<float, type>;
    EXPECT_EQ(index, std::variant_npos);
}

TEST(ReflectionSystemFunctions, holds_variant_option)
{
    using type = std::variant<int, char, std::string, long long, double>;

    bool condition = reflection::holds_variant_option<char, type>;
    EXPECT_TRUE(condition);

    condition = reflection::holds_variant_option<float, type>;
    EXPECT_FALSE(condition);
}

TEST(ReflectionSystemFunctions, remove_class_pointer)
{
    using type = decltype(&ReflectionSystemTest::TestClass::attr1);

    bool condition = std::is_same_v<int,
                                    reflection::remove_class_pointer_t<
                                        decltype(&ReflectionSystemTest::TestClass::attr1),
                                        ReflectionSystemTest::TestClass
                                    >>;
    ASSERT_TRUE(condition);
}

// serializer tests
TEST_F(ReflectionSystemTest, ToJson)
{
    reflection::Serializer serializer;
    Json::Value json = serializer.ToJson<ReflectionSystemTest::TestClass>();

    EXPECT_EQ(json["name"].asString(), "ReflectionSystemTest::TestClass");
    EXPECT_EQ(json["size"].asInt(), sizeof(TestClass));
    EXPECT_EQ(json["parents"].size(), 1);
}

TEST_F(ReflectionSystemTest, ToYaml)
{
    reflection::Serializer serializer;
    YAML::Node yaml = serializer.ToYaml<ReflectionSystemTest::TestClass>();

    EXPECT_EQ(yaml["name"].as<std::string>(), "ReflectionSystemTest::TestClass");
    EXPECT_EQ(yaml["size"].as<int>(), sizeof(TestClass));
    EXPECT_EQ(yaml["parents"].size(), 1);
}

TEST_F(ReflectionSystemTest, ToString)
{
    reflection::Serializer serializer;
    std::string str = serializer.ToString<ReflectionSystemTest::TestClass>();

    EXPECT_FALSE(str.empty());
    EXPECT_TRUE(str.find("ReflectionSystemTest::TestClass") != std::string::npos);
}

TEST_F(ReflectionSystemTest, is_serializable)
{
    EXPECT_TRUE(reflection::is_serializable<ReflectionSystemTest::TestClass>);
    EXPECT_FALSE(reflection::is_serializable<ReflectionSystemTest>);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}