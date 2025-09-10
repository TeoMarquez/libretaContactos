#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "utils.h"

void leerLinea(char *buffer, int size, const char *prompt) {
    while (1) {
        printf("%s", prompt);

        if (fgets(buffer, size, stdin) != NULL) {
            size_t len = strcspn(buffer, "\n"); // buscar \n
            if (len == 0) {
                printf("No puede estar vacio. Intente de nuevo.\n");
                continue;
            }

            // Si el usuario escribió más del tamaño del buffer
            if (buffer[len] != '\n') {
                printf("Excediste el limite de %d caracteres. Intente de nuevo.\n", size - 1);
                int c;
                while ((c = getchar()) != '\n' && c != EOF); // limpiar buffer
                continue; // vuelve a pedir
            }

            buffer[len] = '\0'; // reemplaza \n por null
            break; // input válido
        }
    }
}

void leerLineaEdit(char *campo, int campoSize, const char *prompt) {
    while (1) {
        printf("%s", prompt);
        char buffer[200];

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            size_t len = strcspn(buffer, "\n");

            // Si fgets no leyó el \n, significa que el usuario excedió el buffer temporal
            if (buffer[len] != '\n') {
                printf("Excediste el limite de %d caracteres. Intente de nuevo.\n", campoSize - 1);
                int c; while ((c = getchar()) != '\n' && c != EOF); // limpiar stdin
                continue;
            }

            // Aquí sí podemos verificar el tamaño máximo real del campo
            if (len >= campoSize) {
                printf("Excediste el limite de %d caracteres. Intente de nuevo.\n", campoSize - 1);
                continue;
            }

            buffer[len] = '\0';

            // Copiar solo si ingresó algo
            if (len > 0) {
                strncpy(campo, buffer, campoSize);
                campo[campoSize - 1] = '\0';
            }

            break;
        }
    }
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else  
    system("clear");
#endif
}
void esperarTecla() {
    printf("\nPresione ENTER para continuar...");
    getchar(); // espera un enter
}