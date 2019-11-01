;;; -*- Mode: Lisp; Syntax: Common-Lisp; -*-

#|
=========================================================
Module: eliza.lisp: 
Description: A version of ELIZA that takes inputs without 
paretheses around them unlike eliza1.lisp.
Bugs to vladimir dot kulyukin at usu dot edu.
=========================================================
|#

;;; ==============================

(defun read-line-no-punct ()
  "Read an input line, ignoring punctuation."
  (read-from-string
    (concatenate 'string "(" (substitute-if #\space #'punctuation-p
                                            (read-line))
                 ")")))

(defun punctuation-p (char) (find char ".,;:`!?#-()\\\""))

;;; ==============================

(defun eliza ()
  "Respond to user input using pattern matching rules."
  (loop
    (print 'eliza>)
    (let* ((input (read-line-no-punct))
           (response (flatten (use-eliza-rules input))))
      (print-with-spaces response)
      (if (equal response '(good bye)) (RETURN)))))

(defun print-with-spaces (list)
  (mapc #'(lambda (x) (prin1 x) (princ " ")) list))

(defun print-with-spaces (list)
  (format t "~{~a ~}" list))

;;; ==============================

(defparameter *eliza-rules*
  '(
    ;;; rule 1
    (((?* ?x) hello (?* ?y))      
    (How do you do.  Please state your problem.))

    ;;; rule 2
    (((?* ?x) computer (?* ?y))
     (Do computers worry you?)
     (What do you think about machines?)
     (Why do you mention computers?)
     (What do you think machines have to do with your problem?))

    ;;; rule 3
    (((?* ?x) name (?* ?y))
     (I am not interested in names))

    ;;; rule 4
    (((?* ?x) sorry (?* ?y))
     (Please don't apologize)
     (Apologies are not necessary)
     (What feelings do you have when you apologize))

    ;;; rule 5
    (((?* ?x) I remember (?* ?y)) 
     (Do you often think of ?y)
     (Does thinking of ?y bring anything else to mind?)
     (What else do you remember)
     (Why do you recall ?y right now?)
     (What in the present situation reminds you of ?y)
     (What is the connection between me and ?y))

    ;;; ========== your rules begin
    ;;; rule 6
    (((?* ?x) want (?* ?y))
     (Why do you want ?y right now?)
     (Would getting ?y make you happy?)

    ;;; rule 7
    (((?* ?x) went (?* ?y))
     (When did you go to ?y?)
     (Why did you want to go to ?y?)

    ;;; rule 8
    (((?* ?x) took (?* ?y))
     (Why do you take ?y?)
     (How did taking ?y make you feel?)

    ;;; rule 9
    (((?* ?x) learn (?* ?y))
     (What does learning ?y mean to you?)

    ;;; rule 10
    (((?* ?x) think (?* ?y))
     (Why do you think ?y?)

    ;;; rule 11
    (((?* ?x) read (?* ?y))
     (Why did you want to read ?y?)

    ;;; rule 12
    (((?* ?x) stressed (?* ?y))
     (Why does ?y make you stressed?)

    ;;; rule 13
    (((?* ?x) learn (?* ?y))
     (What does learning ?y mean to you?)

    ;;; rule 14
    (((?* ?x) learn (?* ?y))
     (What does learning ?y mean to you?)

    ;;; rule 15
    (((?* ?x) learn (?* ?y))
     (What does learning ?y mean to you?)

    ;;; rule 16
    (((?* ?x) learn (?* ?y))
     (What does learning ?y mean to you?)

    ;;; rule 17
    (((?* ?x) learn (?* ?y))
     (What does learning ?y mean to you?)

    ;;; rule 18
    (((?* ?x) learn (?* ?y))
     (What does learning ?y mean to you?)

    ;;; rule 19
    (((?* ?x) learn (?* ?y))
     (What does learning ?y mean to you?)

    ;;; rule 20
    (((?* ?x) learn (?* ?y))
     (What does learning ?y mean to you?)

    ;;; rule 21
    (((?* ?x) learn (?* ?y))
     (What does learning ?y mean to you?)

    ;;; rule 22
    (((?* ?x) learn (?* ?y))
     (What does learning ?y mean to you?)

    ;;; rule 23
    (((?* ?x) learn (?* ?y))
     (What does learning ?y mean to you?)

    ;;; rule 24
    (((?* ?x) learn (?* ?y))
     (What does learning ?y mean to you?)

    ;;; rule 25
    (((?* ?x) learn (?* ?y))
     (What does learning ?y mean to you?)

    ;;; add your rules here
    ;;; ========== your rules end

   ))

;;; ==============================

