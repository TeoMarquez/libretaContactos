#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contacto.h"
#include "crud.h"
#include "utils.h"

#define BLOQUE 10   // cantidad de contactos por página

void mostrarBloque(Contacto *lista, int total, int pagina) {
    int inicio = pagina * BLOQUE;
    int fin = inicio + BLOQUE;
    if (fin > total) fin = total;

    printf("\n--- Pagina %d ---\n", pagina + 1);
    printf("%-3s %-20s %-12s %-15s %-25s\n",
           "Nro", "Nombre", "DNI", "Telefono", "Correo");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = inicio; i < fin; i++) {
        printf("%-3d %-20s %-12s %-15s %-25s\n", 
               i + 1,
               lista[i].nombre,
               lista[i].dni,
               lista[i].telefono,
               lista[i].correo);
    }
    printf("-------------------------------------------------------------------------------\n");
}


int main() {
    Contacto *contactos = NULL;
    int total = 0;      // cantidad de contactos cargados
    int pagina = 0;     // índice de la página actual

    // Cargar contactos del binario (futuro crud)
    total = cargarContactos(&contactos);

    char comando[100];
    do {
        clearScreen();
        mostrarBloque(contactos, total, pagina);

        printf("Opciones:\n");
        printf(" a = anterior | s = siguiente\n");
        printf(" N = nuevo contacto\n");
        printf(" E -n = editar contacto n\n");
        printf(" B -n = borrar contacto n\n");
        printf(" Ver -n = ver detalle contacto n\n");
        printf(" Busq -dato = buscar por dato\n");
        printf(" O = Organizar contactos\n");
        printf(" q = salir\n");

        leerLinea(comando, sizeof(comando), "> ");

        if (strcmp(comando, "a") == 0) {
            if (pagina > 0) pagina--;
        } else if (strcmp(comando, "s") == 0) {
            if ((pagina + 1) * BLOQUE < total) pagina++;
        } else if (strncmp(comando, "E -", 3) == 0) {
            int idx = atoi(comando + 3) - 1;
            if (idx >= 0 && idx < total) {
                editarContacto(&contactos[idx]);
            }
        } else if (strcmp(comando, "N") == 0 || strcmp(comando, "n") == 0) {
            agregarContacto(&contactos, &total);
            esperarTecla();
        } else if (strncmp(comando, "B -", 3) == 0) {
                int idx = atoi(comando + 3) - 1;
                if (idx >= 0 && idx < total) {
                    printf("Estas seguro que deseas borrar el contacto #%d: %s? (s/n): ", 
                        idx + 1, contactos[idx].nombre);

                    char resp = getchar();
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF); // limpiar buffer

                    if (tolower(resp) == 's') {
                        borrarContacto(contactos, &total, idx);
                        esperarTecla();    
                    }
                }
        } else if (strncmp(comando, "Ver -", 5) == 0) {
            int idx = atoi(comando + 5) - 1;
            if (idx >= 0 && idx < total) {
                mostrarContacto(&contactos[idx]);
                esperarTecla();
            }
        } else if (strncmp(comando, "Busq -", 6) == 0) {
            char *dato = comando + 6;
            buscarContacto(contactos, total, dato);
            esperarTecla();
        } else if (strcmp(comando, "q") == 0) {
            printf("Saliendo...\n");
        } else if (strcmp(comando, "O") == 0 || strcmp(comando, "o") == 0) {
            organizarContactos(contactos, total);
        } else {
            printf("Comando no reconocido.\n");
        }

    } while (strcmp(comando, "q") != 0);

    // Guardar cambios en binario antes de salir
    guardarContactos(contactos, total);

    free(contactos);
    return 0;
}
