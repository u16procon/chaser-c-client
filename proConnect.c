/*****************************************
*
* U-16旭川プロコン通信用関数群
* Linuxでの動作を想定(実装はMax OS X 10.9.2)
*
*****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <netdb.h>
#include <unistd.h>
#include "proConnect.h"

#define BUF_SIZE  (20)       /* 決めうち */
#define SERVERRV  ("@")      /* サーバの接続確認でぶん投げる文字 */
#define SERVEREN  ("#\r\n")  /* 1ターン終了時にぶん投げる文字 */

#define SOCKETOUT     (-1)
#define CONNECTOUT  (-2)

struct sockaddr_in server;	/* ソケット型の宣言  */
int	sct;	       	        /* ソケット用       */
char	hostadd[16];	    /* サーバアドレス    */
struct hostent *host;
char	hostport[6];	    /* サーバ用ポート番号 */

void printValues(void){int i;for(i = 0; i < VALUE_SIZE - 1; ++i)printf("%d", value[i]);printf("\n");}

void initConnect(const char *ipadr,const int port, const char* name){
	char* buf = malloc (sizeof(name) + sizeof("\r\n"));

	host = gethostbyname(ipadr);
	sct = socket(AF_INET, SOCK_STREAM, 0);
	if(sct == -1){
		perror("接続に失敗しました(scoket)\n");
		exit(SOCKETOUT);
	}

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	memcpy(&server.sin_addr.s_addr, host->h_addr, host->h_length); 
	server.sin_port = htons(port);                                 /* ポート番号の指定 */
	if(connect(sct, (struct sockaddr *)&server, sizeof(server)) == -1){
		perror("接続に失敗しました(connect)\n");
		exit(CONNECTOUT);
	}

	
	strncat(buf, name, NAME_MAX);
	send(sct, strcat(buf, "\r\n"), 5, 0);
	printf("Connect success : %d\n", port);
	value[0] = 1;
} /* (1)(2) */

//void coolConnect(const char* name){initConnect(COOLPORT, name);}/* initConnect(COOLPORT, char　name[]); */
//void hotConnect (const char* name){initConnect(HOTPORT,  name);}/* initConnect(HOTPORT,  char　name[]); */

void getReady(void){
	char buf[BUF_SIZE];
	int i, n;
	do{
		if(value[0] != 0)
			n = recv(sct, buf, sizeof(buf), 0);
		else
			break;
		if(value[0] == '0')
			break;
		if(n == -1){
			printf("受信に失敗しました\n");
			sleep(5 * 100);
			continue;
		}
		else if(n == 0)
			abort();
	}while(buf[0] != '@' && (printf("サーバからの応答を待っています(現在の受信文字列 : %c)\n", buf[0]), 1));
	if(value[0] != 0){
		n = send(sct, "gr\r\n", strlen("gr\r\n"), 0);
		if(n == 0)
			abort();
		recv(sct, value, BUF_SIZE, 0);
		if(n == 0)
			abort();
		value[VALUE_SIZE - 1] = '\0';
		for(i = 0; value[i] != '\0'; ++i)
			value[i] -= '0';
		printf("getReady : ");
		printValues();
	}
} /* GetReady();(3))(4) */

int checkEnd(void){
	if(value[0] == 0){
		printf("checkEnd : End\n");
		return -1;
	}
	else{
		printf("checkEnd : not End\n");
		return 1;
	}
} /* infunction (8) */

void walkRight(void){if(value[0] != 0){if(send(sct, "wr\r\n", strlen("wr\r\n"), 0) == 0) abort(); endTurn(); printf("walkRight : ");printValues();}} /* wr (5) */
void walkLeft (void){if(value[0] != 0){if(send(sct, "wl\r\n", strlen("wl\r\n"), 0) == 0) abort(); endTurn(); printf("walkLeft : "); printValues();}} /* wl (5) */
void walkUp   (void){if(value[0] != 0){if(send(sct, "wu\r\n", strlen("wu\r\n"), 0) == 0) abort(); endTurn(); printf("walkUp : ");   printValues();}} /* wu (5) */
void walkDown (void){if(value[0] != 0){if(send(sct, "wd\r\n", strlen("wd\r\n"), 0) == 0) abort(); endTurn(); printf("walkDown : ");printValues();}} /* wd (5) */

void lookRight(void){if(value[0] != 0){if(send(sct, "lr\r\n", strlen("lr\r\n"), 0) == 0) abort(); endTurn(); printf("lookRight : ");printValues();}} /* lr (5) */
void lookLeft (void){if(value[0] != 0){if(send(sct, "ll\r\n", strlen("ll\r\n"), 0) == 0) abort(); endTurn(); printf("lookLeft : "); printValues();}} /* ll (5) */
void lookUp   (void){if(value[0] != 0){if(send(sct, "lu\r\n", strlen("lu\r\n"), 0) == 0) abort(); endTurn(); printf("lookUp : ");   printValues();}} /* lu (5) */
void lookDown (void){if(value[0] != 0){if(send(sct, "ld\r\n", strlen("ld\r\n"), 0) == 0) abort(); endTurn(); printf("lookDown : "); printValues();}} /* ld (5) */

void searchRight(void){if(value[0] != 0){if(send(sct, "sr\r\n", strlen("sr\r\n"), 0) == 0) abort(); endTurn(); printf("searchRight : ");printValues();}} /* sr (5) */
void searchLeft (void){if(value[0] != 0){if(send(sct, "sl\r\n", strlen("sl\r\n"), 0) == 0) abort(); endTurn(); printf("searchLeft : "); printValues();}} /* sl (5) */
void searchUp   (void){if(value[0] != 0){if(send(sct, "su\r\n", strlen("su\r\n"), 0) == 0) abort(); endTurn(); printf("searchUp : ");   printValues();}} /* su (5) */
void searchDown (void){if(value[0] != 0){if(send(sct, "sd\r\n", strlen("sd\r\n"), 0) == 0) abort(); endTurn(); printf("searchDown : "); printValues();}} /* sd (5) */

void putRight(void){if(value[0] != 0){if(send(sct, "pr\r\n", strlen("pr\r\n"), 0) == 0) abort(); endTurn(); printf("putRight : "); printValues();}} /* pr (5) */
void putLeft (void){if(value[0] != 0){if(send(sct, "ll\r\n", strlen("pl\r\n"), 0) == 0) abort(); endTurn(); printf("putLeft : ");  printValues();}} /* pl (5) */
void putUp   (void){if(value[0] != 0){if(send(sct, "pu\r\n", strlen("pu\r\n"), 0) == 0) abort(); endTurn(); printf("putUp : ");    printValues();}} /* pu (5) */
void putDown (void){if(value[0] != 0){if(send(sct, "pd\r\n", strlen("pd\r\n"), 0) == 0) abort(); endTurn(); printf("putDown : ");  printValues();}} /* pd (5) */

void endTurn (void){
	int i, n;
	if(value[0] != 0)
		n = recv(sct, value, BUF_SIZE, 0);
	if(n == 0)
		abort();
	value[10] = '\0';

	for(i = 0; value[i] != '\0'; ++i)
		value[i] -= '0';
	printf("\n");

	if(value[0] != 0)
		n = send(sct, SERVEREN, strlen(SERVEREN), 0);
	if(n == 0)
		abort();
} /* (6), (7) */

int endGame (void){return shutdown(sct, SHUT_RDWR);}

