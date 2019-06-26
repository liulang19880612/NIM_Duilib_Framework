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
	* 一下三个接口是必须要覆写的接口，父类会调用这三个接口来构建窗口
	* GetSkinFolder		    接口设置你要绘制的窗口皮肤资源路径
	* GetSkinFile			接口设置你要绘制的窗口的 xml 描述文件
	* GetWindowClassName	接口设置窗口唯一的类名称
	*/
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	/**
	* 收到 WM_CREATE 消息时该函数会被调用，通常做一些控件初始化的操作
	*/
	virtual void InitWindow() override;

	/**
	* 收到 WM_CLOSE 消息时该函数会被调用
	*/
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	/**
	* @brief 窗口功能按钮被点击时调用
	* @param[in] param 携带的参数
	* @return 始终返回 true
	*/

	bool OnButtonClick(ui::EventArgs* param);
	static const std::wstring kClassName;
	/**
	* @brief 当要创建的控件不是标准的控件名称时会调用该函数
	* @param[in] pstrClass 控件名称
	* @return 返回一个自定义控件指针，一般情况下根据 pstrClass 参数创建自定义的控件
	*/
	virtual ui::Control* CreateControl(const std::wstring& pstrClass);
protected:
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	//定义托盘图标对象
	NOTIFYICONDATA m_trayIcon;
	//添加托盘图标(初始化)
	void AddTrayIcon();
	//处理托盘图标上的事件
	LRESULT OnTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

