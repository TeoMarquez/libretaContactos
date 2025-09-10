#ifndef CRUD_H
#define CRUD_H

#include "contacto.h"

// CRUD sobre el array y archivo binario
int cargarContactos(Contacto **lista);              // cargar desde binario
void guardarContactos(Contacto *lista, int total);  // guardar en binario
void borrarContacto(Contacto *lista, int *total, int idx);
void buscarContacto(Contacto *lista, int total, const char *dato);
void agregarContacto(Contacto **lista, int *total);

#endif
