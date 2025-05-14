func_begin max
t0 := a > b
return a
if t0 == 0 goto L0
L0:
return b
func_end max
func_begin main
param a
call scan, 1
param b
call scan, 1
param a
param b
call max, 2
t1 := return_value
result := t1
t2 := 10
t3 := result > t2
t4 := 0
i := t4
L1:
t5 := i < result
if t5 == 0 goto L2
t6 := 2
t7 := i % t6
t8 := 0
t9 := t7 == t8
param i
call print, 1
if t9 == 0 goto L3
L3:
t10 := 1
t11 := i + t10
i := t11
goto L1
L2:
if t3 == 0 goto L4
param result
call print, 1
goto L5
L4:
L5:
t12 := 0
return t12
func_end main
