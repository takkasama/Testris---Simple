# Guía de uso de raylib (C++)

Referencia de las funciones principales de la librería gráfica raylib, sin lógica de juego. Todo lo que sigue se basa en `#include "raylib.h"`.

## 1. Ventana y bucle principal

```cpp
InitWindow(800, 450, "Titulo de la ventana");
SetTargetFPS(60);

while (!WindowShouldClose()) {
    BeginDrawing();
        ClearBackground(RAYWHITE);
        // dibujado aquí
    EndDrawing();
}

CloseWindow();
```

- `InitWindow(ancho, alto, titulo)` — crea la ventana. Debe llamarse antes que cualquier otra función de raylib.
- `WindowShouldClose()` — true cuando el usuario cierra la ventana o presiona ESC.
- `SetTargetFPS(n)` — limita los cuadros por segundo.
- `BeginDrawing()` / `EndDrawing()` — delimitan todo lo que se dibuja en un frame.
- `ClearBackground(color)` — limpia el fondo con un color.
- `CloseWindow()` — libera recursos, se llama al final.

Otras funciones útiles de ventana:

```cpp
SetWindowSize(w, h);
SetWindowTitle("Nuevo titulo");
ToggleFullscreen();
IsWindowResized();
GetScreenWidth(); GetScreenHeight();
```

## 2. Colores

raylib trae colores predefinidos como constantes:

```
RAYWHITE  WHITE   BLACK   GRAY    LIGHTGRAY  DARKGRAY
RED       GREEN   BLUE    YELLOW  ORANGE     PURPLE
PINK      MAROON  GOLD    LIME    SKYBLUE    VIOLET
BROWN     BEIGE   MAGENTA
```

Color personalizado (RGBA, 0-255):

```cpp
Color miColor = { 255, 128, 0, 255 };
Color otro = Fade(RED, 0.5f); // rojo con 50% de transparencia
```

## 3. Formas básicas

```cpp
DrawPixel(x, y, color);
DrawLine(x1, y1, x2, y2, color);
DrawLineEx(Vector2{x1,y1}, Vector2{x2,y2}, grosor, color);

DrawCircle(centroX, centroY, radio, color);
DrawCircleLines(centroX, centroY, radio, color); // solo contorno

DrawRectangle(x, y, ancho, alto, color);
DrawRectangleLines(x, y, ancho, alto, color);    // solo contorno
DrawRectangleRounded(Rectangle{x,y,w,h}, redondez, segmentos, color);

DrawTriangle(Vector2{x1,y1}, Vector2{x2,y2}, Vector2{x3,y3}, color);

DrawPoly(centro, lados, radio, rotacion, color); // polígono regular
```

`Vector2` y `Rectangle` son structs propios de raylib:

```cpp
Vector2 pos = { 100.0f, 200.0f };
Rectangle rec = { x, y, ancho, alto };
```

## 4. Texto

```cpp
DrawText("Hola mundo", posX, posY, tamañoFuente, color);
DrawTextEx(fuente, "Hola", Vector2{x,y}, tamaño, espaciado, color);

int ancho = MeasureText("Hola mundo", tamañoFuente);
```

Fuentes personalizadas:

```cpp
Font miFuente = LoadFont("recursos/fuente.ttf");
// usar con DrawTextEx
UnloadFont(miFuente); // liberar al cerrar
```

## 5. Imágenes y texturas

Una `Image` vive en memoria RAM (CPU); una `Texture2D` vive en la GPU y es lo que realmente se dibuja.

```cpp
Texture2D textura = LoadTexture("recursos/sprite.png");

DrawTexture(textura, x, y, WHITE);
DrawTextureEx(textura, Vector2{x,y}, rotacion, escala, WHITE);
DrawTextureRec(textura, Rectangle{sx,sy,sw,sh}, Vector2{x,y}, WHITE); // recorte (sprite sheet)
DrawTexturePro(textura, source, dest, origin, rotacion, WHITE);      // control total

UnloadTexture(textura); // liberar al terminar
```

Cargar/editar en CPU antes de subir a GPU:

```cpp
Image img = LoadImage("recursos/sprite.png");
ImageResize(&img, 64, 64);
Texture2D tex = LoadTextureFromImage(img);
UnloadImage(img);
```

## 6. Entrada de teclado

