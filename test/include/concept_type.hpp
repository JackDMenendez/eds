#ifndef CONCEPT_TYPE_HPP
#define CONCEPT_TYPE_HPP
namespace edst {
     /** @brief enumerated types of functions for probes to test. */
     enum class ConceptType : int {
          a_regular_function,                        ///< A global or static function
          a_regular_function_except,                        ///< A global or static function
          a_regular_function_except_rc,                        ///< A global or static function
          a_regular_function_rc,                        ///< A global or static function
          a_regular_function_pointer,                ///< del A global or static function
          a_regular_function_pointer_without_params, ///< A global or static function with no
                                                     ///< parameters
          a_functional_lvalue,                       ///< A std::function
          a_functional_rvalue,                       ///< A std::function
          a_unique_ptr_functional_value,            ///< A unique_ptr containing std::function
          a_unique_ptr_functional_lvalue,            ///< A unique_ptr containing std::function
          a_unique_ptr_functional_rvalue,            ///< A unique_ptr containing std::function
          a_shared_ptr_functional_value,            ///< A unique_ptr containing std::function
          a_shared_ptr_functional_lvalue,            ///< A unique_ptr containing std::function
          a_shared_ptr_functional_rvalue,            ///< A unique_ptr containing std::function
          a_functional_lvalue_without_parameters,    ///< A std::function
          a_lambda_rvalue,                           ///< A lambda functor
          a_lambda_rvalue_without_parameters,        ///< A lambda functor
          a_member_function_pointer,                 ///< A a_member_function_pointer function
          a_member_function_pointer_without_parameters, ///< A a_member_function_pointer function
          const_member, ///< A const a_member_function_pointer function
          a_const_member_function_pointer_without_parameters, ///< A const a_member_function_pointer function
          not_allowed, ///< A function combination that is not allowed
          none          ///< No function type
     };
     enum class TypeDecoration {
           none,
           unique_ptr,
           shared_ptr
     };
} // namespace edst
#endif // CONCEPT_TYPE_HPP
