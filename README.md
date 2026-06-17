# Clasificador de Objetos por Color con Sensor TCS3200/TCS230
> **Asignatura:** Electrónica Digital II - Universidad Nacional de Córdoba
> **Integrantes:**
> * Rojas, Facundo Nicolás
> * Rojas, Facundo Nicolás
> * Soria Enzo Agustín
> **Profesor:** [Nombre del Profesor]

---

## 1. Descripción General del Proyecto

El sistema es un clasificador automático de objetos por color, pensado como una pequeña estación de control de calidad o de selección de piezas. Un sensor de color TCS3200/TCS230 mide la luz reflejada por un objeto colocado frente a él, el microcontrolador PIC16F887 procesa esa lectura para determinar si predomina el rojo, el verde o el azul, y según el resultado posiciona un servomotor en uno de tres ángulos (0°, 90° o 180°), simulando una compuerta o brazo que dirige el objeto hacia distintas salidas. El resultado de cada clasificación se muestra en un display LCD y se envía por UART a una PC para su registro o monitoreo.

El sistema está dirigido a un entorno educativo de control y automatización, donde se busca demostrar la integración de un sensor digital de frecuencia, un conversor ADC con su periférico de entrada (potenciómetro), un actuador (servomotor) y dos salidas de información simultáneas (LCD y UART) sobre un mismo microcontrolador de 8 bits.

### Alcances del Proyecto

* **El sistema SÍ es capaz de:**
  * Medir la frecuencia de salida del sensor TCS3200/TCS230 para los canales rojo, verde y azul mediante Timer1 en modo contador externo.
  * Clasificar el color predominante del objeto comparando los tres valores medidos.
  * Usar el valor leído por el ADC (potenciómetro en RA0) como umbral mínimo de detección, de forma que si la intensidad de verde no supera ese umbral, el sistema reporta "SIN OBJETO" en lugar de forzar una clasificación errónea.
  * Mostrar el estado del sistema y el resultado de cada clasificación en un LCD 16x2 (modo 8 bits).
  * Posicionar un servomotor SG90 en 0°, 90° o 180° según el color detectado (rojo, verde o azul respectivamente).
  * Transmitir por UART (9600 baudios) un reporte con el valor del ADC y los tres conteos RGB en cada escaneo, además del resultado final.
  * Disparar el escaneo mediante un pulsador externo conectado a RB0 (interrupción externa INT con antirebote por software y hardware).

* **El sistema NO incluye (Fuera de alcance):**
  * Almacenamiento local de datos (Data Logging) en memoria EEPROM o tarjeta SD.
  * Conectividad inalámbrica (Wi-Fi/Bluetooth).
  * Calibración automática del sensor ante condiciones de luz ambiente variables (la calibración es manual, ajustando el potenciómetro de umbral).
  * Interfaz gráfica de usuario en PC; la recepción de datos se realiza con un terminal serie genérico (PuTTY, RealTerm, etc.).

### Posibles Etapas Siguientes (Líneas Futuras)

* Migrar el circuito de protoboard a un circuito impreso (PCB) con blindaje para el sensor de color, reduciendo la interferencia de luz ambiente.
* Implementar una calibración automática de los valores RGB de referencia (blanco/negro) almacenando los extremos en EEPROM interna del PIC.
* Reemplazar la comparación simple por una distancia de color (espacio RGB normalizado) para mejorar la precisión ante colores intermedios o mezclas.
* Diseñar una interfaz gráfica simple en Python (pyserial + tkinter) para visualizar en tiempo real las barras de intensidad RGB y el historial de clasificaciones.

---

## 2. Arquitectura del Sistema: Hardware y Software

### Hardware & Interconexión

* **Diagrama de Bloques:** *(insertar imagen en `docs/diagrama_bloques.png`)*
  `![Diagrama de Bloques](docs/diagrama_bloques.png)`
* **Esquemático del Circuito:** *(captura del esquemático completo en Proteus)*
  `![Esquemático Completo](hardware/esquematico.png)`
