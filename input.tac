func_begin add
t0 := a + b
return t0
func_end add
func_begin main
t1 := 10
t2 := x < t1
t3 := 5
y := t3
if t2 == 0 goto L0
t4 := 10
y := t4
goto L1
L0:
L1:
L2:
t5 := 0
t6 := x > t5
if t6 == 0 goto L3
t7 := 1
t8 := x - t7
x := t8
goto L2
L3:
param x
param y
call add, 2
t9 := return_value
return t9
func_end main
