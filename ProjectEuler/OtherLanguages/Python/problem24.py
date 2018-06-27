from math import factorial

# 10 first digits means 10! possible combinations
# 10! == 3,628,800
# 9! == 362,880

# For each digit 0..9, we find wich sub slice contains our millionth
# Is it the slice starting with 0? Or with 1? 2? etc.
# When found, we append this digit, remove it from the pool, and start again with the remaining n-1 digits
# Until only 1 digit remains (the last one)
# The worst case "complexity" will be 10+9+8+...+1 "operations"
def find_nth_permutation(remaining_digits, nth, lower_bound = 0):
    n = len(remaining_digits)

    if (n == 1):
        return str(remaining_digits.pop(0))

    fac_n = factorial(n)
    fac_below = factorial(n - 1)

    upper_bound = lower_bound + fac_n

    i = 0

    # Find first slice that includes the millionth
    for slice_start_idx in range(lower_bound, upper_bound, fac_below):
        if (slice_start_idx + fac_below >= nth):
            picked_digit = remaining_digits.pop(i)
            return str(picked_digit) + find_nth_permutation(remaining_digits, nth, lower_bound = slice_start_idx)

        i = i + 1

    assert fac_n >= nth, "The nth permutation {} doesn't exist, it is larger than the total number of possible permutations {}".format(nth, fac_n)

millionth_perm_str = find_nth_permutation([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], 1_000_000)
print(millionth_perm_str)
