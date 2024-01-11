#pragma once
#include <string>

#include "Graph.h"

namespace circuit
{
	class Formatter
	{
	public:
		explicit Formatter(class Graph const &g, std::ostream *out_stream);
		Formatter(Formatter &) = delete;
		Formatter(Formatter &&) = delete;
		Formatter &operator=(Formatter &) = delete;
		Formatter &operator=(Formatter &&) = delete;
		virtual ~Formatter() = default;

		Formatter &operator<<(bool value);
		Formatter &operator<<(char value);
		virtual void flush();

	protected:
		std::ostream *m_out_stream;
		std::vector<std::string> m_inputs;
		std::vector<std::string> m_outputs;
		size_t m_current_raw;
		size_t m_current_column;
		virtual void propagate_value(bool value);
		virtual void propagate_value(char value) = 0;
	};

	class Tester final : public Formatter
	{
	public:
		explicit Tester(Graph const &g, std::ostream *out_stream);
		Tester(Tester &) = delete;
		Tester(Tester &&) = delete;
		Tester &operator=(Tester &) = delete;
		Tester &operator=(Tester &&) = delete;
		~Tester() override = default;

	protected:
		void propagate_value(char value) override;
	};

	class TablePrinter final : public Formatter
	{
	public:
		explicit TablePrinter(Graph const &g, std::ostream *out_stream);
		TablePrinter(TablePrinter &) = delete;
		TablePrinter(TablePrinter &&) = delete;
		TablePrinter &operator=(TablePrinter &) = delete;
		TablePrinter &operator=(TablePrinter &&) = delete;
		~TablePrinter() override = default;

	private:
		void print_horizontal_line() const;
		void print_header() const;

		std::string m_separator;
		size_t m_table_width;

	protected:
		void propagate_value(char value) override;
	};
}// namespace circuit