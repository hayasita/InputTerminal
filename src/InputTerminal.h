#ifndef InputTerminal_h
#define InputTerminal_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#define IT_KEYCHKTIM_SHORT	100    // 100ms　キー短押し判定時間
#define IT_KEYCHKTIM_LONG	600    // 600ms　キー長押し判定時間

#define ITERR_NON		0x00		// エラーなし
#define ITERR_KEYNUM	0x01		// キー設定数オーバー

//#define TM_PIN_NUM	16			// 最大のキー入力数。未定義の場合は動的確保する。メモリ使用量を最適化したい場合は定義する。

class InputTerminal
{
public:
	InputTerminal(unsigned char *,unsigned char);		// コンストラクタ　入力キー設定
	~InputTerminal(void);					// デコンストラクタ　終了処理
	void scan(void);						// 入力判別実行
	unsigned int read(void);				// 長押し・短押し区別なし判定読み出し
	unsigned int read_s(void);				// 短押し判定読み出し
	unsigned int read_l(void);				// 長押し判定読み出し
	
	void set_keychktim_s(unsigned int);		// 短押し判定時間設定
	void set_keychktim_l(unsigned int);		// 長押し判定時間設定
	unsigned char read_tmnum(void);			// 設定されている入力キーの数を返す。
	unsigned char read_err(void);			// エラー情報を返す。

	void view_pin(void);					//	デバッグ用。コンストラクタで登録したピンの確認


private:
	unsigned char err;						// エラー情報

#ifdef TM_PIN_NUM
	unsigned char Tm_Pin[TM_PIN_NUM];		// 入力キー設定
#else
	unsigned char *Tm_Pin;
#endif	
	unsigned char Tm_num;					// 入力キー設定数

	unsigned int keydat;					// 入力キー情報
	unsigned long itm_starttiml;			// キー入力処理カウンタ保持
	unsigned int keychktim_shortw;			// キー短押し判定時間
	unsigned int keychktim_longw;			// キー長押し判定時間

	unsigned int shorton_keydataw; 			// キー短押し情報
	unsigned int longon_keydataw;			// キー長押し情報

	unsigned int makekeydata(void);			// キー入力情報作成

//	unsigned long millis(void);				// ダミー


};

#endif