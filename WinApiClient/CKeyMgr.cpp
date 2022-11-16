#include "pch.h"
#include "CKeyMgr.h"

int g_arrVK[(int)KEY::LAST]	// KEY에 대응하는 실제 값
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	VK_MENU,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,
	'A',
	'S',
	'D',
	'F',
	'Z',
	'X',
	'C',
	'V'
};

CKeyMgr::CKeyMgr()
{ 

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; i++) {
		m_vecKey.push_back(KEY_INFO{KEY_STATE::NONE, false});
	}
}

void CKeyMgr::Update()
{
	for (int i = 0; i < (int)KEY::LAST; i++) {
		
		if (GetAsyncKeyState(g_arrVK[i])& 0x8000) // 키가 눌렸을 때
		{
			if (m_vecKey[i].bPrevPush)	// 이전에 눌렸으면
			{
				m_vecKey[i].eState = KEY_STATE::HOLD;
			}
			else                       // 이전에 안눌렸으면
			{
				m_vecKey[i].eState = KEY_STATE::TAP;
			}

			m_vecKey[i].bPrevPush = true;
		}
		else                            // 키가 안눌렸을 때
		{
			if (m_vecKey[i].bPrevPush)	// 이전에 눌렸으면
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else                        // 이전에 안눌렸으면
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
			m_vecKey[i].bPrevPush = false;
		}
	}

}
