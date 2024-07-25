#ifndef TEST_CLASS_PARAMETER_PROPERTY_HPP      
#define TEST_CLASS_PARAMETER_PROPERTY_HPP
namespace edst {
enum class ParameterProperty : int {
     none,
     pointer,
     pointer_to_const,
     lvalue,
     lvalue_const,
     rvalue,
     rvalue_const,
     native,
     native_const
};
} // namespace edst
#endif // TEST_CLASS_PARAMETER_PROPERTY_HPP
