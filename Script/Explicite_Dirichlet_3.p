set terminal png size 1000,1000 enhanced font "Helvetica,20"
set output 'Explicite_Dirichlet_3.png'
datafile = '../output/Explicite_Dirichlet_3.dat'
stats datafile
plot for [IDX=2:STATS_columns-1] datafile using 1:IDX with lines  
pause -1 "Hit any key to continue\n"