#ifndef libcircuit_HPP
#define libcircuit_HPP

#include <electronic_design_automation/libcircuit_export.hpp>

[[nodiscard]] libcircuit_EXPORT int factorial(int) noexcept;

[[nodiscard]] constexpr int factorial_constexpr(int input) noexcept
{
  if (input == 0) { return 1; }

  return input * factorial_constexpr(input - 1);
}

#endif
