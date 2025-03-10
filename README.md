# METX - Proyecto de Apiario de Medios de Transmisión

Este repositorio contiene el código del **Proyecto de Apiario de Medios de Transmisión**, diseñado para la adquisición, transmisión y visualización de datos en un apiario inteligente.

## Descripción

El sistema se compone de tres partes principales:

1. **Transmisión (TX):** Código en Arduino para la adquisición y envío de datos desde los sensores del apiario.
2. **Recepción (RX):** Código en Arduino para la recepción de datos y su posterior almacenamiento.
3. **Interfaz de Usuario (GUI):** Aplicación web que permite visualizar los datos mediante gráficos interactivos.

## Tecnologías Utilizadas

- **TX y RX:** Arduino (C++)
- **Interfaz de Usuario (GUI):**
  - **Backend:** PHP para manejar las solicitudes a la base de datos.
  - **Base de datos:** MariaDB.
  - **Frontend:** HTML, CSS y JavaScript para actualizar los gráficos en tiempo real.
