#pragma once
#include "Graph.h"
#include "Node.h"

namespace circuit::helper
{
	template<size_t N>
	struct TwoOperandGateIO;

	template<>
	struct TwoOperandGateIO<1>
	{
		Passthrough* m_input_a = nullptr;
		Passthrough* m_input_b = nullptr;
		Passthrough* m_input_c = nullptr;
		Passthrough* m_output_s = nullptr;
		Passthrough* m_output_c = nullptr;
	};

	template<size_t N>
	struct ArithmeticLogicUnitIO;

	template<>
	struct ArithmeticLogicUnitIO<1>
	{
		Passthrough* m_input_a = nullptr;
		Passthrough* m_input_b = nullptr;
		Passthrough* m_input_c = nullptr;
		Passthrough* m_input_m0 = nullptr;
		Passthrough* m_input_m1 = nullptr;
		Passthrough* m_output_s = nullptr;
		Passthrough* m_output_c = nullptr;
	};

	template<>
	struct ArithmeticLogicUnitIO<8>
	{
		Passthrough* m_input_a0 = nullptr;
		Passthrough* m_input_b0 = nullptr;
		Passthrough* m_input_a1 = nullptr;
		Passthrough* m_input_b1 = nullptr;
		Passthrough* m_input_a2 = nullptr;
		Passthrough* m_input_b2 = nullptr;
		Passthrough* m_input_a3 = nullptr;
		Passthrough* m_input_b3 = nullptr;
		Passthrough* m_input_a4 = nullptr;
		Passthrough* m_input_b4 = nullptr;
		Passthrough* m_input_a5 = nullptr;
		Passthrough* m_input_b5 = nullptr;
		Passthrough* m_input_a6 = nullptr;
		Passthrough* m_input_b6 = nullptr;
		Passthrough* m_input_a7 = nullptr;
		Passthrough* m_input_b7 = nullptr;
		Passthrough* m_input_c = nullptr;

		Passthrough* m_output_s0 = nullptr;
		Passthrough* m_output_s1 = nullptr;
		Passthrough* m_output_s2 = nullptr;
		Passthrough* m_output_s3 = nullptr;
		Passthrough* m_output_s4 = nullptr;
		Passthrough* m_output_s5 = nullptr;
		Passthrough* m_output_s6 = nullptr;
		Passthrough* m_output_s7 = nullptr;
		Passthrough* m_output_c = nullptr;
		Passthrough* m_input_m0 = nullptr;
		Passthrough* m_input_m1 = nullptr;
	};

	template<>
	struct TwoOperandGateIO<8>
	{
		Passthrough* m_input_a0 = nullptr;
		Passthrough* m_input_b0 = nullptr;
		Passthrough* m_input_a1 = nullptr;
		Passthrough* m_input_b1 = nullptr;
		Passthrough* m_input_a2 = nullptr;
		Passthrough* m_input_b2 = nullptr;
		Passthrough* m_input_a3 = nullptr;
		Passthrough* m_input_b3 = nullptr;
		Passthrough* m_input_a4 = nullptr;
		Passthrough* m_input_b4 = nullptr;
		Passthrough* m_input_a5 = nullptr;
		Passthrough* m_input_b5 = nullptr;
		Passthrough* m_input_a6 = nullptr;
		Passthrough* m_input_b6 = nullptr;
		Passthrough* m_input_a7 = nullptr;
		Passthrough* m_input_b7 = nullptr;
		Passthrough* m_input_c = nullptr;

		Passthrough* m_output_s0 = nullptr;
		Passthrough* m_output_s1 = nullptr;
		Passthrough* m_output_s2 = nullptr;
		Passthrough* m_output_s3 = nullptr;
		Passthrough* m_output_s4 = nullptr;
		Passthrough* m_output_s5 = nullptr;
		Passthrough* m_output_s6 = nullptr;
		Passthrough* m_output_s7 = nullptr;
		Passthrough* m_output_c = nullptr;
	};

	struct MultiplexerIO
	{
		Passthrough* m_input_i0 = nullptr;
		Passthrough* m_input_i1 = nullptr;
		Passthrough* m_input_i2 = nullptr;
		Passthrough* m_input_i3 = nullptr;
		Passthrough* m_input_m0 = nullptr;
		Passthrough* m_input_m1 = nullptr;
		Passthrough* m_output = nullptr;
	};

	using full_adder_1_bit_io_t = TwoOperandGateIO<1>;
	using full_adder_8_bit_io_t = TwoOperandGateIO<8>;
	using arithmetic_logic_unit_1_bit_io_t = ArithmeticLogicUnitIO<1>;
	using arithmetic_logic_unit_8_bit_io_t = ArithmeticLogicUnitIO<8>;
	using multiplexer_io_t = MultiplexerIO;

	full_adder_1_bit_io_t create_full_adder_1_bit(Graph& g);
	full_adder_8_bit_io_t create_full_adder_8_bit(Graph& g);
	multiplexer_io_t create_multiplexer(Graph& g);
	arithmetic_logic_unit_1_bit_io_t create_arithmetic_logic_unit_1_bit(Graph& g);
	arithmetic_logic_unit_8_bit_io_t create_arithmetic_logic_unit_8_bit(Graph& g);
	void register_full_adder_1_bit_io_nodes(Graph& g, full_adder_1_bit_io_t const& full_adder_1_bit_io);
	void register_full_adder_8_bit_io_nodes(Graph& g, full_adder_8_bit_io_t const& full_adder_8_bit_io);
	void register_multiplexer_io_nodes(Graph& g, multiplexer_io_t const& multiplexer_io);
	void register_arithmetic_logic_unit_1_bit_io_nodes(Graph& g, arithmetic_logic_unit_1_bit_io_t const& arithmetic_logic_unit_1_bit_io);
	void register_arithmetic_logic_unit_8_bit_io_nodes(Graph& g, arithmetic_logic_unit_8_bit_io_t const& arithmetic_logic_unit_8_bit_io);
}
