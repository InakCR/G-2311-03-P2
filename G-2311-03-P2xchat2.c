#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <redes2/ircxchat.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM_BYTES 8192
#define LOG_NUM 2000
#define T_AL 20
#define MAX_DS 100
#define MAX_LONG_STRC 50

void *client();
void comandoARealizar(char *strin, int sock);

char id[LOG_NUM] = "";
char *nickC, *userC, *realnameC, *passwordC, serverC;
int sock, portC;
boolean sslC;
int numero = 14606209;
/**
 * @defgroup IRCInterface Interface
 *
 */

/**
 * @defgroup IRCInterfaceCallbacks Callbaks
 * @ingroup IRCInterface
 *
 */

/**
 * @addtogroup IRCInterfaceCallbacks
 * Funciones que van a ser llamadas desde el interface y que deben ser
 * implementadas por el usuario.
 * Todas estas funciones pertenecen al hilo del interfaz.
 *
 * El programador puede, por supuesto, separar todas estas funciones en
 * múltiples ficheros a
 * efectos de desarrollo y modularización.
 *
 * <hr>
 */
/**
 * @brief Manejador de la alarma para el Ping.
 *
 * @description Crea un mensaje de Ping para lanzarlo al servidor
*/

void alarma_ping() {
  char *command, idPing[LOG_NUM] = "";

  command = (char *)malloc(NUM_BYTES * sizeof(char));

  sprintf(idPing, "LAG%d", numero);
  numero++;

  IRCMsg_Ping(&command, NULL, idPing, NULL);
  send(sock, command, strlen(command), 0);

  // Escribimos en el registro plano
  IRCInterface_PlaneRegisterOutMessage(command);
  free(command);
  alarm(20);
}
/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_ActivateChannelKey IRCInterface_ActivateChannelKey
 *
 * @brief Llamada por el botón de activación de la clave del canal.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_ActivateChannelKey (char *channel, char * key)
 * @endcode
 *
 * @description
 * Llamada por el botón de activación de la clave del canal. El segundo
 *parámetro es
 * la clave del canal que se desea poner. Si es NULL deberá impedirse la
 *activación
 * con la función implementada a tal efecto. En cualquier caso sólo se puede
 *realizar si el servidor acepta la orden.
 * Las strings recibidas no deben ser manipuladas por el programador, sólo
 *leídas.
 *
 * @param[in] channel canal sobre el que se va a activar la clave.
 * @param[in] key clave para el canal indicado.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO no se me conceta a metis y no se cual es la funcion a usar*/
void IRCInterface_ActivateChannelKey(char *channel, char *key) {

  long res;

  printf("Activando la clave del canal %s a %s...\n", channel, key);

  //res = IRCTAD_Mode(channel, nickC, "+k");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");

}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_ActivateExternalMessages
 *IRCInterface_ActivateExternalMessages
 *
 * @brief Llamada por el botón de activación de la recepción de mensajes
 *externos.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_ActivateExternalMessages (char *channel)
 * @endcode
 *
 * @description
 * Llamada por el botón de activación de la recepción de mensajes externos.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] channel canal sobre el que se activará la recepción de mensajes
 *externos.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO no se me conceta a metis y no se cual es la funcion a usar*/
void IRCInterface_ActivateExternalMessages(char *channel) {

  long res;

  printf("Activando los mensajes externos del canal %s...\n", channel);

  //res = IRCTAD_Mode(channel, nickC, "+n");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");

}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_ActivateInvite IRCInterface_ActivateInvite
 *
 * @brief Llamada por el botón de activación de canal de sólo invitación.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_ActivateInvite (char *channel)
 * @endcode
 *
 * @description
 * Llamada por el botón de activación de canal de sólo invitación.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] channel canal sobre el que se activará la invitación.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO no se me conceta a metis y no se cual es la funcion a usar*/
void IRCInterface_ActivateInvite(char *channel) {

  long res;

  printf("Activando la función invitar del canal %s...\n", channel);

  //res = IRCTAD_Mode(channel, nickC, "+i");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");

}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_ActivateModerated IRCInterface_ActivateModerated
 *
 * @brief Llamada por el botón de activación de la moderación del canal.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_ActivateModerated (char *channel)
 * @endcode
 *
 * @description
 * Llamada por el botón de activación de la moderación del canal.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] channel canal sobre el que se activará la moderación.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO no se me conceta a metis y no se cual es la funcion a usar*/
void IRCInterface_ActivateModerated(char *channel) {

  long res;

  printf("Activando modo moderado del canal %s...\n", channel);

  //res = IRCTAD_Mode(channel, nickC, "+m");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");

}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_ActivateNicksLimit IRCInterface_ActivateNicksLimit
 *
 * @brief Llamada por el botón de activación del límite de usuarios en el canal.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_ActivateNicksLimit (char *channel, int * limit)
 * @endcode
 *
 * @description
 * Llamada por el botón de activación del límite de usuarios en el canal. El
 *segundo es el
 * límite de usuarios que se desea poner. Si el valor es 0 se sobrentiende que
 *se desea eliminar
 * este límite.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] channel canal sobre el que se activará el límite de usuarios.
 * @param[in] limit límite de usuarios en el canal indicado.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO no se me conceta a metis y no se cual es la funcion a usar*/
void IRCInterface_ActivateNicksLimit(char *channel, int limit) {

  long res;

  printf("Activando limite de usuarios en el canal %s a %d...\n", channel,
          limit);

  //res = IRCTAD_Mode(channel, nickC, "+l");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");

}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_ActivatePrivate IRCInterface_ActivatePrivate
 *
 * @brief Llamada por el botón de activación del modo privado.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_ActivatePrivate (char *channel)
 * @endcode
 *
 * @description
 * Llamada por el botón de activación del modo privado.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] channel canal sobre el que se va a activar la privacidad.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/

void IRCInterface_ActivatePrivate(char *channel) {

  long res;

  printf("Activando el modo privado en el canal %s...\n", channel);

  res = IRCTAD_Mode(channel, nickC, "+p");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");

}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_ActivateProtectTopic IRCInterface_ActivateProtectTopic
 *
 * @brief Llamada por el botón de activación de la protección de tópico.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_ActivateProtectTopic (char *channel)
 * @endcode
 *
 * @description
 * Llamada por el botón de activación de la protección de tópico.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] channel canal sobre el que se va a activar la protección de
 *tópico.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/

void IRCInterface_ActivateProtectTopic(char *channel) {

  long res;

  printf("Activando la protección del topico en el canal %s...\n", channel);

  res = IRCTAD_Mode(channel, nickC, "+t");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");


}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_ActivateSecret IRCInterface_ActivateSecret
 *
 * @brief Llamada por el botón de activación de canal secreto.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_ActivateSecret (char *channel)
 * @endcode
 *
 * @description
 * Llamada por el botón de activación de canal secreto.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] channel canal sobre el que se va a activar el estado de secreto.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO no se me conceta a metis y no se cual es la funcion a usar*/
void IRCInterface_ActivateSecret(char *channel) {

  long res;

  printf("Activando el modo secreto del canal %s...\n", channel);

  //res = IRCTAD_Mode(channel, nickC, "+s");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");

}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_BanNick IRCInterface_BanNick
 *
 * @brief Llamada por el botón "Banear".
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_BanNick (char *channel, char *nick)
 * @endcode
 *
 * @description
 * Llamada por el botón "Banear". Previamente debe seleccionarse un nick del
 * canal para darle voz a dicho usuario.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * Las strings recibidas no deben ser manipuladas por el programador, sólo
 *leídas.
 *
 * @param[in] channel canal sobre el que se va a realizar el baneo. En principio
 *es un valor innecesario.
 * @param[in] nick nick del usuario que va a ser baneado
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO no se me conceta a metis y no se cual es la funcion a usar*/
void IRCInterface_BanNick(char *channel, char *nick) {

  long res;

  printf("Baneando a %s del canal %s...\n", nick, channel);

  //res = IRCTAD_Mode(channel, nickC, "+n");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");

}

int recvCommand(int sock, char* command) {
	return recv(sock, command, 8192, 0);
}

