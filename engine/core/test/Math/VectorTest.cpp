#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#include <boost/test/unit_test.hpp>

#include <OSE/Math/Vector.h>
#include <array>
#include <cmath>
#include <limits>

template<typename T, std::size_t n>
bool Equals(const OSE::Vector<T, n> vec, const std::array<T, n>& values)
{
    for (int i = 0; i < n; ++i)
    {
        if (vec.components[i] != values[i])
            return false;
    }

    return true;
}

template<typename T, std::size_t n>
bool Equals(const OSE::Vector<T, n> vec, const T& value)
{
    for (int i = 0; i < n; ++i)
    {
        if (vec.components[i] != value)
            return false;
    }

    return true;
}

BOOST_AUTO_TEST_CASE(VectorEmpty)
{
    OSE::Vec2 vec2{};
    BOOST_CHECK(vec2.components[0] == 0.0f);
    BOOST_CHECK(vec2.components[1] == 0.0f);

    BOOST_CHECK(Equals(vec2, { 0.0f, 0.0f }));
    BOOST_CHECK(Equals(vec2, 0.0f));

    BOOST_CHECK(vec2.x == 0.0f);
    BOOST_CHECK(vec2.y == 0.0f);
}

BOOST_AUTO_TEST_CASE(VectorNew)
{
    OSE::Vector<float, 3> vec1{};
    BOOST_CHECK(Equals(vec1, 0.0f));

    OSE::Vector<float, 3> vec2( 1.0f ); // ...watch for initializer_list priority in consstructor resolution
    BOOST_CHECK(Equals(vec2, 1.0f));

    //OSE::Vector<float, 3> vec3 = 2.0f;

    OSE::Vector<float, 3> vec3{1.0f, 2.0f, 3.0f};
    BOOST_CHECK(Equals(vec3, { 1.0f, 2.0f, 3.0f }));

    OSE::Vector<float, 3> vec4 = { 2.0f, 3.0f, 4.0f };
    BOOST_CHECK(Equals(vec4, { 2.0f, 3.0f, 4.0f }));

    OSE::Vector<float, 3> vec5{{ 3.0f, 4.0f, 5.0f }};
    BOOST_CHECK(Equals(vec5, { 3.0f, 4.0f, 5.0f }));

    OSE::Vector<float, 3> vec6{ vec5 };
    BOOST_CHECK(Equals(vec6, { 3.0f, 4.0f, 5.0f }));

    OSE::Vector<double, 3> vec7{ 1.0, 2.0, 6.0 };
    BOOST_CHECK(Equals(vec7, { 1.0, 2.0, 6.0 }));
}

BOOST_AUTO_TEST_CASE(VectorNewPredefined)
{
    OSE::Vec2 vec11{ 1.0f, 1.0f };
    BOOST_CHECK(Equals(vec11, 1.0f));

    OSE::Vec3 vec12{ vec11, 1.0f };
    BOOST_CHECK(Equals(vec12, 1.0f));

    OSE::Vec4 vec13{ vec11, 1.0f, 1.0f };
    BOOST_CHECK(Equals(vec13, 1.0f));

    OSE::Vec4 vec14{ vec12.xy, 1.0f, 1.0f };
    BOOST_CHECK(Equals(vec14, 1.0f));

    OSE::Vec4 vec15{ vec12, 1.0f };
    BOOST_CHECK(Equals(vec15, 1.0f));
}

BOOST_AUTO_TEST_CASE(VectorSubscript)
{
    OSE::Vec2 vec{ 3.0f, 6.0f };
    BOOST_CHECK(vec[0] == 3.0f);
    BOOST_CHECK(vec[1] == 6.0f);
}

BOOST_AUTO_TEST_CASE(VectorAddition)
{
    OSE::IVec2 result;
    OSE::IVec2 vec1(1);
    OSE::IVec2 vec2(2);
    result = vec1 + vec2;

    BOOST_CHECK(Equals(vec1, 1));
    BOOST_CHECK(Equals(vec2, 2));

    BOOST_CHECK(Equals(result, 3));

    result = vec1 + OSE::IVec2{ 5, 10 };
    BOOST_CHECK(Equals(result, { 6, 11 }));

    int scalar = 10;
    result = OSE::IVec2(2) + scalar;
    BOOST_CHECK(Equals(result, 12));

    result = scalar + OSE::IVec2{ 4, -10 };
    BOOST_CHECK(Equals(result, { 14, 0 }));
}

