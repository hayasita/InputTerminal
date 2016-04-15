#include "InputTerminal.h"

//#include <memory.h>
#define OK 1
#define NG 0

InputTerminal::InputTerminal(unsigned char *input_terminal, unsigned char terminal_num)
{
	unsigned char i;

	err = ITERR_NON;						// エラー情報クリア
	
	if (terminal_num < 16){
		Tm_num = terminal_num;
#ifndef TM_PIN_NUM
		Tm_Pin = new unsigned char[terminal_num];
#endif

		for (i = 0; i<Tm_num; i++){
			Tm_Pin[i] = input_terminal[i];
			pinMode(Tm_Pin[i], INPUT_PULLUP);	// 入力プルアップ設定
			//		printf("pin %d:%d:%d\n", i, Tm_Pin[i],input_terminal[i]);

		}
		//	memcopy(Tm_Pin,input_terminal,sizeof(input_terminal));
	}
	else{
		Tm_num = 0;
		err = ITERR_KEYNUM;						// キー設定数オーバー
	}


	keychktim_shortw = IT_KEYCHKTIM_SHORT;
	keychktim_longw = IT_KEYCHKTIM_LONG;
	
	shorton_keydataw = 0;
	longon_keydataw = 0;
	keydat = 0;
	
	return;
}

InputTerminal::~InputTerminal(void)
{

#ifndef TM_PIN_NUM
	delete[] Tm_Pin;
#endif

	return;
}


void InputTerminal::view_pin(void)
{
	unsigned char i;

	Serial.print("pin_num:");
	Serial.println(Tm_num);

	for (i = 0; i < Tm_num; i++){
		Serial.print("pin ");
		Serial.print(i);
		Serial.print(":");
		Serial.println(Tm_Pin[i]);
	}

	return;
}

// キー入力ポート状態（瞬時）作成
unsigned int InputTerminal::makekeydata(void)
{
	unsigned char i;

	keydat = 0;
	
	for (i = 0; i<Tm_num; i++){
		keydat |= ((!(unsigned int)digitalRead(Tm_Pin[i])) << i);
	}

	return (keydat);
}

void InputTerminal::scan(void)
{

	unsigned int keydatw;              // キー入力データ（瞬時値）
	static unsigned int keydat_lastw;  // キー入力データ（前回値）
	static unsigned char keychkw;       // キー入力判定許可不許可フラグ

	keydatw = makekeydata();        // キーの瞬時状態読み込み

	if (((shorton_keydataw == 0) && (longon_keydataw == 0) // 前回キー入力処理完了済み
		&& (keydatw == 0) && (keydat_lastw == 0))        // キー入力データなし
//		|| (keymode == KEY_RESET)
		) {                       // リセット時呼び出し準備
		keychkw = OK;                                          // キー入力判定許可
		itm_starttiml = millis();                              // キー入力時間情報初期化
		// キー入力が行われるまで毎回ここで初期化する。
	}
	else {}

	if (keychkw == OK) {
		if (keydatw == keydat_lastw) {               // キー押され中
			if ((millis() - itm_starttiml) >= (unsigned long)keychktim_longw) {   // 長押し判定時間　長押しはON中に判定
				longon_keydataw = keydat_lastw;                    // 長押しキー入力情報確定
				keychkw = NG;                                      // キー入力不可とする
			}
		}
		else if (keydatw < keydat_lastw) {           // 前回から押されているキーが減った = OFFエッジ発生
			// 複数短ON判定は、押されているキーが減った時点で判定する。（OFFタイミングがずれただけと解釈）
			if ((millis() - itm_starttiml) >= (unsigned long)keychktim_shortw) {  // 短押し判定時間。　短押しはOFFエッジで判定
				shorton_keydataw = keydat_lastw;                   // 短押しキー入力情報確定
				keychkw = NG;                                      // キー入力不可とする
				// 複数同時押し時にキーが一つずつOFFとなった場合、残ったキーのみで
				// 再判定しないように、全OFFするまでキー入力判定を不可とする。
			}
			else {}

			itm_starttiml = millis();                              // キー入力時間情報初期化
		}
		else { // 前回から押されているキーが増えた
			// 複数ON時は、押されたキーが増えた時点から再カウント
			itm_starttiml = millis();                              // キー入力時間情報初期化
		}

	}
	else {
		itm_starttiml = millis();                              // キー入力時間情報初期化
	}
			
	keydat_lastw = keydatw;          // 前回値保持
	return;

	return;
}


unsigned int InputTerminal::read(void)
{
	unsigned int ret;
	
	ret = read_s() | read_l();
	
	return(ret);

}


unsigned int InputTerminal::read_s(void)
{
	unsigned int ret;
	
	ret = shorton_keydataw;
	shorton_keydataw = 0;
	
	return(ret);

}

unsigned int InputTerminal::read_l(void)
{
	unsigned int ret;
	
	ret = longon_keydataw;
	longon_keydataw = 0;
	
	return(ret);

}

unsigned char InputTerminal::read_tmnum(void)
{
	return(Tm_num);
}

unsigned char InputTerminal::read_err(void)
{
	return(err);
}


