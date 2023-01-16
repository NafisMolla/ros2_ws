// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from my_robot_interfaces:msg/HardwareStatus.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_INTERFACES__MSG__DETAIL__HARDWARE_STATUS__TRAITS_HPP_
#define MY_ROBOT_INTERFACES__MSG__DETAIL__HARDWARE_STATUS__TRAITS_HPP_

#include "my_robot_interfaces/msg/detail/hardware_status__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

namespace rosidl_generator_traits
{

inline void to_yaml(
  const my_robot_interfaces::msg::HardwareStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: termperature
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "termperature: ";
    value_to_yaml(msg.termperature, out);
    out << "\n";
  }

  // member: are_motors_ready
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "are_motors_ready: ";
    value_to_yaml(msg.are_motors_ready, out);
    out << "\n";
  }

  // member: debug_message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_message: ";
    value_to_yaml(msg.debug_message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const my_robot_interfaces::msg::HardwareStatus & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<my_robot_interfaces::msg::HardwareStatus>()
{
  return "my_robot_interfaces::msg::HardwareStatus";
}

template<>
inline const char * name<my_robot_interfaces::msg::HardwareStatus>()
{
  return "my_robot_interfaces/msg/HardwareStatus";
}

template<>
struct has_fixed_size<my_robot_interfaces::msg::HardwareStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<my_robot_interfaces::msg::HardwareStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<my_robot_interfaces::msg::HardwareStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MY_ROBOT_INTERFACES__MSG__DETAIL__HARDWARE_STATUS__TRAITS_HPP_
