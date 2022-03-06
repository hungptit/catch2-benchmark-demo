#include <iostream>
#include <vector>

#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"

struct MyClass
{
    explicit MyClass()
    {
        std::cout << "Construct a MyClass object.\n";
    }

    ~MyClass()
    {
        std::cout << "Destroy a MyClass object.\n";
    }

    bool RunFirstCheck(const std::string& msg)
    {
        std::cout << msg;
        return true;
    }

    bool RunSecondCheck(const std::string& msg)
    {
        std::cout << msg;
        return false;
    }
};

TEST_CASE("Write tests using TEST_CASE")
{
    MyClass testFixture;

    SECTION("Run the first check")
    {
        CHECK(testFixture.RunFirstCheck("Run the first check.\n"));
    }

    SECTION("Run the second check")
    {
        CHECK(testFixture.RunSecondCheck("Run the second check.\n"));
    }
}

SCENARIO("Write tests using SCENARIO")
{
    MyClass testFixture;

    GIVEN("A default MyClass object")
    {
        WHEN("Execute the first check.")
        {
            THEN("We see the expected output")
            {
                CHECK(testFixture.RunFirstCheck("Run the first check.\n"));
            }
        }

        WHEN("Execute the second check")
        {
            THEN("We see the expected output")
            {
                CHECK(testFixture.RunSecondCheck("Run the second check.\n"));
            }
        }
    }
}

// class MyClassTest : public CppUnit::TestFixture
// {
// public:
//     CPPUNIT_TEST_SUITE_EX(MyClassTest, PRIMARY_TEAM(MY_TEAM));
//     CPPUNIT_TEST(RunFirstCheck());
//     CPPUNIT_TEST(RunSecondCheck());
//     CPPUNIT_TEST_SUITE_END();

//     bool RunFirstCheck();
//     bool RunSecondCheck();

//     void setUp() override;
//     void tearDown() override;
// private:
//     unique_ptr<MyClass> m_myObject;
// };

// void MyClassTest::setUp()
// {
//     m_myObject = make_unique<MyClass>();
// }

// void MyClassTest::tearDown()
// {
//     m_myObject = nullptr;
// }

// void MyClassTest::RunFirstCheck()
// {
//     CPPUNIT_ASSERT(m_myObject->RunFirstCheck("Run the first check.\n"));
// }

// void MyClassTest::RunSecondCheck()
// {
//     CPPUNIT_ASSERT(m_myObject->RunSecondCheck("Run the second check.\n"));
// }

// CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(MyClassTest, TestSuites::AllTests());
// CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(MyClassTest, TestSuites::ModulePrecommitTests());
