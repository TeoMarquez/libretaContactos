#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crud.h"
#include "utils.h"  

#define ARCHIVO "data/contactos.bin"

int cargarContactos(Contacto **lista) {
    FILE *f = fopen(ARCHIVO, "rb");
    if (!f) return 0;

    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    rewind(f);

    int total = tam / sizeof(Contacto);
    *lista = malloc(total * sizeof(Contacto));
    if (!*lista) {
        fclose(f);
        return 0;
    }

    fread(*lista, sizeof(Contacto), total, f);
    fclose(f);
    return total;
}

void guardarContactos(Contacto *lista, int total) {
    FILE *f = fopen(ARCHIVO, "wb");
    if (!f) return;

    fwrite(lista, sizeof(Contacto), total, f);
    fclose(f);
}

void borrarContacto(Contacto *lista, int *total, int idx) {
    if (idx < 0 || idx >= *total) return;

    for (int i = idx; i < *total - 1; i++) {
        lista[i] = lista[i + 1];
    }
    (*total)--;

    printf("Contacto eliminado.\n");
}

void buscarContacto(Contacto *lista, int total, const char *dato) {
    printf("Resultados de busqueda para \"%s\":\n", dato);
    for (int i = 0; i < total; i++) {
        if (strstr(lista[i].nombre, dato) ||
            strstr(lista[i].dni, dato) ||
            strstr(lista[i].telefono, dato) ||
            strstr(lista[i].correo, dato)) {
            printf("%d) %s | %s | %s | %s\n",
                   i + 1,
                   lista[i].nombre,
                   lista[i].dni,
                   lista[i].telefono,
                   lista[i].correo);
        }
    }
}

void agregarContacto(Contacto **lista, int *total) {
    Contacto nuevo;

    leerLinea(nuevo.nombre, sizeof(nuevo.nombre), "Ingrese nombre: ");
    leerLinea(nuevo.dni, sizeof(nuevo.dni), "Ingrese DNI: ");
    leerLinea(nuevo.telefono, sizeof(nuevo.telefono), "Ingrese telefono: ");
    leerLinea(nuevo.correo, sizeof(nuevo.correo), "Ingrese correo: ");

    *lista = realloc(*lista, (*total + 1) * sizeof(Contacto));
    if (*lista == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    (*lista)[*total] = nuevo;
    (*total)++;

    printf("Contacto agregado correctamente.\n");
}
