// sandbox.cpp: define el punto de entrada de la aplicación.
//

#include <cassert>
#include <iostream>
#include <type_traits>
template <typename T>
static constexpr bool is_class_v = std::is_class_v<std::remove_pointer_t<std::remove_reference_t<T>>>; // transfered
template <typename T>
concept a_class = is_class_v<T>;
template <typename T>
static constexpr bool is_copyable_v =
    (std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>);
template <typename T>
concept Copyable = is_copyable_v<T>;
template <typename T> static constexpr bool is_NotCopyable_v = !is_copyable_v<T>;
template <typename T>
concept NotCopyable = is_NotCopyable_v<T>;
/**
 * Trait checks for movable type.
 *
 * The `std::remove_reference_t<...>` is necessary because there is still a reference stuck to
 * the type on an rvalue call, at least with MSVC.
 */
template <typename T>
static constexpr bool is_Movable_v =
    std::is_move_constructible_v<std::remove_reference_t<T>> &&
    std::is_move_assignable_v<std::remove_reference_t<T>>;
template <typename T>
concept Movable = is_Movable_v<T>;
template <typename T> static constexpr bool is_NotMovable_v = !is_Movable_v<T>;
template <typename T>
concept NotMovable = is_NotMovable_v<T>;
template <typename T>
static constexpr bool is_NotCopyableNotMovable_v = is_NotCopyable_v<T> && is_NotMovable_v<T>;
template <typename T>
concept NotCopyableAndNotMovable = is_NotCopyableNotMovable_v<T>;
template <typename T>
static constexpr bool is_CopyableAndMovable_v = is_copyable_v<T> && is_Movable_v<T>;
template <typename T>
concept CopyableAndMovable = is_CopyableAndMovable_v<T>;
template <typename T>
static constexpr bool is_CopyableOrMovable_v = is_copyable_v<T> || is_Movable_v<T>;
template <typename T>
concept CopyableOrMovable = is_CopyableOrMovable_v<T>;
template <typename T>
static constexpr bool is_CopyableNotMovable_v = is_copyable_v<T> && is_NotMovable_v<T>;
template <typename T>
concept CopyableAndNotMovable = is_CopyableNotMovable_v<T>;
template <typename T>
static constexpr bool is_NotCopyableAndMovable_v = is_NotCopyable_v<T> && is_Movable_v<T>;
template <typename T>
concept NotCopyableAndMovable = is_NotCopyableAndMovable_v<T>;
struct A {};

class B {};

enum class E {};

union U {
     class UC {};
};
static_assert(not std::is_class_v<U>);
static_assert(std::is_class_v<U::UC>);

class NotCopyableNotMovable {
     bool m_i_said_it = false;

   public:
     NotCopyableNotMovable() noexcept = default;
     ~NotCopyableNotMovable() noexcept = default;
     NotCopyableNotMovable(const NotCopyableNotMovable &other) noexcept = delete;
     NotCopyableNotMovable(NotCopyableNotMovable &&other) noexcept = delete;
     NotCopyableNotMovable &operator=(const NotCopyableNotMovable &other) noexcept = delete;
     NotCopyableNotMovable &operator=(NotCopyableNotMovable &&other) noexcept = delete;

     void say_it() {
          std::cout << "Not Copyable Not Movable";
          m_i_said_it = true;
     }
     bool did_i_say_it() const noexcept { return m_i_said_it; }
};
class NotExplicit {
     bool m_i_said_it = false;

   public:
     void say_it() {
          std::cout << "Not Explicit";
          m_i_said_it = true;
     }
     bool did_i_say_it() const noexcept { return m_i_said_it; }
};
class NotCopyableMovable {
     bool m_i_said_it = false;

   public:
     NotCopyableMovable() noexcept = default;
     ~NotCopyableMovable() noexcept = default;
     NotCopyableMovable(NotCopyableMovable &&other) noexcept = default;
     NotCopyableMovable &operator=(NotCopyableMovable &&other) noexcept = default;
     NotCopyableMovable(const NotCopyableMovable &other) noexcept = delete;
     NotCopyableMovable &operator=(const NotCopyableMovable &other) noexcept = delete;

     void say_it() {
          std::cout << "Not Copyable Movable";
          m_i_said_it = true;
     }
     bool did_i_say_it() const noexcept { return m_i_said_it; }
};
class CopyableNotMovable {
     bool m_i_said_it = false;

   public:
     CopyableNotMovable() noexcept = default;
     ~CopyableNotMovable() noexcept = default;
     CopyableNotMovable(const CopyableNotMovable &other) noexcept = default;
     CopyableNotMovable(CopyableNotMovable &&other) noexcept = delete;
     CopyableNotMovable &operator=(const CopyableNotMovable &other) noexcept = default;
     CopyableNotMovable &operator=(CopyableNotMovable &&other) noexcept = delete;