* **Descripción del Circuito y Consideraciones de Diseño:**
  El sensor TCS3200/TCS230 se alimenta a 5V y entrega en su pin `OUT` una señal cuadrada cuya frecuencia es proporcional a la intensidad de luz del color seleccionado por los pines `S2`/`S3` (filtro). Esa señal se conecta al pin `RC0` (T1CKI) del PIC, que se configura como entrada de reloj externo del Timer1 para contar pulsos durante una ventana fija de 20ms. El LCD se maneja en modo paralelo de 8 bits por el `PORTD` (líneas de datos) y dos líneas de control (`RS` y `E`) por `PORTE`. El servomotor SG90 se controla por software generando pulsos PWM manuales (período ≈20ms, ancho de pulso entre 0.5ms y 2.5ms) sobre `RC2`. El potenciómetro de 10kΩ se conecta como divisor de tensión entre 0V y 5V con el cursor a `RA0` (canal `AN0` del ADC). La comunicación serie UART (TX) se conecta a un adaptador USB-Serie para visualizar los datos en la PC, y también se usa para cargar el firmware mediante el bootloader AN1310.

### Arquitectura de Software (Firmware)

* **Diagrama de Flujo o Máquina de Estados:** *(insertar imagen en `docs/diagrama_software.png`)*
  `![Diagrama de Flujo](docs/diagrama_software.png)`

El firmware funciona como un lazo principal que permanece leyendo el ADC y mostrando "SISTEMA LISTO" en el LCD hasta que el usuario presiona el pulsador (RB0). Esa pulsación dispara una interrupción externa que solo activa una bandera de software (`FLAG_ESCANEAR`); todo el procesamiento pesado (medición del sensor, comparación y actuación) ocurre en el lazo principal, no dentro de la rutina de interrupción, para mantenerla corta y evitar antirebotes complejos dentro del ISR.

---

## 3. Especificaciones Eléctricas, Alimentación y Entorno

### Parámetros de Alimentación y Consumo

* **Tensión de operación del sistema:** 5V
* **Método de alimentación:** Fuente externa regulada a 5V (alimenta al PIC, LCD, sensor TCS3200/TCS230 y servomotor SG90).
* **Consumo estimado o medido:**
  * En modo activo (servo en movimiento + LCD + sensor activo): `XX mA` *(completar con medición real)*
  * En modo de espera (lazo principal sin escanear): `XX mA` *(completar con medición real)*

### Electrónica Digital II (PIC16F887)

* **Herramientas de Software:** MPLAB X IDE, ensamblador MPASM (proyecto en lenguaje assembler, no C/XC8).
* **Hardware de Programación/Depuración:**
  * **PICkit 3:** usado únicamente para la grabación inicial del bootloader serie en el PIC.
  * **AN1310 (Bootloader serie sobre UART):** usado para las cargas sucesivas del firmware sin necesidad de desconectar el circuito ni usar el PICkit nuevamente.
* **Configuración de Bits (Fuses Críticos):**
  * *Oscilador:* `_FOSC_XT` — cristal externo de 4MHz con dos capacitores de 22pF a GND (en el esquemático de Proteus figuran como "2.2uF" por un error de tipeo del simulador; el valor físico real es 22pF, el típico para este tipo de cristal).
  * *Watchdog Timer (WDT):* `_WDTE_OFF` (deshabilitado).
  * *Master Clear (MCLRE):* `_MCLRE_ON` (pin de reset externo habilitado).
  * *Power-up Timer:* `_PWRTE_ON` (habilitado).
  * *Brown-out Reset:* `_BOREN_ON`, con umbral `_BOR4V_BOR40V`.
* **Periféricos Internos Utilizados:**
  * **Timer1:** como contador de pulsos externos (modo T1CKI) para medir la frecuencia de salida del sensor TCS3200/TCS230.
  * **ADC:** canal `AN0` para leer el potenciómetro de 10kΩ usado como umbral de sensibilidad.
  * **EUSART:** transmisión asíncrona a 9600 baudios (`BRGH=1`, `SPBRG=25` con cristal de 4MHz) para el reporte de datos a la PC.
  * **Interrupción Externa (INT/RB0):** disparo del proceso de escaneo mediante pulsador, con antirebote combinado (deshabilitación temporal de la interrupción + espera activa por software).
* **Gestión de Interrupciones:** El sistema utiliza un único vector de interrupción (dirección `0x04`), compartido potencialmente por varias fuentes (en este proyecto, únicamente INT/RB0 está habilitada). Dentro de la ISR se hace *polling* sobre la bandera `INTCON,INTF` para confirmar que la interrupción fue generada por el pulsador antes de actuar; de encontrarse en alto, se levanta la bandera de software `FLAG_ESCANEAR`, se deshabilita la interrupción externa (`INTCON,INTE`) y se limpia la bandera de hardware, evitando que rebotes mecánicos del pulsador generen múltiples disparos mientras el lazo principal procesa el escaneo. La interrupción externa se vuelve a habilitar recién en `FIN_PROCESO`, una vez que el pulsador fue soltado y se aplicó un retardo adicional de 20ms.

