(defun make-arena (holes num)(
    cond ((= 0 holes) (cons (cons 0 nil) nil))
         (t (cons num (make-arena (- holes 1) num)))
))

(defun find-start (lst pos)
	(cond ((<= pos 0) (and (setf (car lst) 0) lst))
          (t (find-start (cdr lst) (- pos 1)))))

(defun victory() 
    (format t "~%Вы выиграли!~%")
)

(defun lose() 
    (format t "~%Вы проиграли, к сожалению.~%")
)

(defun wrong-hole() 
    (format t "~%Вы не можете выбрать лунку, в которой нет камней. ~%Пожалуйста, повторите попытку.~%")
)

(defun read-hole (holes)
    (format t "~%Введите номер лунки: ")
    (finish-output)
    (let* ((value))
    (and (setq value (read))
    (cond ((<= value 0) 0)
          ((>= (+ holes 1) value) (- value 1))
          (t holes)))))

(defun automatic (desk stones)(
    cond ((listp (car desk))
                 (and (setf (caar desk) (+ (caar desk) 1)) 
                    (if (= stones 1) 
                        t
                    (automatic (cdr desk) (- stones 1)))
                 )
         )
          ((= stones 1) (if (and (= (car desk) 0) (setf (car desk) 1))
                            nil
                (and (setf stones (+ stones (car desk))) (setf (car desk) 0) (automatic (cdr desk) stones))
                        )
          )
          ((>= stones 0) (and (setf (car desk) (+ (car desk) 1)) (automatic (cdr desk) (- stones 1))))
))

(defun not-circle-lst (lst limit)(
    cond ((< limit 0) (cons (car lst) nil))
          (t (cons (car lst) (not-circle-lst (cdr lst) (- limit 1))))
))

(defun is-win (lst count)(
    if (>= count 0)
        (cond ((/= (car lst) 0) nil)
              (t (is-win (cdr lst) (- count 1))))
        t
))

(defun logic (lst pos holes)
    (let* ((head lst)
           (stones (nth pos lst)))
		(cond ((and (> stones 0) (automatic (cdr (find-start lst pos)) stones))
					(cond ((is-win head holes) (progn (print (not-circle-lst head holes)) (victory)))
						  (t (progn (print (not-circle-lst head holes)) (logic head (read-hole holes) holes)))))
			  ((= stones 0) (progn (wrong-hole) (logic head (read-hole holes) holes)))
			  (t (progn (print (not-circle-lst head holes)) (lose))))))


(defun tchuka-ruma (holes stones)
    (cond ((<= holes 0) (format t "Игра невозможна, т. к. количество лунок может быть только натуральным!"))
          ((<= stones 0) (format t "Игра невозможна, т. к. исходное число камней в лунке может быть только натуральным!"))
    (t (let* ((lst (make-arena holes stones))
           (pos))
    (format t "Начальное состояние доски: ~%~a~%" lst)
    (setq pos (read-hole (- holes 1)))
    (setf (cdr (last lst)) lst)
    (logic lst pos (- holes 1)))))
)