void *client() {

  char sendBuff[100], client_message[LOG_NUM];
  char *command, *pipeCommand, *pipe;

  pipe = (char *)malloc(NUM_BYTES * sizeof(char));
  command = (char *)malloc(NUM_BYTES * sizeof(char));

  if (pipe == NULL || command == NULL)
    return NULL;

  alarm(20);
  printf("Creando Alarma...\n");

  if (signal(SIGALRM, alarma_ping) == SIG_ERR){
    printf("Error - No se creó la Alarma.\n");
    return NULL;
  }
  else
    printf("Se creó la Alarma.\n");


  /*Bucle de espera*/
  while (1) {

    bzero(command, NUM_BYTES);

    if (recvCommand(sock, command) == -1)
      return NULL;

    pipe = IRC_UnPipelineCommands(command, &pipeCommand);

    while (pipe != NULL) {

      //printf("pipeCommand -> %s\n", pipeCommand);
      comandoARealizar(pipeCommand, sock);

      pipe = IRC_UnPipelineCommands(NULL, &pipeCommand);
    }

    bzero(command, NUM_BYTES);
  }
}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_Connect IRCInterface_Connect
 *
 * @brief Llamada por los distintos botones de conexión.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	long IRCInterface_Connect (char *nick, char * user, char * realname,
 *char * password, char * server, int port, boolean ssl)
 * @endcode
 *
 * @description
 * Función a implementar por el programador.
 * Llamada por los distintos botones de conexión. Si implementará la
 *comunicación completa, incluido
 * el registro del usuario en el servidor.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * Las strings recibidas no deben ser manipuladas por el programador, sólo
 *leída.
 *
 *
 * @param[in] nick nick con el que se va a realizar la conexíón.
 * @param[in] user usuario con el que se va a realizar la conexión.
 * @param[in] realname nombre real con el que se va a realizar la conexión.
 * @param[in] password password del usuario si es necesaria, puede valer NULL.
 * @param[in] server nombre o ip del servidor con el que se va a realizar la
 *conexión.
 * @param[in] port puerto del servidor con el que se va a realizar la conexión.
 * @param[in] ssl puede ser TRUE si la conexión tiene que ser segura y FALSE si
 *no es así.
 *
 * @retval IRC_OK si todo ha sido correcto (debe devolverlo).
 * @retval IRCERR_NOSSL si el valor de SSL es TRUE y no se puede activar la
 *conexión SSL pero sí una
 * conexión no protegida (debe devolverlo).
 * @retval IRCERR_NOCONNECT en caso de que no se pueda realizar la comunicación
 *(debe devolverlo).
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/

long IRCInterface_Connect(char *nick, char *user, char *realname,
                          char *password, char *server, int port, boolean ssl) {

  struct hostent *he;
  struct sockaddr_in serverdir;
  struct sockaddr_in serveraux;
  pthread_t pthread;
  pthread_attr_t attr;
  char *ip, *command, buffer[MAX_DS], client_msg[LOG_NUM];
  int *nsocket, numbytes, err;

  nickC = (char *) malloc(MAX_LONG_STRC*sizeof(char));
  memcpy(nickC, nick, strlen(nick) + 1);
  userC = (char *) malloc(MAX_LONG_STRC*sizeof(char));
  memcpy(userC, user, strlen(user) + 1);
  realnameC = (char *) malloc(MAX_LONG_STRC*sizeof(char));
  memcpy(realnameC, realname, strlen(realname) + 1);
  passwordC = (char *) malloc(MAX_LONG_STRC*sizeof(char));
  memcpy(passwordC, password, strlen(password) + 1);

  portC = port;
  sslC = ssl;
  // mutex?
  if ((he = gethostbyname(server)) == NULL)
    return IRCERR_NOCONNECT;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return IRCERR_NOCONNECT;

  serverdir.sin_family = AF_INET;
  serverdir.sin_port = htons(port);
  serverdir.sin_addr = *((struct in_addr *)he->h_addr);

  bzero(&(serverdir.sin_zero), 8);
  pthread_attr_init(&attr);
  if (pthread_create(&pthread, NULL, client, NULL) < 0)
    return IRCERR_NOCONNECT;

  if (connect(sock, (struct sockaddr *)&serverdir, sizeof(struct sockaddr)) ==
      -1)
    return IRCERR_NOCONNECT;

  ip = inet_ntoa(serverdir.sin_addr);

  printf("Conectado con el servidor.\n");

  printf("<< CAP LS\n");
  send(sock, "CAP LS\r\n", strlen("CAP LS\r\n"), 0);

  printf("<< Msg_Nick\n");
  if (IRCMsg_Nick(&command, NULL, nick, NULL) != IRC_OK)
    return IRCERR_NOCONNECT;
  send(sock, command, strlen(command), 0);

  printf("<< Msg_User\n");
  if (IRCMsg_User(&command, NULL, user, "w", realname) != IRC_OK)
    return IRCERR_NOCONNECT;
  send(sock, command, strlen(command), 0);

  printf("<< CAP END\n");
  send(sock, "CAP END\r\n", strlen("CAP END\r\n"), 0);
  return IRC_OK;
}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_DeactivateChannelKey IRCInterface_DeactivateChannelKey
 *
 * @brief Llamada por el botón de desactivación de la clave del canal.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_DeactivateChannelKey (char *channel)
 * @endcode
 *
 * @description
 * Llamada por el botón de desactivación de la clave del canal.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] channel canal sobre el que se va a desactivar la clave.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO no se me conceta a metis y no se cual es la funcion a usar*/
void IRCInterface_DeactivateChannelKey(char *channel) {

  long res;

  printf("Desactivando la clave del canal %s...\n", channel);

  //res = IRCTAD_Mode(channel, nickC, "-k");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");

}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_DeactivateExternalMessages
 *IRCInterface_DeactivateExternalMessages
 *
 * @brief Llamada por el botón de desactivación de la recepción de mensajes
 *externos.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_DeactivateExternalMessages (char *channel)
 * @endcode
 *
 * @description
 * Llamada por el botón de desactivación de la recepción de mensajes externos.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] channel canal sobre el que se va a deactivar la recepción de
 *mensajes externos.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO no se me conceta a metis y no se cual es la funcion a usar*/
void IRCInterface_DeactivateExternalMessages(char *channel) {

  long res;

  printf("Desactivando los mensajes externos del canal %s...\n", channel);

  //res = IRCTAD_Mode(channel, nickC, "-n");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");

}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_DeactivateInvite IRCInterface_DeactivateInvite
 *
 * @brief Llamada por el botón de desactivación de canal de sólo invitación.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_DeactivateInvite (char *channel)
 * @endcode
 *
 * @description
 * Llamada por el botón de desactivación de canal de sólo invitación.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] channel canal sobre el que se va a desactivar la invitación.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO no se me conceta a metis y no se cual es la funcion a usar*/
void IRCInterface_DeactivateInvite(char *channel) {

  long res;

  printf("Desactivando la función invitar del canal %s...\n", channel);

  //res = IRCTAD_Mode(channel, nickC, "-i");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");

}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_DeactivateModerated IRCInterface_DeactivateModerated
 *
 * @brief Llamada por el botón de desactivación  de la moderación del canal.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_DeactivateModerated (char *channel)
 * @endcode
 *
 * @description
 * Llamada por el botón de desactivación  de la moderación del canal.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] channel canal sobre el que se va a desactivar la moderación.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO no se me conceta a metis y no se cual es la funcion a usar*/
void IRCInterface_DeactivateModerated(char *channel) {

  long res;

  printf("Desactivando modo moderado del canal %s...\n", channel);

  //res = IRCTAD_Mode(channel, nickC, "-m");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");

}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_DeactivateNicksLimit IRCInterface_DeactivateNicksLimit
 *
 * @brief Llamada por el botón de desactivación de la protección de tópico.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_DeactivateNicksLimit (char *channel)
 * @endcode
 *
 * @description
 * Llamada por el botón de desactivación  del límite de usuarios en el canal.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] channel canal sobre el que se va a desactivar el límite de
 *usuarios.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO no se me conceta a metis y no se cual es la funcion a usar*/
void IRCInterface_DeactivateNicksLimit(char *channel) {

  long res;

  printf("Desactivando limite de usuarios en el canal %s...\n", channel);

  //res = IRCTAD_Mode(channel, nickC, "-l");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");

}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_DeactivatePrivate IRCInterface_DeactivatePrivate
 *
 * @brief Llamada por el botón de desactivación del modo privado.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_DeactivatePrivate (char *channel)
 * @endcode
 *
 * @description
 * Llamada por el botón de desactivación del modo privado.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @param[in] channel canal sobre el que se va a desactivar la privacidad.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO no se me conceta a metis y no se cual es la funcion a usar NO VA*/
void IRCInterface_DeactivatePrivate(char *channel) {

  long res;

  printf("Desactivando el modo privado en el canal %s...\n", channel);

  res = IRCTAD_Mode(channel, nickC, "-p");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");

}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_DeactivateProtectTopic IRCInterface_DeactivateProtectTopic
 *
 * @brief Llamada por el botón de desactivación de la protección de tópico.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_DeactivateProtectTopic (char *channel)
 * @endcode
 *
 * @description
 * Llamada por el botón de desactivación de la protección de tópico.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] channel canal sobre el que se va a desactivar la protección de
 *tópico.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO no se me conceta a metis y no se cual es la funcion a usar*/
void IRCInterface_DeactivateProtectTopic(char *channel) {

  long res;

  printf("Desactivando la protección del topico en el canal %s...\n", channel);

  res = IRCTAD_Mode (channel, nickC, "-t");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");
}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_DeactivateSecret IRCInterface_DeactivateSecret
 *
 * @brief Llamada por el botón de desactivación de canal secreto.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_DeactivateSecret (char *channel)
 * @endcode
 *
 * @description
 * Llamada por el botón de desactivación de canal secreto.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] channel canal sobre el que se va a desactivar la propiedad de
 *canal secreto.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO no se me conceta a metis y no se cual es la funcion a usar*/
