#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_lCurCount;
	LARGE_INTEGER	m_lPrevCount;
	LARGE_INTEGER	m_lFrequency;

	float			m_dDT;
	float			m_dAcc;
	UINT			m_nSCount;
	UINT			m_nFPS;
public:
	void Init();
	void Update();
	float GetDT() { return m_dDT; }
};

