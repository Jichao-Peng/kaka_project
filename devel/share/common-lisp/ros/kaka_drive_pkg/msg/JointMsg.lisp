; Auto-generated. Do not edit!


(cl:in-package kaka_drive_pkg-msg)


;//! \htmlinclude JointMsg.msg.html

(cl:defclass <JointMsg> (roslisp-msg-protocol:ros-message)
  ((Time
    :reader Time
    :initarg :Time
    :type cl:integer
    :initform 0)
   (JointPos
    :reader JointPos
    :initarg :JointPos
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass JointMsg (<JointMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <JointMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'JointMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name kaka_drive_pkg-msg:<JointMsg> is deprecated: use kaka_drive_pkg-msg:JointMsg instead.")))

(cl:ensure-generic-function 'Time-val :lambda-list '(m))
(cl:defmethod Time-val ((m <JointMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kaka_drive_pkg-msg:Time-val is deprecated.  Use kaka_drive_pkg-msg:Time instead.")
  (Time m))

(cl:ensure-generic-function 'JointPos-val :lambda-list '(m))
(cl:defmethod JointPos-val ((m <JointMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kaka_drive_pkg-msg:JointPos-val is deprecated.  Use kaka_drive_pkg-msg:JointPos instead.")
  (JointPos m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <JointMsg>) ostream)
  "Serializes a message object of type '<JointMsg>"
  (cl:let* ((signed (cl:slot-value msg 'Time)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'JointPos))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'JointPos))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <JointMsg>) istream)
  "Deserializes a message object of type '<JointMsg>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Time) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'JointPos) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'JointPos)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<JointMsg>)))
  "Returns string type for a message object of type '<JointMsg>"
  "kaka_drive_pkg/JointMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'JointMsg)))
  "Returns string type for a message object of type 'JointMsg"
  "kaka_drive_pkg/JointMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<JointMsg>)))
  "Returns md5sum for a message object of type '<JointMsg>"
  "18b642456cbd4fcb5191232b30f70080")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'JointMsg)))
  "Returns md5sum for a message object of type 'JointMsg"
  "18b642456cbd4fcb5191232b30f70080")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<JointMsg>)))
  "Returns full string definition for message of type '<JointMsg>"
  (cl:format cl:nil "int32 Time~%float32[] JointPos~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'JointMsg)))
  "Returns full string definition for message of type 'JointMsg"
  (cl:format cl:nil "int32 Time~%float32[] JointPos~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <JointMsg>))
  (cl:+ 0
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'JointPos) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <JointMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'JointMsg
    (cl:cons ':Time (Time msg))
    (cl:cons ':JointPos (JointPos msg))
))
