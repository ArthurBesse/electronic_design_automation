#include "Simulator.h"
#pragma region Generic Simulator
GenericSimulator::Iterator::Iterator(const size_t count, const bool value) : m_bits(count, value)
{
}

GenericSimulator::Iterator::reference GenericSimulator::Iterator::operator->() const
{
	return this->operator*();
}

GenericSimulator::Iterator::reference GenericSimulator::Iterator::operator*() const
{
	return this->m_bits;
}

GenericSimulator::Iterator& GenericSimulator::Iterator::operator++()
{
	for (auto&& i : this->m_bits)
	{
		if (i == false)
		{
			i = true;
			return *this;
		}
		i = false;
	}
	this->m_bits.clear();
	this->m_bits.shrink_to_fit();
	return *this;
}

GenericSimulator::Iterator GenericSimulator::Iterator::operator++(int)
{
	Iterator result = *this;
	this->operator++();
	return result;
}

inline bool GenericSimulator::Iterator::operator==(Iterator const& iterator) const noexcept
{
	return this->m_bits == iterator.m_bits;
}

bool GenericSimulator::Iterator::operator!=(Iterator const& iterator) const noexcept
{
	return !(*this == iterator);
}

bool GenericSimulator::Iterator::operator[](const size_t index) const noexcept
{
	return this->m_bits[index];
}

GenericSimulator::GenericSimulator(const size_t count): m_count(count)
{
}

GenericSimulator::Iterator GenericSimulator::begin() const
{
	return { this->m_count, false };
}

GenericSimulator::Iterator GenericSimulator::end() const
{
	return Iterator(0, false);
}
#pragma endregion

FuzzSimulator::Iterator::Iterator(const size_t count, const bool value) : m_bits(count, value)
{
}

FuzzSimulator::Iterator::reference FuzzSimulator::Iterator::operator->() const
{
	return this->operator*();
}

FuzzSimulator::Iterator::reference FuzzSimulator::Iterator::operator*() const
{
	return this->m_bits;
}

FuzzSimulator::Iterator& FuzzSimulator::Iterator::operator++()
{
	for (auto&& i : this->m_bits)
	{
		if (i == false)
		{
			i = true;
			return *this;
		}
		i = false;
	}
	this->m_bits.clear();
	this->m_bits.shrink_to_fit();
	return *this;
}

FuzzSimulator::Iterator FuzzSimulator::Iterator::operator++(int)
{
	Iterator result = *this;
	this->operator++();
	return result;
}

inline bool FuzzSimulator::Iterator::operator==(Iterator const& iterator) const noexcept
{
	return this->m_bits == iterator.m_bits;
}

bool FuzzSimulator::Iterator::operator!=(Iterator const& iterator) const noexcept
{
	return !(*this == iterator);
}

bool FuzzSimulator::Iterator::operator[](const size_t index) const noexcept
{
	return this->m_bits[index];
}



FuzzSimulator::FuzzSimulator(const size_t count)
{
}

FuzzSimulator::Iterator FuzzSimulator::begin() const
{
	return FuzzSimulator::Iterator();
}

FuzzSimulator::Iterator FuzzSimulator::end() const
{
	return FuzzSimulator::Iterator();
}
