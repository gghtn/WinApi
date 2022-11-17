#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"

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

	//윈도우 포커싱 알아내기
	//HWND hMainWnd = CCore::GetInstance()->GetMainHwnd();
	HWND hWnd = GetFocus();

	// 현재 윈도우가 포커싱 중일 때
	if(hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; i++) {

			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000) // 키가 눌렸을 때
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
	// 포커싱 해제 상태 (창이 내려가 있을 때 키를 입력해도 움직이지 않도록)
	else
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			m_vecKey[i].bPrevPush = false;

			if (m_vecKey[i].eState == KEY_STATE::AWAY)
			{
				m_vecKey[i].eState == KEY_STATE::NONE;
			}
			else if (m_vecKey[i].eState == KEY_STATE::TAP || m_vecKey[i].eState == KEY_STATE::HOLD)
			{
				m_vecKey[i].eState == KEY_STATE::AWAY;
			}
		}
	}
	

}
