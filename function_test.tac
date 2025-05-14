func_begin factorial
t0 := 1
t1 := n <= t0
t2 := 1
return t2
if t1 == 0 goto L0
L0:
t3 := 1
t4 := n - t3
param t4
call factorial, 1
t5 := return_value
t6 := n * t5
return t6
func_end factorial
func_begin printNumber
param x
call print, 1
return
func_end printNumber
func_begin main
t7 := 5
n := t7
param n
call factorial, 1
t8 := return_value
result := t8
param result
call printNumber, 1
t9 := 0
return t9
func_end main
