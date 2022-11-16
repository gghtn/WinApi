#pragma once

enum class KEY_STATE
{
	NONE,	// 눌리지 않았고, 이전에도 눌리지 않은 상태
	TAP,	// 처음 누른 시점
	HOLD,	// 누르그 있는 상태
	AWAY,	// 키를 뗀 시점
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

	LAST //enum의 끝
};

struct KEY_INFO
{
	KEY_STATE	eState;
	bool		bPrevPush;	// 이전 프레임에서 눌렸는지
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

