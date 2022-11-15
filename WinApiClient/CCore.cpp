#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
//CCore* CCore::g_pInst = nullptr;

CCore::CCore():
	m_hWnd(0),
	m_ptResolution{},
	m_hdc(0),
	m_hBit(0),
	m_memDC(0)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hdc);
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

CObject g_obj;
bool CCore::Init(HWND hWnd, POINT ptResolution)
{
	m_hWnd = hWnd;
	m_ptResolution = ptResolution;

	// 원하는 해상도 (클라이언트 창)
	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};
	// 원하는 해상도를 맞추기 위한 윈도우의 전체 크기로 rt 재설정
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
	// 윈도우창 재설정
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hdc = GetDC(m_hWnd);	// DC 생성

	// Mgr 초기화
	CTimeMgr::GetInstance()->Init();

	// 이중 버퍼링, memDC가 가진 비트맵을 교체할 비트맵 생성
	m_hBit = CreateCompatibleBitmap(m_hdc, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hdc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);	// 원래 가진 비트맵 삭제


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
	float DeltaTime = CTimeMgr::GetInstance()->GetDT();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		curPos.x -= 300 * DeltaTime;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		curPos.x += 300 * DeltaTime;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		curPos.y -= 300 * DeltaTime;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		curPos.y += 300 * DeltaTime;
	}

	g_obj.SetPos(curPos);
}

void CCore::Render()
{
	Rectangle(m_memDC, -1, -1, m_ptResolution.x, m_ptResolution.y);
	
	Vec2 curPos = g_obj.GetPos();
	Vec2 curScale = g_obj.GetScale();

	Rectangle(m_memDC,
		(int)curPos.x - curScale.x / 2.f,
		(int)curPos.y - curScale.y / 2.f,
		(int)curPos.x + curScale.x / 2.f,
		(int)curPos.y + curScale.y / 2.f);

	BitBlt(m_hdc, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
}
