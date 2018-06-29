; Auto-generated. Do not edit!


(cl:in-package kaka_interface_pkg-msg)


;//! \htmlinclude InterfaceCtrl.msg.html

(cl:defclass <InterfaceCtrl> (roslisp-msg-protocol:ros-message)
  ((Cmd
    :reader Cmd
    :initarg :Cmd
    :type cl:integer
    :initform 0))
)

(cl:defclass InterfaceCtrl (<InterfaceCtrl>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <InterfaceCtrl>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'InterfaceCtrl)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name kaka_interface_pkg-msg:<InterfaceCtrl> is deprecated: use kaka_interface_pkg-msg:InterfaceCtrl instead.")))

(cl:ensure-generic-function 'Cmd-val :lambda-list '(m))
(cl:defmethod Cmd-val ((m <InterfaceCtrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kaka_interface_pkg-msg:Cmd-val is deprecated.  Use kaka_interface_pkg-msg:Cmd instead.")
  (Cmd m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <InterfaceCtrl>) ostream)
  "Serializes a message object of type '<InterfaceCtrl>"
  (cl:let* ((signed (cl:slot-value msg 'Cmd)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <InterfaceCtrl>) istream)
  "Deserializes a message object of type '<InterfaceCtrl>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Cmd) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<InterfaceCtrl>)))
  "Returns string type for a message object of type '<InterfaceCtrl>"
  "kaka_interface_pkg/InterfaceCtrl")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InterfaceCtrl)))
  "Returns string type for a message object of type 'InterfaceCtrl"
  "kaka_interface_pkg/InterfaceCtrl")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<InterfaceCtrl>)))
  "Returns md5sum for a message object of type '<InterfaceCtrl>"
  "269bcf4b8e9f4499f088fe6b4f64bdda")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'InterfaceCtrl)))
  "Returns md5sum for a message object of type 'InterfaceCtrl"
  "269bcf4b8e9f4499f088fe6b4f64bdda")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<InterfaceCtrl>)))
  "Returns full string definition for message of type '<InterfaceCtrl>"
  (cl:format cl:nil "int32 Cmd~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'InterfaceCtrl)))
  "Returns full string definition for message of type 'InterfaceCtrl"
  (cl:format cl:nil "int32 Cmd~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <InterfaceCtrl>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <InterfaceCtrl>))
  "Converts a ROS message object to a list"
  (cl:list 'InterfaceCtrl
    (cl:cons ':Cmd (Cmd msg))
))
