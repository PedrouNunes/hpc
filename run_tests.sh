
sizes=(64 128 256 512)


output_file="results_plot.csv"
echo "Size,Sequential,Multicore,GPU,Speedup_Multicore,Speedup_GPU" > $output_file

for size in "${sizes[@]}"; do
    echo "Rodando testes para tamanho $size x $size"

    seq_time=$(./kde_sequential $size)
    par_time=$(./kde_parallel $size)
    gpu_time=$(./kde_gpu $size)

    speedup_multicore=$(echo "$seq_time / $par_time" | bc -l)
    speedup_gpu=$(echo "$seq_time / $gpu_time" | bc -l)

    echo "$size,$seq_time,$par_time,$gpu_time,$speedup_multicore,$speedup_gpu" >> $output_file
done

echo "Testes finalizados. Resultados salvos em $output_file"
