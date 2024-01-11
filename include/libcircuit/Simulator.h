#include "Generator.h"
#include "Graph.h"
namespace circuit
{
	class SimulatorCallback
	{
	public:
		SimulatorCallback() = default;
		SimulatorCallback(SimulatorCallback &) = delete;
		SimulatorCallback(SimulatorCallback &&) = delete;
		SimulatorCallback &operator=(SimulatorCallback &) = delete;
		SimulatorCallback &operator=(SimulatorCallback &&) = delete;
		virtual ~SimulatorCallback() = default;
		virtual void set_input_value(std::string name, bool value) = 0;
		virtual void set_output_value(std::string name, bool value) = 0;
		virtual void flush() = 0;
	};

	class SimulatorCallback_impl : public SimulatorCallback
	{
		std::map<std::string, bool> m_inputs;
		std::map<std::string, bool> m_outputs;

	public:
		void set_input_value(const std::string name, const bool value) override { m_inputs[name] = value; }
		void set_output_value(const std::string name, const bool value) override { m_outputs[name] = value; }
		void flush() override {}
	};

	template<typename G>
		requires std::ranges::range<G>
	void simulate(Graph &g, G generator, SimulatorCallback &callback)
	{
		for (auto const &begin : generator)
		{
			for (auto [node, value] : std::views::zip(g.get_inputs(), begin))
			{
				node.second->set_value(value);
				callback.set_input_value(node.first, value);
			}

			for (const auto &[name, node] : g.get_outputs())
				callback.set_output_value(name, node->get_result());

			callback.flush();
		}
	}
}// namespace circuit