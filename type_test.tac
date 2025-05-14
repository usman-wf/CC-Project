func_begin calculate
t0 := 2
t1 := x * t0
return t1
if flag == 0 goto L0
L0:
return x
func_end calculate
func_begin main
t2 := 5
a := t2
t3 := true
b := t3
t4 := "test"
s := t4
t5 := 10
t6 := a + t5
a := t6
t7 := 10
t8 := a > t7
b := t8
t9 := a + b
a := t9
t10 := "string"
b := t10
param b
param a
call calculate, 2
t11 := return_value
a := t11
t12 := 0
return t12
func_end main
