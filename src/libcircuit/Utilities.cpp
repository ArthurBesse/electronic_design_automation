#include <libcircuit/Utilities.h>

namespace circuit::helper
{
	full_adder_1_bit_io_t create_full_adder_1_bit(Graph &g)
	{
		const auto input_node_1 = g.add_node<Passthrough>();
		const auto input_node_2 = g.add_node<Passthrough>();
		const auto input_node_3 = g.add_node<Passthrough>();
		const auto output_node_1 = g.add_node<Passthrough>();
		const auto output_node_2 = g.add_node<Passthrough>();

		const auto nand_1 = g.add_node<Nand>();
		const auto nand_2 = g.add_node<Nand>();
		const auto nand_3 = g.add_node<Nand>();
		const auto nand_4 = g.add_node<Nand>();
		const auto nand_5 = g.add_node<Nand>();
		const auto nand_6 = g.add_node<Nand>();
		const auto nand_7 = g.add_node<Nand>();
		const auto nand_8 = g.add_node<Nand>();
		const auto nand_9 = g.add_node<Nand>();

		nand_1->add_source1(input_node_1);
		nand_1->add_source2(input_node_2);
		nand_2->add_source1(input_node_1);
		nand_2->add_source2(nand_1);
		nand_3->add_source1(nand_1);
		nand_3->add_source2(input_node_2);
		nand_4->add_source1(nand_2);
		nand_4->add_source2(nand_3);
		nand_5->add_source1(nand_4);
		nand_5->add_source2(input_node_3);
		nand_6->add_source1(nand_4);
		nand_6->add_source2(nand_5);
		nand_7->add_source1(nand_5);
		nand_7->add_source2(input_node_3);
		nand_8->add_source1(nand_6);
		nand_8->add_source2(nand_7);
		nand_9->add_source1(nand_5);
		nand_9->add_source2(nand_1);

		output_node_1->add_source(nand_8);
		output_node_2->add_source(nand_9);
		return { input_node_1, input_node_2, input_node_3, output_node_1, output_node_2 };
	}

	full_adder_8_bit_io_t create_full_adder_8_bit(Graph &g)
	{
		full_adder_8_bit_io_t result;

		full_adder_1_bit_io_t current;

		{
			const auto temp = create_full_adder_1_bit(g);
			current = temp;

			result.m_input_a0 = current.m_input_a;
			result.m_input_b0 = current.m_input_b;
			result.m_input_c = current.m_input_c;
			result.m_output_s0 = current.m_output_s;
		}

		{
			const auto temp = create_full_adder_1_bit(g);
			temp.m_input_c->add_source(current.m_output_c);
			current = temp;

			result.m_input_a1 = current.m_input_a;
			result.m_input_b1 = current.m_input_b;
			result.m_output_s1 = current.m_output_s;
		}

		{
			const auto temp = create_full_adder_1_bit(g);
			temp.m_input_c->add_source(current.m_output_c);
			current = temp;

			result.m_input_a2 = current.m_input_a;
			result.m_input_b2 = current.m_input_b;
			result.m_output_s2 = current.m_output_s;
		}

		{
			const auto temp = create_full_adder_1_bit(g);
			temp.m_input_c->add_source(current.m_output_c);
			current = temp;

			result.m_input_a3 = current.m_input_a;
			result.m_input_b3 = current.m_input_b;
			result.m_output_s3 = current.m_output_s;
		}

		{
			const auto temp = create_full_adder_1_bit(g);
			temp.m_input_c->add_source(current.m_output_c);
			current = temp;

			result.m_input_a4 = current.m_input_a;
			result.m_input_b4 = current.m_input_b;
			result.m_output_s4 = current.m_output_s;
		}

		{
			const auto temp = create_full_adder_1_bit(g);
			temp.m_input_c->add_source(current.m_output_c);
			current = temp;

			result.m_input_a5 = current.m_input_a;
			result.m_input_b5 = current.m_input_b;
			result.m_output_s5 = current.m_output_s;
		}

		{
			const auto temp = create_full_adder_1_bit(g);
			temp.m_input_c->add_source(current.m_output_c);
			current = temp;

			result.m_input_a6 = current.m_input_a;
			result.m_input_b6 = current.m_input_b;
			result.m_output_s6 = current.m_output_s;
		}

		{
			const auto temp = create_full_adder_1_bit(g);
			temp.m_input_c->add_source(current.m_output_c);
			current = temp;

			result.m_input_a7 = current.m_input_a;
			result.m_input_b7 = current.m_input_b;
			result.m_output_s7 = current.m_output_s;
			result.m_output_c = current.m_output_c;
		}


		return result;
	}

