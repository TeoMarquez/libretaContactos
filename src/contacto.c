#include <stdio.h>
#include <string.h>
#include "contacto.h"
#include <stdlib.h>   
#include "utils.h"

void mostrarContacto(const Contacto *c) {
    printf("Nombre: %s\n", c->nombre);
    printf("DNI: %s\n", c->dni);
    printf("Telefono: %s\n", c->telefono);
    printf("Correo: %s\n", c->correo);
}

void editarContacto(Contacto *c) {
    int opcion;
    char buffer[100];

    do {
        printf("\n--- Editar contacto: %s ---\n", c->nombre);
        printf("1) Nombre: %s\n", c->nombre);
        printf("2) DNI: %s\n", c->dni);
        printf("3) Telefono: %s\n", c->telefono);
        printf("4) Correo: %s\n", c->correo);
        printf("0) Salir\n");
        printf("Seleccione campo a editar: ");

        scanf("%d", &opcion);
        int ch; while ((ch = getchar()) != '\n' && ch != EOF); // limpiar buffer

        switch(opcion) {
            case 1:
                leerLineaEdit(c->nombre, sizeof(c->nombre), "Nuevo nombre: ");
                break;
            case 2:
                leerLineaEdit(c->dni, sizeof(c->dni), "Nuevo DNI: ");
                break;
            case 3:
                leerLineaEdit(c->telefono, sizeof(c->telefono), "Nuevo telefono: ");
                break;
            case 4:
                leerLineaEdit(c->correo, sizeof(c->correo), "Nuevo correo: ");
                break;
            case 0:
                printf("Saliendo de edicion...\n");
                break;
            default:
                printf("Opción invalida.\n");
        }
    } while(opcion != 0);

}

static int orden_global; // 1 = asc, -1 = desc
static int campo_global; // 1=nombre,2=dni,3=telefono,4=correo

int compararWrapper(const void *a, const void *b) {
    switch(campo_global) {
        case 1: return cmpNombre(a, b, orden_global);
        case 2: return cmpDNI(a, b, orden_global);
        case 3: return cmpTelefono(a, b, orden_global);
        case 4: return cmpCorreo(a, b, orden_global);
        default: return 0;
    }
}

int cmpNombre(const void *a, const void *b, int orden) {
    Contacto *c1 = (Contacto *)a;
    Contacto *c2 = (Contacto *)b;
    return orden * strcmp(c1->nombre, c2->nombre);
}

int cmpDNI(const void *a, const void *b, int orden) {
    Contacto *c1 = (Contacto *)a;
    Contacto *c2 = (Contacto *)b;
    return orden * strcmp(c1->dni, c2->dni);
}

int cmpTelefono(const void *a, const void *b, int orden) {
    Contacto *c1 = (Contacto *)a;
    Contacto *c2 = (Contacto *)b;
    return orden * strcmp(c1->telefono, c2->telefono);
}

int cmpCorreo(const void *a, const void *b, int orden) {
    Contacto *c1 = (Contacto *)a;
    Contacto *c2 = (Contacto *)b;
    return orden * strcmp(c1->correo, c2->correo);
}

void organizarContactos(Contacto *lista, int total) {
    char opcion[10];

    printf("\nOrdenar por:\n1) Nombre\n2) DNI\n3) Telefono\n4) Correo\nSeleccione opcion: ");
    leerLinea(opcion, sizeof(opcion), "> ");
    campo_global = atoi(opcion);

    printf("Orden:\n1) Ascendente\n2) Descendente\nSeleccione opcion: ");
    leerLinea(opcion, sizeof(opcion), "> ");
    int ord = atoi(opcion);
    if (ord == 1) orden_global = 1;
    else if (ord == 2) orden_global = -1;
    else {
        printf("Opcion invalida.\n");
        return;
    }

    qsort(lista, total, sizeof(Contacto), compararWrapper);

    printf("Contactos organizados correctamente.\n");
    esperarTecla();
}
