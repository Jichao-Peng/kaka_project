
(cl:in-package :asdf)

(defsystem "kaka_interface_pkg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "InterfaceCtrl" :depends-on ("_package_InterfaceCtrl"))
    (:file "_package_InterfaceCtrl" :depends-on ("_package"))
  ))