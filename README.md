# Tarea 1 2022-2

## Agustín Urrutia

## Compilar

```
make
```

## Recompilar

```
make clean && make
```

## Ejecutar

Para la parte 1:

```
./dccompress p1-imgs/egg_king.png out.png filter 5
```

Para la parte 2:

```
./bstman p2-txt/input.txt output.txt
```

## Información adicional

El código fue desarrollado utilizando `GitHub Copilot`

Para el cálculo de la media y la desviación fueron utilizados los métodos incrementales [del link](https://datagenetics.com/blog/november22017/index.html) entregado por el equipo docente

No se utilizó código de terceros, salvo el código inicial provisto por el equipo docente

### Sobre `dccompress` :black_joker:

- `QuadTree.c` y `QuadTree.h` se encargan princiaplemte del manejo del árbol, su creación, copia, manejo de algún atributo y destrucción.

- `filter.c` y `filter.h` se encargan de la aplicación de los filtros a las imágenes, incluyendo los cálculos de la media y desviación. Se importa la bibliotea `math.h` para el cálculo.

### Sobre `bstman` :evergreen_tree:

- El algoritmo creado no realiza ningún tipo de operación de balanceo.

- Se vio la cápsula subida por el equipo docente, la que fue utilizada solo como estudio, pero el código fue desarrollado por mí. Pudo ocurrir que inconscientemente y el uso de `Copilot` haya generado un código muy similar al de la cápsula, pero no fue intencional (lo menciono por si acaso).
