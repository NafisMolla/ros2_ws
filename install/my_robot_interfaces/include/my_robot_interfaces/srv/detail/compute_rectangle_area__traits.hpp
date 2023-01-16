// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from my_robot_interfaces:srv/ComputeRectangleArea.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_INTERFACES__SRV__DETAIL__COMPUTE_RECTANGLE_AREA__TRAITS_HPP_
#define MY_ROBOT_INTERFACES__SRV__DETAIL__COMPUTE_RECTANGLE_AREA__TRAITS_HPP_

#include "my_robot_interfaces/srv/detail/compute_rectangle_area__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

namespace rosidl_generator_traits
{

inline void to_yaml(
  const my_robot_interfaces::srv::ComputeRectangleArea_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: length
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "length: ";
    value_to_yaml(msg.length, out);
    out << "\n";
  }

  // member: width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "width: ";
    value_to_yaml(msg.width, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const my_robot_interfaces::srv::ComputeRectangleArea_Request & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<my_robot_interfaces::srv::ComputeRectangleArea_Request>()
{
  return "my_robot_interfaces::srv::ComputeRectangleArea_Request";
}

template<>
inline const char * name<my_robot_interfaces::srv::ComputeRectangleArea_Request>()
{
  return "my_robot_interfaces/srv/ComputeRectangleArea_Request";
}

template<>
struct has_fixed_size<my_robot_interfaces::srv::ComputeRectangleArea_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<my_robot_interfaces::srv::ComputeRectangleArea_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<my_robot_interfaces::srv::ComputeRectangleArea_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

inline void to_yaml(
  const my_robot_interfaces::srv::ComputeRectangleArea_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: area
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "area: ";
    value_to_yaml(msg.area, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const my_robot_interfaces::srv::ComputeRectangleArea_Response & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<my_robot_interfaces::srv::ComputeRectangleArea_Response>()
{
  return "my_robot_interfaces::srv::ComputeRectangleArea_Response";
}

template<>
inline const char * name<my_robot_interfaces::srv::ComputeRectangleArea_Response>()
{
  return "my_robot_interfaces/srv/ComputeRectangleArea_Response";
}

template<>
struct has_fixed_size<my_robot_interfaces::srv::ComputeRectangleArea_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<my_robot_interfaces::srv::ComputeRectangleArea_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<my_robot_interfaces::srv::ComputeRectangleArea_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<my_robot_interfaces::srv::ComputeRectangleArea>()
{
  return "my_robot_interfaces::srv::ComputeRectangleArea";
}

template<>
inline const char * name<my_robot_interfaces::srv::ComputeRectangleArea>()
{
  return "my_robot_interfaces/srv/ComputeRectangleArea";
}

template<>
struct has_fixed_size<my_robot_interfaces::srv::ComputeRectangleArea>
  : std::integral_constant<
    bool,
    has_fixed_size<my_robot_interfaces::srv::ComputeRectangleArea_Request>::value &&
    has_fixed_size<my_robot_interfaces::srv::ComputeRectangleArea_Response>::value
  >
{
};

template<>
struct has_bounded_size<my_robot_interfaces::srv::ComputeRectangleArea>
  : std::integral_constant<
    bool,
    has_bounded_size<my_robot_interfaces::srv::ComputeRectangleArea_Request>::value &&
    has_bounded_size<my_robot_interfaces::srv::ComputeRectangleArea_Response>::value
  >
{
};

template<>
struct is_service<my_robot_interfaces::srv::ComputeRectangleArea>
  : std::true_type
{
};

template<>
struct is_service_request<my_robot_interfaces::srv::ComputeRectangleArea_Request>
  : std::true_type
{
};

template<>
struct is_service_response<my_robot_interfaces::srv::ComputeRectangleArea_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // MY_ROBOT_INTERFACES__SRV__DETAIL__COMPUTE_RECTANGLE_AREA__TRAITS_HPP_
