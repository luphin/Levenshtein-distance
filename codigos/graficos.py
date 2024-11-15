import matplotlib.pyplot as plt

# Leer datos del archivo
casos = []
tiemposFB = []
memoriasFB = []
tiemposDP = []
memoriasDP = []
promedios_largos = []

with open('resultados.txt', 'r') as f:
    for line in f:
        if "Caso:" in line:
            # Extraer los strings del caso
            strings = line.split("Caso: ")[1].split(" vs ")
            string1, string2 = strings[0].strip(), strings[1].strip()
            # Calcular el promedio de los largos de los dos strings
            promedio_largo = (len(string1) + len(string2)) / 2
            promedios_largos.append(promedio_largo)
        elif "Tiempo (FB)" in line:
            tiemposFB.append(int(line.split("Tiempo (FB): ")[1].split(" us")[0]))
            memoriasFB.append(int(line.split("Memoria (FB): ")[1].split(" KB")[0]))
        elif "Tiempo (DP)" in line:
            tiemposDP.append(int(line.split("Tiempo (DP): ")[1].split(" us")[0]))
            memoriasDP.append(int(line.split("Memoria (DP): ")[1].split(" KB")[0]))

# Ordenar los datos por el promedio de los largos de los strings
ordenado = sorted(zip(promedios_largos, tiemposFB, memoriasFB, tiemposDP, memoriasDP), key=lambda x: x[0])

# Desempaquetar los datos ordenados
promedios_largos_ordenados, tiemposFB_ordenados, memoriasFB_ordenadas, tiemposDP_ordenados, memoriasDP_ordenadas = zip(*ordenado)

# Crear gráfico de tiempo vs promedio de largos con escala logarítmica en el eje Y
plt.figure(figsize=(12, 6))
plt.plot(promedios_largos_ordenados, tiemposFB_ordenados, label='Tiempo Fuerza Bruta', marker='o', color='red')
plt.plot(promedios_largos_ordenados, tiemposDP_ordenados, label='Tiempo Programación Dinámica', marker='x', color='green')
# Labels
plt.xlabel('Promedio del Largo de los Strings en Cada Caso')
plt.ylabel('Tiempo de Ejecución (microsegundos)')
plt.yscale('log')  # Aplicar escala logarítmica en el eje Y
plt.legend()
# Title
plt.title('Tiempo de Ejecución vs Promedio de Largo de los Strings (Escala Logarítmica)')

# Añadir etiquetas para cada punto, alternando la posición
for i, (promedio, tiempo_fb, tiempo_dp) in enumerate(zip(promedios_largos_ordenados, tiemposFB_ordenados, tiemposDP_ordenados)):
    offset = (0, 10) if i % 2 == 0 else (0, -15)  # Alternar posiciones FB
    plt.annotate(f"{tiempo_fb}", (promedio, tiempo_fb), textcoords="offset points", xytext=offset, ha='center', fontsize=8, color='red')
    offset_dp = (0, 10) if i % 2 != 0 else (0, -15) # Alternar posiciones PD
    plt.annotate(f"{tiempo_dp}", (promedio, tiempo_dp), textcoords="offset points", xytext=offset_dp, ha='center', fontsize=8, color='green')

plt.show()

# Crear gráfico de memoria vs promedio de largos
plt.figure(figsize=(12, 6))
plt.plot(promedios_largos_ordenados, memoriasFB_ordenadas, label='Memoria Fuerza Bruta', marker='o', color='red')
plt.plot(promedios_largos_ordenados, memoriasDP_ordenadas, label='Memoria Programación Dinámica', marker='x', color='green')
# Labels
plt.xlabel('Promedio del Largo de los Strings en Cada Caso')
plt.ylabel('Memoria (KB)')
plt.legend()
# Title
plt.title('Memoria vs Promedio de Largo de los Strings')

# Añadir etiquetas para cada punto, alternando la posición
for i, (promedio, memoria_fb, memoria_dp) in enumerate(zip(promedios_largos_ordenados, memoriasFB_ordenadas, memoriasDP_ordenadas)):
    offset = (0, 10) if i % 2 == 0 else (0, -15)  # Alternar posiciones FB
    plt.annotate(f"{memoria_fb}", (promedio, memoria_fb), textcoords="offset points", xytext=offset, ha='center', fontsize=8, color='red')
    offset_dp = (0, 10) if i % 2 != 0 else (0, -15) # Alternar posiciones PD
    plt.annotate(f"{memoria_dp}", (promedio, memoria_dp), textcoords="offset points", xytext=offset_dp, ha='center', fontsize=8, color='green')

plt.show()
