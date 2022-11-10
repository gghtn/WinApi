#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_lCurCount;
	LARGE_INTEGER	m_lPrevCount;
	LARGE_INTEGER	m_lFrequency;

	double			m_dDT;
	double			m_dAcc;
	UINT			m_iSCount;
public:
	void Init();
	void Update();
};

