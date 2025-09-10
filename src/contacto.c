#include <stdio.h>
#include <string.h>
#include "contacto.h"
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
