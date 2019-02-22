;; -*- mode: EusLisp; coding: utf-8-unix; -*-
#!/usr/bin/env roseus

(if (not (find-package "TEST_EUSNP")) (make-package "TEST_EUSNP"))
;; (setq *eusrobot-package-name* "TEST_EUSNP")
(setq test_eusnp::*eusrobot-plugin* (load-foreign "/home/kangaroo/work/test_eus_numpy/build/libTestEusNumpy.so"))

(In-package "TEST_EUSNP")
(let* ((lib test_eusnp::*eusrobot-plugin*))
  (defforeign init-py lib "test_eusnp_init_py" () :integer)
  (defforeign set-arr lib "test_eusnp_set_arr" (:string) :integer)
  (defforeign get-arr lib "test_eusnp_get_arr" (:string) :integer)
  (defforeign update-add-123 lib "test_eusnp_add123_" () :integer)
  (defforeign _add123 lib "test_eusnp_add123" (:string :string) :integer)
  )

(defvar test_eusnp::*arr* #f(1 1 1))
(defvar test_eusnp::*ret* (instantiate float-vector 3))

(defun test_eusnp::add123
    (&key (arr test_eusnp::*arr*) (ret test_eusnp::*ret*))
  (test_eusnp::_add123 arr ret)
  (format t "~A -> ~A~%" arr ret)
  )

(defun test_eusnp::test-update-add123
    (&key (arr test_eusnp::*arr*) (ret test_eusnp::*ret*))
  (format t "Before ~A~%" arr)
  (test_eusnp::set-arr arr)
  (test_eusnp::update-add-123)
  (test_eusnp::get-arr ret)
  (format t "After ~A~%" ret)
  )

(test_eusnp::init-py)
(warning-message 1 "~%[test_eusnp] test_eusnp::add123~%")
(warning-message 1 "~%[test_eusnp] test_eusnp::test-update-add123~%")
