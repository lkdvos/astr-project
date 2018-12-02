set term gif animate delay 50 size 400, 400
set output "data/data.gif"
do for [n=1:50] {
  splot "data/data.txt" u 2:3:4 every ::n::(n+2) w lp, "data/data.txt" u 8:9:10 every ::n::(n+2) w lp, "data/data.txt" u 14:15:16 every ::n::(n+2) w lp t sprintf("n=%i", n)


}
