#ifndef UI_CORE_RENDER_H_
#define UI_CORE_RENDER_H_

#pragma once

namespace ui 
{

class UILIB_API RenderContext_GdiPlus : public IRenderContext
{
public:
	RenderContext_GdiPlus();
	virtual ~RenderContext_GdiPlus();

	virtual HDC GetDC() override;
	virtual bool Resize(int width, int height, bool flipBItmap = true) override;
	virtual void Clear() override;
	virtual std::unique_ptr<IRenderContext> Clone() override;

	virtual HBITMAP DetachBitmap() override;
	virtual BYTE* GetBits() override;
	virtual int	GetWidth() override;
	virtual int GetHeight() override;
	virtual void ClearAlpha(const CRect& rcDirty, int alpha = 0) override;
	virtual void RestoreAlpha(const CRect& rcDirty, const CRect& rcShadowPadding = CRect(), int alpha = 0) override;

	virtual bool IsRenderTransparent() const override;
	virtual bool SetRenderTransparent(bool bTransparent) override;

	virtual void Save() override;
	virtual void Restore() override;

	virtual CPoint OffsetWindowOrg(CPoint ptOffset) override;
	virtual CPoint SetWindowOrg(CPoint ptOffset) override;
	virtual CPoint GetWindowOrg() const override;

	virtual void SetClip(const CRect& rc) override;
	virtual void SetRoundClip(const CRect& rc, int width, int height) override;
	virtual void ClearClip() override;

	virtual HRESULT BitBlt(int x, int y, int cx, int cy, HDC hdcSrc, int xSrc = 0, int yScr = 0, DWORD rop = SRCCOPY) override;
	virtual bool AlphaBlend(int xDest, int yDest, int widthDest, int heightDest, HDC hdcSrc, int xSrc, int yScr, int widthSrc, int heightSrc, BYTE uFade = 255) override;

	virtual void DrawImage(const CRect& rcPaint, HBITMAP hBitmap, bool bAlphaChannel,
		const CRect& rcImageDest, const CRect& rcImageSource, const CRect& rcCorners, BYTE uFade = 255, bool xtiled = false, bool ytiled = false) override;

	virtual void DrawColor(const CRect& rc, DWORD dwColor, BYTE uFade = 255) override;
	virtual void DrawColor(const CRect& rc, const std::wstring& colorStr, BYTE uFade = 255) override;

	virtual void DrawLine(const CRect& rc, int nSize, DWORD dwPenColor) override;
	virtual void DrawLine(const IPen* pen, int x1, int y1, int x2, int y2) override;
	virtual void DrawBezier(const IPen* pen, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
	virtual void DrawRect(const CRect& rc, int nSize, DWORD dwPenColor) override;
	virtual void DrawText(const CRect& rc, const std::wstring& strText, DWORD dwTextColor, int iFont, UINT uStyle, BYTE uFade = 255, bool bLineLimit = false) override;

	virtual void DrawEllipse(const CRect& rc, int nSize, DWORD dwColor) override;
	virtual void FillEllipse(const CRect& rc, DWORD dwColor) override;

	virtual CRect MeasureText(const std::wstring& strText, int iFont, UINT uStyle, int width = DUI_NOSET_VALUE) override;

	virtual void DrawPath(const IPath* path, const IPen* pen) override;
	virtual void FillPath(const IPath* path, const IBrush* brush) override;

private:
	HDC			m_hDC;
	int			m_saveDC;
	HBITMAP		m_hOldBitmap;

	bool		m_bTransparent;
	GdiClip		m_clip;
	GdiBitmap	m_bitmap;
};

} // namespace ui

#endif // UI_CORE_RENDER_H_
