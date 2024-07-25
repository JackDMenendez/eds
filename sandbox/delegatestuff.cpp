#include "eds_event.hpp"


constexpr void staticMemberPointer(int *_count, int amount) noexcept { *_count += amount; }
using delegate_t = eds::Delegate<void(int*,int) noexcept>;
int main(int argc, char const *argv[]) { 
     int count = 0;
     auto test_delegate = delegate_t::make_delegate(staticMemberPointer);
     test_delegate(&count, 5);
     return count;
}
