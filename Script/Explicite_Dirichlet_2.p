datafile = '../output/Explicite_Dirichlet_2.dat'
stats datafile
plot for [IDX=1:STATS_blocks] datafile index (IDX-1) u 1:2 w lines 
pause -1 "Hit any key to continue\n"