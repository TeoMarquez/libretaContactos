#ifndef CONTACTO_H
#define CONTACTO_H

typedef struct {
    char nombre[50];
    char dni[12];
    char telefono[16];
    char correo[50];
} Contacto;

// Funciones de contacto
void mostrarContacto(const Contacto *c);
void editarContacto(Contacto *c);
void organizarContactos(Contacto *lista, int total);

int cmpNombre(const void *a, const void *b, int orden);
int cmpDNI(const void *a, const void *b, int orden);
int cmpTelefono(const void *a, const void *b, int orden);
int cmpCorreo(const void *a, const void *b, int orden);

#endif
