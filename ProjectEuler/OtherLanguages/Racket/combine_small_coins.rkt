#lang racket
(require memoize)
(require srfi/26)

(define/memo (comb s)
  (cond
    ((> s 100) 0)
    ((= s 100) 1)
    (#t (+ (comb (+ s 50))
           (comb (+ s 20))
           (comb (+ s 10))
           (comb (+ s 5))
           (comb (+ s 2))
           (comb (+ s 1))))))

(define lpieces (list 50 20 10 5 2 1))

(define/memo (combl s)
  (cond
    ((> s 100) 0)
    ((= s 100) 1)
    (#t (apply + (map (lambda (p) (comb (+ s p))) lpieces)))))

(define combl0 (combl 0))

