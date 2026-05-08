
*Este proyecto ha sido creado como parte del currículo de 42 por ksudyn y ldel-val.*

# miniRT

### Descripción
**miniRT** es un proyecto introductorio al mundo del Raytracing (trazado de rayos). Permite renderizar imágenes generadas por ordenador utilizando técnicas básicas de trazado de rayos, simulando cómo interactúan los rayos de luz con los objetos para crear escenas 3D realistas desde cero.

El proyecto permite:
- **Renderizar imágenes 3D:** Generar salidas visuales mediante algoritmos de intersección rayo-objeto.
- **Entender conceptos clave:** Trabajar con cámaras, fuentes de luz (Ambiental y Puntual) y primitivas geométricas (Esferas, Planos y Cilindros).
- **Aplicar fórmulas matemáticas:** Implementar álgebra lineal y ecuaciones cuadráticas para resolver intersecciones en el espacio 3D.

### Instrucciones

#### Requisitos previos
Antes de compilar, asegúrate de tener instaladas las librerías necesarias para **MinilibX**:
- En **Linux**: `libx11-dev`, `libxext-dev` y `make`.
- En **macOS**: Herramientas de línea de comandos de `Xcode`.

#### Compilación
Para compilar el proyecto, navega al directorio raíz y ejecuta:
```bash
make
```
Esto generará el ejecutable `miniRT`.

#### Ejecución
Para renderizar una escena, ejecuta el programa proporcionando un archivo de configuración `.rt` válido como argumento:
```bash
./miniRT scenes/example.rt
```

### Controles
- **ESC / X de la ventana:** Cierra el programa y libera toda la memoria.
- **W, A, S, D:** Mover la cámara (Adelante, Izquierda, Atrás, Derecha).
- **ESPACIO / SHIFT:** Mover la cámara hacia Arriba o Abajo.
- **Flechas del teclado:** Rotar la vista de la cámara (Inclinación y Giro).
- **Teclas + / -:** Ajustar el Campo de Visión (FOV).

### Elementos de la Escena (Mapa RT)
El archivo `.rt` define el diseño de la escena utilizando el siguiente formato:
- **Luz Ambiental (A):** `A [ratio] [R,G,B]` - Intensidad y color de la iluminación global.
- **Cámara (C):** `C [x,y,z] [v_x,v_y,v_z] [FOV]` - Posición, vector de orientación y campo de visión.
- **Luz (L):** `L [x,y,z] [brillo] [R,G,B]` - Posición de la fuente de luz puntual e intensidad.
- **Esfera (sp):** `sp [centro x,y,z] [diámetro] [R,G,B]`
- **Plano (pl):** `pl [punto x,y,z] [normal v_x,v_y,v_z] [R,G,B]`
- **Cilindro (cy):** `cy [centro x,y,z] [eje v_x,v_y,v_z] [diámetro] [altura] [R,G,B]`

### Implementación Técnica

#### Fórmulas de Intersección
- **Esfera:** Basada en la fórmula 3D $(x - h)^2 + (y - k)^2 + (z - l)^2 = r^2$. Resolvemos para la ecuación del rayo $P = O + tD$.
- **Plano:** Representado como $ax + by + cz + d = 0$. La intersección se encuentra donde el rayo impacta el plano definido por su vector normal.
- **Cilindro:** Se resuelve intersecando un rayo con un cilindro infinitamente largo y luego recortando el resultado según la altura especificada.

#### Sombreado y Color
- **Color Inicial:** El color base del objeto multiplicado por la luz ambiental.
- **Iluminación Difusa:** Calculada basándose en el ángulo entre el vector normal en el punto de intersección y el vector de la luz (Ley del Coseno de Lambert).
- **Sombras:** Se lanza un rayo de sombra desde el punto de intersección hacia la fuente de luz. Si se encuentra un objeto en medio, el punto permanece en sombra.
- **Color Final:** La suma de los componentes ambientales y difusos, asegurando que los valores se mantengan dentro del rango RGB [0, 255].

#### Estructuras de Datos
- **t_scene / t_data:** Estructuras principales que contienen las listas de objetos, configuración de la cámara e información de las luces.
- **t_camera:** Almacena el FOV, el origen y la orientación para calcular la dirección del rayo para cada píxel.

### Recursos

#### Documentación
- **Scratchapixel:** Recurso principal para los fundamentos del Ray Tracing.
- **Modelo de Reflexión de Phong:** Lógica para la iluminación y el sombreado.
- **Docs de MinilibX:** Gestión de ventanas y eventos.

#### Uso de IA
La IA (específicamente Google Gemini) se utilizó como herramienta colaborativa para:
- **Depuración de Memoria:** Identificar y corregir bloques "still reachable" y errores de doble liberación en el parser y la lógica de `get_next_line`.
- **Optimización del Parser:** Refactorizar el bucle de `read_file` para manejar errores de forma segura sin dejar residuos en memoria.
- **Refinamiento Lógico:** Asistencia en la implementación de fórmulas matemáticas para intersecciones rayo-objeto y sombreado.
- **Redacción Técnica:** Estructuración y traducción de esta documentación para asegurar claridad y estándares profesionales.

### Compatibilidad
El proyecto incluye soporte multiplataforma para **Linux** y **macOS**. El `Makefile` detecta automáticamente el SO para enlazar las librerías correctas (X11/Xext para Linux o OpenGL/AppKit para macOS) y gestiona las diferencias de códigos de teclas para la interacción con el teclado.
```