#pragma once

#include "vhalloc.hpp"

auto user_arena = Arena<1024>{};

class User
{
    public:
        auto operator new(std::size_t size) -> void* 
        {
            return user_arena.allocate(size);
        }

        auto operator delete(void* p) -> void
        {
            user_arena.deallocate(static_cast<char*>(p), sizeof(User));
        }

        auto operator new[](std::size_t size) -> void*
        {
            return user_arena.allocate(size);
        }

        auto operator delete[](void* p, std::size_t size) -> void
        {
            user_arena.deallocate(static_cast<char*>(p), size);
        }

    private:
        int id_{0};
};
