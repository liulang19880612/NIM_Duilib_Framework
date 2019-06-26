#pragma once

class PartitionLine : public ui::Control
{
public:
	PartitionLine(){ m_nLineMargin = 4; m_nLineStyle = LineStyle::V_Line; }
	virtual ~PartitionLine(){}
public:
	void Paint(ui::IRenderContext* pRender, const ui::CRect& rcPaint)
	{
		if (!::IntersectRect(&m_rcPaint, &rcPaint, &m_rcItem)) return;

		PaintBkColor(pRender);
		PaintBkImage(pRender);
		PaintStatusColor(pRender);
		PaintStatusImage(pRender);
		PaintPartitionLine(pRender);
		PaintBorder(pRender);
	}
	virtual void PaintPartitionLine(ui::IRenderContext* pRender)
	{
		ui::CPoint pt1, pt2;
		switch (m_nLineStyle)
		{
			case PartitionLine::H_Line:
			{
				pt1.x = m_rcPaint.left + m_nLineMargin; pt1.y = m_rcPaint.top + m_rcPaint.GetHeight() / 2;
				pt2.x = m_rcPaint.right - m_nLineMargin; pt2.y = m_rcPaint.top + m_rcPaint.GetHeight() / 2;
			}
			break;
			case PartitionLine::V_Line:
			{
				pt1.x = m_rcPaint.left + m_rcPaint.GetWidth() / 2; pt1.y = m_rcPaint.top + m_nLineMargin;
				pt2.x = m_rcPaint.left + m_rcPaint.GetWidth() / 2; pt2.y = m_rcPaint.bottom - m_nLineMargin;
			}
			break;
		}
		auto pPen  =  ui::GlobalManager::CreatePen(RGB(100, 100,100), 1);
		pRender->DrawLine(pPen.get(), pt1.x, pt1.y, pt2.x, pt2.y);
		pRender->DrawColor(m_rcPaint, RGB(100, 255, 100));
	}
	enum LineStyle
	{
		H_Line,
		V_Line
	};
protected:
	LineStyle             m_nLineStyle;
	int                   m_nLineMargin;
};
class CRAMainForm : public ui::WindowImplBase
{
public:
	CRAMainForm();
	~CRAMainForm();
public:
	/**
	* һ�������ӿ��Ǳ���Ҫ��д�Ľӿڣ����������������ӿ�����������
	* GetSkinFolder		    �ӿ�������Ҫ���ƵĴ���Ƥ����Դ·��
	* GetSkinFile			�ӿ�������Ҫ���ƵĴ��ڵ� xml �����ļ�
	* GetWindowClassName	�ӿ����ô���Ψһ��������
	*/
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	/**
	* �յ� WM_CREATE ��Ϣʱ�ú����ᱻ���ã�ͨ����һЩ�ؼ���ʼ���Ĳ���
	*/
	virtual void InitWindow() override;

	/**
	* �յ� WM_CLOSE ��Ϣʱ�ú����ᱻ����
	*/
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	/**
	* @brief ���ڹ��ܰ�ť�����ʱ����
	* @param[in] param Я���Ĳ���
	* @return ʼ�շ��� true
	*/

	bool OnButtonClick(ui::EventArgs* param);
	static const std::wstring kClassName;
	/**
	* @brief ��Ҫ�����Ŀؼ����Ǳ�׼�Ŀؼ�����ʱ����øú���
	* @param[in] pstrClass �ؼ�����
	* @return ����һ���Զ���ؼ�ָ�룬һ������¸��� pstrClass ���������Զ���Ŀؼ�
	*/
	virtual ui::Control* CreateControl(const std::wstring& pstrClass);
protected:
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	//��������ͼ�����
	NOTIFYICONDATA m_trayIcon;
	//�������ͼ��(��ʼ��)
	void AddTrayIcon();
	//��������ͼ���ϵ��¼�
	LRESULT OnTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