void IRCInterface_DeactivateSecret(char *channel) {

  long res;

  printf("Desactivando el modo secreto del canal %s...\n", channel);

  //res = IRCTAD_Mode(channel, nickC, "-s");

	if (res == IRC_OK)
		printf("Hecho.\n");
  else if (res = IRCERR_INVALIDCHANNELNAME)
    printf("Error - IRCERR_INVALIDCHANNELNAME.\n");
  else if (res = IRCERR_ISNOTOPERATOR)
    printf("Error - IRCERR_ISNOTOPERATOR.\n");
  else if (res = IRCERR_NOUSERONCHANNEL)
    printf("Error - IRCERR_NOUSERONCHANNEL.\n");
  else
    printf("Error Indefinido.\n");

}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_DisconnectServer IRCInterface_DisconnectServer
 *
 * @brief Llamada por los distintos botones de desconexión.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	boolean IRCInterface_DisconnectServer (char * server, int port)
 * @endcode
 *
 * @description
 * Llamada por los distintos botones de desconexión. Debe cerrar la conexión con
 el servidor.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.

 * @param[in] server nombre o ip del servidor del que se va a realizar la
 desconexión.
 * @param[in] port puerto sobre el que se va a realizar la desconexión.
 *
 * @retval TRUE si se ha cerrado la conexión (debe devolverlo).
 * @retval FALSE en caso contrario (debe devolverlo).
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/

boolean IRCInterface_DisconnectServer(char *server, int port) {
  printf("Desconectamos del servidor\n");

  char *command; // = (char*)malloc(sizeof(char)*8192);

  printf("<< QUIT\n");

  if (IRCMsg_Quit(&command, NULL, "Salir, Adios") != IRC_OK)
    return FALSE;

  IRCInterface_PlaneRegisterOutMessage(command);
  send(sock, command, strlen(command), 0);

  IRCInterface_WriteSystem("*", "Desconectado ().");
  IRCInterface_RemoveAllChannels();
  close(sock);
  alarm(0);

  free(command);
  return TRUE;
}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_ExitAudioChat IRCInterface_ExitAudioChat
 *
 * @brief Llamada por el botón "Cancelar" del diálogo de chat de voz.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_ExitAudioChat (char *nick)
 * @endcode
 *
 * @description
 * Llamada por el botón "Parar" del diálogo de chat de voz. Previamente debe
 *seleccionarse un nick del
 * canal para darle voz a dicho usuario. Esta función cierrala comunicación.
 *Evidentemente tiene que
 * actuar sobre el hilo de chat de voz.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] nick nick del usuario que solicita la parada del chat de audio.
 *
 * @retval TRUE si se ha cerrado la comunicación (debe devolverlo).
 * @retval FALSE en caso contrario (debe devolverlo).
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/
/*TODO*/
boolean IRCInterface_ExitAudioChat(char *nick) { return TRUE; }

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_GiveOp IRCInterface_GiveOp
 *
 * @brief Llamada por el botón "Op".
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_GiveOp (char *channel, char *nick)
 * @endcode
 *
 * @description
 * Llamada por el botón "Op". Previamente debe seleccionarse un nick del
 * canal para darle "op" a dicho usuario.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * Las strings recibidas no deben ser manipuladas por el programador, sólo
 *leídas.
 *
 * @param[in] channel canal sobre el que se va dar op al usuario.
 * @param[in] nick nick al que se le va a dar el nivel de op.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/

void IRCInterface_GiveOp(char *channel, char *nick) {

  printf("GiveOp\n");

	char *command;

	if (IRCMsg_Mode(&command, NULL, channel, "+o", nick) != IRC_OK) return;
	send(sock, command, strlen(command), 0);

	printf("Enviado msg_mode: %s\n", command);

	IRCInterface_PlaneRegisterOutMessage(command);

}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_GiveVoice IRCInterface_GiveVoice
 *
 * @brief Llamada por el botón "Dar voz".
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_GiveVoice (char *channel, char *nick)
 * @endcode
 *
 * @description
 * Llamada por el botón "Dar voz". Previamente debe seleccionarse un nick del
 * canal para darle voz a dicho usuario.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * Las strings recibidas no deben ser manipuladas por el programador, sólo
 *leídas.
 *
 * @param[in] channel canal sobre el que se va dar voz al usuario.
 * @param[in] nick nick al que se le va a dar voz.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/

void IRCInterface_GiveVoice(char *channel, char *nick) {}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_KickNick IRCInterface_KickNick
 *
 * @brief Llamada por el botón "Echar".
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_KickNick (char *channel, char *nick)
 * @endcode
 *
 * @description
 * Llamada por el botón "Echar". Previamente debe seleccionarse un nick del
 * canal para darle voz a dicho usuario.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * Las strings recibidas no deben ser manipuladas por el programador, sólo
 *leídas.
 *
 * @param[in] channel canal sobre el que se va a expulsar al usuario.
 * @param[in] nick nick del usuario que va a ser expulsado.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/

void IRCInterface_KickNick(char *channel, char *nick) {}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_NewCommandText IRCInterface_NewCommandText
 *
 * @brief Llamada la tecla ENTER en el campo de texto y comandos.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_NewCommandText (char *command)
 * @endcode
 *
 * @description
 * Llamada de la tecla ENTER en el campo de texto y comandos. El texto deberá
 *ser
 * enviado y el comando procesado por las funciones de "parseo" de comandos de
 * usuario.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] comando introducido por el usuario.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/

