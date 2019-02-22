;; -*- mode: EusLisp; coding: utf-8-unix; -*-
#!/usr/bin/env roseus

(if (not (find-package "TEST_EUSNP")) (make-package "TEST_EUSNP"))
;; (setq *eusrobot-package-name* "TEST_EUSNP")
(setq test_eusnp::*eusrobot-plugin* (load-foreign "/home/leus/work/test_eus_numpy/build/libTestEusNumpy.so"))

(format t "load foreign~%")

(In-package "TEST_EUSNP")
(let* ((lib test_eusnp::*eusrobot-plugin*))
  (defforeign init-py lib "test_eusnp_init_py" () :integer)
  (defforeign _add123 lib "test_eusnp_add123" (:string :string) :integer)
  )

(defvar test_eusnp::*arr* (instantiate float-vector 3))
(defvar test_eusnp::*ret* (instantiate float-vector 3))

(defun test_eusnp::add123
  (&key (arr test_eusnp::*arr*) (ret test_eusnp::*ret*))
  (test_eusnp::init-py)
  (fill arr 1)
  (test_eusnp::_add123 arr ret)
  (format t "~A -> ~A~%" arr ret)
  )

(warning-message 1 "~%[test_eusnp] test_eusnp::add123~%")
(test_eusnp::add123)
