#ifndef OBJECT_PROPERTIES_HPP
#define OBJECT_PROPERTIES_HPP
namespace edst {
     enum class object_properties { not_copyable_and_not_movable,
          copyable_and_not_movable,
          copyable_and_movable,
          not_copyable_and_movable,
           none
     };
} // namespace edst
#endif // OBJECT_PROPERTIES_HPP
