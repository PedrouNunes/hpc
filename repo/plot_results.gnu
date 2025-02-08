set terminal pngcairo enhanced font 'Verdana,12'
set output "execution_time.png"
set title "Comparação de Tempo de Execução"
set xlabel "Tamanho da Imagem"
set ylabel "Tempo de Execução (s)"
set grid
plot "results.dat" using 1:2 with linespoints title "Sequencial", \
     "results.dat" using 1:3 with linespoints title "Multicore", \
     "results.dat" using 1:4 with linespoints title "GPU"

set output "speedup.png"
set title "Speedup Comparativo"
set ylabel "Speedup"
plot "results.dat" using 1:($2/$3) with linespoints title "Speedup Multicore", \
     "results.dat" using 1:($2/$4) with linespoints title "Speedup GPU"
