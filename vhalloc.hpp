#pragma once

#include <cstddef>
#include <cctype>

template <std::size_t N>
class Arena
{
    static constexpr std::size_t alignment = alignof(std::max_align_t);

    public:
    Arena() noexcept : ptr_(buffer_) {} 
    Arena(const Arena&) {};
    Arena& operator=(const Arena&) = delete;

    auto reset() noexcept { ptr_ = buffer_; }
    static constexpr auto size() noexcept { return N; }

    auto used() const noexcept
    {
        return static_cast<std::size_t>(ptr_ - buffer_);
    }

    auto allocate(std::size_t n) -> char*
    {
        const auto aligned_n = align_up(n);
        const auto available_bytes = 
            static_cast<decltype(aligned_n)>(buffer_ + N - ptr_);
        if(available_bytes >= aligned_n)
        {
            char* r = ptr_;
            ptr_ += aligned_n;
            return r;
        }

        return static_cast<char*>(::operator new(n));
    }

    auto deallocate(char* p, std::size_t n) noexcept -> void
    {
        if(pointer_in_buffer(p))
        {
            n = align_up(n);
            if(p + n == ptr_)
            {
                ptr_ = p;
            }
        }
        else
        {
            ::operator delete(p);
        }
    }

    private:
    static auto align_up(std::size_t n) noexcept -> std::size_t
    {
        return (n + (alignment - 1)) & ~(alignment - 1);
    }

    auto pointer_in_buffer(const char* p) const noexcept -> bool
    {
        return buffer_ <= p && p <= buffer_ + N;
    }

    alignas(alignment) char buffer_[N];
    char* ptr_{nullptr};
};
