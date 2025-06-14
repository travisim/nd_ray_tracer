set term pngcairo size 800,800
set output '3D Test - Octant 8 (+,-,-).png'
set title '3D Test - Octant 8 (+,-,-)'
set xlabel 'X'
set ylabel 'Y'
set zlabel 'Z'
set grid
set view 60, 30
set arrow 1 from 1.5,5.5,5.5 to 1.5,5.5,5.5 head filled lw 2 lc 'red'
set arrow 2 from 2,5,5 to 2.5,4.5,4.5 head filled lw 2 lc 'red'
set arrow 3 from 3,4,4 to 3.5,3.5,3.5 head filled lw 2 lc 'red'
set arrow 4 from 4,3,3 to 4.5,2.5,2.5 head filled lw 2 lc 'red'
set arrow 5 from 5,2,2 to 5.5,1.5,1.5 head filled lw 2 lc 'red'
set pm3d depthorder
splot '-' with lines title 'Path', '-' with points pt 7 ps 2 lc 'red' title 'Intersections', '-' with points pt 5 ps 1.5 lc 'green' title 'Start', '-' with points pt 5 ps 1.5 lc 'blue' title 'Goal', '-' with points pt 9 ps 1.5 lc 'purple' title 'Y Coords', '-' with polygons fill solid 0.3 border lc 'cyan' notitle, '-' with polygons fill solid 0.3 border lc 'cyan' notitle, '-' with polygons fill solid 0.3 border lc 'cyan' notitle, '-' with polygons fill solid 0.3 border lc 'cyan' notitle, '-' with polygons fill solid 0.3 border lc 'cyan' notitle
1.5 5.5 5.5
2 5 5
3 4 4
4 3 3
5 2 2
5.5 1.5 1.5
e
1.5 5.5 5.5
2 5 5
3 4 4
4 3 3
5 2 2
e
1.5 5.5 5.5
e
5.5 1.5 1.5
e
1 6 6
2 5 5
3 4 4
4 3 3
5 2 2
e
1 5 5
2 5 5
2 6 5
1 6 5
1 5 5

1 5 6
2 5 6
2 6 6
1 6 6
1 5 6

1 5 5
2 5 5
2 5 6
1 5 6
1 5 5

1 6 5
2 6 5
2 6 6
1 6 6
1 6 5

1 5 5
1 6 5
1 6 6
1 5 6
1 5 5

2 5 5
2 6 5
2 6 6
2 5 6
2 5 5

e
2 4 4
3 4 4
3 5 4
2 5 4
2 4 4

2 4 5
3 4 5
3 5 5
2 5 5
2 4 5

2 4 4
3 4 4
3 4 5
2 4 5
2 4 4

2 5 4
3 5 4
3 5 5
2 5 5
2 5 4

2 4 4
2 5 4
2 5 5
2 4 5
2 4 4

3 4 4
3 5 4
3 5 5
3 4 5
3 4 4

e
3 3 3
4 3 3
4 4 3
3 4 3
3 3 3

3 3 4
4 3 4
4 4 4
3 4 4
3 3 4

3 3 3
4 3 3
4 3 4
3 3 4
3 3 3

3 4 3
4 4 3
4 4 4
3 4 4
3 4 3

3 3 3
3 4 3
3 4 4
3 3 4
3 3 3

4 3 3
4 4 3
4 4 4
4 3 4
4 3 3

e
4 2 2
5 2 2
5 3 2
4 3 2
4 2 2

4 2 3
5 2 3
5 3 3
4 3 3
4 2 3

4 2 2
5 2 2
5 2 3
4 2 3
4 2 2

4 3 2
5 3 2
5 3 3
4 3 3
4 3 2

4 2 2
4 3 2
4 3 3
4 2 3
4 2 2

5 2 2
5 3 2
5 3 3
5 2 3
5 2 2

e
5 1 1
6 1 1
6 2 1
5 2 1
5 1 1

5 1 2
6 1 2
6 2 2
5 2 2
5 1 2

5 1 1
6 1 1
6 1 2
5 1 2
5 1 1

5 2 1
6 2 1
6 2 2
5 2 2
5 2 1

5 1 1
5 2 1
5 2 2
5 1 2
5 1 1

6 1 1
6 2 1
6 2 2
6 1 2
6 1 1

e
