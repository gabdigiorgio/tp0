#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	log_info(logger, "Hola! Soy un log");

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	valor = config_get_string_value(config, "CLAVE");


	// Loggeamos el valor de config

	log_info(logger, "Mi IP es: %s", ip);
	log_info(logger, "Mi PUERTO es: %s", puerto);
	log_info(logger, "Mi CLAVE es: %s", valor);

	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	nuevo_logger = log_create("./tp0.log", "client", true, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	nuevo_config = config_create("/home/utnso/Documents/tp0/client/cliente.config");

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	while (strcmp((leido = readline("> ")), "") != 0) {
			log_info(logger, leido);
	        free(leido);
	    }

	    free(leido); // Libera las lineas no vacias

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete

	while(1) {
		leido = readline("> ");

		if(strcmp(leido,"")==0){
			break;
		}

		agregar_a_paquete(paquete, leido, strlen(leido)+1);
		free(leido);
	}

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
	enviar_paquete(paquete, conexion);
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
