
// face503Dlg.h : ͷ�ļ�
//

#pragma once
#include "cv.h"
#include "highgui.h"
//#include "CvvImage.h"

#include <vector>

using namespace cv;

// Cface503Dlg �Ի���
class Cface503Dlg : public CDialogEx
{
// ����
public:
	Cface503Dlg(CWnd* pParent = NULL);	// ��׼���캯��


// �Ի�������
	enum { IDD = IDD_FACE503_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	IplImage* m_pImgSrc;


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HRESULT ShowPic(CDC *pDC,CString lpstrFile,int x,int y, int nScrWidth, int nScrHeight);
	afx_msg void OnBnClickedOpenPic();
	afx_msg void OnBnClickedButton2();
};
