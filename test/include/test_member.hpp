#ifndef TEST_MEMBER_HPP
#define TEST_MEMBER_HPP
#include "concept_type.hpp"
#include "object_properties.hpp"
#include "function_type.hpp"
#include "../include/test_class_forwarding_property.hpp"
#include "../include/test_class_parameter_property.hpp"
#include "test_object_interface.hpp"
#define EDST_TEST_MEMBER_FUNCTION_CALLED sm_function_called
#define EDST_TEST_MEMBER_INSTANCE_CALLED sm_member_called
#define EDST_TEST_MEMBER_CONST_MEMBER sm_const_member
#define EDST_TEST_MEMBER_CONCEPT_TYPE sm_concept_type
#define EDST_TEST_MEMBER_FUNCTION_TYPE sm_function_type
#define EDST_TEST_MEMBER_TEST_ID sm_test_id
#define EDST_TEST_MEMBER_REQUESTED_CONCEPT_TYPE sm_requested_concept_type
namespace edst {
     class TestMember : TestObjectInterface {
          
        public:
          static bool EDST_TEST_MEMBER_FUNCTION_CALLED;
          static ConceptType EDST_TEST_MEMBER_CONCEPT_TYPE;
          static FunctionType EDST_TEST_MEMBER_FUNCTION_TYPE;
          static bool EDST_TEST_MEMBER_INSTANCE_CALLED;
          static bool EDST_TEST_MEMBER_CONST_MEMBER;
          static ConceptType EDST_TEST_MEMBER_REQUESTED_CONCEPT_TYPE;
          static int EDST_TEST_MEMBER_TEST_ID;
          TestMember() noexcept = default;
          TestMember(const TestMember &) noexcept = delete;
          TestMember(TestMember &&) noexcept = delete;
          TestMember(const TestMember &&) noexcept = delete;
          TestMember &operator=(const TestMember &) noexcept = delete;
          TestMember &operator=(TestMember &&) noexcept = delete;
          TestMember &operator=(const TestMember &&) noexcept = delete;
          bool test(object_properties expected_properties) override {
               return expected_properties == object_properties::not_copyable_and_not_movable;
          }
          virtual ~TestMember() noexcept = default;   
          bool isMember() const noexcept { return EDST_TEST_MEMBER_INSTANCE_CALLED; }
          bool isConstMember() const noexcept { return sm_const_member; }
          FunctionType get_function_type() const noexcept { return sm_function_type; }
          static void StaticMemberWithParams(ConceptType concept_type, int test_id) noexcept {
               EDST_TEST_MEMBER_FUNCTION_CALLED = true;
               EDST_TEST_MEMBER_CONCEPT_TYPE = concept_type;
               EDST_TEST_MEMBER_FUNCTION_TYPE = FunctionType::StaticMemberWithParams;
               EDST_TEST_MEMBER_INSTANCE_CALLED = false;
               EDST_TEST_MEMBER_CONST_MEMBER = false;
               EDST_TEST_MEMBER_TEST_ID = test_id;
          }
          static void StaticMemberWithoutNoexcept(ConceptType concept_type, int test_id) {
              }
          static int StaticMemberWithRC(ConceptType concept_type, int test_id) noexcept { return 0;
              }
          static int StaticMemberWithRCExcept(ConceptType concept_type, int test_id) { return 0;
              }
          static void StaticMemberWithoutParams() noexcept {
               EDST_TEST_MEMBER_FUNCTION_CALLED = true;
               EDST_TEST_MEMBER_FUNCTION_TYPE = FunctionType::StaticMemberWithoutParams;
               EDST_TEST_MEMBER_INSTANCE_CALLED = false;
               EDST_TEST_MEMBER_CONST_MEMBER = false;
          }
          void memberFunction(ConceptType concept_type) noexcept {
          }
          void memberConstFunction(ConceptType a) const noexcept {
          }
          void memberFunctionNoParams() noexcept {
          }
          void memberConstFunctionNoParams() const noexcept {
          }
     }; // class TestMember
} // namespace edst
#endif // TEST_MEMBER_HPP
