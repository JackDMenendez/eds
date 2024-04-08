
// clang-format off
/** @page unit_test_concepts_page Unit Testing EDS Concepts

There is a separate testing unit for concepts. The source code for concepts can be found at \ref eds_concepts.hpp. The unit testing
is done using Google Test framework and the source code for testing concepts can be found at \ref eds_concepts_test.cpp.

@anchor table_test_concepts_cross_reference "Test Concepts Cross Reference"

   Test ID    |            Test Name               |    Google Test Class     | Fixture Class | Test Description
------------- | ---------------------------------- | ------------------------ | ------------- | ---------------------------------------
@ref UT010100 | @ref edsUGTest.ConceptsFT.UT010100 | ConceptsFT_UT010100_Test |   ConceptsFT  | concept eds::a_regular_function_pointer
@ref UT010105 | @ref edsUGTest.ConceptsFT.UT010105 | ConceptsFT_UT010105_Test |   ConceptsFT  | concept eds::a_functional_lvalue
@ref UT010110 | @ref edsUGTest.ConceptsFT.UT010110 | ConceptsFT_UT010110_Test |   ConceptsFT  | concept eds::a_lambda_rvalue
@ref UT010115 | @ref edsUGTest.ConceptsFT.UT010115 | ConceptsFT_UT010115_Test |   ConceptsFT  | concept eds::a_functional_lvalue
@ref UT010120 | @ref edsUGTest.ConceptsFT.UT010120 | ConceptsFT_UT010120_Test |   ConceptsFT  | concept eds::a_lambda_rvalue
@ref UT010125 | @ref edsUGTest.ConceptsFT.UT010125 | ConceptsFT_UT010125_Test |   ConceptsFT  | concept eds::a_functional_lvalue
@ref UT010130 | @ref edsUGTest.ConceptsFT.UT010130 | ConceptsFT_UT010130_Test |   ConceptsFT  | concept eds::a_member_function_pointer
@ref UT010135 | @ref edsUGTest.ConceptsFT.UT010135 | ConceptsFT_UT010135_Test |   ConceptsFT  | concept eds::a_functional_lvalue
@ref UT010140 | @ref edsUGTest.ConceptsFT.UT010140 | ConceptsFT_UT010140_Test |   ConceptsFT  | concept eds::a_member_function_pointer
@ref UT010200 | @ref edsUGTest.ConceptsFT.UT010200 | ConceptsFT_UT010200_Test |   ConceptsFT  | concept eds::a_regular_function_pointer
@ref UT010205 | @ref edsUGTest.ConceptsFT.UT010205 | ConceptsFT_UT010205_Test |   ConceptsFT  | concept eds::a_functional_lvalue
@ref UT010210 | @ref edsUGTest.ConceptsFT.UT010210 | ConceptsFT_UT010210_Test |   ConceptsFT  | concept eds::a_lambda_rvalue
@ref UT010215 | @ref edsUGTest.ConceptsFT.UT010215 | ConceptsFT_UT010215_Test |   ConceptsFT  | concept eds::a_functional_lvalue
@ref UT010220 | @ref edsUGTest.ConceptsFT.UT010220 | ConceptsFT_UT010220_Test |   ConceptsFT  | concept eds::a_lambda_rvalue
@ref UT010225 | @ref edsUGTest.ConceptsFT.UT010225 | ConceptsFT_UT010225_Test |   ConceptsFT  | concept eds::a_functional_lvalue
@ref UT010230 | @ref edsUGTest.ConceptsFT.UT010230 | ConceptsFT_UT010230_Test |   ConceptsFT  | concept eds::a_member_function_pointer
@ref UT010235 | @ref edsUGTest.ConceptsFT.UT010235 | ConceptsFT_UT010235_Test |   ConceptsFT  | concept eds::a_functional_lvalue
@ref UT010240 | @ref edsUGTest.ConceptsFT.UT010240 | ConceptsFT_UT010240_Test |   ConceptsFT  | concept eds::a_member_function_pointer

The following table shows test completeness for each of the function types:

@anchor table_test_concepts_completeness "Test Concepts Completeness"

  Test ID     |             ConceptsFT::ConceptType               | Test Status | Concept
------------- | ------------------------------------------------- | ----------- | ---------------------------------------
@ref UT010100 | Concepts::ConceptType::a_regular_function_pointer | Complete    | concept eds::a_regular_function_pointer
@ref UT010105 | Concepts::ConceptType::a_functional_lvalue        | Complete    | concept eds::a_functional_lvalue
@ref UT010110 | Concepts::ConceptType::a_lambda_rvalue            | Complete    | concept eds::a_lambda_rvalue
@ref UT010115 | Concepts::ConceptType::a_functional_lvalue        | Complete    | concept eds::a_functional_lvalue
@ref UT010120 | Concepts::ConceptType::a_lambda_rvalue            | Complete    | concept eds::a_lambda_rvalue
@ref UT010125 | Concepts::ConceptType::a_functional_lvalue        | Complete    | concept eds::a_functional_lvalue
@ref UT010130 | Concepts::ConceptType::a_member_function_pointer  | Complete    | concept eds::a_member_function_pointer
@ref UT010135 | Concepts::ConceptType::a_functional_lvalue        | Complete    | concept eds::a_functional_lvalue       
@ref UT010140 | Concepts::ConceptType::a_member_function_pointer  | Complete    | concept eds::a_member_function_pointer 
@ref UT010200 | Concepts::ConceptType::a_regular_function_pointer | Complete    | concept eds::a_regular_function_pointer
@ref UT010205 | Concepts::ConceptType::a_functional_lvalue        | Complete    | concept eds::a_functional_lvalue
@ref UT010210 | Concepts::ConceptType::a_lambda_rvalue            | Complete    | concept eds::a_lambda_rvalue
@ref UT010215 | Concepts::ConceptType::a_functional_lvalue        | Complete    | concept eds::a_functional_lvalue
@ref UT010220 | Concepts::ConceptType::a_lambda_rvalue            | Complete    | concept eds::a_lambda_rvalue
@ref UT010225 | Concepts::ConceptType::a_functional_lvalue        | Complete    | concept eds::a_functional_lvalue
@ref UT010230 | Concepts::ConceptType::a_member_function_pointer  | Complete    | concept eds::a_member_function_pointer
@ref UT010235 | Concepts::ConceptType::a_functional_lvalue        | Complete    | concept eds::a_functional_lvalue       
@ref UT010240 | Concepts::ConceptType::a_member_function_pointer  | Complete    | concept eds::a_member_function_pointer 

The following table shows test coverage for each of the function types:

@anchor table_test_concepts_coverage "Test Concepts Coverage"

                   Function Type                     |       function used            | Applicable Test IDs
 --------------------------------------------------- | ------------------------------ | -------------------------------------
 a static member function                            | @ref UT010100_setConceptResult | @ref UT010100
 a std::function containing a static member function | @ref UT010105_setConceptResult | @ref UT010105
 a lambda function no capture                        | @ref UT010110_setConceptResult | @ref UT010110
 a std::function containing a non-capture lambda     | @ref UT010105_setConceptResult | @ref UT010115
 a lambda with capture                               | @ref UT010110_setConceptResult | @ref UT010120
 a std::function containing a capture lambda         | @ref UT010105_setConceptResult | @ref UT010125
 a member function pointer and object                | @ref UT010130_setConceptResult | @ref UT010130
 a member function lvalue and object                 | @ref UT010135_setConceptResult | @ref UT010135
 a pointer to a const member function                | @ref UT010140_setConceptResult | @ref UT010140
 a static member function                            | @ref UT010200_setConceptResult | @ref UT010200
 a std::function containing a static member function | @ref UT010205_setConceptResult | @ref UT010205
 a lambda function no capture                        | @ref UT010210_setConceptResult | @ref UT010210
 a std::function containing a non-capture lambda     | @ref UT010205_setConceptResult | @ref UT010215
 a lambda with capture                               | @ref UT010210_setConceptResult | @ref UT010220
 a std::function containing a capture lambda         | @ref UT010205_setConceptResult | @ref UT010225
 a member function pointer and object                | @ref UT010230_setConceptResult | @ref UT010230
 a member function lvalue and object                 | @ref UT010235_setConceptResult | @ref UT010235
 a pointer to a const member function                | @ref UT010240_setConceptResult | @ref UT010240

Go back to @ref Test 

Go back to @ref Main

 */
// clang-format on 
