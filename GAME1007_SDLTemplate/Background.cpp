#include "Background.h"

void Background::Update()
{
	if (GetDst()->x <= m_endX)
		GetDst()->x = m_startX;

	// Scrolling
	GetDst()->x -= m_scrollSpeed;
}

void Background::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), TEMA::GetTexture("background"), GetSrc(), GetDst());
}