BOOST_AUTO_TEST_CASE(VectorAdditionAssignment)
{
    OSE::IVec2 result(1);
    OSE::IVec2 vec1(2);
    result += vec1;

    BOOST_CHECK(Equals(vec1, 2));
    BOOST_CHECK(Equals(result, 3));

    int scalar = 10;
    result += scalar;
    BOOST_CHECK(Equals(result, 13));

    result += OSE::IVec2{ 7, -3};
    BOOST_CHECK(Equals(result, { 20, 10 }));
}

BOOST_AUTO_TEST_CASE(VectorSubtraction)
{
    OSE::IVec2 result;
    OSE::IVec2 vec1{ 5, 2 };
    OSE::IVec2 vec2{ 1, 2 };
    result = vec1 - vec2;

    BOOST_CHECK(Equals(vec1, { 5, 2 }));
    BOOST_CHECK(Equals(vec2, { 1, 2 }));

    BOOST_CHECK(Equals(result, { 4, 0 }));

    result = vec1 - OSE::IVec2{ 5, -3 };
    BOOST_CHECK(Equals(result, { 0, 5 }));

    int scalar = 10;
    result = OSE::IVec2(2) - scalar;
    BOOST_CHECK(Equals(result, -8));
}

BOOST_AUTO_TEST_CASE(VectorSubtractionAssignment)
{
    OSE::IVec2 result(1);
    OSE::IVec2 vec1(2);
    result -= vec1;

    BOOST_CHECK(Equals(vec1, 2));
    BOOST_CHECK(Equals(result, -1));

    int scalar = 5;
    result -= scalar;
    BOOST_CHECK(Equals(result, -6));

    result -= OSE::IVec2{ 4, -6 };
    BOOST_CHECK(Equals(result, { -10, 0 }));
}

BOOST_AUTO_TEST_CASE(VectorMultiplication)
{
    OSE::IVec2 result;
    OSE::IVec2 vec1(1);
    OSE::IVec2 vec2(2);
    result = vec1 * vec2;

    BOOST_CHECK(Equals(vec1, 1));
    BOOST_CHECK(Equals(vec2, 2));

    BOOST_CHECK(Equals(result, 2));

    result = OSE::IVec2{ 1, 2 } * OSE::IVec2{ 5, 10 };
    BOOST_CHECK(Equals(result, { 5, 20 }));

    int scalar = 10;
    result = OSE::IVec2(2) * scalar;
    BOOST_CHECK(Equals(result, 20));

    result = scalar * OSE::IVec2{ 4, -10 };
    BOOST_CHECK(Equals(result, { 40, -100 }));
}

BOOST_AUTO_TEST_CASE(VectorMultiplicationAssignment)
{
    OSE::IVec2 result(1);
    OSE::IVec2 vec1(2);
    result *= vec1;

    BOOST_CHECK(Equals(vec1, 2));
    BOOST_CHECK(Equals(result, 2));

    int scalar = 10;
    result *= scalar;
    BOOST_CHECK(Equals(result, 20));

    result *= OSE::IVec2{ 7, -3};
    BOOST_CHECK(Equals(result, { 140, -60 }));
}

BOOST_AUTO_TEST_CASE(VectorDivision)
{
    OSE::IVec2 result;
    OSE::IVec2 vec1{ 5, 2 };
    OSE::IVec2 vec2{ 1, 2 };
    result = vec1 / vec2;

    BOOST_CHECK(Equals(vec1, { 5, 2 }));
    BOOST_CHECK(Equals(vec2, { 1, 2 }));

    BOOST_CHECK(Equals(result, { 5, 1 }));

    result = vec1 / OSE::IVec2{ 5, -2 };
    BOOST_CHECK(Equals(result, { 1, -1 }));

    int scalar = 10;
    result = OSE::IVec2(2) / scalar;
    BOOST_CHECK(Equals(result, 0));
}

BOOST_AUTO_TEST_CASE(VectorDivisionAssignment)
{
    OSE::IVec2 result(10);
    OSE::IVec2 vec1(2);
    result /= vec1;

    BOOST_CHECK(Equals(vec1, 2));
    BOOST_CHECK(Equals(result, 5));

    int scalar = -2;
    result /= scalar;
    BOOST_CHECK(Equals(result, -2));

    result /= OSE::IVec2{ -2, 1 };
    BOOST_CHECK(Equals(result, { 1, -2 }));
}

//TODO equality and negation tests
BOOST_AUTO_TEST_CASE(VectorNegation)
{
    OSE::Vec2 vec1{ 2.0f, -2.0f };
    OSE::Vec2 result = -vec1;

    BOOST_CHECK(Equals(vec1, { 2.0f, -2.0f }));
    BOOST_CHECK(Equals(result, { -2.0f, 2.0f }));
}