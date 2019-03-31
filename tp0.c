/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"
#include<readline/readline.h>

int main(void)
{
	int conexion;
	char* ip;
	char* puerto;
	//las variables de logger y config estan declaradas como globales en el encabezado de este tp0
	iniciar_logger();

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	//Una vez hecho eso, tenemos que conectarnos a él! Las conexiones se representan mediante enteros por cosas que hablaremos más adelante.
	//Esta parte la vamos a hacer aca en el main por simpleza.
	loguear("Iniciando conexion");
	ip=getKey("IP");
	puerto=getKey("PUERTO");
	conexion=crear_conexion(ip,puerto);
	loguear("Conexion iniciada!");

	enviar_mensaje("pepito",conexion);

	//paquete(conexion);

	enviarMultiplesMensajes(conexion);

	terminar_programa(conexion);

}

void iniciar_logger(void)
{
	//creemos el log! Este se debe crear con el nombre "tp0.log", se debe mostrar por consola y debe estar en el nivel INFO
	g_logger = log_create("tp0.log","unProgramaQueLOguea" , 1, LOG_LEVEL_INFO);

	//logeemos el mensaje "Soy un log"
	log_info(g_logger, "Soy un log");
	log_destroy(g_logger);
}
void loguear(char *valor){
	g_logger = log_create("tp0.log","un logueo" , 1, LOG_LEVEL_INFO);
	log_info(g_logger, valor);
	log_destroy(g_logger);
}


char* concat(const char *s1, const char *s2){
	char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
	// in real code you would check for errors in malloc here

	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

char* obtenerDesdeConsola(int socket)
{
	char* leido;
	puts("Comienza lectura, ingrese mensajes");

	leido = readline(">");

	while(*leido!='\0'){
		puts("\n #### Enviando... \n");
		enviar_mensaje(leido,socket);
		free(leido);

		puts("\n #### Enviado!! \n");
		leido = readline(">");
	}
	free(leido);
	return "UN MENSAJE HARDCODEADO";
}
char*  getKey(char* clave){
	char* valor;

	//ahora, vamos a abrir el archivo de configuracion "tp0.config"
	g_config = config_create("/home/utnso/tp0/tp0.config");

	//tenemos que levantar en valor asociado a la clave "CLAVE" del archivo y asignarselo a la variable valor
	valor=config_get_string_value(g_config,clave);
	loguear("Obteniendo datos");
	loguear(valor);
	//config_destroy(g_config);
	return valor;

}
void leer_config(void){
	char* valor;

	//ahora, vamos a abrir el archivo de configuracion "tp0.config"
	g_config = config_create("/home/utnso/tp0/tp0.config");
	//tenemos que levantar en valor asociado a la clave "CLAVE" del archivo y asignarselo a la variable valor
	valor=config_get_string_value(g_config,"CLAVE");
	loguear(valor);

	config_destroy(g_config);

}

void leer_consola(void)
{
	char* leido;

	puts("Comienza lectura");

	leido = readline(">");
	while(strcmp(leido,"")){
		loguear(leido);
		puts(leido);
		free(leido);
		leido = readline(">");
	}
	free(leido);
}

void paquete(int conexion)
{
	//Ahora toca lo divertido!

	char* leido;
	t_paquete* paquete = crear_paquete();

	leido=readline("");
	while(*leido!='\0'){
		agregar_a_paquete(paquete,leido,strlen(leido)+1);
		free(leido);
		leido=readline("");
	}
	free(leido);
	//Una vez hayamos terminado de ingresar valores, toca enviarlo
	enviar_paquete(paquete, conexion);

	//Y no nos olvidemos de borrar el paquete con eliminar_paquete
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion)
{
	liberar_conexion(conexion);
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}
void enviarMultiplesMensajes(int socket){
	obtenerDesdeConsola(socket);

	//puts("comentado");
}