void IRCInterface_NewCommandText(char *command) {

  char *channel, *password, *command1, *nick, *user, *realname, *server, *searchstring, *targetserver, *newnick, *msg, *reason, *topic, *mask, *nickorchannel;

  	int port, ssl, i;
  	char **listusers;
  	long aux;
  	char *pipeCommand, *pipe;
  	char msgaux[2000]="";

  	/*pipe = (char *) malloc(sizeof(char) *8192);

  	pipe = IRC_UnPipelineCommands(command, &pipeCommand, pipe);

  	while (pipe != NULL) {

  		printf("Commando a realizar %s - INFO", command);
  		commandAlRealizar(command);
  		pipe = IRC_UnPipelineCommands(command, &pipeCommand, pipe);

  	}*/

  	/*nick = (char *) malloc(30 * sizeof(char));
  	user = (char *) malloc(30 * sizeof(char));
  	realname = (char *) malloc(30 * sizeof(char));
  	password = (char *) malloc(30 * sizeof(char));
  	server = (char *) malloc(30 * sizeof(char));*/

  	//IRCInterface_GetMyUserInfoThread(&nick, &user, &realname, &password, &server, &port, &ssl);

  	switch (IRCUser_CommandQuery(command)) {

  		/*--------- JOIN ---------*/
  		case UJOIN:

  			if (IRCUserParse_Join(command, &channel, &password) == IRC_OK) {

  				printf("Comando JOIN - OK???\n");
  				if (IRCMsg_Join(&command1, NULL, channel, password, NULL) == IRC_OK) {

  					printf("JOIN - Enviamos Msg_Join\n");
  					IRCInterface_PlaneRegisterOutMessage(command1);
  					send(sock, command1, strlen(command1), 0);

  				}

  				if (IRCMsg_Mode(&command1, NULL, channel, NULL, NULL) != IRC_OK) break;
  				printf("JOIN - Enviamos Msg_Mode\n");
  				IRCInterface_PlaneRegisterOutMessage(command1);
  				send(sock, command1, strlen(command1), 0);

  				if (IRCMsg_Who(&command1, NULL, channel, NULL) != IRC_OK) break;
  				printf("JOIN - Enviamos Msg_Who\n");
  				IRCInterface_PlaneRegisterOutMessage(command1);
  				send(sock, command1, strlen(command1), 0);

  				free(channel);
  				free(password);
  				free(command1);
  				break;

  			}

  			printf("Comando JOIN - ERROR\n");
  			break;

  		/*--------- QUIT ---------mirar*/
  		case UQUIT:

  			printf("Comando QUIT - OK???\n");
  			if (IRCUserParse_Quit(command, &reason) != IRC_OK) break;

  			printf("QUIT - Enviamos Msg_Quit\n");

  			if (reason == NULL)
  				sprintf(msgaux, "Saliendo");
  			else
  				sprintf(msgaux, "%s", reason);

  			if (IRCMsg_Quit(&command1, NULL, msgaux) != IRC_OK) break;

  			IRCInterface_PlaneRegisterOutMessage(command1);
  			send(sock, command1, strlen(command1), 0);

  			printf("QUIT - Enviado el mensaje quit\n");

  			IRCInterface_WriteSystem("*", "Desconectado ().");
  			IRCInterface_RemoveAllChannels();
  			close(sock);
  			alarm(0);

  			free(reason);
  			free(command1);
  			break;


  		/*--------- LIST ---------*/
  		case ULIST:

  			if (IRCUserParse_List(command, &channel, &searchstring) == IRC_OK) {

  				printf("Comando LIST - OK???\n");
  				if (IRCMsg_List(&command1, NULL, channel, searchstring) == IRC_OK) {
  					printf("LIST - Enviamos Msg_List\n");
  					send(sock, command1, strlen(command1), 0);

  					IRCInterface_PlaneRegisterOutMessage(command1);

  					printf("Comando LIST - OK\n");

  					free(channel);
  					free(searchstring);
  					free(command1);
  					break;

  				}

  			}

  			printf("Comando LIST - ERROR\n");
  			break;

  		/*--------- NAMES ---------ERROR*/
  		case UNAMES:

  			printf("1.UNAMES---%s\n", command);

  			if (IRCUserParse_Names(command, &channel, &targetserver) == IRC_OK) {

  				printf("Comando NAMES - OK???\n");

  				if (strcmp(IRCInterface_ActiveChannelName(), "System") != 0) {

  					if (IRCMsg_Names(&command1, NULL, IRCInterface_ActiveChannelName(), targetserver) == IRC_OK) {
  						printf("NAMES - Enviamos Msg_Names\n");
  						send(sock, command1, strlen(command1), 0);

  						/*if (IRCTADChan_GetNumberOfUsers(channel) < 0)
  							IRCInterface_WriteSystem(nickC, client_message);*/

  						IRCInterface_PlaneRegisterOutMessage(command1);

  						printf("Comando NAMES - OK\n");

  						free(channel);
  						free(targetserver);
  						free(command1);
  						break;

  					}

  				}


  			// if (aux == IRCERR_NOSTRING)
  			} /*else {

  				printf("Comando NAMES Sin parametro de canal\n");
  				IRCMsg_RplEndOfNames(&command1, NULL, nickC, NULL);
  				send(sock, command1, strlen(command1), 0);

  				free(command1);
  				break;

  			}*/

  			printf("2.UNAMES---%s--%s\n", channel, targetserver);
  			printf("Comando NAMES - ERROR\n");
  			break;


  		/*--------- NICK ---------*/
  		case UNICK:

  			if (IRCUserParse_Nick(command, &newnick) == IRC_OK) {

  				printf("Comando NICK - OK???\n");
  				if (IRCMsg_Nick(&command1, NULL, NULL, newnick) == IRC_OK) {

  					printf("NICK - Enviamos Msg_Nick\n");
  					send(sock, command1, strlen(command1), 0);

  					IRCInterface_PlaneRegisterOutMessage(command1);

  					printf("Comando NICK - OK\n");

  					free(newnick);
  					free(command1);
  					break;

  				}

  			}

  			printf("Comando NICK - ERROR\n");
  			break;


  		/*--------- PART ---------*/
  		case UPART:

  			if (IRCUserParse_Part(command, &msg) == IRC_OK) {

  				printf("Comando PART - OK???\n");
  				if (IRCMsg_Part(&command1, NULL, IRCInterface_ActiveChannelName(), msg) == IRC_OK) {

  					printf("PART - Enviamos Msg_Part\n");
  					send(sock, command1, strlen(command1), 0);

  					IRCInterface_PlaneRegisterOutMessage(command1);

  					printf("Comando PART - OK\n");

  					free(msg);
  					free(command1);
  					break;

  				}

  			}

  			printf("Comando PART - ERROR\n");
  			break;


  		/*--------- AWAY ---------*/
  		case UAWAY:

  			if (IRCUserParse_Away(command, &reason) == IRC_OK) {

  				printf("Comando AWAY - OK???\n");
  				printf("Comando AWAY - %s\n", reason);

  				if (reason == NULL)
  					sprintf(msgaux, "Estoy ocupado");
  				else
  					sprintf(msgaux, "%s", reason);

  				//if (strcmp(reason, "(null)") == 0)
  					//
  					//printf("EI");
  				//else
  					//sprintf(msgaux, "%s", reason);

  				if (IRCMsg_Away(&command1, NULL, msgaux) == IRC_OK) {

  					printf("AWAY - Enviamos Msg_Away\n");
  					send(sock, command1, strlen(command1), 0);

  					IRCInterface_PlaneRegisterOutMessage(command1);

  					printf("Comando AWAY - OK\n");

  					free(reason);
  					free(command1);
  					break;

  				}

  			}

  			printf("Comando AWAY - ERROR\n");
  			break;

  		/*--------- KICK ---------*/
  		case UKICK:

  			if (IRCUserParse_Kick(command, &nick, &msg) == IRC_OK) {

  				printf("Comando KICK - OK???\n");
  				if (IRCMsg_Kick(&command1, NULL, IRCInterface_ActiveChannelName(), nick, msg) == IRC_OK) {

  					printf("KICK - Enviamos Msg_Kick\n");
  					send(sock, command1, strlen(command1), 0);

  					//if (IRCTADChan_GetNumberOfUsers(channel) < 0)
  						//IRCInterface_WriteSystem(nickC, client_message);

  					IRCInterface_PlaneRegisterOutMessage(command1);

  					printf("Comando KICK - OK\n");

  					free(msg);
  					free(nick);
  					free(command1);
  					break;

  				}

  			}

  			printf("Comando KICK - ERROR\n");
  			break;

  		/*--------- TOPIC ---------*/
  		case UTOPIC:

  			if (IRCUserParse_Topic(command, &topic) == IRC_OK) {

  				printf("Comando TOPIC - OK???\n");
  				if (IRCMsg_Topic(&command1, NULL, IRCInterface_ActiveChannelName(), topic) == IRC_OK) {

  					printf("TOPIC - Enviamos Msg_Topic\n");
  					send(sock, command1, strlen(command1), 0);

  					//if (IRCTADChan_GetNumberOfUsers(channel) < 0)
  						//IRCInterface_WriteSystem(nickC, client_message);

  					IRCInterface_PlaneRegisterOutMessage(command1);

  					printf("Comando TOPIC - OK\n");

  					free(topic);
  					free(command1);
  					break;

  				}

  			}

  			printf("Comando TOPIC - ERROR\n");
  			break;

  		/*--------- ULUSERS ---------faltaaaaaaaa*/
  		case ULUSERS:

  			if (IRCUserParse_Lusers(command, &server) == IRC_OK) {

  				printf("Comando ULUSERS - OK???\n");
  				if (IRCMsg_Lusers(&command1, NULL, NULL, NULL) == IRC_OK) {

  					printf("ULUSERS - Enviamos Msg_Lusers\n");
  					send(sock, command1, strlen(command1), 0);

  					//if (IRCTADChan_GetNumberOfUsers(channel) < 0)
  						//IRCInterface_WriteSystem(nickC, client_message);

  					IRCInterface_PlaneRegisterOutMessage(command1);

  					printf("Comando ULUSERS - OK\n");

  					if (server != NULL)
  						free(server);
  					free(command1);
  					break;

  				}

  			}

  			printf("Comando ULUSERS - ERROR\n");
  			break;

  		/*--------- UWHO ---------*/
  		case UWHO:

  			if (IRCUserParse_Who(command, &mask) == IRC_OK) {

  				printf("Comando UWHO - OK???\n");
  				if (IRCMsg_Who(&command1, NULL, mask, NULL) == IRC_OK) {

  					printf("UWHO - Enviamos Msg_Who\n");
  					send(sock, command1, strlen(command1), 0);

  					//if (IRCTADChan_GetNumberOfUsers(channel) < 0)
  						//IRCInterface_WriteSystem(nickC, client_message);

  					IRCInterface_PlaneRegisterOutMessage(command1);

  					printf("Comando UWHO - OK\n");

  					free(mask);
  					free(command1);
  					break;

  				}

  			}

  			printf("Comando UWHO - ERROR\n");
  			break;

  		/*--------- MOTD ---------errooooooooor*/
  		case UMOTD:

  			if (IRCUserParse_Motd(command, &server) == IRC_OK) {

  				printf("Comando MOTD - OK???\n");
  				if (IRCMsg_Motd(&command1, NULL, server) == IRC_OK) {

  					printf("MOTD - Enviamos Msg_Who\n");
  					send(sock, command1, strlen(command1), 0);

  					//if (IRCTADChan_GetNumberOfUsers(channel) < 0)
  						//IRCInterface_WriteSystem(nickC, client_message);

  					IRCInterface_PlaneRegisterOutMessage(command1);

  					printf("Comando MOTD - OK\n");

  					free(server);
  					free(command1);
  					break;

  				}

  			}

  			printf("Comando MOTD - ERROR\n");
  			break;

  		/*--------- UMSG ---------*/
  		case UMSG:

  			if (IRCUserParse_Msg(command, &nickorchannel, &msg) == IRC_OK) {

  				printf("Comando UMSG - OK? --%s--%s\n", command, IRCInterface_ActiveChannelName());

  				if (IRCMsg_Privmsg(&command1, NULL, nickorchannel, msg) == IRC_OK) {

  					printf("UMSG - Enviamos Msg_Privmsg\n");
  					send(sock, command1, strlen(command1), 0);

  					//if (IRCTADChan_GetNumberOfUsers(channel) < 0)
  						//IRCInterface_WriteSystem(nickC, client_message);

  					IRCInterface_PlaneRegisterOutMessage(command1);
  					IRCInterface_WriteChannel(nickorchannel, nickC, msg);

  					printf("Comando UMSG - OK\n");

  					free(nickorchannel);
  					free(msg);
  					free(command1);
  					break;

  				}

  			}

  			printf("Comando UMSG - ERROR\n");
  			break;

  		/*--------- ULEAVE ---------mirar*/
  		case ULEAVE:

  			if (IRCUserParse_Leave(command, &msg) == IRC_OK) {

  				printf("Comando ULEAVE - OK???\n");
  				if (IRCMsg_Part(&command1, NULL, IRCInterface_ActiveChannelName(), msg) == IRC_OK) {

  					printf("ULEAVE - Enviamos Msg_Part\n");
  					send(sock, command1, strlen(command1), 0);

  					//if (IRCTADChan_GetNumberOfUsers(channel) < 0)
  						//IRCInterface_WriteSystem(nickC, client_message);
  					IRCInterface_DeleteNickChannel(IRCInterface_ActiveChannelName(), nickC);
  					IRCInterface_PlaneRegisterOutMessage(command1);

  					printf("Comando ULEAVE - OK\n");

  					if (msg != NULL)
  						free(msg);
  					free(command1);
  					break;

  				}

  			}

  			printf("Comando ULEAVE - ERROR\n");
  			break;

  		/*--------- UWHOIS ---------*/
  		case UWHOIS:

  			if (IRCUserParse_Whois(command, &nick) == IRC_OK) {

  				printf("Comando UWHOIS - OK???\n");
  				if (IRCMsg_Whois(&command1, NULL, nick, nick) == IRC_OK) {

  					printf("UWHOIS - Enviamos Msg_Whois\n");
  					send(sock, command1, strlen(command1), 0);

  					//if (IRCTADChan_GetNumberOfUsers(channel) < 0)
  						//IRCInterface_WriteSystem(nickC, client_message);
  					IRCInterface_PlaneRegisterOutMessage(command1);

  					printf("Comando UWHOIS - OK\n");

  					free(nick);
  					free(command1);
  					break;

  				}

  			}

  			printf("Comando UWHOIS - ERROR\n");
  			break;

  		/*--------- UNOTICE ---------mirar*/
  		case UNOTICE:

  			if (IRCUserParse_Notice(command, &nickorchannel, &msg) == IRC_OK) {

  				printf("Comando UNOTICE - OK???\n");
  				if (IRCMsg_Notice(&command1, NULL, nickorchannel, msg) == IRC_OK) {

  					printf("UNOTICE - Enviamos Msg_Notice\n");
  					send(sock, command1, strlen(command1), 0);

  					//if (IRCTADChan_GetNumberOfUsers(channel) < 0)
  						//IRCInterface_WriteSystem(nickC, client_message);
  					IRCInterface_PlaneRegisterOutMessage(command1);

  					printf("Comando UNOTICE - OK\n");

  					if (msg != NULL)
  						free(msg);
  					if (nickorchannel != NULL)
  						free(nickorchannel);
  					free(command1);
  					break;

  				}

  			}

  			printf("Comando UNOTICE - ERROR\n");
  			break;

  		/*--------- UQUERY ---------mirar*/
  		case UQUERY:

  			if (IRCUserParse_Query(command, &nickorchannel, &msg) == IRC_OK) {

  				printf("Comando UQUERY - OK???\n");
  				if (IRCMsg_Squery(&command1, NULL, nickorchannel, msg) == IRC_OK) {

  					printf("UQUERY - Enviamos Msg_Squery\n");
  					send(sock, command1, strlen(command1), 0);

  					//if (IRCTADChan_GetNumberOfUsers(channel) < 0)
  						//IRCInterface_WriteSystem(nickC, client_message);
  					IRCInterface_PlaneRegisterOutMessage(command1);

  					printf("Comando UQUERY - OK\n");

  					if (msg != NULL)
  						free(msg);
  					if (nickorchannel != NULL)
  						free(nickorchannel);
  					free(command1);
  					break;

  				}

  			}

  			printf("Comando UQUERY - ERROR\n");
  			break;

  		/*--------- UINVITE ---------mirar*/
  		case UINVITE:

  			if (IRCUserParse_Invite(command, &nick, &channel) == IRC_OK) {

  				printf("Comando UINVITE - OK???\n");
  				if (IRCMsg_Invite(&command1, NULL, nick, channel) == IRC_OK) {

  					printf("UINVITE - Enviamos Msg_Invite\n");
  					send(sock, command1, strlen(command1), 0);

  					//if (IRCTADChan_GetNumberOfUsers(channel) < 0)
  						//IRCInterface_WriteSystem(nickC, client_message);
  					IRCInterface_PlaneRegisterOutMessage(command1);

  					printf("Comando UINVITE - OK\n");

  					if (nick != NULL)
  						free(nick);
  					if (channel != NULL)
  						free(channel);
  					free(command1);
  					break;

  				}

  			}

  			printf("Comando UINVITE - ERROR\n");
  			break;

  		default:

  			if (strcmp(IRCInterface_ActiveChannelName(),"System") != 0) {

  				printf("Comando default - privmsg\n");

  				//IRCMsg_Privmsg (char **command, char *prefix, char * msgtarget, char *msg)
  				IRCMsg_Privmsg(&command1, NULL, IRCInterface_ActiveChannelName(), command);
  				send(sock, command1, strlen(command1), 0);

  				IRCInterface_PlaneRegisterOutMessage(command1);
  				IRCInterface_WriteChannel(IRCInterface_ActiveChannelName(), nickC, command);

  				free(command1);

  			}

  			break;

  	}

  }

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_NewTopicEnter IRCInterface_NewTopicEnter
 *
 * @brief Llamada cuando se pulsa la tecla ENTER en el campo de tópico.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_NewTopicEnter (char * topicdata)
 * @endcode
 *
 * @description
 * Llamada cuando se pulsa la tecla ENTER en el campo de tópico.
 * Deberá intentarse cambiar el tópico del canal.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * param[in] topicdata string con el tópico que se desea poner en el canal.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/

