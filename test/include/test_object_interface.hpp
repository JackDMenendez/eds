#ifndef TEST_OBJECT_INTERFACE_HPP
#define TEST_OBJECT_INTERFACE_HPP
#include "object_properties.hpp"
namespace edst {
     struct TestObjectInterface {
          virtual ~TestObjectInterface() = default;
          virtual bool test(object_properties expected_properties) = 0;
     };
} // namespace edst
#endif // TEST_OBJECT_INTERFACE_HPP
