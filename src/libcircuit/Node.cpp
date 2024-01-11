#include <algorithm>

#include <libcircuit/Node.h>

void Node::add_sink(Node *sink) noexcept { this->m_sinks.push_back(sink); }

bool const &Node::get_result() const noexcept { return this->m_result; }

#pragma region Passthrough node imlementation
void Passthrough::add_source(Node *source) noexcept
{
	this->m_input = source;
	source->add_sink(this);
}

void Passthrough::propagate() noexcept
{
	this->m_result = this->m_input->get_result();
	std::ranges::for_each(this->m_sinks, [](Node *node) { node->propagate(); });
}
#pragma endregion

#pragma region Input node imlementation
void Input::add_source(Node *source) noexcept
{
	this->m_input = source;
	source->add_sink(this);
}

void Input::propagate() noexcept
{
	std::ranges::for_each(this->m_sinks, [](Node *node) { node->propagate(); });
}

void Input::set_value(const bool value) noexcept
{
	this->m_result = value;
	this->propagate();
}
#pragma endregion

#pragma region Output node imlementation
void Output::add_sink(Node *) noexcept {}
void Output::add_source(Node *source) noexcept
{
	this->m_input = source;
	source->add_sink(this);
}

void Output::propagate() noexcept { this->m_result = this->m_input->get_result(); }

#pragma endregion

#pragma region And node imlementation
void And::add_source1(Node *source) noexcept
{
	this->m_input1 = source;
	source->add_sink(this);
}

void And::add_source2(Node *source) noexcept
{
	this->m_input2 = source;
	source->add_sink(this);
}

void And::propagate() noexcept
{
	this->m_result = this->m_input1->get_result() && this->m_input2->get_result();
	std::ranges::for_each(this->m_sinks, [](Node *node) { node->propagate(); });
}
#pragma endregion

#pragma region Nand node imlementation
void Nand::add_source1(Node *source) noexcept
{
	this->m_input1 = source;
	source->add_sink(this);
}

void Nand::add_source2(Node *source) noexcept
{
	this->m_input2 = source;
	source->add_sink(this);
}

void Nand::propagate() noexcept
{
	this->m_result = !(this->m_input1->get_result() && this->m_input2->get_result());
	std::ranges::for_each(this->m_sinks, [](Node *node) { node->propagate(); });
}
#pragma endregion

#pragma region Or node imlementation
void Or::add_source1(Node *source) noexcept
{
	this->m_input1 = source;
	source->add_sink(this);
}

void Or::add_source2(Node *source) noexcept
{
	this->m_input2 = source;
	source->add_sink(this);
}

void Or::propagate() noexcept
{
	this->m_result = this->m_input1->get_result() || this->m_input2->get_result();
	std::ranges::for_each(this->m_sinks, [](Node *node) { node->propagate(); });
}
#pragma endregion

#pragma region Nor node imlementation
void Nor::add_source1(Node *source) noexcept
{
	this->m_input1 = source;
	source->add_sink(this);
}

void Nor::add_source2(Node *source) noexcept
{
	this->m_input2 = source;
	source->add_sink(this);
}

void Nor::propagate() noexcept
{
	this->m_result = !(this->m_input1->get_result() || this->m_input2->get_result());
	std::ranges::for_each(this->m_sinks, [](Node *node) { node->propagate(); });
}
#pragma endregion

#pragma region Xor node imlementation
void Xor::add_source1(Node *source) noexcept
{
	this->m_input1 = source;
	source->add_sink(this);
}

void Xor::add_source2(Node *source) noexcept
{
	this->m_input2 = source;
	source->add_sink(this);
}

void Xor::propagate() noexcept
{
	this->m_result = this->m_input1->get_result() ^ this->m_input2->get_result();
	std::ranges::for_each(this->m_sinks, [](Node *node) { node->propagate(); });
}
#pragma endregion

#pragma region Not node imlementation
void Not::add_source(Node *source) noexcept
{
	this->m_input = source;
	source->add_sink(this);
}

void Not::propagate() noexcept
{
	this->m_result = !this->m_input->get_result();
	std::ranges::for_each(this->m_sinks, [](Node *node) { node->propagate(); });
}
#pragma endregion
