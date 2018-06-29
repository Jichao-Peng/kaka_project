
(cl:in-package :asdf)

(defsystem "kaka_vision_pkg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "VisionMsg" :depends-on ("_package_VisionMsg"))
    (:file "_package_VisionMsg" :depends-on ("_package"))
  ))