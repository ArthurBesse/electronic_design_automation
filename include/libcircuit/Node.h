#pragma once
#include <list>

class Node
{
protected:
	bool m_result = false;
	std::list<Node *> m_sinks;

public:
	virtual void propagate() noexcept = 0;
	virtual void add_sink(Node *sink) noexcept;

	Node() = default;
	Node(Node const &) = delete;
	Node(Node &&) = delete;
	Node &operator=(Node const &) = delete;
	Node &operator=(Node &&) = delete;
	virtual ~Node() = default;

	[[nodiscard]] bool const &get_result() const noexcept;
};

class Input final : public Node
{
	Node *m_input = nullptr;

public:
	void add_source(Node *source) noexcept;
	void propagate() noexcept override;
	void set_value(bool value) noexcept;
};

class Passthrough final : public Node
{
	Node *m_input = nullptr;

public:
	void add_source(Node *source) noexcept;
	void propagate() noexcept override;
};

class Output final : public Node
{
	Node *m_input = nullptr;
	void add_sink(Node *) noexcept override;

public:
	void add_source(Node *source) noexcept;
	void propagate() noexcept override;
};

class And final : public Node
{
	Node *m_input1 = nullptr;
	Node *m_input2 = nullptr;

public:
	void add_source1(Node *source) noexcept;
	void add_source2(Node *source) noexcept;
	void propagate() noexcept override;
};

class Nand final : public Node
{
	Node *m_input1 = nullptr;
	Node *m_input2 = nullptr;

public:
	void add_source1(Node *source) noexcept;
	void add_source2(Node *source) noexcept;
	void propagate() noexcept override;
};

class Or final : public Node
{
	Node *m_input1 = nullptr;
	Node *m_input2 = nullptr;

public:
	void add_source1(Node *source) noexcept;
	void add_source2(Node *source) noexcept;
	void propagate() noexcept override;
};

class Nor final : public Node
{
	Node *m_input1 = nullptr;
	Node *m_input2 = nullptr;

public:
	void add_source1(Node *source) noexcept;
	void add_source2(Node *source) noexcept;
	void propagate() noexcept override;
};

class Xor final : public Node
{
	Node *m_input1 = nullptr;
	Node *m_input2 = nullptr;

public:
	void add_source1(Node *source) noexcept;
	void add_source2(Node *source) noexcept;
	void propagate() noexcept override;
};

class Not final : public Node
{
	Node *m_input = nullptr;

public:
	void add_source(Node *source) noexcept;
	void propagate() noexcept override;
};
