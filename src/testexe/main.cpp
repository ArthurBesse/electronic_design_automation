#include "libcircuit/Generator.h"
#include "libcircuit/Graph.h"
#include "libcircuit/Simulator.h"
#include "libcircuit/Utilities.h"

#include <array>
#include <functional>
#include <iostream>
#include <optional>

#include <random>

// NOLINTNEXTLINE(bugprone-exception-escape)
int main([[maybe_unused]] int argc, [[maybe_unused]] const char **argv)
{
	circuit::Graph g;
	auto const graph_io = circuit::helper::create_arithmetic_logic_unit_8_bit(g);
	circuit::helper::register_arithmetic_logic_unit_8_bit_io_nodes(g, graph_io);

	circuit::SimulatorCallback_impl sc;
	circuit::simulate(g, generic_simulator(g), sc);

	return 0;
}