```cpp
IsKeyPressed(KEY_SPACE);   // true solo en el frame que se presionó
IsKeyDown(KEY_RIGHT);      // true mientras se mantiene presionada
IsKeyReleased(KEY_A);      // true en el frame que se soltó
IsKeyUp(KEY_A);            // true mientras no está presionada

int tecla = GetKeyPressed(); // última tecla presionada (para captura de texto)
```

Teclas comunes: `KEY_UP`, `KEY_DOWN`, `KEY_LEFT`, `KEY_RIGHT`, `KEY_ENTER`, `KEY_ESCAPE`, `KEY_A`...`KEY_Z`, `KEY_ZERO`...`KEY_NINE`.

## 7. Entrada de mouse

```cpp
Vector2 mouse = GetMousePosition();
int mx = GetMouseX();
int my = GetMouseY();

IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
IsMouseButtonDown(MOUSE_BUTTON_LEFT);
IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

float rueda = GetMouseWheelMove();
```

## 8. Tiempo

```cpp
float dt = GetFrameTime();  // segundos desde el frame anterior
float t  = GetTime();       // segundos desde que inició el programa
int fps  = GetFPS();
```

## 9. Audio

```cpp
InitAudioDevice();

Sound efecto = LoadSound("recursos/efecto.wav");
PlaySound(efecto);
UnloadSound(efecto);

Music musica = LoadMusicStream("recursos/musica.mp3");
PlayMusicStream(musica);
UpdateMusicStream(musica); // llamar cada frame mientras suena
UnloadMusicStream(musica);

CloseAudioDevice(); // al finalizar el programa
```

## 10. Cámara 2D (desplazar/hacer zoom a la escena)

```cpp
Camera2D camara = { 0 };
camara.target = Vector2{ 0, 0 };
camara.offset = Vector2{ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
camara.rotation = 0.0f;
camara.zoom = 1.0f;

BeginMode2D(camara);
    // dibujar elementos del "mundo"
EndMode2D();
// lo que se dibuje fuera de BeginMode2D/EndMode2D es UI fija en pantalla
```

## 11. Colisiones básicas (geometría, no lógica de juego)

```cpp
CheckCollisionRecs(rec1, rec2);
CheckCollisionCircles(centro1, radio1, centro2, radio2);
CheckCollisionPointRec(punto, rectangulo);
```

## 12. Buenas prácticas de memoria

Todo lo que se carga con `Load...` debe liberarse con `Unload...` correspondiente antes de `CloseWindow()`:

| Carga | Descarga |
|---|---|
| `LoadTexture` | `UnloadTexture` |
| `LoadImage` | `UnloadImage` |
| `LoadFont` | `UnloadFont` |
| `LoadSound` | `UnloadSound` |
| `LoadMusicStream` | `UnloadMusicStream` |

## 13. Ejemplos prácticos: animar el movimiento de una pieza

Estos ejemplos son puramente gráficos (interpolación y dibujo). No incluyen reglas de juego, solo cómo mover algo suavemente en pantalla.

### 13.1 Movimiento continuo con velocidad (frame-independiente)

La forma correcta es mover en función de `GetFrameTime()`, no de un contador fijo, para que la velocidad no dependa de los FPS:

```cpp
Vector2 posicion = { 100.0f, 100.0f };
float velocidad = 200.0f; // píxeles por segundo

while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    if (IsKeyDown(KEY_RIGHT)) posicion.x += velocidad * dt;
    if (IsKeyDown(KEY_LEFT))  posicion.x -= velocidad * dt;

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle((int)posicion.x, (int)posicion.y, 40, 40, BLUE);
    EndDrawing();
}
```

### 13.2 Interpolación entre dos puntos (Lerp) — "deslizar" de una casilla a otra

Útil cuando una pieza debe pasar suavemente de una posición de cuadrícula a otra en vez de saltar de golpe. `raymath.h` trae `Lerp`:

```cpp
#include "raymath.h" // incluye Lerp, Vector2Lerp, etc.

Vector2 origen  = { 0.0f, 0.0f };
Vector2 destino = { 200.0f, 0.0f };
float t = 0.0f;          // progreso de 0.0 a 1.0
float duracion = 0.5f;   // segundos que tarda el movimiento

Vector2 posicionActual = origen;

while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    if (t < 1.0f) {
        t += dt / duracion;
        if (t > 1.0f) t = 1.0f;
        posicionActual.x = Lerp(origen.x, destino.x, t);
        posicionActual.y = Lerp(origen.y, destino.y, t);
    }

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleV(posicionActual, Vector2{40, 40}, RED);
    EndDrawing();
}
```

