#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "contacto.h"
#include "crud.h" // Para usar guardarContactos()

int main() {
    srand(time(NULL)); // inicializar generador aleatorio

    int total = 35;
    Contacto *contactos = malloc(sizeof(Contacto) * total);
    if (!contactos) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    const char *nombresBase[] = {"Mateo", "Lucia", "Pedro", "Ana", "Carlos"};
    int baseCount = sizeof(nombresBase) / sizeof(nombresBase[0]);

    for (int i = 0; i < total; i++) {
        // Elegir nombre base aleatorio
        const char *base = nombresBase[rand() % baseCount];

        // A veces agregamos un número al final (50% de probabilidad)
        if (rand() % 2 == 0) {
            int num = rand() % 20 + 1; // número del 1 al 20
            snprintf(contactos[i].nombre, sizeof(contactos[i].nombre), "%s%d", base, num);
        } else {
            snprintf(contactos[i].nombre, sizeof(contactos[i].nombre), "%s", base);
        }

        snprintf(contactos[i].dni, sizeof(contactos[i].dni), "100000%02d", i+1);
        snprintf(contactos[i].telefono, sizeof(contactos[i].telefono), "4123%04d", i+1);
        snprintf(contactos[i].correo, sizeof(contactos[i].correo), "%s%d@mail.com", base, i+1);
    }

    guardarContactos(contactos, total);

    free(contactos);
    printf("Archivo de prueba creado con %d contactos.\n", total);
    return 0;
}
