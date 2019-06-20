#include "StdAfx.h"

namespace ui 
{

AutoClip::AutoClip(IRenderContext* pRender, const CRect& rc, bool bClip)
{
	m_pRender = NULL;
	m_bClip = false;

	if (bClip)
	{
		m_bClip = bClip;
		assert(pRender);
		m_pRender = pRender;
		m_pRender->SetClip(rc);
	}
}

AutoClip::AutoClip(IRenderContext* pRender, const CRect& rcRound, int width, int height, bool bClip)
{
	m_pRender = NULL;
	m_bClip = false;

	if (bClip)
	{
		m_bClip = bClip;
		assert(pRender);
		m_pRender = pRender;
		m_pRender->SetRoundClip(rcRound, width, height);
	}
}

AutoClip::~AutoClip()
{
	if (m_bClip && m_pRender)
		m_pRender->ClearClip();
}

}