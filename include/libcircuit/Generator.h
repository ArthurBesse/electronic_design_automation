#pragma once
#include <experimental/generator>
#include <vector>

#include "Graph.h"

std::experimental::generator<std::vector<bool>> generic_simulator(std::vector<bool> first, std::vector<bool> last);
std::experimental::generator<std::vector<bool>> generic_simulator(circuit::Graph const &g);