void IRCInterface_NewTopicEnter(char *topicdata) {

  printf("<< New TOPIC\n");

	char msgaux[8000]="";
	//char *command1 = (char*)malloc(sizeof(char)*8192);
	char *command1;

	printf("New topic :%s\n", topicdata);

	if (topicdata != NULL) {

		printf("Vamos a cambiar topico del canal %s por %s\n", IRCInterface_ActiveChannelName(), nickC);

		if (IRCMsg_Topic(&command1, NULL, IRCInterface_ActiveChannelName(), topicdata) != IRC_OK) return;
		send(sock, command1, strlen(command1), 0);

		printf("Enviado msg_topic\n");

		IRCInterface_PlaneRegisterInMessage(command1);

		//sprintf(msgaux, "%s ha cambiado el topic a: %s", nickC, topicdata);
		//IRCInterface_WriteChannel(IRCInterface_ActiveChannelName(), NULL, msgaux);

		free(command1);

	}
}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_SendFile IRCInterface_SendFile
 *
 * @brief Llamada por el botón "Enviar Archivo".
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_SendFile (char * filename, char *nick, char *data,
 *long unsigned int length)
 * @endcode
 *
 * @description
 * Llamada por el botón "Enviar Archivo". Previamente debe seleccionarse un nick
 *del
 * canal para darle voz a dicho usuario. Esta función como todos los demás
 *callbacks bloquea el interface
 * y por tanto es el programador el que debe determinar si crea un nuevo hilo
 *para enviar el archivo o
 * no lo hace.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * Las strings recibidas no deben ser manipuladas por el programador, sólo
 *leídas.
 *
 * @param[in] filename nombre del fichero a enviar.
 * @param[in] nick nick del usuario que enviará el fichero.
 * @param[in] data datos a ser enviados.
 * @param[in] length longitud de los datos a ser enviados.
 *
 * @retval TRUE si se ha establecido la comunicación (debe devolverlo).
 * @retval FALSE en caso contrario (debe devolverlo).
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/

boolean IRCInterface_SendFile(char *filename, char *nick, char *data,
                              long unsigned int length) {
  return TRUE;
}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_StartAudioChat IRCInterface_StartAudioChat
 *
 * @brief Llamada por el botón "Iniciar" del diálogo de chat de voz.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_StartAudioChat (char *nick)
 * @endcode
 *
 * @description
 * Llamada por el botón "Iniciar" del diálogo de chat de voz. Previamente debe
 *seleccionarse un nick del
 * canal para darle voz a dicho usuario. Esta función como todos los demás
 *callbacks bloquea el interface
 * y por tanto para mantener la funcionalidad del chat de voz es imprescindible
 *crear un hilo a efectos
 * de comunicación de voz.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] nick nick del usuario con el que se desea conectar.
 *
 * @retval TRUE si se ha establecido la comunicación (debe devolverlo).
 * @retval FALSE en caso contrario (debe devolverlo).
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/

