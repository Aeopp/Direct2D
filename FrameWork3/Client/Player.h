#pragma once
#include <vector>

class CPlayer final
{
private:
	explicit CPlayer();
	virtual ~CPlayer();
public :
	HRESULT Ready_GameObject(); 
	void Update_GameObject();
	void LateUpdate_GameObject();
	void Render_GameObject(HDC hDC);
	void Release_GameObject();

private:
	D3DXVECTOR3 WorldLocation{};
	std::vector<D3DXVECTOR3> LocalPosVec;
	float RotationSpeed;
public :
	static CPlayer* Create(); 
	void Free(); 
};

