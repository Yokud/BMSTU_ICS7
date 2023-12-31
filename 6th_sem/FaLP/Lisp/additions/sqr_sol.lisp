(defun sqr-sol (a b c)
	(cond ((= a 0)
		(cond ((= b 0) (cond 
				((= c 0) (string "Любые значения"))
				(t (string "Нет корней"))))
			(t (cond 
				((= c 0) '(0))
				(t `(,(/ c (- b))))))))
	(t (cond ((= b 0) (cond 
				((= c 0) '(0 0))
				(t `(,(sqrt (/ (- c) a)) ,( - (sqrt (/ (- c) a)))))))
		(t (let* (( D (- (* b b) (* 4 a c)))
			(r1 (/ (+ (- b) (sqrt D)) (* 2 a)))
			(r2 (/ (- (- b) (sqrt D)) (* 2 a))))
			`(,r1 ,r2)))))))
			
(defun num-to-str (num) 
	(if (complexp num) 
		(format nil "~f ~fi" (realpart num) (imagpart num))
		(format nil "~f" num)))
		
(defun print-roots-to-file (roots filename)
	(with-open-file (str filename 
						:direction :output
						:if-exists :supersede
						:if-does-not-exist :create)
		(if (stringp roots) 
			(format str "~A" roots)
			(if (null (cdr roots)) 
				(format str "X = ~A" (num-to-str (car roots)))
				(format str "X1 = ~A ~%X2 = ~A" (num-to-str (car roots)) (num-to-str (cadr roots)))))))
			
(fiveam:test sqr-sol-test 
	(fiveam:is (equal (sqr-sol 0 0 0) (string "Любые значения")))
	(fiveam:is (equal (sqr-sol 0 0 1) (string "Нет корней")))
	(fiveam:is (equal (sqr-sol 0 1 0) '(0)))
	(fiveam:is (equal (sqr-sol 0 2 1) `(,(/ -1 2))))
	(fiveam:is (equal (sqr-sol 1 0 0) '(0 0)))
	(fiveam:is (equal (sqr-sol 1 0 1) `(,#C(0.0 1.0) ,(- #C(0.0 1.0)))))
	(fiveam:is (equal (sqr-sol 1 2 1) `(,(float -1) ,(float -1))))
	(fiveam:is (equal (sqr-sol 1 2 0) `(,(float 0) ,(float -2))))
)
	
(fiveam:run!)		