boolean IRCInterface_StartAudioChat(char *nick) { return TRUE; }

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_StopAudioChat IRCInterface_StopAudioChat
 *
 * @brief Llamada por el botón "Parar" del diálogo de chat de voz.
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_StopAudioChat (char *nick)
 * @endcode
 *
 * @description
 * Llamada por el botón "Parar" del diálogo de chat de voz. Previamente debe
 *seleccionarse un nick del
 * canal para darle voz a dicho usuario. Esta función sólo para la comunicación
 *que puede ser reiniciada.
 * Evidentemente tiene que actuar sobre el hilo de chat de voz.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * La string recibida no debe ser manipulada por el programador, sólo leída.
 *
 * @param[in] nick nick del usuario con el que se quiere parar el chat de voz.
 *
 * @retval TRUE si se ha parado la comunicación (debe devolverlo).
 * @retval FALSE en caso contrario (debe devolverlo).
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/

boolean IRCInterface_StopAudioChat(char *nick) { return TRUE; }

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_TakeOp IRCInterface_TakeOp
 *
 * @brief Llamada por el botón "Quitar Op".
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_TakeOp (char *channel, char *nick)
 * @endcode
 *
 * @description
 * Llamada por el botón "Quitar Op". Previamente debe seleccionarse un nick del
 * canal para quitarle "op" a dicho usuario.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * Las strings recibidas no deben ser manipuladas por el programador, sólo
 *leídas.
 *
 * @param[in] channel canal sobre el que se va a quitar op al usuario.
 * @param[in] nick nick del usuario al que se le va a quitar op.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/

void IRCInterface_TakeOp(char *channel, char *nick) {

  printf("IRCInterface_TakeOp\n");

	char *command;

	if (IRCMsg_Mode(&command, NULL, channel, "-o", nick) != IRC_OK) return;
	send(sock, command, strlen(command), 0);

	printf("Enviado msg_mode: %s\n", command);

	IRCInterface_PlaneRegisterOutMessage(command);
}

/**
 * @ingroup IRCInterfaceCallbacks
 *
 * @page IRCInterface_TakeVoice IRCInterface_TakeVoice
 *
 * @brief Llamada por el botón "Quitar voz".
 *
 * @synopsis
 * @code
 *	#include <redes2/ircxchat.h>
 *
 * 	void IRCInterface_TakeVoice (char *channel, char *nick)
 * @endcode
 *
 * @description
 * Llamada por el botón "Quitar voz". Previamente debe seleccionarse un nick del
 * canal para darle voz a dicho usuario.
 *
 * En cualquier caso sólo se puede realizar si el servidor acepta la orden.
 * Las strings recibidas no deben ser manipuladas por el programador, sólo
 *leídas.
 *
 * @param[in] channel canal sobre el que se le va a quitar voz al usuario.
 * @param[in] nick nick del usuario al que se va a quitar la voz.
 *
 * @warning Esta función debe ser implementada por el alumno.
 *
 * @author
 * Eloy Anguiano (eloy.anguiano@uam.es)
 *
 *<hr>
*/

void IRCInterface_TakeVoice(char *channel, char *nick) {}

