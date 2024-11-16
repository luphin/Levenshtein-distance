# Proyecto Explorando la Distancia entre Cadenas, una Operación a la Vez
Proyecto de ramo Algoritmos y Complejodad 2024-2 Universidad Técnica Federico Santa María

## Objetivo
Este proyecto implementa los algoritmos de **Fuerza Bruta** y **Programación Dinámica** para calcular la distnacia mínima de edición entre dos cadenas de texto, considerando costos variables para las operaciones de inserción, eliminación, sustitución y transposición. El objetivo es realizar un análisis comparativo entre ambos algoritmos en términos de tiempo de ejecución y uso de memoria.

## Resultados
- [x] Correcta implementación de los algoritmos de Fuerza Bruta y Programación Dinámica.
    - Se determina adecuadamente la distancia mínima de edición según los costos asignados a las operaciones.
- [x] Cálculo de los tiempos de ejecución por algoritmo.
- [ ] Cálculo del uso de memoria por algoritmo.
    - La implementación no fue correcta dentro de los algoritmos, ya que no determina adecuadamente el uso de memoria. 
    Además, el archivo `operaciones.txt`, que debía almacenar las operaciones realizadas, no fue actualizado porque se registraban todas las operaciones de ambos algoritmos, lo que resultaba en un archivo excesivamente extenso.

Puede revisar la documentación en [AlgoReportTemplate-main/tarea_main.pdf](https://github.com/luphin/Tarea2y3Algoritmos-FB-PD/blob/main/AlgoReportTemplate-main/tarea_main.pdf)

## Requisitos
Para ejecutar este proyecto, asegúrese de tener instalado lo siguiente:

- **g++**: Para compilar los programas en C++.
- **Python**: Para generar gráficos basados en los resultados (se requiere el script `graficos.py`).

>[!IMPORTANT]
> Implementación utiliza la biblioteca sys/resource.h de C++, la cual permite la lectura del consumo de memoria en las operaciones, pero solo está disponible en entornos Linux y Unix. En caso de utilizar un entorno diferente, será necesario eliminar esta funcionalidad en el archivo main.cpp. Esto implicará realizar modificaciones tales como eliminar la función de lectura de memoria del main y omitir la escritura de este dato en el archivo de resultados

## Instrucciones de Uso

### Compilación

Para compilar el proyecto, simplemente ejecute:
```zsh
make
```
Esto compilará primero el archivo para generar los costos aleatorios (`random-costos.cpp`) y luego, el programa principal (`main.cpp`).

2. Comandos Disponibles

El Makefile proporciona varios comandos que puedes ejecutar para generar los resultados y gráficos. Los comandos son los siguientes:

- Compilar los archivos de costos (fijos):
```zsh
make costos
```
Esto generará el archivo ejecutable `costos.cpp`, que crea los archivos de costos con valores fijos (1 para todas las operaciones).

- Compilar los archivos de costos aleatorios:
```zsh
make random
```
Este comando generará el archivo ejecutable `randomcostos.cpp`, que crea los archivos de costos con valores aleatorios entre 1 y 10.

- Compilar el programa principal:
```zsh
make main
```
Esto compilará el archivo `main.cpp`, que contiene la implementación de los algoritmos de Fuerza Bruta y Programación Dinámica.

- Ejecutar el generador de costos fijos:
```zsh
make run-costos
```
Este comando ejecuta el archivo costos y genera los archivos de costos fijos.

- Ejecutar el generador de costos aleatorios:
```zsh
make run-random
```
Ejecuta el archivo randomcostos y genera los archivos de costos aleatorios.

- Ejecutar el programa principal:
```zsh
make run-main
```
Este comando ejecuta el archivo main, que realiza el cálculo de la distancia de Levenshtein con los costos definidos previamente.

- Generar gráficos (Python):
```zsh
make python
```
Ejecuta el script Python graficos.py para generar los gráficos basados en los resultados obtenidos.

>[!NOTE]
> Puede ejecutarlo de manera manueal con `python graficos.py` o `python3 graficos.py`.

- Limpiar los archivos generados:
```zsh
make clean
```
Este comando elimina los archivos compilados (costos, randomcostos, main) para limpiar el directorio.

### Ejemplo de Ejecución

1. Primero, genere los archivos de costos (fijos o aleatorios):
```zsh
make run-costos  # o make run-random
```

2. Luego, ejecute el programa principal:
```zsh
make run-main
```

3.Finalmente, si desea visualizar los gráficos, ejecute el script Python:
```zsh
make python
```

>[!NOTE]
> Asegúrese de que todos los archivos de entrada estén disponibles antes de ejecutar el programa.
> Los gráficos generados se basarán en los resultados de las pruebas con diferentes longitudes y estructuras de las cadenas de entrada.

## Contribuciones

Si desea contribuir al proyecto, no dude en realizar un fork y enviar sus mejoras mediante un pull request.

## Autor 
Luis Zegarra - 202073628-6
