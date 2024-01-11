#include <fstream>
#include <iostream>
#include <ranges>

#include "Graph.h"
#include "Simulator.h"
#include "Utilities.h"

int main(int, char **)
{
	std::ofstream os("out.txt");
	circuit::Graph g;
	auto const graph_io = circuit::helper::create_arithmetic_logic_unit_8_bit(g);
	circuit::helper::register_arithmetic_logic_unit_8_bit_io_nodes(g, graph_io);

	const GenericSimulator gs(g.get_inputs().size());

	circuit::simulate<circuit::Tester>(std::next(gs.begin(), 58921), std::next(gs.begin(), 58999), g, std::cout);

	return 0;
}
