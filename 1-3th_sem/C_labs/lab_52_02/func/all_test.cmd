@ECHO OFF
FOR /L %%B IN (1,1,1) DO (call pos_sort_test.cmd 0%%B)
FOR /L %%B IN (1,1,2) DO (call neg_sort_test.cmd 0%%B)
FOR /L %%B IN (1,1,1) DO (call pos_print_by_substr_test.cmd 0%%B)
FOR /L %%B IN (1,1,3) DO (call neg_print_by_substr_test.cmd 0%%B)
FOR /L %%B IN (1,1,4) DO (call pos_add_test.cmd 0%%B)
FOR /L %%B IN (1,1,6) DO (call neg_add_test.cmd 0%%B)