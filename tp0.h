/*
 * Cliente.h
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#ifndef TP0_H_
#define TP0_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include<stdio.h>
#include "utils.h"

// Por lo general, a menos que tengan que tener recursos compartidos, no es buena práctica usar variables globales. Nosotros lo estamos haciendo por la simplicidad del TP0 :)
t_log* g_logger;
t_config* g_config;

void iniciar_logger(void);
void leer_config(void);
void leer_consola(void);
void paquete(int);
void terminar_programa(int);

char*  getKey(char* clave);
void loguear(char *valor);
char* concat(const char *s1, const char *s2);
char* obtenerDesdeConsola(int);
void enviarMultiplesMensajes();

#endif /* TP0_H_ */
