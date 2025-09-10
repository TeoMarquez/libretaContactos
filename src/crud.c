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
    int indices[100]; 
    int encontrados = 0;

    printf("\nResultados de busqueda para \"%s\":\n", dato);

    for (int i = 0; i < total; i++) {
        if (strstr(lista[i].nombre, dato) ||
            strstr(lista[i].dni, dato) ||
            strstr(lista[i].telefono, dato) ||
            strstr(lista[i].correo, dato)) {

            printf("%d) %s | %s | %s | %s\n",
                   encontrados + 1,
                   lista[i].nombre,
                   lista[i].dni,
                   lista[i].telefono,
                   lista[i].correo);

            indices[encontrados] = i; 
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("No se encontraron contactos.\n");
        return;
    }

    char opcion[10];
    while (1) {
        printf("\nSeleccione un contacto por numero (0 para volver): ");
        leerLinea(opcion, sizeof(opcion), "");

        int sel = atoi(opcion);
        if (sel == 0) return; 
        if (sel < 1 || sel > encontrados) {
            printf("Opcion invalida.\n");
            continue;
        }

        int idx = indices[sel - 1]; // índice real del contacto

        printf("Seleccione accion: 1=Ver, 2=Editar, 0=Volver: ");
        leerLinea(opcion, sizeof(opcion), "");
        int act = atoi(opcion);

        switch (act) {
            case 0:
                break; 
            case 1:
                mostrarContacto(&lista[idx]);
                esperarTecla();
                break;
            case 2:
                editarContacto(&lista[idx]);
                break;
            default:
                printf("Opcion invalida.\n");
        }

        printf("\nResultados de busqueda para \"%s\":\n", dato);
        for (int j = 0; j < encontrados; j++) {
            int real = indices[j];
            printf("%d) %s | %s | %s | %s\n",
                   j + 1,
                   lista[real].nombre,
                   lista[real].dni,
                   lista[real].telefono,
                   lista[real].correo);
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