	multiplexer_io_t create_multiplexer(Graph &g)
	{
		const auto input_node_i1 = g.add_node<Passthrough>();
		const auto input_node_i2 = g.add_node<Passthrough>();
		const auto input_node_i3 = g.add_node<Passthrough>();
		const auto input_node_i4 = g.add_node<Passthrough>();
		const auto input_node_m1 = g.add_node<Passthrough>();
		const auto input_node_m2 = g.add_node<Passthrough>();
		const auto output_node = g.add_node<Passthrough>();

		const auto and_1 = g.add_node<And>();
		const auto and_2 = g.add_node<And>();
		const auto and_3 = g.add_node<And>();
		const auto and_4 = g.add_node<And>();
		const auto and_p1 = g.add_node<And>();
		const auto and_p2 = g.add_node<And>();
		const auto and_p3 = g.add_node<And>();
		const auto and_p4 = g.add_node<And>();
		const auto or_1 = g.add_node<Or>();
		const auto or_2 = g.add_node<Or>();
		const auto or_3 = g.add_node<Or>();
		const auto not_1 = g.add_node<Not>();
		const auto not_2 = g.add_node<Not>();

		not_1->add_source(input_node_m1);
		not_2->add_source(input_node_m2);
		and_1->add_source1(and_p1);
		and_2->add_source1(and_p2);
		and_3->add_source1(and_p3);
		and_4->add_source1(and_p4);
		and_1->add_source2(input_node_i1);
		and_2->add_source2(input_node_i2);
		and_3->add_source2(input_node_i3);
		and_4->add_source2(input_node_i4);
		and_p1->add_source1(not_1);
		and_p1->add_source2(not_2);
		and_p2->add_source1(not_1);
		and_p2->add_source2(input_node_m2);
		and_p3->add_source1(input_node_m1);
		and_p3->add_source2(not_2);
		and_p4->add_source1(input_node_m1);
		and_p4->add_source2(input_node_m2);
		or_1->add_source1(and_1);
		or_1->add_source2(and_2);
		or_2->add_source1(and_3);
		or_2->add_source2(and_4);
		or_3->add_source1(or_1);
		or_3->add_source2(or_2);
		output_node->add_source(or_3);

		return { input_node_i1,
			input_node_i2,
			input_node_i3,
			input_node_i4,
			input_node_m1,
			input_node_m2,
			output_node };
	}

	arithmetic_logic_unit_1_bit_io_t create_arithmetic_logic_unit_1_bit(Graph &g)
	{
		auto [a, b, ci, s, co] = create_full_adder_1_bit(g);
		auto [i0, i1, i2, i3, m0, m1, mo] = create_multiplexer(g);

		const auto and_node = g.add_node<And>();
		const auto or_node = g.add_node<Or>();
		const auto xor_node = g.add_node<Xor>();

		and_node->add_source1(a);
		and_node->add_source2(b);
		or_node->add_source1(a);
		or_node->add_source2(b);
		xor_node->add_source1(a);
		xor_node->add_source2(b);

		i0->add_source(s);
		i1->add_source(and_node);
		i2->add_source(or_node);
		i3->add_source(xor_node);

		return { a, b, ci, m0, m1, mo, co };
	}

