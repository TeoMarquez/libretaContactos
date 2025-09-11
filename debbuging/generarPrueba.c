#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contacto.h"
#include "crud.h" 

int main() {
    int total = 35;
    Contacto *contactos = malloc(sizeof(Contacto) * total);
    if (!contactos) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    for (int i = 0; i < total; i++) {
        snprintf(contactos[i].nombre, sizeof(contactos[i].nombre), "Contacto%d", i+1);
        snprintf(contactos[i].dni, sizeof(contactos[i].dni), "100000%02d", i+1);
        snprintf(contactos[i].telefono, sizeof(contactos[i].telefono), "4123%04d", i+1);
        snprintf(contactos[i].correo, sizeof(contactos[i].correo), "contacto%d@mail.com", i+1);
    }

    guardarContactos(contactos, total);

    free(contactos);
    printf("Archivo de prueba creado con %d contactos.\n", total);
    return 0;
}
