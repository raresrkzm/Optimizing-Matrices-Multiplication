import matplotlib.pyplot as plt

# Valorile lui N si ale timpilor
N = [200, 400, 600, 800, 1000]
blas_times = [0.014061, 0.115400, 0.193476, 0.620291, 0.851346]
neopt_times = [0.116644, 1.308298, 3.224134, 10.85633, 14.495811]
opt_m_times = [0.093291, 1.072563, 2.563044, 8.246308, 11.793517]

def adnoteaza(x, y):
    for i in range(len(x)):
        plt.annotate(f"({x[i]}, {y[i]:.2f})", (x[i], y[i]), textcoords="offset points", xytext=(0,5), ha='center', fontsize=8)

# === 1. Grafic pentru BLAS ===
plt.figure()
plt.plot(N, blas_times, marker='o', color='green', label='blas')
adnoteaza(N, blas_times)
plt.title("Timp execuție - BLAS")
plt.xlabel("Dimensiune matrice N")
plt.ylabel("Timp (secunde)")
plt.legend()
plt.grid(True)
plt.savefig("grafice/grafic_blas.png")

# === 2. Grafic pentru NEOPT ===
plt.figure()
plt.plot(N, neopt_times, marker='o', color='blue', label='neopt')
adnoteaza(N, neopt_times)
plt.title("Timp execuție - NEOPT")
plt.xlabel("Dimensiune matrice N")
plt.ylabel("Timp (secunde)")
plt.legend()
plt.grid(True)
plt.savefig("grafice/grafic_neopt.png")

# === 3. Grafic pentru OPT_M ===
plt.figure()
plt.plot(N, opt_m_times, marker='o', color='orange', label='opt_m')
adnoteaza(N, opt_m_times)
plt.title("Timp execuție - OPT_M")
plt.xlabel("Dimensiune matrice N")
plt.ylabel("Timp (secunde)")
plt.legend()
plt.grid(True)
plt.savefig("grafice/grafic_opt_m.png")

# === 4. Grafic comparativ ===
plt.figure()
plt.plot(N, blas_times, marker='o', label="blas", color='green')
adnoteaza(N, blas_times)
plt.plot(N, neopt_times, marker='o', label="neopt", color='blue')
adnoteaza(N, neopt_times)
plt.plot(N, opt_m_times, marker='o', label="opt_m", color='orange')
adnoteaza(N, opt_m_times)
plt.title("Comparație timp de execuție metode")
plt.xlabel("Dimensiune matrice N")
plt.ylabel("Timp (secunde)")
plt.legend()
plt.grid(True)
plt.savefig("grafice/grafic_comparativ.png")

plt.show()
