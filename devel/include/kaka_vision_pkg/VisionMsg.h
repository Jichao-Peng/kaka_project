// Generated by gencpp from file kaka_vision_pkg/VisionMsg.msg
// DO NOT EDIT!


#ifndef KAKA_VISION_PKG_MESSAGE_VISIONMSG_H
#define KAKA_VISION_PKG_MESSAGE_VISIONMSG_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace kaka_vision_pkg
{
template <class ContainerAllocator>
struct VisionMsg_
{
  typedef VisionMsg_<ContainerAllocator> Type;

  VisionMsg_()
    : Quaternion()
    , Position()  {
    }
  VisionMsg_(const ContainerAllocator& _alloc)
    : Quaternion(_alloc)
    , Position(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _Quaternion_type;
  _Quaternion_type Quaternion;

   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _Position_type;
  _Position_type Position;




  typedef boost::shared_ptr< ::kaka_vision_pkg::VisionMsg_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::kaka_vision_pkg::VisionMsg_<ContainerAllocator> const> ConstPtr;

}; // struct VisionMsg_

typedef ::kaka_vision_pkg::VisionMsg_<std::allocator<void> > VisionMsg;

typedef boost::shared_ptr< ::kaka_vision_pkg::VisionMsg > VisionMsgPtr;
typedef boost::shared_ptr< ::kaka_vision_pkg::VisionMsg const> VisionMsgConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::kaka_vision_pkg::VisionMsg_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::kaka_vision_pkg::VisionMsg_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace kaka_vision_pkg

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'kaka_vision_pkg': ['/home/leo/Desktop/Kaka_Project/src/kaka_vision_pkg/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::kaka_vision_pkg::VisionMsg_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::kaka_vision_pkg::VisionMsg_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::kaka_vision_pkg::VisionMsg_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::kaka_vision_pkg::VisionMsg_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::kaka_vision_pkg::VisionMsg_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::kaka_vision_pkg::VisionMsg_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::kaka_vision_pkg::VisionMsg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4655a1952cd34f99cf33dce7a46cf9cd";
  }

  static const char* value(const ::kaka_vision_pkg::VisionMsg_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4655a1952cd34f99ULL;
  static const uint64_t static_value2 = 0xcf33dce7a46cf9cdULL;
};

template<class ContainerAllocator>
struct DataType< ::kaka_vision_pkg::VisionMsg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "kaka_vision_pkg/VisionMsg";
  }

  static const char* value(const ::kaka_vision_pkg::VisionMsg_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::kaka_vision_pkg::VisionMsg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64[] Quaternion\n\
float64[] Position\n\
";
  }

  static const char* value(const ::kaka_vision_pkg::VisionMsg_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::kaka_vision_pkg::VisionMsg_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.Quaternion);
      stream.next(m.Position);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct VisionMsg_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::kaka_vision_pkg::VisionMsg_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::kaka_vision_pkg::VisionMsg_<ContainerAllocator>& v)
  {
    s << indent << "Quaternion[]" << std::endl;
    for (size_t i = 0; i < v.Quaternion.size(); ++i)
    {
      s << indent << "  Quaternion[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.Quaternion[i]);
    }
    s << indent << "Position[]" << std::endl;
    for (size_t i = 0; i < v.Position.size(); ++i)
    {
      s << indent << "  Position[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.Position[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // KAKA_VISION_PKG_MESSAGE_VISIONMSG_H