---

## 4. Proceso de Integración y Desarrollo

* **Etapa 1 (Validación inicial):** Configuración del oscilador externo de 4MHz, prueba de inicialización y escritura en el LCD 16x2 en modo 8 bits.
* **Etapa 2 (Adquisición/Comunicación):** Implementación de la lectura del ADC sobre el potenciómetro y envío de los valores crudos por UART para verificar el rango y la resolución obtenida.
* **Etapa 3 (Integración del sensor de color):** Configuración de Timer1 como contador externo sobre `RC0`, control de los pines de filtro `S2`/`S3` del TCS3200/TCS230 y medición secuencial de los tres canales (rojo, verde, azul) dentro de una ventana de tiempo fija.
* **Etapa 4 (Sistema Completo):** Integración de la lógica de comparación entre los tres canales junto con el umbral dado por el potenciómetro, acople del servomotor como actuador final, y validación cruzada del resultado mostrado en el LCD contra el reporte enviado por UART.

---

## 5. Ensayos, Pruebas y Resultados

* **Pruebas Funcionales Realizadas:**
  * Verificación de la secuencia de inicialización del LCD y corrección de la rutina de encendido (se requería repetir el comando de configuración de función `0x38` para asegurar la sincronización del controlador HD44780).
  * Inyección de valores simulados (mock) en las variables `CONT_ROJO`, `CONT_VERDE` y `CONT_AZUL` desde el depurador de MPLAB X, para validar la lógica de comparación de colores de forma independiente del sensor físico, ante la imposibilidad de simular la señal real del TCS3200/TCS230 en el simulador.
  * Verificación con hardware real del reporte por UART (`ADC: ddd - R:ddd V:ddd A:ddd`) usando un terminal serie a 9600 baudios, contrastando los valores reportados contra el color físico expuesto al sensor.
* **Evidencia Fotográfica y Gráficos:**
  * *Capturas de terminal serie:* *(insertar captura del reporte UART en `docs/`)*
  * *Foto del Prototipo Real:* *(insertar foto del circuito armado en `docs/`)*

---

## 6. Estructura del Repositorio

```text
├── firmware/
│   └── src/                # Código fuente en ensamblador (MPASM, proyecto MPLAB X)
│       ├── main.asm        # Programa principal: configuración, lazo principal y lógica de clasificación
│       ├── delays.inc      # Rutinas de retardo por software
│       ├── lcd.inc         # Manejo del LCD 16x2 en modo 8 bits y textos mostrados
│       ├── uart.inc        # Transmisión por EUSART y conversión binario→decimal ASCII
│       ├── servo.inc       # Generación de pulsos PWM por software para el servomotor SG90
│       └── sensor.inc      # Medición de frecuencia del sensor TCS3200/TCS230 vía Timer1
├── hardware/                # Esquemático de Proteus (imagen/PDF) y lista de componentes (BOM)
├── docs/                    # Diagramas de flujo, capturas de UART, fotos del prototipo
└── README.md                 # Este archivo
```

> **Nota sobre la estructura del proyecto en MPLAB X:** todos los archivos (`main.asm` y los `.inc`) se mantienen en una misma carpeta (`firmware/src/`), replicando exactamente cómo está configurado el proyecto original en MPLAB X IDE (sin una carpeta de *include path* separada). Al clonar este repositorio, basta con abrir `firmware/src/` como carpeta de fuentes del proyecto en MPLAB X para que los `#include` se resuelvan correctamente sin configuración adicional.

---

## 7. Cómo compilar y cargar el firmware

1. Abrir MPLAB X IDE y crear un proyecto nuevo para el dispositivo **PIC16F887**, seleccionando el toolchain **mpasm** (ensamblador, no XC8).
2. Agregar como archivo fuente principal `firmware/src/main.asm`. Los archivos `.inc` no necesitan agregarse manualmente al proyecto: son incluidos automáticamente por las directivas `#include` dentro de `main.asm`, siempre y cuando estén en la misma carpeta.
3. Compilar (`Build`) para generar el archivo `.hex`.
4. **Primera carga:** usar un **PICkit 3** conectado al header ICSP del circuito para grabar el `.hex` (este paso solo es necesario una vez, para instalar el bootloader serie AN1310 si aún no está presente en el PIC).
5. **Cargas posteriores:** usar el software **AN1310** (bootloader serie) conectado por el puerto UART/USB-Serie del circuito para cargar nuevas versiones del `.hex` sin necesidad del PICkit.
