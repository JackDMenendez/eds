/**
 *
 * @file mainpage.h
 * @brief  Event Delegate Subscription (EDS) System Design Document
 * @details This file contains doxygen formatted comments.
 * @sa eds_main_page
 * @author Joaquín "Jack" D. Menéndez
 * @date   March 2024
 * @version 1.0
 * See also @ref index "Main Page"
 */
/** @mainpage Event Delegate Subscription (EDS) System Design Document
 * @tableofcontents{HTML:5}
 * @section introduction_sec Introduction
 * @section test_sec Testing
 * EDS testing is broken down into two categories: unit testing and integration testing.
 * @subsection how_google_test_is_used How Google Test is used
 * Event Delegate Subscription (EDS) uses Google Test to test each level of the library with a
 * separate .cpp file for unit tests and integration testing. The following table is an overview with links to the test implementation
 * files.
 *
 * Test ID  |  Fixture Class  |     File Name         |      Description       
 * -------- | --------------- | --------------------- | --------------------
 * UT04nnnn | UTToolsFT       | ToolsUGTest.cpp       | Tools Unit Testing
 * UT03nnnn | UTHashFT        | HashUGTest.cpp        | Hash Unit Testing
 * UT04nnnn | UTTraitsFT      | TraitsUGTest.cpp      | Traits Unit Testing
 * UT01nnnn | UTConceptsFT    | ConceptsUGTest.cpp    | Concepts Unit Testing
 * IT01nnnn | ITConceptsFT    | ConceptsIGTest.cpp    | Concepts Integration Testing
 * UT02nnnn | UTMemberCallFT  | MemberCallUGTest.cpp  | Member Call Unit Testing
 * IT02nnnn | ITMemberCallFT  | MemberCallIGTest.cpp  | Member Call Integration Testing
 * UT07nnnn | UTCallHandlerFT | CallHandlerUGTest.cpp | Call Handler Unit Testing
 * IT07nnnn | ITCallHandlerFT | CallHandlerIGTest.cpp | Call Handler Integration Testing
 * UT08nnnn | UTDelegateFT    | DelegateUGTest.cpp    | Delegate Unit Testing
 * IT08nnnn | ITDelegateFT    | DelegateIGTest.cpp    | Delegate Integration Testing
 * UT09nnnn | UTEventFT       | EventUGTest.cpp       | Event Unit Testing
 * IT09nnnn | ITEventFT       | EventIGTest.cpp       | Event Integration Testing
 * @subsection  concepts_unit_test Concepts Testing Strategy
 * @subsubsection concepts_test_intro Concepts Testing Introduction
 * C++ 20 introduced the <A
 * HREF="https://en.cppreference.com/w/cpp/language/constraints">concept feature</A> to the
 * language. Concepts are a way to define a set of requirements for a type to be used in a
 * template. The requirements are defined in the concept definition. The concept is used in the
 * template definition to restrict the types that can be used.
 *
 * Event Delegate Subscription (EDS) uses concepts to define the requirements for the
 * types that can be used in the subscription of a function or delegate to an event. The goal
 * of concepts unit testing is to verify that the concepts defined in eds_concepts.hpp are able
 * to isolate eligible types of functions to specific template methods via template
 * specialization. When an ineligible type is passed we test to make sure that specialization
 * is isolated such that an error via static_assert could be used to generate the error with
 * descriptive messaging.
 * 1. Test that a valid function type is selected by the specialization.
 * 2. Test that invalid functions specialize to a function that could, if needed, generate a
 * a static_assert error.
 *
 * There will be a probe in each test case that tests whether the function is a valid delegate.
 * @subsection concepts_test_layout Concepts Testing Layout
 * Tests are identified by a unique test id. The test ids for concepts run from 10100 to 19999.
 * Documentation anchors are derived from the test ids by prefixing the test id with "UT".
 * @section definitions_sec Definitions
 * @paragraph flag_definition Flag 
 * A flag is a boolean value that is used to control the flow of the program. Flags
 * are also used to hold the outcome of a test.
 */
