#pragma once
#include <concepts>
#include <functional>
#include <map>
#include <memory>
#include <ranges>
#include <string>
#include <vector>

#include "Formatter.h"
#include "Node.h"

namespace circuit
{
	class Graph
	{
	public:
		using inputs_t = std::map<std::string, Input *>;
		using outputs_t = std::map<std::string, Output *>;

		template<typename T>
			requires std::derived_from<T, Node>
		T *add_node()
		{
			T *new_node = new T;
			m_vertex_handles.push_back(std::unique_ptr<Node>(static_cast<Node *>(new_node)));
			return new_node;
		}

		[[nodiscard]] inputs_t const &get_inputs() const noexcept;
		[[nodiscard]] Input *get_input(std::string const &name) const;
		void register_input(Passthrough *input, std::string name);
		[[nodiscard]] outputs_t const &get_outputs() const noexcept;
		[[nodiscard]] Output *get_output(std::string const &name) const;
		void register_output(Passthrough *output, std::string name);

	private:
		std::vector<std::unique_ptr<Node>> m_vertex_handles;
		inputs_t m_inputs;
		outputs_t m_outputs;
	};

}// namespace circuit