#lang racket

(require memoize)

(define/memo (go n i j)
  (if (or (> i n) (> j n))
      0
      (if (and (= i n) (= j n))
          1
          (+ (go n (+ i 1) j)
             (go n i (+ j 1))))))
      
  