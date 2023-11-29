#pragma once
#include <type_traits>
#include <vector>

template<typename T>
concept simulator = requires(T t)
{
	t.begin() == t.end();
	t.begin() != t.end();
	t.begin() == t.end();
}
&& std::input_iterator<typename T::Iterator>;

class GenericSimulator
{
	size_t m_count;
public:
	class Iterator final
	{
		friend class GenericSimulator;
		std::vector<bool> m_bits;

		Iterator(size_t count, bool value);

	public:
		using difference_type = std::make_signed_t<size_t>;
		using reference = std::vector<bool>const &;
		using pointer = std::vector<bool>*;
		using value_type = std::vector<bool> const;
		using iterator_category = std::input_iterator_tag;

		reference operator->() const;

		reference operator*() const;

		Iterator& operator++();

		Iterator operator++(int);

		bool operator==(Iterator const& iterator) const noexcept;

		bool operator!=(Iterator const& iterator) const noexcept;

		bool operator[](size_t index) const noexcept;
	};

	explicit GenericSimulator(const size_t count);

	[[nodiscard]] Iterator begin() const;

	[[nodiscard]] Iterator end() const;
};

class FuzzSimulator
{
	size_t m_count;
public:
	class Iterator final
	{
		friend class FuzzSimulator;
		std::vector<bool> m_bits;

		Iterator(size_t count, bool value);

	public:
		using difference_type = std::make_signed_t<size_t>;
		using reference = std::vector<bool>const&;
		using pointer = std::vector<bool>*;
		using value_type = std::vector<bool> const;
		using iterator_category = std::input_iterator_tag;

		reference operator->() const;

		reference operator*() const;

		Iterator& operator++();

		Iterator operator++(int);

		bool operator==(Iterator const& iterator) const noexcept;

		bool operator!=(Iterator const& iterator) const noexcept;

		bool operator[](size_t index) const noexcept;
	};

	explicit FuzzSimulator(const size_t count);

	[[nodiscard]] Iterator begin() const;

	[[nodiscard]] Iterator end() const;
};

