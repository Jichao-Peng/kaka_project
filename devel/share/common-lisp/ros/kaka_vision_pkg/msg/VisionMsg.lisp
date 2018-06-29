; Auto-generated. Do not edit!


(cl:in-package kaka_vision_pkg-msg)


;//! \htmlinclude VisionMsg.msg.html

(cl:defclass <VisionMsg> (roslisp-msg-protocol:ros-message)
  ((Quaternion
    :reader Quaternion
    :initarg :Quaternion
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (Position
    :reader Position
    :initarg :Position
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass VisionMsg (<VisionMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VisionMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VisionMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name kaka_vision_pkg-msg:<VisionMsg> is deprecated: use kaka_vision_pkg-msg:VisionMsg instead.")))

(cl:ensure-generic-function 'Quaternion-val :lambda-list '(m))
(cl:defmethod Quaternion-val ((m <VisionMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kaka_vision_pkg-msg:Quaternion-val is deprecated.  Use kaka_vision_pkg-msg:Quaternion instead.")
  (Quaternion m))

(cl:ensure-generic-function 'Position-val :lambda-list '(m))
(cl:defmethod Position-val ((m <VisionMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kaka_vision_pkg-msg:Position-val is deprecated.  Use kaka_vision_pkg-msg:Position instead.")
  (Position m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VisionMsg>) ostream)
  "Serializes a message object of type '<VisionMsg>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'Quaternion))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'Quaternion))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'Position))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'Position))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VisionMsg>) istream)
  "Deserializes a message object of type '<VisionMsg>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'Quaternion) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'Quaternion)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'Position) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'Position)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VisionMsg>)))
  "Returns string type for a message object of type '<VisionMsg>"
  "kaka_vision_pkg/VisionMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VisionMsg)))
  "Returns string type for a message object of type 'VisionMsg"
  "kaka_vision_pkg/VisionMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VisionMsg>)))
  "Returns md5sum for a message object of type '<VisionMsg>"
  "4655a1952cd34f99cf33dce7a46cf9cd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VisionMsg)))
  "Returns md5sum for a message object of type 'VisionMsg"
  "4655a1952cd34f99cf33dce7a46cf9cd")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VisionMsg>)))
  "Returns full string definition for message of type '<VisionMsg>"
  (cl:format cl:nil "float64[] Quaternion~%float64[] Position~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VisionMsg)))
  "Returns full string definition for message of type 'VisionMsg"
  (cl:format cl:nil "float64[] Quaternion~%float64[] Position~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VisionMsg>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'Quaternion) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'Position) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VisionMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'VisionMsg
    (cl:cons ':Quaternion (Quaternion msg))
    (cl:cons ':Position (Position msg))
))
