set term pngcairo size 800,800
set output '2D Test - Quadrant 4 (SE).png'
set title '2D Test - Quadrant 4 (SE)'
set xlabel 'X'
set ylabel 'Y'
set grid
set size square
set object 1 rect from 1,5 to 2,6 fc rgb 'cyan' fs solid 0.3
set object 2 rect from 2,4 to 3,5 fc rgb 'cyan' fs solid 0.3
set object 3 rect from 3,3 to 4,4 fc rgb 'cyan' fs solid 0.3
set object 4 rect from 4,2 to 5,3 fc rgb 'cyan' fs solid 0.3
set object 5 rect from 5,1 to 6,2 fc rgb 'cyan' fs solid 0.3
set arrow 1 from 1.5,5.5 to 1.5,5.5 head filled lw 2 lc 'red'
set arrow 2 from 2,5 to 2.5,4.5 head filled lw 2 lc 'red'
set arrow 3 from 3,4 to 3.5,3.5 head filled lw 2 lc 'red'
set arrow 4 from 4,3 to 4.5,2.5 head filled lw 2 lc 'red'
set arrow 5 from 5,2 to 5.5,1.5 head filled lw 2 lc 'red'
plot '-' with lines title 'Path', '-' with points pt 7 ps 2 lc 'red' title 'Intersections', '-' with points pt 5 ps 1.5 lc 'green' title 'Start', '-' with points pt 5 ps 1.5 lc 'blue' title 'Goal', '-' with points pt 9 ps 1.5 lc 'purple' title 'Y Coords'
1.5 5.5
2 5
3 4
4 3
5 2
5.5 1.5
e
1.5 5.5
2 5
3 4
4 3
5 2
e
1.5 5.5
e
5.5 1.5
e
1 6
2 5
3 4
4 3
5 2
e
