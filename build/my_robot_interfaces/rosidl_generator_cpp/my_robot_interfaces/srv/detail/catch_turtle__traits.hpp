// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from my_robot_interfaces:srv/CatchTurtle.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_INTERFACES__SRV__DETAIL__CATCH_TURTLE__TRAITS_HPP_
#define MY_ROBOT_INTERFACES__SRV__DETAIL__CATCH_TURTLE__TRAITS_HPP_

#include "my_robot_interfaces/srv/detail/catch_turtle__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

namespace rosidl_generator_traits
{

inline void to_yaml(
  const my_robot_interfaces::srv::CatchTurtle_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "name: ";
    value_to_yaml(msg.name, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const my_robot_interfaces::srv::CatchTurtle_Request & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<my_robot_interfaces::srv::CatchTurtle_Request>()
{
  return "my_robot_interfaces::srv::CatchTurtle_Request";
}

template<>
inline const char * name<my_robot_interfaces::srv::CatchTurtle_Request>()
{
  return "my_robot_interfaces/srv/CatchTurtle_Request";
}

template<>
struct has_fixed_size<my_robot_interfaces::srv::CatchTurtle_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<my_robot_interfaces::srv::CatchTurtle_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<my_robot_interfaces::srv::CatchTurtle_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

inline void to_yaml(
  const my_robot_interfaces::srv::CatchTurtle_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    value_to_yaml(msg.success, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const my_robot_interfaces::srv::CatchTurtle_Response & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<my_robot_interfaces::srv::CatchTurtle_Response>()
{
  return "my_robot_interfaces::srv::CatchTurtle_Response";
}

template<>
inline const char * name<my_robot_interfaces::srv::CatchTurtle_Response>()
{
  return "my_robot_interfaces/srv/CatchTurtle_Response";
}

template<>
struct has_fixed_size<my_robot_interfaces::srv::CatchTurtle_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<my_robot_interfaces::srv::CatchTurtle_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<my_robot_interfaces::srv::CatchTurtle_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<my_robot_interfaces::srv::CatchTurtle>()
{
  return "my_robot_interfaces::srv::CatchTurtle";
}

template<>
inline const char * name<my_robot_interfaces::srv::CatchTurtle>()
{
  return "my_robot_interfaces/srv/CatchTurtle";
}

template<>
struct has_fixed_size<my_robot_interfaces::srv::CatchTurtle>
  : std::integral_constant<
    bool,
    has_fixed_size<my_robot_interfaces::srv::CatchTurtle_Request>::value &&
    has_fixed_size<my_robot_interfaces::srv::CatchTurtle_Response>::value
  >
{
};

template<>
struct has_bounded_size<my_robot_interfaces::srv::CatchTurtle>
  : std::integral_constant<
    bool,
    has_bounded_size<my_robot_interfaces::srv::CatchTurtle_Request>::value &&
    has_bounded_size<my_robot_interfaces::srv::CatchTurtle_Response>::value
  >
{
};

template<>
struct is_service<my_robot_interfaces::srv::CatchTurtle>
  : std::true_type
{
};

template<>
struct is_service_request<my_robot_interfaces::srv::CatchTurtle_Request>
  : std::true_type
{
};

template<>
struct is_service_response<my_robot_interfaces::srv::CatchTurtle_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // MY_ROBOT_INTERFACES__SRV__DETAIL__CATCH_TURTLE__TRAITS_HPP_
