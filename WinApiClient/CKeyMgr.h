#pragma once

enum class KEY_STATE
{
	NONE,	// ������ �ʾҰ�, �������� ������ ���� ����
	TAP,	// ó�� ���� ����
	HOLD,	// ������ �ִ� ����
	AWAY,	// Ű�� �� ����
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ALT,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,
	A,
	S,
	D,
	F,
	Z,
	X,
	C,
	V,

	LAST //enum�� ��
};

struct KEY_INFO
{
	KEY_STATE	eState;
	bool		bPrevPush;	// ���� �����ӿ��� ���ȴ���
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<KEY_INFO> m_vecKey;

public:
	void Init();
	void Update();

	KEY_STATE GetKeyState(KEY eKey) { return m_vecKey[(int)eKey].eState; }
};

