#include "stdafx.h"
#include "MainGame.h"

#include "Camera.h"
#include "Grid.h"

#include "Lobby.h"

#include "ObjectLoader.h"
#include "MtlTex.h"

#include "XFileLoader.h"

//======================================
// - ## 09.29.17 ##
// - written by �輱ȣ
// - MainGame -> ���ӽ���
//======================================

MainGame::MainGame()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
{
}

MainGame::~MainGame()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pLobby);
}

void MainGame::Setup()
{
	/*   ī�޶� ����   */
	m_pCamera = new Camera;
	m_pCamera->Setup(NULL);

	/*   �׸��� ����   */
	m_pGrid = new Grid;
 	m_pGrid->Setup();

	m_pLobby = new Lobby;
	m_pLobby->Setup();

	//Setup_Object();
}

void MainGame::Update()
{
	if(m_pCamera)
		m_pCamera->Update();
	if (m_pLobby)
		m_pLobby->Update();
}

void MainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		1.0F, 0);
	g_pD3DDevice->BeginScene();
	// �׸��� ����
	m_pGrid->Render();
	m_pLobby->Render();
	// �׸��� ����
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void MainGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(m_pCamera)
		m_pCamera->WndProc(hWnd, msg, wParam, lParam);
}

void MainGame::Setup_Object()
{
	ObjectLoader loader;
	m_pObjMesh = loader.LoadMesh(
		m_vecObjMtlTex,
		"map/lobby", "lobby1.obj");
}

void MainGame::Render_Object()
{

	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16	matWorld, matS, matR;

	D3DXMatrixIdentity(&matWorld);
	{

	}

	g_pD3DDevice->SetTransform(D3DTS_WORLD,
		&matWorld);

	for (size_t i = 0; i < m_vecObjMtlTex.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(
			&m_vecObjMtlTex[i]->GetMaterial());

		g_pD3DDevice->SetTexture(
			0,
			m_vecObjMtlTex[i]->GetTexture());
		m_pObjMesh->DrawSubset(i);
	}

}



