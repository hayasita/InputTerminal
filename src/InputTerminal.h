#ifndef InputTerminal_h
#define InputTerminal_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#define IT_KEYCHKTIM_SHORT	100    // 100ms�@�L�[�Z�������莞��
#define IT_KEYCHKTIM_LONG	600    // 600ms�@�L�[���������莞��

#define ITERR_NON		0x00		// �G���[�Ȃ�
#define ITERR_KEYNUM	0x01		// �L�[�ݒ萔�I�[�o�[

//#define TM_PIN_NUM	16			// �ő�̃L�[���͐��B����`�̏ꍇ�͓��I�m�ۂ���B�������g�p�ʂ��œK���������ꍇ�͒�`����B

class InputTerminal
{
public:
	InputTerminal(unsigned char *,unsigned char);		// �R���X�g���N�^�@���̓L�[�ݒ�
	~InputTerminal(void);					// �f�R���X�g���N�^�@�I������
	void scan(void);						// ���͔��ʎ��s
	unsigned int read(void);				// �������E�Z������ʂȂ�����ǂݏo��
	unsigned int read_s(void);				// �Z��������ǂݏo��
	unsigned int read_l(void);				// ����������ǂݏo��
	
	void set_keychktim_s(unsigned int);		// �Z�������莞�Ԑݒ�
	void set_keychktim_l(unsigned int);		// ���������莞�Ԑݒ�
	unsigned char read_tmnum(void);			// �ݒ肳��Ă�����̓L�[�̐���Ԃ��B
	unsigned char read_err(void);			// �G���[����Ԃ��B

	void view_pin(void);					//	�f�o�b�O�p�B�R���X�g���N�^�œo�^�����s���̊m�F


private:
	unsigned char err;						// �G���[���

#ifdef TM_PIN_NUM
	unsigned char Tm_Pin[TM_PIN_NUM];		// ���̓L�[�ݒ�
#else
	unsigned char *Tm_Pin;
#endif	
	unsigned char Tm_num;					// ���̓L�[�ݒ萔

	unsigned int keydat;					// ���̓L�[���
	unsigned long itm_starttiml;			// �L�[���͏����J�E���^�ێ�
	unsigned int keychktim_shortw;			// �L�[�Z�������莞��
	unsigned int keychktim_longw;			// �L�[���������莞��

	unsigned int shorton_keydataw; 			// �L�[�Z�������
	unsigned int longon_keydataw;			// �L�[���������

	unsigned int makekeydata(void);			// �L�[���͏��쐬

//	unsigned long millis(void);				// �_�~�[


};

#endif