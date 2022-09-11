#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/backend/simulator.cpp"
//#include "../src/backend/endhost.cpp"
#include "../src/backend/link.hpp"
#include "../src/backend/router.cpp"
#include "../src/backend/summary.cpp"
#include "../frontend/components/ns-terminal.h"

/**
 * @brief Test suite for adding new objects to Simulator:
 * 
 * AddNode: Adds EndHost and Router objects to the system
 * 
 * AddLink: Adds Link objects (connections between nodes) to the system
 * 
 * AddScenario: Adds Dataflowscenario object to the system, this does not check that the
 * scenario is valid! Only that is has been successfully added 
 * 
 */

TEST_CASE("AddNode")
{
    // HOX! Add test with Router
    Simulator s;
    SECTION("node list should be empty")
    {
        REQUIRE(s.GetNodes().size() == 0);
    }

    SECTION("node list should have one node")
    {
        s.CreateNode("pc1", endhost);
        REQUIRE(s.GetNodes().size() == 1);
    }

    SECTION("node list should have more than one node")
    {
        s.CreateNode("pc3", endhost);
        s.CreateNode("r1", router);
        REQUIRE(s.GetNodes().size() > 1);
    }
}

TEST_CASE("AddLink")
{
    Simulator s;
    SECTION("link list should be empty")
    {
        REQUIRE(s.GetLinks().size() == 0);
    }

    SECTION("link list should have one link")
    {
        auto pc3 = s.CreateNode("pc3", endhost);
        auto pc4 = s.CreateNode("pc4", endhost);
        s.AddLink(pc3, pc4, 100.0);
        REQUIRE(s.GetLinks().size() == 1);
    }

    SECTION("link list should have more than one link")
    {
        auto pc2 = s.CreateNode("pc2", endhost);
        auto pc3 = s.CreateNode("pc3", endhost);
        auto pc4 = s.CreateNode("pc4", endhost);
        s.AddLink(pc2, pc3, 100.0);
        s.AddLink(pc3, pc4, 100.0);
        REQUIRE(s.GetNodes().size() > 1);
    }
}

TEST_CASE("AddScenario")
{
    Simulator s;
    SECTION("scenario list should be empty")
    {
        REQUIRE(s.GetScenarios().size() == 0);
    }

    SECTION("scenario list should have one scenario")
    {
        auto pc2 = s.CreateNode("pc2", endhost);
        auto pc3 = s.CreateNode("pc3", endhost);
        s.AddScenario(pc2, pc3, 100);
        REQUIRE(s.GetScenarios().size() == 1);
    }

    SECTION("scenario list should have more than one scenario")
    {
        auto pc2 = s.CreateNode("pc2", endhost);
        auto pc3 = s.CreateNode("pc3", endhost);
        s.AddScenario(pc2, pc3, 100);
        s.AddScenario(pc3, pc2, 100);
        REQUIRE(s.GetScenarios().size() > 1);
    }
}

#endif