`Vector2Lerp(a, b, t)` hace lo mismo directamente sobre un `Vector2` completo, sin interpolar x/y por separado:

```cpp
posicionActual = Vector2Lerp(origen, destino, t);
```

### 13.3 Animación por "easing" (aceleración/desaceleración suave)

En vez de interpolar de forma lineal, se puede aplicar una curva al valor de `t` antes de pasarlo a `Lerp` para que el movimiento se sienta más natural (arranca lento, acelera, frena):

```cpp
float easeOutQuad(float t) {
    return 1.0f - (1.0f - t) * (1.0f - t);
}

// dentro del bucle, reemplazando el uso directo de t:
float tSuavizado = easeOutQuad(t);
posicionActual = Vector2Lerp(origen, destino, tSuavizado);
```

### 13.4 Animación de un sprite por cuadros (spriteSheet)

Cuando la "pieza" es una imagen con varios cuadros de animación en una misma textura (sprite sheet), se recorta un rectángulo distinto cada cierto tiempo con `DrawTextureRec`:

```cpp
Texture2D hojaDeSprites = LoadTexture("recursos/pieza.png");
int anchoCuadro = 32;
int totalCuadros = 4;
int cuadroActual = 0;
float tiempoAcumulado = 0.0f;
float tiempoPorCuadro = 0.15f;

while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    tiempoAcumulado += dt;

    if (tiempoAcumulado >= tiempoPorCuadro) {
        tiempoAcumulado = 0.0f;
        cuadroActual = (cuadroActual + 1) % totalCuadros;
    }

    Rectangle origenRec = { (float)(cuadroActual * anchoCuadro), 0, (float)anchoCuadro, (float)hojaDeSprites.height };

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureRec(hojaDeSprites, origenRec, Vector2{300, 200}, WHITE);
    EndDrawing();
}

UnloadTexture(hojaDeSprites);
```

### 13.5 Rotación animada

```cpp
float rotacion = 0.0f;

// dentro del bucle:
rotacion += 90.0f * GetFrameTime(); // 90 grados por segundo

DrawRectanglePro(
    Rectangle{ 400, 300, 40, 40 }, // posición y tamaño
    Vector2{ 20, 20 },             // origen del pivote (centro del rectángulo)
    rotacion,
    BLUE
);
```

### 13.6 Escala animada (efecto "pulso")

```cpp
float tiempo = 0.0f;

// dentro del bucle:
tiempo += GetFrameTime();
float escala = 1.0f + sinf(tiempo * 4.0f) * 0.1f; // oscila entre 0.9 y 1.1

float tamañoBase = 40.0f;
float tamañoActual = tamañoBase * escala;
DrawRectangle(400 - tamañoActual/2, 300 - tamañoActual/2, tamañoActual, tamañoActual, GREEN);
```

## 14. Documentación oficial y repositorios de referencia

raylib no tiene un manual de referencia tradicional: la biblioteca se aprende principalmente a través de los ejemplos, ya que no hay documentación de API estándar pero sí existe un cheatsheet con todas las funciones disponibles, una breve descripción de cada una, sus parámetros de entrada y su valor de retorno. También aclara que raylib no ofrece la típica documentación de API ni un gran conjunto de tutoriales, ya que está diseñada para aprenderse desde el cheatsheet junto con una amplia colección de ejemplos.

**Documentación oficial:**
- Sitio oficial: https://www.raylib.com/
- Cheatsheet (todas las funciones): https://www.raylib.com/cheatsheet/cheatsheet.html
- Ejemplos oficiales por categoría (core, shapes, textures, text, audio, etc.): https://www.raylib.com/examples.html
- Wiki oficial (guías de compilación, diseño interno, FAQ): https://github.com/raysan5/raylib/wiki

**Repositorio principal:**
- Código fuente: https://github.com/raysan5/raylib

**Colecciones de ejemplos y proyectos de la comunidad:**
- Lista curada de proyectos, bindings, plantillas y herramientas hechas con raylib ("awesome list"): https://github.com/southdy/awesome-raylib
- Colección de ejemplos adicionales en C: https://github.com/Pakz001/Raylib-Examples
- Ejemplos con explicación paso a paso (incluye un Tetris y un Snake hechos en C++ con raylib, útiles como referencia de estructura de proyecto): https://github.com/topics/raylib-examples

## 15. Referencia rápida oficial

La documentación completa de todas las funciones (cheatsheet) está en:
https://www.raylib.com/cheatsheet/cheatsheet.html
