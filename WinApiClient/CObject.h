#pragma once

class CObject
{
private:
	Vec2	m_ptPos;
	Vec2	m_ptScale;

public:
	CObject();
	~CObject();

	void SetPos(Vec2 vPos) { m_ptPos = vPos; }
	void SetScale(Vec2 vScale) { m_ptScale = vScale; }

	Vec2 GetPos() { return m_ptPos; }
	Vec2 GetScale() { return m_ptScale; }

};

