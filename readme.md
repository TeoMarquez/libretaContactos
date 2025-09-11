# 🗂️ Libreta de Contactos en C

## Descripción
Aplicación de gestión de contactos desarrollada en **C**, con funcionalidades avanzadas para manejar información de personas:

- Alta, baja y edición de contactos.
- Búsqueda por cualquier campo: nombre, DNI, teléfono o correo.
- Ordenamiento de contactos por cualquier campo, ascendente o descendente.
- Paginación para mostrar bloques de contactos.
- Guardado y carga desde archivos binarios.
- Generador de datos de prueba para testing de edge cases (nombres con números, correos, teléfonos largos, etc.).

El sistema está pensado para ser robusto y seguro, evitando editar contactos fuera del contexto de búsqueda, y permite manejar hasta cientos de contactos sin problemas.

---

## Instalación / Compilación

Se incluyen scripts `.bat` que automatizan la compilación en Windows:

- **Compilar la aplicación principal:**
compile.bat

- **Compilar el generador de datos de prueba:**
compilarGenerador.bat

No se requiere instalar dependencias externas, solo un compilador de C como **MinGW**.

---

## Uso de la Aplicación

Al ejecutar `libretaContactos.exe`:

- Navegación:
  - `a` → Página anterior
  - `s` → Página siguiente
- Gestión de contactos:
  - `N` → Nuevo contacto
  - `E -n` → Editar contacto n
  - `B -n` → Borrar contacto n
  - `Ver -n` → Ver detalle contacto n
- Búsqueda:
  - `Busq -dato` → Buscar contactos por cualquier campo
- Organización:
  - `O` → Organizar contactos por nombre, DNI, teléfono o correo
- Salir:
  - `q` → Salir de la aplicación

---

## Estructura de Carpetas

- `src/` – Archivos fuente `.c` del proyecto.  
- `headers/` – Archivos `.h` con declaraciones y diccionarios de palabras.  
- `debbuging/` - Carpeta para pruebas y archivos temporales
- `data/` - Carpeta donde se almacenan los archivos binarios de contactos

## Notas Importantes

- El sistema de búsqueda realiza una **búsqueda por subcadena**: encuentra contactos cuyo nombre, correo, teléfono o DNI contenga la cadena ingresada.
- Ordenamiento:
  - Se puede ordenar ascendente o descendente por cualquier campo.
  - Implementa comparadores personalizados que respetan el orden alfabético y numérico cuando aplica.
- Seguridad:
  - La edición después de una búsqueda solo afecta los contactos mostrados en los resultados.
- Generador de datos:
  - `generarPrueba.exe` crea contactos de prueba con nombres aleatorios, algunos con números al final, para simular edge cases.
  - Ideal para probar el sistema de ordenamiento y búsqueda.

---
