set term pngcairo size 800,800
set output '3D Test - Start at Obstacle.png'
set title '3D Test - Start at Obstacle'
set xlabel 'X'
set ylabel 'Y'
set zlabel 'Z'
set grid
splot '-' with lines title 'Path', '-' with points pt 7 ps 2 lc 'red' title 'Intersections', '-' with points pt 5 ps 1.5 lc 'green' title 'Start', '-' with points pt 5 ps 1.5 lc 'blue' title 'Goal', '-' with points pt 9 ps 1.5 lc 'purple' title 'Y Coords'
1 1 1
e
1 1 1
e
1 1 1
e
5 5 5
e
1 1 1
e
