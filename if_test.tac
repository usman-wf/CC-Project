func_begin main
t0 := 10
x := t0
t1 := 20
y := t1
t2 := x < y
t3 := 1
t4 := x + t3
x := t4
if t2 == 0 goto L0
L0:
t5 := x > y
t6 := 2
t7 := x * t6
x := t7
if t5 == 0 goto L1
t8 := 2
t9 := y / t8
y := t9
goto L2
L1:
L2:
t10 := 10
t11 := x == t10
t12 := 20
t13 := y == t12
t14 := 0
x := t14
if t13 == 0 goto L3
L3:
if t11 == 0 goto L4
L4:
t15 := 0
return t15
func_end main
