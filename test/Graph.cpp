#include <gtest/gtest.h>

#include "libcircuit/Generator.h"
#include "libcircuit/Graph.h"
#include "libcircuit/Simulator.h"
#include "libcircuit/Utilities.h"

TEST(GraphTest, GraphTest1)
{
	circuit::Graph g;
	auto const graph_io = circuit::helper::create_arithmetic_logic_unit_1_bit(g);
	circuit::helper::register_arithmetic_logic_unit_1_bit_io_nodes(g, graph_io);

	class Callback : public circuit::SimulatorCallback
	{
		std::map<std::string, bool> m_inputs;
		std::map<std::string, bool> m_outputs;

	public:
		void set_input_value(const std::string name, const bool value) override { m_inputs[name] = value; }
		void set_output_value(const std::string name, const bool value) override { m_outputs[name] = value; }
		void flush() override
		{
			const int a = static_cast<int>(m_inputs["A"]);
			const int b = static_cast<int>(m_inputs["B"]);
			const int cin = static_cast<int>(m_inputs["Cin"]);
			const int s = static_cast<int>(m_outputs["S"]);
			const int cout = static_cast<int>(m_outputs["Cout"]);
			if (m_inputs["M0"] == false && m_inputs["M1"] == false)
				EXPECT_EQ(a + b + cin, 2 * cout + s);
			else if (m_inputs["M0"] == false && m_inputs["M1"] == true)
				EXPECT_EQ(a & b, s);
			else if (m_inputs["M0"] == true && m_inputs["M1"] == false)
				EXPECT_EQ(a | b, s);
			else if (m_inputs["M0"] == true && m_inputs["M1"] == true)
				EXPECT_EQ(a ^ b, s);
		}
	};
	Callback callback;
	circuit::simulate(g, generic_simulator(g), callback);
}