void comandoARealizar(char *strin, int sock) {

    if (strin == NULL)
        return;

    char *prefix, *server, *server2, *msg, *channel, *key, *target, *nick, *type, *token;
    char *nickname, *username, *host, *name, *nick2, *user, *realname, *usermodestring;
    char *modetxt, *visible, *topic, *servername, *version, *availableusermodes, *availablechannelmodes;
    char *servicename, *addedg, *versionname, *hostmask, *linkname, *comment, *msgtarget;
    char *serverinfo, *chanelstr, *channeluser, *mode;

    char *command = (char*)malloc(sizeof(char)*8192);
    long numberOfUsers;
    int  hopcount, nusers, ninvisibles, nservers, nchannels, sendq, sentmessages, sentKB, recmessages, recKB, timeopen;
    int secs_idle, signon;
    char msgaux[8000]="", msgg[8000]="", tokenAux[8000]="", token1[2000]="";

    switch(IRC_CommandQuery(strin)) {

	case USER:

	   break;

    case PONG:

  		printf("<< PONG\n");

    	IRCParse_Pong(strin, &prefix, &server, &server2, &msg);
		IRCMsg_Pong(&command, prefix, server, server2, msg);

    	//IRCInterface_PlaneRegisterInMessageThread(command);
    	IRCInterface_PlaneRegisterInMessageThread(strin);

    	free(command);
    	free(prefix);
    	free(server);
    	free(server2);
    	free(msg);

   		break;

   	case RPL_WHOISUSER:

   		IRCParse_RplWhoIsUser(strin, &prefix, &nick, &nick2, &name, &host, &realname);

   		printf("1.RplWhoIsUser\n");

		sprintf(msgaux, "[%s] (%s): %s", nick2, host, nick2);

		//printf("69.--%s--%s--%s--%s--msgaux(%s)\n", prefix, nick, channel, msg, msgaux);
   		IRCInterface_WriteSystemThread("*", msgaux);
		IRCInterface_PlaneRegisterInMessageThread(strin);
		//IRCInterface_WriteChannelThread(channel, NULL, msgaux);

		free(prefix);
		free(nick);
		free(nick2);
		free(name);
		free(host);
		free(realname);

   		break;

   	case  RPL_WHOISSERVER:

   		IRCParse_RplWhoIsServer(strin, &prefix, &nick, &nick2, &server, &serverinfo);

   		printf("1.RplWhoIsServer\n");

   		sprintf(msgaux, "[%s] %s %s", nick2, server, serverinfo);

		//printf("69.--%s--%s--%s--%s--msgaux(%s)\n", prefix, nick, channel, msg, msgaux);
   		IRCInterface_WriteSystemThread("*", msgaux);
		IRCInterface_PlaneRegisterInMessageThread(strin);
		//IRCInterface_WriteChannelThread(channel, NULL, msgaux);

		free(prefix);
		free(nick);
		free(nick2);
		free(server);
		free(serverinfo);

   		break;

   	case RPL_WHOISCHANNELS:

   		IRCParse_RplWhoIsChannels(strin, &prefix, &nick, &nick2, &chanelstr);

   		printf("1.RplWhoIsChannels\n");

   		sprintf(msgaux, "[%s] %s", nick2, chanelstr);

		//printf("69.--%s--%s--%s--%s--msgaux(%s)\n", prefix, nick, channel, msg, msgaux);
   		IRCInterface_WriteSystemThread("*", msgaux);
		IRCInterface_PlaneRegisterInMessageThread(strin);
		//IRCInterface_WriteChannelThread(channel, NULL, msgaux);

		free(prefix);
		free(nick);
		free(nick2);
		free(chanelstr);

   		break;

   	case RPL_WHOISIDLE:

   		IRCParse_RplWhoIsIdle(strin, &prefix, &nick, &nick2, &secs_idle, &signon, &msg);

   		printf("1.RplWhoIsIdle\n");

   		sprintf(msgaux, "[%s] inactivo %d, entró: %s %d", nick2, secs_idle, msg, signon);

		//printf("69.--%s--%s--%s--%s--msgaux(%s)\n", prefix, nick, channel, msg, msgaux);
   		IRCInterface_WriteSystemThread("*", msgaux);
		IRCInterface_PlaneRegisterInMessageThread(strin);
		//IRCInterface_WriteChannelThread(channel, NULL, msgaux);

		free(prefix);
		free(nick);
		free(nick2);
		free(msg);

   		break;

   	case RPL_ENDOFWHOIS:

		IRCParse_RplEndOfWhoIs(strin, &prefix, &nick, &name, &msg);

   		printf("1.RplEndOfWhoIs\n");

   		sprintf(msgaux, "[%s] Final de la lista WHOIS.", name);

		//printf("69.--%s--%s--%s--%s--msgaux(%s)\n", prefix, nick, channel, msg, msgaux);
   		IRCInterface_WriteSystemThread("*", msgaux);
		IRCInterface_PlaneRegisterInMessageThread(strin);
		//IRCInterface_WriteChannelThread(channel, NULL, msgaux);

		free(prefix);
		free(nick);
		free(name);
		free(msg);

   		break;

   	case RPL_NOTOPIC:

   		IRCParse_RplNoTopic(strin, &prefix, &nick, &channel, &topic);

		printf("1.RplNoTopic\n");

		//sprintf(msgaux, "El topic para %s es %s", channel, msg);

		//printf("69.--%s--%s--%s--%s--msgaux(%s)\n", prefix, nick, channel, msg, msgaux);

		IRCInterface_PlaneRegisterInMessageThread(strin);
		//IRCInterface_WriteChannelThread(channel, NULL, msgaux);

		free(prefix);
		free(nick);
		free(channel);
		free(topic);

   		break;

   	case RPL_TOPIC:

   		IRCParse_RplTopic(strin, &prefix, &nick, &channel, &msg);

		printf("1.RplTopic\n");

		sprintf(msgaux, "El topic para %s es %s", channel, msg);

		printf("69.--%s--%s--%s--%s--msgaux(%s)\n", prefix, nick, channel, msg, msgaux);

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteChannelThread(channel, NULL, msgaux);

		free(prefix);
		free(nick);
		free(channel);
		free(msg);

   		break;

	case TOPIC:

		printf("<< TOPIC\n");

		IRCParse_Topic(strin, &prefix, &channel, &topic);
		IRCParse_ComplexUser(prefix, &nickname, &username, &host, &server);

		IRCInterface_PlaneRegisterInMessageThread(strin);

		if (topic == NULL)
			sprintf(msgaux, "%s ha cambiado el topic a:", nickname);
		else
			sprintf(msgaux, "%s ha cambiado el topic a: %s", nickname, topic);

		IRCInterface_WriteChannelThread(channel, NULL, msgaux);

		free(prefix);
		free(channel);
		free(topic);
		free(nickname);
		free(username);
		free(host);
		free(server);

	   	break;

	case RPL_VERSION:

		IRCParse_RplVersion(strin, &prefix, &nick, &version, &server, &msg);

		printf("1.RplVersion");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(version);
		free(server);
		free(msg);

		break;

	case RPL_WELCOME:

		IRCParse_RplWelcome(strin, &prefix, &nick, &msg);

		printf("1.RplWelcome");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(msg);

		break;

	case RPL_MYINFO:

		IRCParse_RplMyInfo(strin, &prefix, &nick, &servername, &version, &availableusermodes, &availablechannelmodes, &addedg);

		printf("1.RplMyInfo");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(servername);
		free(version);
		free(availableusermodes);
		free(availablechannelmodes);
		free(addedg);

		break;

	case RPL_STATSOLINE:

		IRCParse_RplStatsOLine(strin, &prefix, &nick, &hostmask, &name);

		printf("1.RplStatsOLine");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(hostmask);
		free(name);

		break;

	case RPL_STATSLINKINFO:

		IRCParse_RplStatsLinkInfo(strin, &prefix, &nick, &linkname, &sendq, &sentmessages, &sentKB, &recmessages, &recKB, &timeopen);

		printf("1.RplMotdStart");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(linkname);

		break;

	case RPL_MOTDSTART:

		IRCParse_RplMotdStart(strin, &prefix, &nick, &msg, &server);

		printf("1.RplMotdStart");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(msg);
		free(server);

		break;

	case RPL_LUSERCLIENT:

		IRCParse_RplLuserClient(strin, &prefix, &nick, &msg, &nusers, &ninvisibles, &nservers);

		printf("1.RplLuserClient");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(msg);

		break;

	case RPL_MOTD:

		IRCParse_RplMotd(strin, &prefix, &nick, &msg);

		printf("1.RplMotd");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(msg);

		break;

	case RPL_YOURESERVICE:

		IRCParse_RplYoureService(strin, &prefix, &nick, &msg, &servicename);

		printf("1.RplYoureService");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(msg);
		free(servicename);

		break;

	case RPL_ENDOFMOTD:

		IRCParse_RplEndOfMotd(strin, &prefix, &nick, &msg);

		printf("1.RplEndOfMotd");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(msg);


		break;

	case RPL_YOURHOST:

		IRCParse_RplYourHost(strin, &prefix, &nick, &msg, &servername, &versionname);

		printf("1.RplYourHost");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(msg);
		free(servername);
		free(versionname);

		break;

	case RPL_LISTEND:

		IRCParse_RplListEnd(strin, &prefix, &nick, &msg);

		printf("1.RplListEnd");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(msg);

		break;

	case RPL_LIST:

		IRCParse_RplList(strin, &prefix, &nick, &channel, &visible, &topic);

		printf("1.RplList");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(channel);
		free(visible);
		free(topic);

		break;

	case RPL_CHANNELMODEIS:

		IRCParse_RplChannelModeIs(strin, &prefix, &nick, &channel, &modetxt);

		printf("1.RplChannelModeIs");

		IRCInterface_PlaneRegisterInMessageThread(strin);

		free(prefix);
		free(nick);
		free(channel);
		free(modetxt);

		break;

	//De momento no es necesario
	case RPL_UMODEIS:

		IRCParse_RplUModeIs(strin, &prefix, &nick, &usermodestring);

		printf("1.RplUModeIs");

		IRCInterface_PlaneRegisterInMessageThread(strin);

		free(prefix);
		free(nick);
		free(usermodestring);

		break;

	case RPL_WHOREPLY:

		IRCParse_RplWhoReply(strin, &prefix, &nick, &channel, &user, &host, &server, &nick2, &type, &msg, &hopcount, &realname);

		printf("1.RplWhoReply");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(channel);
		free(user);
		free(host);
		free(server);
		free(nick2);
		free(type);
		free(msg);
		free(realname);

		break;


	case RPL_ENDOFWHO:

		IRCParse_RplEndOfWho(strin, &prefix, &nick, &name, &msg);

		printf("1.RplEndOfWho----%s--%s--%s--%s\n", prefix, nick, name, msg);

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(name);
		free(msg);

		break;

	case RPL_ENDOFNAMES:

		IRCParse_RplEndOfNames(strin, &prefix, &nick, &channel, &msg);

		printf("1.RplEndOfNames");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(channel);
		free(msg);
		break;

	// Mirar el segundo strtok !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	case RPL_NAMREPLY:

		//char* token;// = (char*)malloc(5192);

		IRCParse_RplNamReply(strin, &prefix, &nick, &type, &channel, &msg);

		printf("1.Rpl_namreply----%s--%s--%s--%s--%s\n", prefix, nick, type, channel, msg);

		strcpy(msgg, msg);

		token = strtok(msg, " ");

		while (token != NULL) {

			printf("2.Rpl_namreply---TOKEN?: %s\n", token);

			if (strpbrk(token, "@") == NULL) {

				printf("Rpl_namreply---Annadimos nick NONE\n");
				IRCInterface_AddNickChannelThread(channel, token, token, token, prefix, NONE);

			// Cuando se trata de un OP
			} else {

				//strcpy(tokenAux, token);
				//token1 = strtok(tokenAux, "@");
				//strcpy(tokenAux, token);

				memmove(token1, token+1, strlen(token)-1);
				printf("MIRAR AQUI: -------------%s--%s\n", token1, token);

				printf("Rpl_namreply---Annadimos nick OP\n");
				IRCInterface_AddNickChannelThread(channel, token1, token1, token1, prefix, OPERATOR);
			}

			token = strtok(NULL, " ");

		}

		/*if (strlen(tokenAux) != 0) {

			token1 = strtok(tokenAux, "@");

			printf("Rpl_namreply---Annadimos nick OP de verdad\n");
			IRCInterface_AddNickChannelThread(channel, token1, token1, token1, prefix, OPERATOR);

		}*/

		sprintf(msgaux, "Usuarios en %s: %s", channel, msgg);

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteChannelThread(channel, "*", msgaux);

		free(prefix);
		free(nick);
		free(type);
		free(channel);
		free(msg);
		break;

	case RPL_AWAY:

		IRCParse_RplAway(strin, &prefix, &nick, &nick2, &msg);

		printf("1.RplAway");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, msg);

		sprintf(msgaux, "[%s] está ausente (%s)", nick2, msg);

		IRCInterface_WriteChannelThread(IRCInterface_ActiveChannelName(), "*", msgaux);

		free(prefix);
		free(nick);
		free(nick2);
		free(msg);

		break;

	case RPL_NOWAWAY:

		IRCParse_RplNowAway(strin, &prefix, &nick, &msg);

		printf(">>>>> 69.RplNowAway");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, msg);

		free(prefix);
		free(nick);
		free(msg);

		break;

	case RPL_LUSERCHANNELS:

		IRCParse_RplLuserChannels(strin, &prefix, &nick, &nchannels, &msg);

		printf(">>>>> RplLuserChannels");

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteSystemThread(NULL, strin);

		free(prefix);
		free(nick);
		free(msg);

		break;

	case JOIN:

		printf("<< JOIN\n");

		IRCParse_Join(strin, &prefix, &channel, &key, &msg);
		IRCParse_ComplexUser(prefix, &nickname, &username, &host, &server);

		printf("1.Join----%s--%s--%s--%s--%s\n", prefix, channel, key, msg, nickC);

		if (strcmp(nickC, nickname) != 0)
			sprintf(msgaux, "%s (~%s@%s) ha entrado en %s", nickname, nickname, server, msg);
		else
			sprintf(msgaux, "Has entrado en %s", msg);

		IRCInterface_AddNewChannelThread(msg, NONE);
		IRCInterface_PlaneRegisterInMessageThread(strin);

		IRCInterface_WriteChannelThread(msg, NULL, msgaux);

		if (strcmp(nickname, nickC) != 0)
			IRCInterface_AddNickChannelThread(msg, nickname, username, username, server, NONE);

		printf("2.Join OK");

		free(prefix);
		free(channel);
		free(key);
		free(msg);
		free(nickname);
		free(username);
		free(host);
		free(server);

	   	break;

	// Me falta que el mensaje de Usted es ahora conocido como se imprima en los canales
	case NICK:

		printf("<< NICK\n");
		IRCParse_Nick(strin, &prefix, &nick, &msg);
		IRCParse_ComplexUser(strin, &nickname, &username, &host, &server);

		printf("1.Nick---%s--%s--%s\n", prefix, nick, msg);

		if (strcmp(nickname, nickC) != 0) {
			sprintf(msgaux, "%s es ahora conocido como %s", nickname, msg);
			IRCInterface_ChangeNickThread(nickname, msg);
		} else {
			sprintf(msgaux, "Usted es ahora conocido como %s", msg);
			IRCInterface_ChangeNickThread(nickC, msg);
			IRCInterface_WriteSystemThread(NULL, msgaux);
			strcpy(nickC, msg);
		}

		IRCInterface_PlaneRegisterInMessageThread(strin);
		IRCInterface_WriteChannelThread(IRCInterface_ActiveChannelName(), NULL, msgaux);

		free(prefix);
		free(nick);
		free(msg);
		free(nickname);
		free(username);
		free(host);
		free(server);

		break;

	case LIST:

		printf("<< LIST\n");
		IRCParse_List(strin, &prefix, &channel, &target);

		IRCInterface_WriteSystemThread(NULL, strin);
		IRCInterface_PlaneRegisterInMessageThread(strin);

		free(prefix);
		free(channel);
		free(target);

	   	break;

    case QUIT:

    	printf("<< QUIT\n");

    	IRCParse_Quit(strin, &prefix, &msg);
		IRCParse_ComplexUser(prefix, &nickname, &username, &host, &server);


		if (strcmp(nickname, nickC) != 0) {

			sprintf(msgaux, "%s se ha marchado (%s)", nickname, msg);

			//IRCInterface_NickListChannelThread( char *channel, char **nick, char **user, char **real, char **host, nickstate *ns)
			IRCInterface_WriteChannelThread(IRCInterface_ActiveChannelName(), "*", msgaux);
			IRCInterface_PlaneRegisterInMessageThread(strin);

		} /*else {

			IRCInterface_WriteChannelThread(IRCInterface_ActiveChannelName(), NULL, "Desconectado ().");
			IRCInterface_WriteSystemThread(NULL, "Desconectado ().");
			close(sock);
		}*/

		free(prefix);
		free(msg);
		free(nickname);
		free(username);
		free(host);
		free(server);

	   	break;

	/*case WHOIS:

	   	break;*/

	case PRIVMSG:

		printf("<< PRIVMSG\n");
		IRCParse_Privmsg(strin, &prefix, &msgtarget, &msg);
		IRCParse_ComplexUser(prefix, &nickname, &username, &host, &server);

		printf("1.Privmsg--%s--%s--%s\n", prefix, msgtarget, msg);

		if (IRCInterface_QueryChannelExistThread(msgtarget) == FALSE) {
			IRCInterface_AddNewChannelThread(msgtarget, NONE);
		}

		IRCInterface_WriteChannelThread(msgtarget, nickname, msg);
		IRCInterface_PlaneRegisterInMessageThread(strin);

		free(prefix);
		free(msgtarget);
		free(msg);
		free(nickname);
		free(username);
		free(host);
		free(server);

	   	break;

  	case NAMES:

        break;

	case AWAY:

   	   	break;

   	// Faltaria cambiar nombre al canal o modo y eliminar todos los nicks
	case KICK:

		printf("<< KICK\n");
		IRCParse_Kick(strin, &prefix, &channel, &user, &comment);
		IRCParse_ComplexUser(prefix, &nickname, &username, &host, &server);

		if (strcmp(user, nickC)) {
			sprintf(msgaux, "%s ha echado a %s de %s (%s)", nickname, user, channel, nickname);
		} else {
			sprintf(msgaux, "Se le ha echado de %s por %s (%s)", channel, nickname, nickname);
		}

		IRCInterface_WriteChannelThread(channel, NULL, msgaux);

		IRCInterface_DeleteNickChannel(channel, user);
		IRCInterface_PlaneRegisterInMessageThread(strin);

		free(prefix);
		free(channel);
		free(user);
		free(comment);
		free(nickname);
		free(username);
		free(host);
		free(server);

	   	break;

	case PART:

		printf("<< PART\n");
		IRCParse_Part(strin, &prefix, &channel, &msg);
		IRCParse_ComplexUser(prefix, &nickname, &username, &host, &server);

		if (strcmp(nickname, nickC) != 0) {
			sprintf(msgaux,"%s (%s) ha abandonado %s (%s)", nickname, server, channel, nickname);
		} else {
			sprintf(msgaux,"Ha abandonado el canal %s (%s)", channel, msg);
		}

		IRCInterface_WriteChannelThread(channel, NULL, msgaux);

		IRCInterface_DeleteNickChannel(channel, nickname);
		IRCInterface_PlaneRegisterInMessageThread(strin);

	  	free(prefix);
	  	free(channel);
	  	free(msg);
	  	free(nickname);
	  	free(username);
	  	free(host);
	  	free(server);

	   	break;

	case MODE:

		IRCParse_Mode(strin, &prefix, &channeluser, &mode, &user);
		IRCParse_ComplexUser(prefix, &nickname, &username, &host, &server);

		if (strcmp(mode, "+o") == 0) {
			sprintf(msgaux,"%s da OP a %s", nickname, user);
			IRCInterface_ChangeNickStateChannelThread(channeluser, user, OPERATOR);
		}

		if (strcmp(mode, "-o") == 0) {
			sprintf(msgaux,"%s quita OP de %s", nickname, user);
			IRCInterface_ChangeNickStateChannelThread(channeluser, user, NONE);
		}

		IRCInterface_WriteChannelThread(channeluser, "*", msgaux);

		IRCInterface_PlaneRegisterInMessageThread(strin);

		free(prefix);
	  	free(channeluser);
	  	free(mode);
	  	free(user);
	  	free(nickname);
	  	free(username);
	  	free(host);
	  	free(server);

	   	break;

	case MOTD:

	   break;

	case IRCERR_UNKNOWNCOMMAND:

           break;

	default:
	   break;

    }

}

