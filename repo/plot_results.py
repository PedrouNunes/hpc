import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.csv")


sizes = df["Size"]
sequential = df["Sequential"]
multicore = df["Multicore"]
gpu = df["GPU"]


plt.figure(figsize=(8, 6))
plt.plot(sizes, sequential, marker='o', label="Sequencial")
plt.plot(sizes, multicore, marker='s', label="Multicore")
plt.plot(sizes, gpu, marker='^', label="GPU")
plt.xlabel("Tamanho da Imagem")
plt.ylabel("Tempo de Execução (s)")
plt.title("Comparação de Tempo de Execução")
plt.legend()
plt.grid()
plt.savefig("execution_time.png")
plt.show()


speedup_multicore = sequential / multicore
speedup_gpu = sequential / gpu

plt.figure(figsize=(8, 6))
plt.plot(sizes, speedup_multicore, marker='s', label="Speedup Multicore")
plt.plot(sizes, speedup_gpu, marker='^', label="Speedup GPU")
plt.xlabel("Tamanho da Imagem")
plt.ylabel("Speedup")
plt.title("Comparação de Speedup")
plt.legend()
plt.grid()
plt.savefig("speedup.png")
plt.show()
