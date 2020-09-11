#include "stdafx.h"
#include "Player.h"
#include <algorithm>
#include <cmath>
CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	
}

HRESULT CPlayer::Ready_GameObject()
{
	LocalPosVec.resize(4);
	LocalPosVec[0] = { -100,100  , 0};
	LocalPosVec[1] = { 100,100,0 };
	LocalPosVec[2] = { 100,-100,0 };
	LocalPosVec[3] = { -100,-100,0 };

	WorldLocation = { 400,300 , 0 };
	
	RotationSpeed = 3.141592 / 100;
	
	return S_OK;
}

void CPlayer::Update_GameObject()
{
	float Speed = 10.f;
	
	if (GetAsyncKeyState('A') & 0x8000)
		WorldLocation += D3DXVECTOR3{ -Speed,0,0 };
	if (GetAsyncKeyState('D') & 0x8000)
		WorldLocation += D3DXVECTOR3{ +Speed,0,0 };
	if (GetAsyncKeyState('S') & 0x8000)
		WorldLocation += D3DXVECTOR3{  0 , +Speed,0 };
	if (GetAsyncKeyState('W') & 0x8000)
		WorldLocation += D3DXVECTOR3{ 0,-Speed,0 };

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		RotationSpeed = abs(RotationSpeed) * -1;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		RotationSpeed = abs(RotationSpeed);
}

void CPlayer::LateUpdate_GameObject()
{
	if (LocalPosVec.empty())return;


	/*
	 * 
	 *  sin(a+b) = sina cosb + cosa sinb
		cos (a+b ) = cosacosb - sinasinb
	 */
	D3DXVECTOR3 beta{ std::cosf(RotationSpeed),std::sinf(RotationSpeed) , 0 };

	for (auto& alpha : LocalPosVec)
	{
		float x = alpha.x * beta.x - alpha.y * beta.y;
		float y = alpha.y * beta.x + alpha.x * beta.y;

		alpha.x = x;
		alpha.y = y;
	}
}

void CPlayer::Render_GameObject(HDC hDC)
{
	D3DXVECTOR3 _WorldLocation = WorldLocation;
	
	auto RenderPosVec = LocalPosVec;
	
	std::for_each(std::begin(RenderPosVec), std::end(RenderPosVec),
		[_WorldLocation](D3DXVECTOR3& Pos)
		{
		Pos += _WorldLocation;
		});
	if (RenderPosVec.empty())return;
	D3DXVECTOR3 Start = RenderPosVec.front();
	
	MoveToEx(hDC, Start.x, Start.y, nullptr);
	for(auto iter = std::next(RenderPosVec.begin());
		iter != std::end(RenderPosVec ) ;++iter)
	{
		D3DXVECTOR3 CurrentPos = *iter;
		LineTo(hDC, CurrentPos.x, CurrentPos.y);
	}

	LineTo(hDC, Start.x, Start.y);
}

void CPlayer::Release_GameObject()
{
	
}

CPlayer * CPlayer::Create()
{
	CPlayer* pInstance = new CPlayer; 
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance; 
		pInstance = nullptr; 
	}
	return pInstance;
}

void CPlayer::Free()
{
}
