# Test files

It is a common practice to do unit tests of each class before you integrate it into the project to validate its operation.
In this folder, you can create your own unit test files to validate the operation of your components.

> It might be a good idea to also take some notes about the tests since you are required to
> report these in the final report.

NOTE: tests might not run at the moment due to the back-end and front-end integration at the end of the project

# Unit Tests

## Test of Simulator

Test suite for adding new objects to Simulator:

AddNode: Adds EndHost and Router objects to the system

AddLink: Adds Link objects (connections between nodes) to the system

AddScenario: Adds Dataflowscenario object to the system, this does not check that the
scenario is valid! Only that is has been successfully added

**Involved Classes:**
EndHost, Link, Router, DataflowScenario, Simularot

**Test File:**
simulator_init_test.cpp

## Test of Node

Only operator== method tested in this suite. However this method was used a lot in a project.

**Involved Classes:**
Node, EndHost

**Test File:**
node_test.cpp

## Test of DataflowScenario

Simple init tests and testing with unvalid datapath.
One end-to-end test for utility purposes to run the scenario, super helpful.
Should print the results in format:

======================================================================

Simulation info:

Dataflow path:
(pc1) --100-- (r1) --100-- (r2) --10-- (pc2)

Size of the original data: 1 MB
Packet MTU = 1500 bytes

Summary:
Total no of packets sent ---------------------------- 674
Total no of packets received ------------------------ 175

Total transmission time (mm:ss.mls) ----------------- 00:21.603
Average transmission time / packet (mm:ss.mls) ------ 00:00.123

Router r1 dropped 0 packets
Router r2 dropped 499 packets

======================================================================

**Involved Classes:**
DataflowScenario, Simulator, Link, EndHost

**Test File:**
node_test.cpp
