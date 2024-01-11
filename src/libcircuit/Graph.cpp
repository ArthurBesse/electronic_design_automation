#include <ranges>
#include <stdexcept>

#include <libcircuit/Graph.h>

namespace circuit
{
	Graph::inputs_t const &Graph::get_inputs() const noexcept { return this->m_inputs; }

	Input *Graph::get_input(std::string const &name) const
	{
		const auto result = this->m_inputs.find(name);
		if (this->m_inputs.end() == result)
			throw std::invalid_argument(
				"Input node with name " + name + " not found in graph (" __FILE__ ").");
		return result->second;
	}

	void Graph::register_input(Passthrough *input, std::string name)
	{
		auto i = this->add_node<Input>();
		input->add_source(i);
		this->m_inputs.insert_or_assign(std::move(name), i);
	}

	Graph::outputs_t const &Graph::get_outputs() const noexcept { return this->m_outputs; }

	Output *Graph::get_output(std::string const &name) const
	{
		const auto result = this->m_outputs.find(name);
		if (this->m_outputs.end() == result)
			throw std::invalid_argument(
				"Output node with name " + name + " not found in graph (" __FILE__ ").");
		return result->second;
	}

	void Graph::register_output(Passthrough *output, std::string name)
	{
		auto o = this->add_node<Output>();
		o->add_source(output);
		this->m_outputs.insert_or_assign(std::move(name), o);
	}

}// namespace circuit
