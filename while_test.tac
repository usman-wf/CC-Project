func_begin main
t0 := 0
i := t0
t1 := 0
sum := t1
L0:
t2 := 10
t3 := i < t2
if t3 == 0 goto L1
t4 := sum + i
sum := t4
t5 := 1
t6 := i + t5
i := t6
goto L0
L1:
t7 := 0
i := t7
L2:
t8 := 3
t9 := i < t8
if t9 == 0 goto L3
t10 := 0
j := t10
L4:
t11 := 3
t12 := j < t11
if t12 == 0 goto L5
t13 := 1
t14 := sum + t13
sum := t14
t15 := 1
t16 := j + t15
j := t16
goto L4
L5:
t17 := 1
t18 := i + t17
i := t18
goto L2
L3:
return sum
func_end main