     void say_it() {
          std::cout << "Copyable Not Movable";
          m_i_said_it = true;
     }
     bool did_i_say_it() const noexcept { return m_i_said_it; }
};
class CopyableMovable {
     bool m_i_said_it = false;

   public:
     CopyableMovable() noexcept = default;
     ~CopyableMovable() noexcept = default;
     CopyableMovable(const CopyableMovable &other) noexcept = default;
     CopyableMovable(CopyableMovable &&other) noexcept = default;
     CopyableMovable &operator=(const CopyableMovable &other) noexcept = default;
     CopyableMovable &operator=(CopyableMovable &&other) noexcept = default;

     void say_it() {
          std::cout << "Copyable And Movable";
          m_i_said_it = true;
     }
     bool did_i_say_it() const noexcept { return m_i_said_it; }
};
class SayItController {
   public:
     SayItController() noexcept {}

     template <typename SOMEBODY>
          requires NotCopyableAndNotMovable<SOMEBODY> && a_class<SOMEBODY>
     void MakeItSayIt(SOMEBODY *somebody_who_can) {
          std::cout << "Pointer " << typeid(SOMEBODY).name() << ": \"";
          somebody_who_can->say_it();
          std::cout << "\"" << std::endl;
     }
     template <typename SOMEBODY>
          requires CopyableOrMovable<SOMEBODY> && a_class<SOMEBODY>
     void MakeItSayIt(SOMEBODY *somebody_who_can) {
          static_assert(!is_CopyableOrMovable_v<SOMEBODY>,
                        "1. The copyable or movable class must be passed as a reference");
     }
     template <typename SOMEBODY>
          requires NotCopyableAndNotMovable<SOMEBODY> && a_class<SOMEBODY>

     void MakeItSayIt(SOMEBODY &somebody_who_can) {
          static_assert(!is_NotCopyableNotMovable_v<SOMEBODY>,
                        "2. The non-copyable class must be passed as a pointer");
     }
     template <typename SOMEBODY>
          requires CopyableAndNotMovable<SOMEBODY> && a_class<SOMEBODY>
     void MakeItSayIt(SOMEBODY &somebody_who_can) {
          std::cout << "lvalue Copyable(" << is_copyable_v<SOMEBODY> << ") Movable("
                    << is_Movable_v<SOMEBODY> << ") " << typeid(SOMEBODY).name() << ": \"";
          somebody_who_can.say_it();
          std::cout << "\"" << std::endl;
     }
     template <typename SOMEBODY>
          requires Movable<SOMEBODY> && a_class<SOMEBODY>
     void MakeItSayIt(SOMEBODY &&somebody_who_can) {
          std::cout << "rvalue Copyable(" << is_copyable_v<SOMEBODY> << ") Movable("
                    << is_Movable_v<SOMEBODY> << ") " << typeid(SOMEBODY).name() << ": \"";
          somebody_who_can.say_it();
          std::cout << "\"" << std::endl;
     }

     ~SayItController() {}
};

int main() {
     std::cout << std::boolalpha;
     std::cout << is_class_v<A> << ": A\n";
     std::cout << is_class_v<B> << ": B\n";
     std::cout << is_class_v<B *> << ": B*\n";
     std::cout << is_class_v<B &> << ": B&\n";
     std::cout << is_class_v<const B> << ": const B\n";
     std::cout << is_class_v<E> << ": E\n";
     std::cout << is_class_v<int> << ": int\n";
     std::cout << is_class_v<struct S> << ": struct S (incomplete)\n";
     std::cout << is_class_v<class C> << ": class C (incomplete)\n";
     SayItController controller;
     NotCopyableNotMovable notCopyableNotMovable;
     CopyableNotMovable copyableNotMovable;
     NotCopyableMovable notCopyableMovable;
     CopyableMovable copyableMovable;
     NotExplicit notExplicit;
     controller.MakeItSayIt(&notCopyableNotMovable);
     // controller.MakeItSayIt(notCopyableNotMovable); // fails 2. The non-copyable
     // non-moveable class must be passed as a pointer
     // controller.MakeItSayIt(&copyableMovable); // fails 1. The copyable or movable class
     // must be passed as a reference controller.MakeItSayIt(&copyableNotMovable); // fails 1.
     // The copyable or movable class must be passed as a reference
     // controller.MakeItSayIt(&notCopyableMovable);  // fails 1. The copyable or movable class
     // must be passed as a reference controller.MakeItSayIt(&notExplicit); // fails 1. The
     // copyable or movable class must be passed as a reference
     controller.MakeItSayIt(copyableMovable);
     controller.MakeItSayIt(copyableNotMovable);
     controller.MakeItSayIt(notCopyableMovable);
     controller.MakeItSayIt(notExplicit);
     return 0;
}
