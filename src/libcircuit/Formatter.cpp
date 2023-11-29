#include "Formatter.h"
#include "Formatter.h"
#include "Formatter.h"
#include <iomanip>
#include <ios>

#include "Formatter.h"

namespace circuit
{
    Formatter::Formatter(Graph const& g, std::ostream* out_stream)
        : m_out_stream(out_stream)
    {
        std::ranges::copy(g.get_inputs() | std::ranges::views::keys, std::back_inserter(this->m_inputs));
        std::ranges::copy(g.get_outputs() | std::ranges::views::keys, std::back_inserter(this->m_outputs));
        this->m_outputs.emplace_back("Status");
    }


    Formatter& Formatter::operator<<(const bool value)
    {
        this->propagate_value(value);
        return *this;
    }

    Formatter& Formatter::operator<<(const char value)
    {
        this->propagate_value(value);
        return *this;
    }

    void Formatter::flush()
    {
        while (m_current_column != 0)
            this->propagate_value('U');
    }


    void Formatter::propagate_value(bool value)
    {
        this->propagate_value(value ? '1' : '0');
    }

    Tester::Tester(Graph const& g, std::ostream* out_stream)
        : Formatter(g, out_stream)
        , m_current_raw(0)
        , m_current_column(0)
    {
    }

    void Tester::propagate_value(char value)
    {
        if (this->m_current_column + 1 == this->m_inputs.size() + m_outputs.size())
        {
            ++this->m_current_raw;
            this->m_current_column = 0;
            *this->m_out_stream << "Case #" << m_current_raw << ": " << value << '\n';
        }
        else
        {
            ++this->m_current_column;
        }
    }

    TablePrinter::TablePrinter(Graph const& g, std::ostream* out_stream)
        : Formatter(g, out_stream)
        , m_separator("|")
        , m_current_raw(0)
        , m_current_column(0)
        , m_table_width(1)
    {
        for (auto const& c : this->m_inputs)
            m_table_width += c.size() + 3;
        for (auto const& c : this->m_outputs)
            m_table_width += c.size() + 3;
        this->print_header();
    }

    void TablePrinter::propagate_value(char value)
    {
        if (this->m_current_column == 0) *this->m_out_stream << this->m_separator;

        *this->m_out_stream << std::left;
        auto const& current_column = this->m_current_column < this->m_inputs.size() ?
            this->m_inputs[this->m_current_column] : this->m_outputs[this->m_current_column - this->m_inputs.size()];
        *this->m_out_stream << std::setw(static_cast<std::streamsize>(current_column.size() + 2)) << value;
        *this->m_out_stream << this->m_separator;

        if (this->m_current_column + 1 == this->m_inputs.size() + m_outputs.size())
        {
            *this->m_out_stream << '\n';
            this->print_horizontal_line();
            ++this->m_current_raw;
            this->m_current_column = 0;
        }
        else
        {
            ++this->m_current_column;
        }
    }

    void TablePrinter::print_horizontal_line() const
    {
        *this->m_out_stream << '+';

        for (size_t i = 1; i + 1 < m_table_width; ++i) *this->m_out_stream << '-';

        *this->m_out_stream << '+';
        *this->m_out_stream << '\n';
    }

    void TablePrinter::print_header() const
    {
        this->print_horizontal_line();
        *this->m_out_stream << this->m_separator;

        for (const auto& m_input : this->m_inputs)
        {

            *this->m_out_stream << std::left;
            *this->m_out_stream << std::setw(static_cast<std::streamsize>(m_input.size() + 2))
                << m_input;

            *this->m_out_stream << this->m_separator;
        }

        for (const auto& m_output : this->m_outputs)
        {

            *this->m_out_stream << std::left;
            *this->m_out_stream << std::setw(static_cast<std::streamsize>(m_output.size() + 2))
                << m_output;

            *this->m_out_stream << this->m_separator;
        }
        *this->m_out_stream << '\n';
        this->print_horizontal_line();
    }

}
