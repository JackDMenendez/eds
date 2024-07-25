#ifndef FUNCTION_TYPE_HPP
#define FUNCTION_TYPE_HPP
namespace edst {
enum class FunctionType : int {
     none,
     MemberFunctionPTRWithParams,
     StaticMemberWithParams,  // Checked
     StaticMemberWithoutParams,  // Checked
     lambdaNoClosure,
     lambdaWithClosure,
     STDFunctionLambda,
     UniquePTRSTDFunctionLambda,
     SharedPTRSTDFunctionLambda,
     STDMoveOnlyFunctionLambda
};
} // namespace edst
#endif
