#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"

int g_arrVK[(int)KEY::LAST]	// KEY�� �����ϴ� ���� ��
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

	//������ ��Ŀ�� �˾Ƴ���
	//HWND hMainWnd = CCore::GetInstance()->GetMainHwnd();
	HWND hWnd = GetFocus();

	// ���� �����찡 ��Ŀ�� ���� ��
	if(hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; i++) {

			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000) // Ű�� ������ ��
			{
				if (m_vecKey[i].bPrevPush)	// ������ ��������
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else                       // ������ �ȴ�������
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrevPush = true;
			}
			else                            // Ű�� �ȴ����� ��
			{
				if (m_vecKey[i].bPrevPush)	// ������ ��������
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else                        // ������ �ȴ�������
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevPush = false;
			}
		}
	}
	// ��Ŀ�� ���� ���� (â�� ������ ���� �� Ű�� �Է��ص� �������� �ʵ���)
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