	arithmetic_logic_unit_8_bit_io_t create_arithmetic_logic_unit_8_bit(Graph &g)
	{
		arithmetic_logic_unit_8_bit_io_t result;

		arithmetic_logic_unit_1_bit_io_t current;

		{
			const auto temp = create_arithmetic_logic_unit_1_bit(g);

			current = temp;

			result.m_input_c = current.m_input_c;
			result.m_input_m0 = current.m_input_m0;
			result.m_input_m1 = current.m_input_m1;
			result.m_input_a0 = current.m_input_a;
			result.m_input_b0 = current.m_input_b;
			result.m_output_s0 = current.m_output_s;
		}

		{
			const auto temp = create_arithmetic_logic_unit_1_bit(g);
			temp.m_input_c->add_source(current.m_output_c);
			temp.m_input_m0->add_source(current.m_input_m0);
			temp.m_input_m1->add_source(current.m_input_m1);

			current = temp;

			result.m_input_a1 = current.m_input_a;
			result.m_input_b1 = current.m_input_b;
			result.m_output_s1 = current.m_output_s;
		}

		{
			const auto temp = create_arithmetic_logic_unit_1_bit(g);
			temp.m_input_c->add_source(current.m_output_c);
			temp.m_input_m0->add_source(current.m_input_m0);
			temp.m_input_m1->add_source(current.m_input_m1);

			current = temp;

			result.m_input_a2 = current.m_input_a;
			result.m_input_b2 = current.m_input_b;
			result.m_output_s2 = current.m_output_s;
		}

		{
			const auto temp = create_arithmetic_logic_unit_1_bit(g);
			temp.m_input_c->add_source(current.m_output_c);
			temp.m_input_m0->add_source(current.m_input_m0);
			temp.m_input_m1->add_source(current.m_input_m1);

			current = temp;

			result.m_input_a3 = current.m_input_a;
			result.m_input_b3 = current.m_input_b;
			result.m_output_s3 = current.m_output_s;
		}

		{
			const auto temp = create_arithmetic_logic_unit_1_bit(g);
			temp.m_input_c->add_source(current.m_output_c);
			temp.m_input_m0->add_source(current.m_input_m0);
			temp.m_input_m1->add_source(current.m_input_m1);

			current = temp;

			result.m_input_a4 = current.m_input_a;
			result.m_input_b4 = current.m_input_b;
			result.m_output_s4 = current.m_output_s;
		}

		{
			const auto temp = create_arithmetic_logic_unit_1_bit(g);
			temp.m_input_c->add_source(current.m_output_c);
			temp.m_input_m0->add_source(current.m_input_m0);
			temp.m_input_m1->add_source(current.m_input_m1);

			current = temp;

			result.m_input_a5 = current.m_input_a;
			result.m_input_b5 = current.m_input_b;
			result.m_output_s5 = current.m_output_s;
		}

		{
			const auto temp = create_arithmetic_logic_unit_1_bit(g);
			temp.m_input_c->add_source(current.m_output_c);
			temp.m_input_m0->add_source(current.m_input_m0);
			temp.m_input_m1->add_source(current.m_input_m1);

			current = temp;

			result.m_input_a6 = current.m_input_a;
			result.m_input_b6 = current.m_input_b;
			result.m_output_s6 = current.m_output_s;
		}

		{
			const auto temp = create_arithmetic_logic_unit_1_bit(g);
			temp.m_input_c->add_source(current.m_output_c);
			temp.m_input_m0->add_source(current.m_input_m0);
			temp.m_input_m1->add_source(current.m_input_m1);

			current = temp;

			result.m_input_a7 = current.m_input_a;
			result.m_input_b7 = current.m_input_b;
			result.m_output_s7 = current.m_output_s;
			result.m_output_c = current.m_output_c;
		}

		return result;
	}

	void register_full_adder_1_bit_io_nodes(Graph &g, full_adder_1_bit_io_t const &full_adder_1_bit_io)
	{
		g.register_input(full_adder_1_bit_io.m_input_a, "A");
		g.register_input(full_adder_1_bit_io.m_input_b, "B");
		g.register_input(full_adder_1_bit_io.m_input_c, "Cin");
		g.register_output(full_adder_1_bit_io.m_output_s, "S");
		g.register_output(full_adder_1_bit_io.m_output_c, "Cout");
	}

	void register_full_adder_8_bit_io_nodes(Graph &g, full_adder_8_bit_io_t const &full_adder_8_bit_io)
	{
		// Input bit 0
		g.register_input(full_adder_8_bit_io.m_input_a0, "A0");
		g.register_input(full_adder_8_bit_io.m_input_b0, "B0");
		g.register_output(full_adder_8_bit_io.m_output_s0, "S0");

		// Input bit 1
		g.register_input(full_adder_8_bit_io.m_input_a1, "A1");
		g.register_input(full_adder_8_bit_io.m_input_b1, "B1");
		g.register_output(full_adder_8_bit_io.m_output_s1, "S1");

		// Input bit 2
		g.register_input(full_adder_8_bit_io.m_input_a2, "A2");
		g.register_input(full_adder_8_bit_io.m_input_b2, "B2");
		g.register_output(full_adder_8_bit_io.m_output_s2, "S2");

		// Input bit 3
		g.register_input(full_adder_8_bit_io.m_input_a3, "A3");
		g.register_input(full_adder_8_bit_io.m_input_b3, "B3");
		g.register_output(full_adder_8_bit_io.m_output_s3, "S3");

		// Input bit 4
		g.register_input(full_adder_8_bit_io.m_input_a4, "A4");
		g.register_input(full_adder_8_bit_io.m_input_b4, "B4");
		g.register_output(full_adder_8_bit_io.m_output_s4, "S4");

		// Input bit 5
		g.register_input(full_adder_8_bit_io.m_input_a5, "A5");
		g.register_input(full_adder_8_bit_io.m_input_b5, "B5");
		g.register_output(full_adder_8_bit_io.m_output_s5, "S5");

		// Input bit 6
		g.register_input(full_adder_8_bit_io.m_input_a6, "A6");
		g.register_input(full_adder_8_bit_io.m_input_b6, "B6");
		g.register_output(full_adder_8_bit_io.m_output_s6, "S6");

		// Input bit 7
		g.register_input(full_adder_8_bit_io.m_input_a7, "A7");
		g.register_input(full_adder_8_bit_io.m_input_b7, "B7");
		g.register_output(full_adder_8_bit_io.m_output_s7, "S7");

		// Carry bits
		g.register_input(full_adder_8_bit_io.m_input_c, "Cin");
		g.register_output(full_adder_8_bit_io.m_output_c, "Cout");
	}

