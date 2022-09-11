#ifndef NODE_TESTS
#define NODE_TESTS

#include "catch.hpp"
#include "../src/backend/endhost.cpp"
#include "../src/backend/node.cpp"
#include "../src/backend/link.hpp"

TEST_CASE("Equals")
{
    auto start = EndHost("pc1");
    auto end = EndHost("pc2");

    SECTION("end and start should not be the same")
    {
        REQUIRE((start == end) == false);
    }

    SECTION("nodes with the same name should be the same")
    {
        auto copy_end = EndHost("pc2");
        REQUIRE((copy_end == end) == true);
    }
}

#endif