#lang racket
(require srfi/26)
(require racket/sequence)
(require memoize)

(define (even_div n d) (= 0 (modulo n d)))

(define (first_divisor n)
  (let* ([sentinel_n (add1 (integer-sqrt n))]
         [found_divisor (+ 2 (sequence-length (stop-before (in-range 2 sentinel_n) (lambda (x) (even_div n x)))))])
    (if (= found_divisor sentinel_n) n
        found_divisor)))

(define (split_eq_ranges l)
  (if (empty? l) '()
      (let ([first_eq_range (takef l (lambda (x) (= x (first l))))])
        (cons first_eq_range (split_eq_ranges (drop l (length first_eq_range)))))))

(define (comb_pows acc ns)
  (if (empty? ns) (list acc)
      (cons acc (comb_pows (* acc (car ns)) (cdr ns)))))

(define (to_mults ps)
  (map (cut comb_pows 1 <>) (split_eq_ranges ps)))

(define (list_sum l) (apply + l))

(define (sum_comb_mult path_acc mults)
  (if (empty? mults) path_acc
      (let ([t (rest mults)])
        (apply +
               (map (lambda (m) (sum_comb_mult (* path_acc m) t))
                    (first mults))))))
; OR
(define (sum_comb_mult_via_catersian mults)
  (apply + (map (cut apply * <>) (apply cartesian-product mults))))

(define (prime_factors n)
  (let ([divisor (first_divisor n)])
    (if (= divisor n) (list n)
        (cons divisor (prime_factors (/ n divisor))))))

(define divisors_sum_withself (compose sum_comb_mult_via_catersian to_mults prime_factors))
(define (divisors_sum n) (- (divisors_sum_withself n) n))

(define/memo (divs_sum_memo n) (divisors_sum n))

(define (amicables i j) (and (= i (divisors_sum j)) (= j (divisors_sum i))))
(define (amicables_memo i j) (and (= i (divs_sum_memo j)) (= j (divs_sum_memo i))))

(define (solve below_n)
  (for/sum ([i (in-range 2 below_n)])
    (for/sum ([j (in-range 2 below_n)])
      (cond
        [(= i j) 0]
        [(amicables_memo i j) i]
        [#t 0]
        ))))