	void register_multiplexer_io_nodes(Graph &g, multiplexer_io_t const &multiplexer_io)
	{
		g.register_input(multiplexer_io.m_input_i0, "I0");
		g.register_input(multiplexer_io.m_input_i1, "I1");
		g.register_input(multiplexer_io.m_input_i2, "I2");
		g.register_input(multiplexer_io.m_input_i3, "I3");
		g.register_input(multiplexer_io.m_input_m0, "M0");
		g.register_input(multiplexer_io.m_input_m1, "M1");
		g.register_output(multiplexer_io.m_output, "Y");
	}

	void register_arithmetic_logic_unit_1_bit_io_nodes(Graph &g,
		arithmetic_logic_unit_1_bit_io_t const &arithmetic_logic_unit_1_bit_io)
	{
		g.register_input(arithmetic_logic_unit_1_bit_io.m_input_a, "A");
		g.register_input(arithmetic_logic_unit_1_bit_io.m_input_b, "B");
		g.register_input(arithmetic_logic_unit_1_bit_io.m_input_c, "Cin");
		g.register_input(arithmetic_logic_unit_1_bit_io.m_input_m0, "M0");
		g.register_input(arithmetic_logic_unit_1_bit_io.m_input_m1, "M1");
		g.register_output(arithmetic_logic_unit_1_bit_io.m_output_s, "S");
		g.register_output(arithmetic_logic_unit_1_bit_io.m_output_c, "Cout");
	}

	void register_arithmetic_logic_unit_8_bit_io_nodes(Graph &g,
		arithmetic_logic_unit_8_bit_io_t const &arithmetic_logic_unit_8_bit_io)
	{
		// Input bit 0
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_a0, "A0");
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_b0, "B0");
		g.register_output(arithmetic_logic_unit_8_bit_io.m_output_s0, "S0");

		// Input bit 1
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_a1, "A1");
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_b1, "B1");
		g.register_output(arithmetic_logic_unit_8_bit_io.m_output_s1, "S1");

		// Input bit 2
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_a2, "A2");
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_b2, "B2");
		g.register_output(arithmetic_logic_unit_8_bit_io.m_output_s2, "S2");

		// Input bit 3
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_a3, "A3");
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_b3, "B3");
		g.register_output(arithmetic_logic_unit_8_bit_io.m_output_s3, "S3");

		// Input bit 4
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_a4, "A4");
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_b4, "B4");
		g.register_output(arithmetic_logic_unit_8_bit_io.m_output_s4, "S4");

		// Input bit 5
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_a5, "A5");
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_b5, "B5");
		g.register_output(arithmetic_logic_unit_8_bit_io.m_output_s5, "S5");

		// Input bit 6
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_a6, "A6");
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_b6, "B6");
		g.register_output(arithmetic_logic_unit_8_bit_io.m_output_s6, "S6");

		// Input bit 7
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_a7, "A7");
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_b7, "B7");
		g.register_output(arithmetic_logic_unit_8_bit_io.m_output_s7, "S7");

		// Carry bits
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_c, "Cin");
		g.register_output(arithmetic_logic_unit_8_bit_io.m_output_c, "Cout");
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_m0, "M0");
		g.register_input(arithmetic_logic_unit_8_bit_io.m_input_m1, "M1");
	}
}// namespace circuit::helper
