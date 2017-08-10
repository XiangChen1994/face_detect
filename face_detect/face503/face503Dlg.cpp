
// face503Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "face503.h"
#include "face503Dlg.h"
#include "afxdialogex.h"
#define random(x) (rand()%x)
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cface503Dlg 对话框




Cface503Dlg::Cface503Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cface503Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cface503Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cface503Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_PIC, &Cface503Dlg::OnBnClickedOpenPic)
	ON_BN_CLICKED(IDC_BUTTON2, &Cface503Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Cface503Dlg 消息处理程序

BOOL Cface503Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cface503Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cface503Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cface503Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HRESULT Cface503Dlg::ShowPic(CDC *pDC,CString lpstrFile,int x,int y, int nScrWidth, int nScrHeight)//对指定路径文件缩放处理
{
	IPicture  *pPic;  
	IStream   *pStm;  
	BOOL      bResult;  

	HANDLE    hFile=NULL;  
	DWORD     dwFileSize,dwByteRead;  

	//打开硬盘中的图形文件  
	hFile=CreateFile(lpstrFile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);  
	if (hFile!=INVALID_HANDLE_VALUE)  
	{  
		dwFileSize=GetFileSize(hFile,NULL);//获取文件字节数  
		if(dwFileSize==0xFFFFFFFF)  
		{
			CloseHandle(hFile);
			return E_FAIL;  
		}
	}  
	else  
	{  
		return E_FAIL;  
	}  


	//分配全局存储空间  
	HGLOBAL hGlobal=GlobalAlloc(GMEM_MOVEABLE,dwFileSize);  
	if(hGlobal==NULL)  
		return E_FAIL;  

	LPVOID  pvData =GlobalLock(hGlobal);  

	if(pvData==NULL)//锁定分配内存块  
	{
		GlobalFree(hGlobal);
		return E_FAIL;  
	}
	ReadFile(hFile,pvData,dwFileSize,&dwByteRead,NULL);//把文件读入内存缓冲区  
	CloseHandle(hFile);//关闭打开的文件  

	GlobalUnlock(hGlobal);  

	CreateStreamOnHGlobal(hGlobal,TRUE,&pStm);  

	//装入图形文件  
	bResult=OleLoadPicture(pStm,dwFileSize,TRUE,IID_IPicture,(LPVOID*)&pPic);  
	GlobalFree(hGlobal);

	if(FAILED(bResult))  
		return E_FAIL;  

	long   hmWidth;//图片的真实宽度  
	long   hmHeight;//图片的真实高度  
	pPic->get_Width(&hmWidth);  
	pPic->get_Height(&hmHeight);  


	//将图形输出到屏幕上（有点像BitBlt）  
	bResult=pPic->Render(pDC->m_hDC,x,y,nScrWidth,nScrHeight,0,hmHeight,hmWidth,-hmHeight,NULL);  

	pPic->Release();  

	if(SUCCEEDED(bResult))  
	{  
		return   S_OK;  
	}  
	else  
	{  
		return   E_FAIL;  
	} 
}

CString lpstrFile=_T("C:\\Users\\Administrator\\Desktop\\1.bmp");

void Cface503Dlg::OnBnClickedOpenPic()
{
	// TODO: 在此添加控件通知处理程序代码
	CDC *pDc=GetDlgItem(IDC_SHOW)->GetDC();//得到dc


	ShowPic(pDc,lpstrFile,0,0, 180,180);


}



void Cface503Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDC *pDc1=GetDlgItem(IDC_DETECTION)->GetDC();//得到dc
	IplImage *jack = cvLoadImage("C:\\Users\\Administrator\\Desktop\\1.bmp");
	IplImage *src = jack;
	IplImage *dst0 = cvCreateImage(cvGetSize(jack), jack->depth, 1);
	IplImage *dst1 = cvCreateImage(cvGetSize(jack), jack->depth, 1);
	IplImage *dst2 = cvCreateImage(cvGetSize(jack), jack->depth, 1);
	IplImage *sub0 = cvCreateImage(cvGetSize(jack), jack->depth, 1);
	IplImage *sub1 = cvCreateImage(cvGetSize(jack), jack->depth, 1);
	IplImage *sub2 = cvCreateImage(cvGetSize(jack), jack->depth, 1);
	CvScalar all[11];
	cvSplit(src, dst0, dst1, dst2, NULL);
	for (int i = 1; i <= 10; i++) 
	{
		char ch[100];
		sprintf(ch, "%d", i); 
		CString ch_new(ch);
		CString num = _T("C:\\Users\\Administrator\\Desktop\\testimg\\");
		num = num + ch_new + _T(".bmp");
		//
		int len = WideCharToMultiByte(CP_ACP, 0, num, -1, NULL, 0, NULL, NULL);
		char *num_new = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, num, -1, num_new, len, NULL, NULL);
//		delete[] ptxtTemp;
		//
		IplImage *image = cvLoadImage(num_new);
		IplImage *dst3 = cvCreateImage(cvGetSize(image), image->depth, 1);
		IplImage *dst4 = cvCreateImage(cvGetSize(image), image->depth, 1);
		IplImage *dst5 = cvCreateImage(cvGetSize(image), image->depth, 1);
		cvSplit(image, dst3, dst4, dst5, NULL);
		cvSub(dst0, dst3, sub0);
		cvSub(dst1, dst4, sub1);
		cvSub(dst2, dst5, sub2);
		IplImage * result = cvCreateImage(cvGetSize(image), image->depth, 1);
		cvAdd(sub0, sub1, result);
		cvAdd(result, sub2, result);
		CvScalar a = cvSum(result);
		all[i] = a;
		cvReleaseImage(&image);
		cvReleaseImage(&dst3);
		cvReleaseImage(&dst4);
		cvReleaseImage(&dst5);
		cvReleaseImage(&result);
	}
	CvScalar min = all[1];
	int minimum;
	int m_id;
	for (int i = 1; i <= 10; i++)
	{
		if (all[i].val[0] <= min.val[0])
		{
			minimum = i;
			min = all[i];
			m_id=i;
		}


	}
	CString s_id;
	s_id.Format(_T("%d"),m_id);
	CString filName = _T("C:\\Users\\Administrator\\Desktop\\testimg\\");
	CString result_filename=filName+ "\\" + s_id + ".bmp" ;
	ShowPic(pDc1,result_filename,0,0, 180,180);
}
