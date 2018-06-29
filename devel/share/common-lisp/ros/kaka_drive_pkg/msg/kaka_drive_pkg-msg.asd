
(cl:in-package :asdf)

(defsystem "kaka_drive_pkg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "JointMsg" :depends-on ("_package_JointMsg"))
    (:file "_package_JointMsg" :depends-on ("_package"))
  ))