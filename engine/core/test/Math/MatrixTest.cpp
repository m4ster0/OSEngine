#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#include <boost/test/unit_test.hpp>

#include <OSE/Math/Vector.h>
#include <OSE/Math/Matrix.h>

BOOST_AUTO_TEST_CASE(MatrixIdentity)
{
    auto isIdentity = [](const OSE::Mat3& mat) {
        for (std::size_t i = 0; i < 3; ++i)
        {
            if (mat[i][i] != 1.0f)
                return false;
        }

        return true;
    };

    OSE::Mat3 mat3;
    BOOST_CHECK(isIdentity(mat3));
}

BOOST_AUTO_TEST_CASE(MatrixInitList)
{
    std::initializer_list<float> args{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    OSE::Mat3 mat3{ args };

    auto hasValidElements = [&args](const OSE::Mat3& mat) {
        std::size_t index = 0;
        for (auto it = args.begin(); it != args.end(); ++it, ++index)
        {
            if (mat.elements[index] != *it)
                return false;
        }

        return true;
    };

    BOOST_CHECK(hasValidElements(mat3));
}

BOOST_AUTO_TEST_CASE(MatrixSubscript)
{
    std::initializer_list<float> args{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    OSE::Mat3 mat3{ args };

    BOOST_CHECK(mat3[0][0] == 1.0f);
    BOOST_CHECK(mat3[0][1] == 2.0f);
    BOOST_CHECK(mat3[0][2] == 3.0f);
    BOOST_CHECK(mat3[1][0] == 4.0f);
    BOOST_CHECK(mat3[1][1] == 5.0f);
    BOOST_CHECK(mat3[1][2] == 6.0f);
    BOOST_CHECK(mat3[2][0] == 7.0f);
}

BOOST_AUTO_TEST_CASE(MatrixAddition)
{
    std::initializer_list<int> args{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    OSE::Matrix<int, 3, 3> mat3{ args };

    OSE::Matrix<int, 3, 3> mat3rev;
    std::size_t index = args.size();
    for (auto it = args.begin(); it != args.end(); ++it)
    {
        mat3rev.elements[--index] = *it;
    }
    OSE::Matrix<int, 3, 3> result;

    auto forAll = [&result](int val) {
        for (std::size_t i = 0; i < 9; ++i)
        {
            if (result.elements[i] != val)
                return false;
        }

        return true;
    };

    result = mat3 + mat3rev;
    BOOST_CHECK(forAll(10));
}

BOOST_AUTO_TEST_CASE(MatrixSubtraction)
{
    std::initializer_list<int> args{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    OSE::Matrix<int, 3, 3> mat3{ args };
    OSE::Matrix<int, 3, 3> mat3other{ args };

    OSE::Matrix<int, 3, 3> result;

    auto forAll = [&result](int val) {
        for (std::size_t i = 0; i < 9; ++i)
        {
            if (result.elements[i] != val)
                return false;
        }

        return true;
    };

    result = mat3 - mat3other;
    BOOST_CHECK(forAll(0));
}

BOOST_AUTO_TEST_CASE(MatrixMultiplication)
{
    std::initializer_list<int> args{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    OSE::Matrix<int, 3, 3> mat3{ args };
    OSE::Matrix<int, 3, 3> mat3other{ args };

    OSE::Matrix<int, 3, 3> result = mat3 * mat3other;
    BOOST_CHECK(result[0][0] == 30);
    BOOST_CHECK(result[0][2] == 42);
    BOOST_CHECK(result[1][0] == 66);
    BOOST_CHECK(result[1][2] == 96);
    BOOST_CHECK(result[2][0] == 102);

    //different dimensions
    OSE::Matrix<int, 2, 3> mat2x3 = { 1, 2, 3, 4, 5, 6 };
    OSE::Matrix<int, 3, 4> mat3x4 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    OSE::Matrix<int, 2, 4> otherResult = mat2x3 * mat3x4;
    BOOST_CHECK(otherResult[0][0] == 38);
    BOOST_CHECK(otherResult[0][3] == 56);
    BOOST_CHECK(otherResult[1][0] == 83);
    BOOST_CHECK(otherResult[1][3] == 128);

    //vector * matrix
    OSE::Vector<int, 2> vec2{ 1, 2 };
    OSE::Vector<int, 4> vecResult = vec2 * otherResult;
    BOOST_CHECK(vecResult.x == 204);
    BOOST_CHECK(vecResult.y == 240);
    BOOST_CHECK(vecResult.z == 276);
    BOOST_CHECK(vecResult.w == 312);

}