#include <experimental/generator>
#include <libcircuit/Generator.h>

std::experimental::generator<std::vector<bool>> generic_simulator(std::vector<bool> first, std::vector<bool> last)
{
	co_yield first;
	while (first != last)
	{
		for (auto &&i : first)
		{
			if (i == false)
			{
				i = true;
				break;
			}
			i = false;
		}
		co_yield first;
	}
	co_return;
}

std::experimental::generator<std::vector<bool>> generic_simulator(circuit::Graph const &g)
{
	return generic_simulator(
		std::vector<bool>(g.get_inputs().size(), false), std::vector<bool>(g.get_inputs().size(), true));
}
