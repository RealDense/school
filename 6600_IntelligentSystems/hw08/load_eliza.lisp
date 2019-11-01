;;; -*- Mode: Lisp; Syntax: Common-Lisp; -*-

#|
=========================================================
Module: load-eliza.lisp: 
Description: a load for three eliza modules.
bugs to vladimir dot kulyukin at usu dot edu.
=========================================================
|#

;;; change this parameter as needed.
(defparameter *eliza-path* 
  "/home/vladimir/teaching/AI/F19/hw/hw08_f19/hw08_f19/")

(defparameter *eliza-files* 
  '("auxfuns.lisp" "eliza1.lisp" "eliza.lisp"
    )) 

(defun load-eliza (path files)
  (mapc #'(lambda (file)
	    (load (concatenate 'string path file)))
	files))

	
