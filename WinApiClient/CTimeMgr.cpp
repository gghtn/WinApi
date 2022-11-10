#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr() :
	m_lCurCount{},
	m_lPrevCount{},
	m_lFrequency{},
	m_dDT(0.0),
	m_dAcc(0.0),
	m_iSCount(0)
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
	m_dDT = (double)(m_lCurCount.QuadPart - m_lPrevCount.QuadPart) / (double)m_lFrequency.QuadPart;
	// ī��Ʈ ����
	m_lPrevCount = m_lCurCount;
	m_dAcc += m_dDT;

	if (m_dAcc >= 1.)
	{
		m_dAcc = 0.;
	}
}
