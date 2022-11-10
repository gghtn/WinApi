#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
//CCore* CCore::g_pInst = nullptr;

CCore::CCore():
	m_hWnd(0),
	m_ptResolution{},
	m_hdc(0)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hdc);
}

CObject g_obj;
bool CCore::Init(HWND hWnd, POINT ptResolution)
{
	m_hWnd = hWnd;
	m_ptResolution = ptResolution;

	// ���ϴ� �ػ� (Ŭ���̾�Ʈ â)
	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};
	// ���ϴ� �ػ󵵸� ���߱� ���� �������� ��ü ũ��� rt �缳��
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
	// ������â �缳��
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hdc = GetDC(m_hWnd);	// DC ����

	// Mgr �ʱ�ȭ
	CTimeMgr::GetInstance()->Init();


	g_obj.SetPos(Vec2((float)m_ptResolution.x / 2, (float)m_ptResolution.y / 2));
	g_obj.SetScale(Vec2(100, 100));

	return true;
}

void CCore::Progress()
{
	// TimeMgr update
	CTimeMgr::GetInstance()->Update();

	Update();

	Render();
}

void CCore::Update()
{
	Vec2 curPos = g_obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		curPos.x -= 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		curPos.x += 1;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		curPos.y -= 1;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		curPos.y += 1;
	}

	g_obj.SetPos(curPos);
}

void CCore::Render()
{
	Vec2 curPos = g_obj.GetPos();
	Vec2 curScale = g_obj.GetScale();
	Rectangle(m_hdc,
		(int)curPos.x - curScale.x / 2.f,
		(int)curPos.y - curScale.y / 2.f,
		(int)curPos.x + curScale.x / 2.f,
		(int)curPos.y + curScale.y / 2.f);
}
