# **Sintetizador monofónico sustractivo**

---


## 1. Descripción

Este proyecto consiste en el desarrollo de un instrumento virtual software capaz de generar sonido mediante síntesis sustractiva, inspirado en la arquitectura clásica del sintetizador analógico Minimoog Model-D.

La aplicación se implementará como un plugin de audio compatible con los formatos VST3 y AU, permitiendo su integración en estaciones de trabajo de audio digital (DAW) utilizadas
por músicos y productores.

El sistema permitirá recibir mensajes MIDI desde un teclado externo o desde un secuenciador digital, procesar la información de notas y o controladores, generar audio en tiempo real mediante osciladores digitales, filtros resonantes y generadores de envolvente.

El sintetizador incluirá además un sistema de gestión de presets que permitirá almacenar y recuperar configuraciones sonoras mediante una base de datos, posibilitando su sincronización en la nube para facilitar la portabilidad de los sonidos del usuario.

El proyecto se desarrollará utilizando JUCE, un framework de C++ estándar en la industria del audio, que permite unificar el desarrollo de plugins multiplataforma compilables para diferentes sistemas operativos.

---

## 2. Identificación
- Título del proyecto: Sintetizador monofónico sustractivo
- Participante: José Mateos Gutiérrez
- Ciclo formativo: Desarrollo de Aplicaciones Multiplataforma (DAM)
- Centro educativo: IES Valle del Jerte, Plasencia

---

## 3. Objetivos

Desarrollo de un instrumento virtual funcional de baja latencia, basado en síntesis
sustractiva, que permita generar y modificar sonido en tiempo real a partir de eventos MIDI.
### Objetivos específicos
1. Generación de sonido:
   - Implementar tres osciladores digitales (VCO).
   - Permitir seleccionar diferentes formas de onda:
      - diente de sierra
      - pulso
      - triángulo
      - senoidal

   - Permitir el ajuste de afinación (detune) y la mezcla de niveles entre osciladores para modificar el timbre final.​

2. Procesado de señal:
   - Implementar un filtro paso bajo resonante de 24 dB/octava.
   - Implementar generadores de envolvente ADSR para:
      - amplitud
      - frecuencia de corte del filtro​
3. Gestión de eventos MIDI:
   - Interpretar mensajes MIDI de tipo:
      - Note On / Note Off
      - Control Change
      - Pitch Bend.
   - Permitir controlar parámetros del sintetizador desde un teclado o secuenciador digital.​
4. Gestión de presets:
   - Diseñar un sistema de almacenamiento de presets.
   - Implementar operaciones de:
      - guardar
      - cargar
      - modificar
5. Integración con base de datos:
   - Utilizar MongoDB para almacenar configuraciones del sintetizador.
   - Diseñar un esquema de datos que represente los parámetros sonoros de manera eficiente.​
6. Despliegue en la nube:
   - Implementar una base de datos accesible desde Internet mediante Google Cloud, AWS, OracleWebServices u otros.
   - Permitir la sincronización de presets entre diferentes equipos.
   - Garantizar la persistencia y seguridad de los datos.​
7. Desarrollo multiplataforma:
   - Crear el plugin compatible con Windows, Linux y macOS mediante JUCE.

---

## 4. Justificación
El proyecto se clasifica dentro de los proyectos de innovación aplicada, al consistir en el desarrollo de un producto software tecnológico funcional.

Este proyecto concurre con el currículo de Desarrollo de Aplicaciones Multiplataforma ya que integra múltiples modulos del ciclo:

- Programación (C++).
- ACDAT (gestión de bases de datos)
- LMSGI ( git y control de versiones)
- Desarrollo de interfaces (Implementación y desarrollo de la interfaz gráfica).
- PSP (Implementación de procesamiento de audio en tiempo real mediante hilos y buffers de JUCE)​.

Por tanto, este proyecto permitirá aplicar conocimientos adquiridos durante el ciclo formativo
en un contexto práctico, desarrollando una aplicación real orientada al ámbito de la
producción musical digital.

---

## 5. Aspectos principales del proyecto:
El desarrollo del proyecto se estructurará en los siguientes módulos funcionales:

1. Motor de síntesis:
   Implementación del núcleo del sintetizador encargado de generar el audio digital en tiempo
   real. Este módulo incluirá:
   - osciladores digitales
   - mezclador de señal
   - generadores de envolvente
   - filtro resonante.​
2. Procesamiento de audio en tiempo real:
   Implementación del sistema de procesamiento de audio utilizando las herramientas del
   framework JUCE, gestionando buffers de audio y garantizando baja latencia.
3. Sistema de control MIDI:
   Implementación del módulo encargado de interpretar eventos MIDI y transformarlos en
   cambios de parámetros dentro del sintetizador.
4. Interfaz gráfica de usuario:
   - Desarrollo de una interfaz visual que permita al usuario modificar parámetros como:
     -volumen de osciladores
      - frecuencia de corte del filtro
      - resonancia
      - parámetros de envolvente.
      - Forma de onda por oscilador.​
5. Sistema de gestión de presets:
   - Diseño e implementación de un sistema que permita almacenar configuraciones sonoras en
     una base de datos.
6. Integración con base de datos:
   - Diseño del modelo de datos en MongoDB para almacenar presets y gestión de las
     operaciones CRUD necesarias.
7. Integración con servicios cloud:
   - Despliegue de la base de datos en un proveedor cloud para permitir el acceso remoto a los
     presets.
8. Control de versiones:
   - Uso de Git y GitHub para gestionar el desarrollo del proyecto, control de versiones y mantener un historial de cambios.

---

## 6. Medios a utilizar:
- Lenguaje de programación:
   - C++ (17/21)​
- Framework de desarrollo:
   - JUCE (para desarrollo de plugins de audio y procesamiento digital de señal)​
- Entornos de desarrollo:
   - VSCodium
   - CLion​
- Testing y pruebas:
   - Bitwig Studio (DAW)
   - CLion Debugger​
- Base de datos:
   - MongoDB
- Servicios cloud:
   - Google Cloud o AWS
- Control de versiones:
   - Git
   - GitHub

---

## 7. Diagrama:

![alt text](https://files.soniccdn.com/imagecache/fd1/6818fa7d6cd40f3f95bed368f9fae-4685833.jpg "Diagrama de flujo del Behringer Model-D")
