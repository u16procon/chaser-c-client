/********************************************************
*
* U-16旭川プロコン通信用C言語ヘッダファイル
* Linuxでの動作を想定(実装はMax OS X 10.9.2)
*
********************************************************/

#ifndef _ASAHIKAWA_PROCONCONNECT__
	#define _ASAHIKAWA_PROCONCONNECT__

	#define HOTPORT    (2010) /* hotのポート番号 */
	#define COOLPORT   (2009) /* coolのポート番号 */
	#define NAME_MAX   (8)
	#define VALUE_SIZE (11)

	void initConnect(const char *ipadr, const int port, const char* name); /* (1)(2) */
	void coolConnect(const char* name);/* initConnect(COOLPORT, char　name[]); */
	void hotConnect (const char* name);/* initConnect(HOTPORT,  char　name[]); */

	void getReady(void); /* GetReady();(3))(4) */
	char value[VALUE_SIZE]; /* (4) */
	int checkEnd(void); /* infunction (8) */

	void walkRight(void); /* wr (5) */
	void walkLeft (void); /* wl (5) */
	void walkUp   (void); /* wu (5) */
	void walkDown (void); /* wd (5) */

	void lookRight(void); /* lr (5) */
	void lookLeft (void); /* ll (5) */
	void lookUp   (void); /* lu (5) */
	void lookDown (void); /* ld (5) */

	void searchRight(void); /* sr (5) */
	void searchLeft (void); /* sl (5) */
	void searchUp   (void); /* su (5) */
	void searchDown (void); /* sd (5) */

	void putRight(void); /* pr (5) */
	void putLeft (void); /* pl (5) */
	void putUp   (void); /* pu (5) */
	void putDown (void); /* pd (5) */

	void endTurn (void); /* (6), (7) */
	int  endGame (void); /* ゲーム終了時に返す感じで */

	#include "proConnect.c"
#endif