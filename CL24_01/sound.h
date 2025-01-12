#pragma once

#include <xaudio2.h>

// �T�E���h�t�@�C��
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// �T���v��BGM
	SOUND_LABEL_BGM001,		// �T���v��BGM
	SOUND_LABEL_SE001,			// �T���v��SE
	SOUND_LABEL_SE002,			// �T���v��SE
	SOUND_LABEL_SEthrow,			// �T���v��SE
	SOUND_LABEL_SEhit1,			// �T���v��SE
	SOUND_LABEL_SEhit2,			// �T���v��SE
	SOUND_LABEL_SEhit3,			// �T���v��SE



	SOUND_LABEL_MAX,
} SOUND_LABEL;

class Sound {
private:
	// �p�����[�^�\����
	typedef struct
	{
		LPCSTR filename;	// �����t�@�C���܂ł̃p�X��ݒ�
		bool bLoop;			// true�Ń��[�v�B�ʏ�BGM��ture�ASE��false�B
	} PARAM;

	PARAM m_param[SOUND_LABEL_MAX] =
	{
		{"asset/BGM/y014.wav", true},	// �T���v��BGM�i���[�v������̂�true�ݒ�j
		{"asset/BGM/w001.wav", true},
		{"asset/SE/menu-button.wav", false},	// SE
		{"asset/SE/falled.wav", false}, // SE
		{"asset/SE/throw.wav", false}, // SE
		{"asset/SE/hit1.wav", false}, // SE
		{"asset/SE/hit2.wav", false}, // SE
		{"asset/SE/hit3.wav", false}, // SE
	};

	IXAudio2* m_pXAudio2 = NULL;
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;
	IXAudio2SourceVoice* m_pSourceVoice[SOUND_LABEL_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SOUND_LABEL_MAX]; // WAV�t�H�[�}�b�g
	XAUDIO2_BUFFER m_buffer[SOUND_LABEL_MAX];
	BYTE* m_DataBuffer[SOUND_LABEL_MAX];

	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

public:
	// �Q�[�����[�v�J�n�O�ɌĂяo���T�E���h�̏���������
	HRESULT Init(void);

	// �Q�[�����[�v�I����ɌĂяo���T�E���h�̉������
	void Uninit(void);

	// �����Ŏw�肵���T�E���h���Đ�����
	void Play(SOUND_LABEL label);

	// �����Ŏw�肵���T�E���h���~����
	void Stop(SOUND_LABEL label);

	// �����Ŏw�肵���T�E���h�̍Đ����ĊJ����
	void Resume(SOUND_LABEL label);

};