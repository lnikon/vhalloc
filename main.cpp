#include <iostream>

#include "user.hpp"

int main()
{
    auto user1 = new User{};
    delete user1;

    return 0;
}