/***************************************************************************************************/
/***************************************************************************************************/
/** **/
/** MMMMMMMMMM               MMMMM           AAAAAAA           IIIIIII
 * NNNNNNNNNN          NNNNNN **/
/**  MMMMMMMMMM             MMMMM            AAAAAAAA           IIIII
 * NNNNNNNNNN          NNNN  **/
/**   MMMMM MMMM           MM MM            AAAAA   AA           III     NNNNN
 * NNNN          NN   **/
/**   MMMMM  MMMM         MM  MM            AAAAA   AA           III     NNNNN
 * NNNN         NN   **/
/**   MMMMM   MMMM       MM   MM           AAAAA     AA          III     NNNNN
 * NNNN        NN   **/
/**   MMMMM    MMMM     MM    MM           AAAAA     AA          III     NNNNN
 * NNNN       NN   **/
/**   MMMMM     MMMM   MM     MM          AAAAA       AA         III     NNNNN
 * NNNN      NN   **/
/**   MMMMM      MMMM MM      MM          AAAAAAAAAAAAAA         III     NNNNN
 * NNNN     NN   **/
/**   MMMMM       MMMMM       MM         AAAAA         AA        III     NNNNN
 * NNNN    NN   **/
/**   MMMMM        MMM        MM         AAAAA         AA        III     NNNNN
 * NNNN   NN   **/
/**   MMMMM                   MM        AAAAA           AA       III     NNNNN
 * NNNN  NN   **/
/**   MMMMM                   MM        AAAAA           AA       III     NNNNN
 * NNNN NN   **/
/**  MMMMMMM                 MMMM     AAAAAA            AAAA    IIIII   NNNNNN
 * NNNNNNN  **/
/** MMMMMMMMM               MMMMMM  AAAAAAAA           AAAAAA  IIIIIII NNNNNNN
 * NNNNNNN **/
/** **/
/***************************************************************************************************/
/***************************************************************************************************/

int main(int argc, char *argv[]) {
  /* La función IRCInterface_Run debe ser llamada al final      */
  /* del main y es la que activa el interfaz gráfico quedándose */
  /* en esta función hasta que se pulsa alguna salida del       */
  /* interfaz gráfico.                                          */

printf("Run\n");

  IRCInterface_Run(argc, argv);

  return 0;
}
