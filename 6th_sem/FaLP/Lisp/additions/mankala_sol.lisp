(defun create_list2 (lst num lst_begin)
	(cond
	((null lst)
		(cons (cons 'H 0) lst_begin))
	((zerop num)
		(let ((head (cons (cons num (car lst)) nil)))
		(nconc head (create_list2 (cdr lst) (+ num 1) head))))
	(t 
		(cons (cons num (car lst)) (create_list2 (cdr lst) (+ num 1) lst_begin)))))

;Функция, которая находит срез [ind:]
(defun find_slice (lst ind)
	(if (zerop ind)
		lst
		(find_slice (cdr lst) (- ind 1))
	)
)



;ФУНКЦИИ ДЛЯ РАБОТЫ СО СТЕКОМ (СТЕК СОХРАНЯЕТ ТЕКУЩИЕ ШАГИ АЛГОРИТМА, ДЛЯ ЕГО ОБРАТНОГО ХОДА В СЛУЧАЕ ПРОИГРЫША)

;Стек - обычный список, первый элемент - дескриптор стека, каждый следующий - дескриптор подстека
(defun create_empty_stack (len)
	(cons (+ len 1) nil))

(defun is_empty_stack (stack)
	(not (cdr stack)))

(defun push_move (stack)
	(let ((substack (cons nil (cdr stack))))
	(setf (cdr stack) substack)
	stack))

(defun pop_move (stack) 
	(let ((current (cdr stack)))
	(setf (cdr stack) (cdr current))
	(car current)))

(defun push_value (stack index cnt)
	(let ((new (cons (cons index cnt) nil)))
	(setf (cdr new) (cadr stack))
	(setf (cadr stack) new)))

;Подстек - обычный список, первый элемент - дескриптор этого подстека, каждый следующий - элемент хранящий (индекс . взятое значение)
;Этот подстек становится пустой, если в списке остается только последний дескриптор
(defun pop_value (substack)
	(cond
	((eql (cdr substack) nil)
		nil)
	(t
		(let ((current (cdr substack)))
		(setf (cdr substack) (cdr current))
		(setf (cdr current) nil)
		current))))

(defun find_previous_lst (lst_begin stack)
	(find_slice lst_begin (caar (last (cadr stack)))))

(defun reverse_substacks (stack)
	(cond
	((null stack) nil)
	(t 
		(progn
			(setf (car stack) (reverse (car stack)))
			(reverse_substacks (cdr stack))
			stack))))

(defun reverse_stack (stack)
	(reverse (reverse_substacks (cdr stack))))





;ФУНКЦИИ ХОДА И СБРОСА ХОДА
;Функция, которая присваивает op([i], 1) первым n элементам
(defun op_next_n_values1 (lst n op)
	(cond 
	((= n 1)
		(progn
		(setf (cdar lst) (apply op `(,(cdar lst) 1)))
		lst))
	(t
		(progn
		(setf (cdar lst) (apply op `(,(cdar lst) 1)))
		(op_next_n_values1 (cdr lst) (- n 1) op)))))
(defun op_next_n_values (lst n op) (op_next_n_values1 (cdr lst) n op))

;Функция, отменяющая предыдущий шаг игры
(defun reset_step1 (lst index count)
		(progn
		(op_next_n_values (find_slice lst index) count '-)
		(setf (cdar (find_slice lst index)) count)
		lst)
)
(defun reset_step (lst ind_cnt) 
	(reset_step1 lst (car ind_cnt) (cdr ind_cnt)))

;Функция, отменяющая предыдущий ход
(defun reset_move (lst_begin stack)
	(reduce #'reset_step (pop_move stack) :initial-value lst_begin)
)


(defun set_step (stack lst)
	(let ((ind (caar lst)) (val (cdar lst)) (tmp_lst nil))
	(setf tmp_lst (find_slice lst val))
	(cond 
	((eql ind 'H)
		t)
	((or (and (> (car stack) val) (not (eql (caar tmp_lst) 'H)) (zerop (cdar tmp_lst))) (eql val (car stack)))
		nil)
	(t
		(progn
		(push_value stack ind val)
		(setf (cdar lst) 0)
		(set_step stack (op_next_n_values lst val '+)))))))

;Ход - сеем семена до тех пор, пока не будет пустая лунка или дом
(defun set_move (lst stack)
	(set_step (push_move stack) lst)
)



;ПЕРЕБОР ХОДОВ. ОСНОВНАЯ ЛОГИКА ИГРЫ

;Сущности
;1)"Стопка" (stack)
;2)Список лунок (lst_begin)
;3)Текущий выбранный индекс (lst, check2_result)


(defun check_list (lst)
	(cond 
	((eql (caar lst) 'H)
		nil)
	((not (zerop (cdar lst)))
		lst)
	(t
		(check_list (cdr lst)))))


(defun subgame (lst stack lst_begin)
	(let ((check1_result (check_list lst_begin))(check2_result (check_list lst)))
	(cond 
	((null check1_result) ;Победа?
		stack)
	((null check2_result) ;Проигрыш?
		(cond 
		((is_empty_stack stack)
			nil) ;Проигрыш
		(t
			(subgame (cdr (find_previous_lst lst_begin stack)) stack (reset_move lst_begin stack))))) ;Переигрываем предыдущий ход
	(t ;Ходим
		(let ((move_result (set_move check2_result stack))) ;Делаем ход с выбранного значения
		(cond
		((null move_result) ;Ход закончился неудачно
			(subgame (cdr check2_result) stack (reset_move lst_begin stack))) ;Сбрасываем ход и делаем ход со следующего подходящего элемента
		(t ;Ход закончился удачно
			(subgame lst_begin stack lst_begin)))))))) ;Делаем ход со следующего подходящего элемента

(defun result-format (res)
	(cond ((null res) (format t "Нет выйгрышной стратегии"))
		  (t (let ((form-res (mapcar #'(lambda (x) (+ 1 (caar x))) res))) 
				(format t "Список ходов для выйгрыша: ~A ~%" form-res)))))

(defun tchuka-ruma-sol (lst)
	(let ((stack (create_empty_stack (length lst))) (new_lst (create_list2 lst 0 nil)))
	(result-format (reverse_stack (subgame new_lst stack new_lst)))))
