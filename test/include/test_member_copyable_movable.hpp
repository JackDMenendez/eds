#ifndef TEST_MEMBER_COPYABLE_MOVABLE_HPP
#define TEST_MEMBER_COPYABLE_MOVABLE_HPP
#include "concept_type.hpp"
#include "test_object_interface.hpp"
namespace edst {
     class TestMemberCopyMovable {
          bool m_member = false;
          mutable bool m_const_member = false;
        public:
          static bool sm_FunctionCalled;
          static ConceptType sm_ConceptType;
          TestMemberCopyMovable() noexcept = default;
          TestMemberCopyMovable(const TestMemberCopyMovable &) noexcept = default;
          TestMemberCopyMovable(TestMemberCopyMovable &&) noexcept = default;
          TestMemberCopyMovable &operator=(const TestMemberCopyMovable &) noexcept = default;
          TestMemberCopyMovable &operator=(TestMemberCopyMovable &&) noexcept = default;
          virtual ~TestMemberCopyMovable() noexcept = default;
          bool isMember() const noexcept { return m_member; }
          bool isConstMember() const noexcept { return m_const_member; }
          /**
           * @brief A member function that can be passed as a function pointer or std::function
           *
           * \param concept_type The concept that can be set and tested to make sure this
           * function ran properly.
           */
          void memberFunction(ConceptType concept_type) noexcept {
               sm_FunctionCalled = true;
               sm_ConceptType = concept_type;
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
#endif // TEST_MEMBER_COPYABLE_MOVABLE_HPP
