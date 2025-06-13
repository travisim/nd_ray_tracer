set term pngcairo size 800,800
set output '2D Test - Start at Obstacle.png'
set title '2D Test - Start at Obstacle'
set xlabel 'X'
set ylabel 'Y'
set grid
set size square
plot '-' with lines title 'Path', '-' with points pt 7 ps 2 lc 'red' title 'Intersections', '-' with points pt 5 ps 1.5 lc 'green' title 'Start', '-' with points pt 5 ps 1.5 lc 'blue' title 'Goal', '-' with points pt 9 ps 1.5 lc 'purple' title 'Y Coords', '-' with boxes fill solid 0.2 title 'Front Cells 0', '-' with boxes fill solid 1.0 border lc 'black' title 'Obstacle 0'
1 1
e
1 1
e
1 1
e
5 5
e
1 1
e
1 1 1 1
e
1 1 1 1
e
