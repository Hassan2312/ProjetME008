set terminal png size 1000,1000 enhanced font "Helvetica,20"
set output 'Explicite_Dirichlet_2.png'
datafile = '../output/Explicite_Dirichlet_2.dat'
stats datafile
plot for [IDX=1:STATS_blocks] datafile index (IDX-1) u 1:2 w lines  
pause -1 "Hit any key to continue\n"