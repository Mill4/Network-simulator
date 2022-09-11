#ifndef DATAFLOW_TESTS
#define DATAFLOW_TESTS
#include "catch.hpp"
#include <list>
#include "../src/backend/dataflowscenario.cpp"
//#include "../src/backend/endhost.cpp"
#include "../src/backend/simulator.hpp"
#include "../src/backend/link.cpp"
//#include "../src/backend/node.cpp"
//#include "../src/backend/packet.hpp"

TEST_CASE("New instance")
{
    auto start = new EndHost("pc1");
    auto end = new EndHost("pc2");
    auto l1 = new Link(100, start, end);
    std::list<Node *> nodes;
    std::list<Link *> links;
    nodes.push_back(start);
    nodes.push_back(end);
    links.push_back(l1);
    DataflowScenario dws = DataflowScenario(start, end, 1, nodes, links);

    SECTION("data sixze should be 1")
    {
        REQUIRE(dws.GetSize() == 1);
    }

    SECTION("scenario should be unvalid")
    {
        REQUIRE(dws.IsValid() == false);
    }

    auto s = dws.GetStartNode();

    SECTION("get start node")
    {
        REQUIRE(s == start);
    }

    auto e = dws.GetEndNode();

    SECTION("get end node")
    {
        REQUIRE(e == end);
    }

    // add more when endhost is implemented
}

TEST_CASE("FindPath")
{
    Simulator s;

    auto pc1 = s.CreateNode("pc1", endhost);
    auto pc2 = s.CreateNode("pc2", endhost);
    auto r1 = s.CreateNode("r1", router);
    auto r2 = s.CreateNode("r2", router);

    s.AddLink(pc1, r1, 100);
    s.AddLink(r1, r2, 100);
    s.AddLink(r2, pc2, 10);

    s.AddScenario(pc1, pc2, 10);

    SECTION("Scenario should be valid")
    {
        auto scenarios = s.GetScenarios();
        for (auto s : scenarios)
        {
            REQUIRE(s.IsValid() == true);
        }
    }
}

TEST_CASE("Run")
{
    Simulator s;

    auto pc1 = s.CreateNode("pc1", endhost);
    auto pc2 = s.CreateNode("pc2", endhost);
    auto r1 = s.CreateNode("r1", router);
    auto r2 = s.CreateNode("r2", router);

    s.AddLink(pc1, r1, 100);
    s.AddLink(r1, r2, 100);
    s.AddLink(r2, pc2, 10);

    s.AddScenario(pc1, pc2, 1);

    SECTION("Run scenarios")
    {
        auto result = s.RunScenarios();
        REQUIRE(true);
    }
}

#endif