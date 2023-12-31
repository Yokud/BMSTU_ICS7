(defun nappend-element (lst el) 
    (nconc lst (cons el Nil)))

(defun div (a b) (multiple-value-bind (q r) (floor a b) q))

(defun mod-inv (q r newq newr n) 
    (cond ((zerop newr) (cond ((> r 1) Nil) ((< q 0) (+ q n)) (t q)))
            (t (let* ((quotient (div r newr))
                        (oldq q) 
                        (q newq) 
                        (newq (- oldq (* quotient newq)))
                        (oldr r)
                        (r newr)
                        (newr (- oldr (* quotient newr)))) 
                    (mod-inv q r newq newr n)))))

(defun modular-inverse (a n) 
    (mod-inv 0 n 1 a n))

(defun get-basis (n) 
    (list (- (expt 2 n) 1) (expt 2 n) (+ (expt 2 n) 1)))


(defun to-cok-internal (num basis acc) 
    (cond ((null basis) acc) 
            (t (to-cok-internal num (cdr basis) (nappend-element acc (mod num (car basis)))))))

(defun to-cok (num basis) 
    (to-cok-internal num basis ()))

(defun from-cok (cok basis) 
    (let* ((M (apply #'* basis))
            (Mi (mapcar #'(lambda (x) (/ M x)) basis))
            (Bi (mapcar #'modular-inverse Mi basis))) 
        (mod (apply #'+ (mapcar #'* cok Mi Bi)) M)))


(defun op-coks-internal (cok1 cok2 basis op acc) 
    (cond ((null basis) acc)
            ((eql #'/ op) (op-coks-internal (cdr cok1) (cdr cok2) (cdr basis) op 
                                    (nappend-element acc (mod (funcall #'* (car cok1) (modular-inverse (car cok2) (car basis))) 
                                                                (car basis)))))
            (t (op-coks-internal (cdr cok1) (cdr cok2) (cdr basis) op 
                                    (nappend-element acc (mod (funcall op (car cok1) (car cok2)) (car basis)))))))

(defun add-coks (cok1 cok2 basis) 
    (op-coks-internal cok1 cok2 basis #'+ ()))

(defun sub-coks (cok1 cok2 basis) 
    (op-coks-internal cok1 cok2 basis #'- ()))

(defun mul-coks (cok1 cok2 basis) 
    (op-coks-internal cok1 cok2 basis #'* ()))

(defun div-coks (cok1 cok2 basis)
    (cond ((or (zerop (reduce #'* cok2)) (not (zerop (mod (from-cok cok1 basis) (from-cok cok2 basis))))) Nil)
            (t (op-coks-internal cok1 cok2 basis #'/ ()))))

(defun nth-root (a n) 
    (exp (/ (log a) n)))

(defun to-int (a) (multiple-value-bind (i f) (truncate a) i))

(defun is-nth-root (a n) (eql a (expt (to-int (nth-root a n)) n)))

(defun cok-radical-n (cok basis n) 
    (cond ((is-nth-root (from-cok cok basis) n) (to-cok (to-int (nth-root (from-cok cok basis) n)) basis))
            (t Nil)))
