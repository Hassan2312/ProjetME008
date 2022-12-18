datafile = '../output/Explicite_Dirichlet_3.dat'
stats datafile
set key autotitle columnheader
plot for [IDX=2:STATS_columns-1] datafile using 1:IDX with lines  
pause -1 "Hit any key to continue\n"