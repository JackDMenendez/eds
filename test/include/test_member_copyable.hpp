#ifndef TEST_MEMBER_COPYABLE_HPP
#define TEST_MEMBER_COPYABLE_HPP
#include "concept_type.hpp"
#include "function_type.hpp"
#include "test_object_interface.hpp"
namespace edst {
     class TestMemberCopyable : TestObjectInterface {
          
          bool m_member = false;
          mutable bool m_const_member = false;

          FunctionType m_function_type = FunctionType::none;
        public:
          static bool sm_FunctionCalled;
          static ConceptType sm_ConceptType;
          TestMemberCopyable() noexcept = default;
          TestMemberCopyable(const TestMemberCopyable &) noexcept = default;
          TestMemberCopyable(TestMemberCopyable &&) noexcept = delete;
          TestMemberCopyable(const TestMemberCopyable &&) noexcept = delete;
          TestMemberCopyable &operator=(const TestMemberCopyable &) noexcept = default;
          TestMemberCopyable &operator=(TestMemberCopyable &&) noexcept = delete;
          TestMemberCopyable &operator=(const TestMemberCopyable &&) noexcept = delete;

          bool test(object_properties expected_properties) override {
               return expected_properties == object_properties::copyable_and_not_movable;
          }

          virtual ~TestMemberCopyable() noexcept = default;
          bool isMember() const noexcept { return m_member; }
          bool isConstMember() const noexcept { return m_const_member; }
          FunctionType get_function_type() const noexcept { return m_function_type; }
          /**
           * @brief A member function that can be passed as a function pointer or std::function
           *
           * \param concept_type The concept that can be set and tested to make sure this
           * function ran properly.
           */
          void memberFunction(ConceptType concept_type) noexcept {
               sm_FunctionCalled = true;
               sm_ConceptType = concept_type;
               m_function_type = FunctionType::MemberFunctionPTRWithParams;
               m_member = true;
          }
          void memberConstFunction(ConceptType a) const noexcept {
               sm_FunctionCalled = true;
               sm_ConceptType = a;
               m_const_member = true;
          }
          void memberFunctionNoParams() noexcept {
               sm_FunctionCalled = true;
               sm_ConceptType = ConceptType::a_member_function_pointer_without_parameters;
               m_member = true;
          }
          void memberConstFunctionNoParams() const noexcept {
               sm_FunctionCalled = true;
               sm_ConceptType = ConceptType::a_const_member_function_pointer_without_parameters;
               m_const_member = true;
          }
     };
} // namespace edst
#endif // TEST_MEMBER_COPYABLE_HPP
