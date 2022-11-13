#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr() :
	m_lCurCount{},
	m_lPrevCount{},
	m_lFrequency{},
	m_dDT(0.f),
	m_dAcc(0.f),
	m_nSCount(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	QueryPerformanceCounter(&m_lPrevCount);
	QueryPerformanceFrequency(&m_lFrequency);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_lCurCount);

	// ���� ī���� - ���� ī���� 
	m_dDT = (float)(m_lCurCount.QuadPart - m_lPrevCount.QuadPart) / (float)m_lFrequency.QuadPart;
	// ī��Ʈ ����
	m_lPrevCount = m_lCurCount;
	m_dAcc += m_dDT;
	m_nFPS++;

	if (m_dAcc >= 1.)
	{
		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS:%d  DT: %f", m_nFPS, m_dDT);
		SetWindowText(CCore::GetInstance()->GetMainHwnd(), szBuffer);//���� FPS�� DT â�� ǥ��

		m_dAcc = 0.;
		m_nFPS = 0;
	}
}
