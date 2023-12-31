(defun coprimep (a b) (eql (gcd a b) 1))

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

(defun chose-e (n)
    (cond ((and (> n 65537) (coprimep n 65537)) 65537)
            ((and (> n 257) (coprimep n 257)) 257)
            ((and (> n 17) (coprimep n 17)) 17)
            (t 3)))

(defun rsa-gen-key (p q)
    (let* ((n (* p q))
            (l (lcm (- p 1) (- q 1)))
            (e (chose-e n))
            (d (modular-inverse e l)))
        (list `(,e . ,n) `(,d . ,n))))

(defun rsa-code (m e n) 
    (mod (expt m e) n))

(defun rsa-decode (c d n)
    (mod (expt c d) n))


(defun rsa-fcode (f-in f-out e n) 
    (let ((code (map 'list #'(lambda (x) (rsa-code (char-code x) e n)) (with-open-file (stream f-in) (read-line stream)))))
        (with-open-file (str f-out :direction :output 
                                    :if-exists :supersede
						            :if-does-not-exist :create) 
        (mapcar #'(lambda (x) (format str "~A " x)) code)) nil))

(defun rsa-fdecode (f-in f-out d n) 
    (let ((code (mapcar #'(lambda (x) (code-char (rsa-decode (parse-integer x) d n))) (str:words (with-open-file (stream f-in) (read-line stream))))))
        (with-open-file (str f-out :direction :output 
                                    :if-exists :supersede
						            :if-does-not-exist :create) 
        (mapcar #'(lambda (x) (format str "~A" x)) code)) nil))


; Тесты :3
(fiveam:test rsa-tests 
    (fiveam:is (eql t (coprimep 2 3))
    (fiveam:is (eql nil (coprimep 2 4)))
    (fiveam:is (eql 2 (div 5 2))))
    (fiveam:is (eql 3 (modular-inverse 2 5)))
    (fiveam:is (eql 65537 (chose-e 666666)))
    (fiveam:is (eql 257 (chose-e 300)))
    (fiveam:is (eql 17 (chose-e 30)))
    (fiveam:is (eql 3 (chose-e 15)))
    (fiveam:is (equal '((3 . 187) (27 . 187)) (rsa-gen-key 11 17)))
    (fiveam:is (eql 140 (rsa-code 13 3 187)))
    (fiveam:is (eql 13 (rsa-decode 140 27 187)))
    (fiveam:is (equal "183 118 80 80 100 43 102 100 130 80 111 33 " (progn 
                                                                        (rsa-fcode "c:\\Users\\Yokud\\Desktop\\temp.txt" "c:\\Users\\Yokud\\Desktop\\temp1.txt" 3 187) 
                                                                        (with-open-file (stream "c:\\Users\\Yokud\\Desktop\\temp1.txt") (read-line stream)))))
    (fiveam:is (equal "Hello world!" (progn 
                                        (rsa-fdecode "c:\\Users\\Yokud\\Desktop\\temp1.txt" "c:\\Users\\Yokud\\Desktop\\temp2.txt" 27 187) 
                                        (with-open-file (stream "c:\\Users\\Yokud\\Desktop\\temp2.txt") (read-line stream))))))