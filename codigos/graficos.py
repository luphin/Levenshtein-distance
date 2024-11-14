import matplotlib.pyplot as plt

# Leer datos del archivo
casos = []
tiemposFB = []
memoriasFB = []
tiemposDP = []
memoriasDP = []

with open('resultados.txt', 'r') as f:
    for line in f:
        if "Tiempo (FB)" in line:
            tiemposFB.append(int(line.split("Tiempo (FB): ")[1].split(" us")[0]))
            memoriasFB.append(int(line.split("Memoria (FB): ")[1].split(" KB")[0]))
        elif "Tiempo (DP)" in line:
            tiemposDP.append(int(line.split("Tiempo (DP): ")[1].split(" us")[0]))
            memoriasDP.append(int(line.split("Memoria (DP): ")[1].split(" KB")[0]))

# Crear gráfico de tiempo vs caso
plt.figure(figsize=(12, 6))
plt.plot(range(len(tiemposFB)), tiemposFB, label='Tiempo Fuerza Bruta', marker='o')
plt.plot(range(len(tiemposDP)), tiemposDP, label='Tiempo Programación Dinámica', marker='x')
plt.xlabel('Número de Caso')
plt.ylabel('Tiempo de Ejecución (microsegundos)')
plt.legend()
plt.title('Tiempo de Ejecución vs Número de Caso')
plt.show()

# Crear gráfico de memoria vs caso
plt.figure(figsize=(12, 6))
plt.plot(range(len(memoriasFB)), memoriasFB, label='Memoria Fuerza Bruta', marker='o')
plt.plot(range(len(memoriasDP)), memoriasDP, label='Memoria Programación Dinámica', marker='x')
plt.xlabel('Número de Caso')
plt.ylabel('Memoria (KB)')
plt.legend()
plt.title('Memoria vs Número de Caso')
plt.show()
