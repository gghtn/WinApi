#pragma once

// 프로그램의 중심이 되는 Core 클래스
// 싱글톤 패턴 -> 객체의 생성을 1개로 제한 -> private로 생성자 감춤 -> static 멤버 함수로 접근
// 어디서는 접근 가능

// 1. 동적 할당방식의 싱글톤 패턴
//class CCore
//{
//private:
//	static CCore* g_pInst;
//
//public:
//	// 정적 멤버 함수 -> 객체의 멥버에는 접근 불가(this가 없음), 정적 멤버에는 접근 가능
//	static CCore* GetInstance() 
//	{
//		// 최초 호출시에만 생성
//		if (g_pInst == nullptr) 
//		{
//			g_pInst = new CCore;
//		}
//
//		return g_pInst;
//	}
//
//	// 동적 할당된 포인터 해제
//	static void Release() 
//	{
//		if(g_pInst != nullptr)
//		delete g_pInst;
//		g_pInst = nullptr;
//	}
//
//private:
//	// 외부에서 생성자 접근 불가
//	CCore();
//	~CCore();
//};

// 2. 데이터 영역에 객체를 생성 (정적으로)
// 장점: 코드가 직관적으로 보기 쉽고 해제가 필요하지 않다.
// 단점: 원할 때 해제하고 생성하지 못하기 때문에 프로그램이 종료될 때까지 남아있다.
class CCore {
	SINGLE(CCore);
	/* SINGLE(CCore) 매크로
	static CCore* GetInstance()
	{
		static CCore core;

		return &core;
	}*/
private:
	void Update();
	void Render();

private:
	HWND	m_hWnd;			// 메인 윈도우 핸들
	POINT	m_ptResolution;	// 해상도
	HDC		m_hdc;			// 메인 윈도우에 그릴 dc

public:
	bool Init(HWND hWnd, POINT ptResolution);
	void Progress();	// 게임(프로그램) 진행 
};
