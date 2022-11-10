#pragma once

// ���α׷��� �߽��� �Ǵ� Core Ŭ����
// �̱��� ���� -> ��ü�� ������ 1���� ���� -> private�� ������ ���� -> static ��� �Լ��� ����
// ��𼭴� ���� ����

// 1. ���� �Ҵ����� �̱��� ����
//class CCore
//{
//private:
//	static CCore* g_pInst;
//
//public:
//	// ���� ��� �Լ� -> ��ü�� ������� ���� �Ұ�(this�� ����), ���� ������� ���� ����
//	static CCore* GetInstance() 
//	{
//		// ���� ȣ��ÿ��� ����
//		if (g_pInst == nullptr) 
//		{
//			g_pInst = new CCore;
//		}
//
//		return g_pInst;
//	}
//
//	// ���� �Ҵ�� ������ ����
//	static void Release() 
//	{
//		if(g_pInst != nullptr)
//		delete g_pInst;
//		g_pInst = nullptr;
//	}
//
//private:
//	// �ܺο��� ������ ���� �Ұ�
//	CCore();
//	~CCore();
//};

// 2. ������ ������ ��ü�� ���� (��������)
// ����: �ڵ尡 ���������� ���� ���� ������ �ʿ����� �ʴ�.
// ����: ���� �� �����ϰ� �������� ���ϱ� ������ ���α׷��� ����� ������ �����ִ�.
class CCore {
	SINGLE(CCore);
	/* SINGLE(CCore) ��ũ��
	static CCore* GetInstance()
	{
		static CCore core;

		return &core;
	}*/
private:
	void Update();
	void Render();

private:
	HWND	m_hWnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution;	// �ػ�
	HDC		m_hdc;			// ���� �����쿡 �׸� dc

public:
	bool Init(HWND hWnd, POINT ptResolution);
	void Progress();	// ����(���α׷�) ���� 
};