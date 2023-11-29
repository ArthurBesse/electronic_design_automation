#pragma once
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <ranges>
#include <concepts>
#include <functional>

#include "Formatter.h"
#include "Node.h"

namespace circuit
{
	class Graph
	{
	public:
		using inputs_t = std::map<std::string, Input*>;
		using outputs_t = std::map<std::string, Output*>;

		template <typename T> requires std::derived_from<T, Node>
		T* add_node()
		{
			T* new_node = new T;
			m_vertex_handles.push_back(std::unique_ptr<Node>(static_cast<Node*>(new_node)));
			return new_node;
		}

		[[nodiscard]] inputs_t const& get_inputs() const noexcept;
		[[nodiscard]] Input* get_input(std::string const& name) const;
		void register_input(Passthrough* input, std::string name);
		[[nodiscard]] outputs_t const& get_outputs() const noexcept;
		[[nodiscard]] Output* get_output(std::string const& name) const;
		void register_output(Passthrough* output, std::string name);
		int operator[](std::string const&) const;
	private:

		std::vector<std::unique_ptr<Node> > m_vertex_handles;
		inputs_t m_inputs;
		outputs_t m_outputs;
	};

	template<typename F, std::input_iterator I> requires std::derived_from<F, class Formatter>
	void simulate(I begin, I const& end, Graph& g, std::ostream& out, 
		std::function<bool(Graph const&)> verifier)
	{
		F formatter(g, &out);
		std::map<std::string, bool> inputs;
		for (; begin != end; ++begin)
		{
			for (auto [node, value] : std::views::zip(g.get_inputs() | std::ranges::views::values, *begin))
			{
				node->set_value(value);
				formatter << value;
			}

			for (auto const& node : g.get_outputs() | std::ranges::views::values)
				formatter << node->get_result();

			formatter << (std::invoke(verifier, g) ? 'T' : 'F');
		}
	}

	template<typename F, std::input_iterator I> requires std::derived_from<F, class Formatter>
	void simulate(I begin, I const& end, Graph& g, std::ostream& out)
	{
		F formatter(g, &out);
		std::map<std::string, bool> inputs;
		for (; begin != end; ++begin)
		{
			for (auto [node, value] : std::views::zip(g.get_inputs() | std::ranges::views::values, *begin))
			{
				node->set_value(value);
				formatter << value;
			}

			for (auto const& node : g.get_outputs() | std::ranges::views::values)
				formatter << node->get_result();

			formatter << 'U';
		}
	}
}