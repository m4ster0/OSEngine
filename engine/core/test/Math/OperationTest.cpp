#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#include <boost/test/unit_test.hpp>

#include <OSE/Math/Common.h>

BOOST_AUTO_TEST_CASE(VectorLengthTest)
{
    OSE::Vec2 vec{ 1.0f, 0.0f };
    float len = OSE::Math::length(vec);

    BOOST_CHECK(len == 1.0f);
}