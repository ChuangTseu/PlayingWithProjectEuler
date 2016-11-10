#lang racket

(define (b2i b) (if b 1 0))
(define (even_div n d) (= 0 (modulo n d)))

(match-define (list mon tue wed thu fri sat sun) (range 7))
(match-define (list jan feb mar apr may jun jul aug sep oct nov dec) (range 12))

(define months_30 (list apr jun sep nov))
(define months_31 (list jan mar may jul aug oct dec))

(define (bump_month month year)
  (if (< month 11)
      (list (+ month 1) year)
      (list 0 (+ year 1))))

(define (is_leap year)
  (or (even_div year 400)
      (and (not (even_div year 100))
           (even_div year 4))))

(define (days_in_month month year)
  (cond
    [(= month feb) (if (is_leap year) 29 28)]
    [(member month months_30) 30]
    [#t 31]))

(define (next_dayname cur_dayname day_sep)
  (modulo (+ cur_dayname day_sep) 7))

(define (count_dayname_from_to counted_dayname from_dayname from_month from_year last_month last_year)
  (cond
    [(or (> from_year last_year) (and (= from_year last_year) (> from_month last_month))) 0]
    [#t
     (match-let
         ([(list next_month next_year) (bump_month from_month from_year)])
       (+
        (b2i (= from_dayname counted_dayname))
        (count_dayname_from_to
         counted_dayname
         (next_dayname from_dayname (days_in_month from_month from_year))
         next_month
         next_year
         last_month
         last_year)))]))

(define sundays_from_1_jan_1901_to_31_dec_2000 (count_dayname_from_to sun    (next_dayname mon 365) jan 1901    dec 2000))

