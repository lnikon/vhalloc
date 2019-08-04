#pragma once

#include <cctype>

template <std::size_t N>
class Arena
{
  static constexpr std::size_t alignment = alignof(std::max_align_t);

  public:
  Arena() noexcept : ptr_(buffer_) {} 
  Arena(const Arena&) = delete;
  Arena& operator=(const Arena&) = delete;

  auto reset() noexcept { ptr_ = buffer_; }
  static constexpr auto size() noexcept { return N; }

  auto used() <F2>;
