datafile = '../output/Explicite_Dirichlet_2.dat'
stats datafile
set title "Concentration en fonction de la position a differents temps"
set xlabel "Position (x)"
set ylabel "Concentration (U)"
set key autotitle columnheader
plot for [IDX=1:STATS_blocks] datafile index (IDX-1) u 1:2 w lines
pause -1 "Hit any key to continue\n"