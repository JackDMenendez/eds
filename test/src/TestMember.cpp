#include "concept_type.hpp"
#include "function_type.hpp"
#include "test_member.hpp"
#include "test_class_forwarding_property.hpp"
#include "test_class_parameter_property.hpp"
bool edst::TestMember::EDST_TEST_MEMBER_FUNCTION_CALLED = false;
bool edst::TestMember::EDST_TEST_MEMBER_INSTANCE_CALLED = false;
bool edst::TestMember::sm_const_member = false;
int edst::TestMember::sm_test_id = 0;
edst::ConceptType edst::TestMember::sm_concept_type = edst::ConceptType::none;
edst::FunctionType edst::TestMember::sm_function_type = edst::FunctionType::none;
edst::ConceptType edst::TestMember::sm_requested_concept_type = edst::ConceptType::none;

