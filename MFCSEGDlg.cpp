
// MFCSEGDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCSEG.h"
#include "MFCSEGDlg.h"
#include "afxdialogex.h"
#include "init.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Mat src;
Mat dst;
int m_threshold;
int m_blocksize;
int m_bias;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCSEGDlg 对话框



CMFCSEGDlg::CMFCSEGDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSEG_DIALOG, pParent)
	, m_savename(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSEGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_str);
	DDX_Control(pDX, IDC_PIC, m_pic_ctrl);
	DDX_Text(pDX, IDC_EDIT7, m_savename);
}

BEGIN_MESSAGE_MAP(CMFCSEGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCSEGDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCSEGDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCSEGDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCSEGDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCSEGDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCSEGDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCSEGDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCSEGDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCSEGDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCSEGDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CMFCSEGDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CMFCSEGDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CMFCSEGDlg::OnBnClickedButton12)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCSEGDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCSEGDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT4, &CMFCSEGDlg::OnEnChangeEdit4)
	ON_STN_CLICKED(IDC_PIC, &CMFCSEGDlg::OnStnClickedPic)
	ON_BN_CLICKED(IDC_BUTTON13, &CMFCSEGDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CMFCSEGDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CMFCSEGDlg::OnBnClickedButton15)
	ON_EN_CHANGE(IDC_EDIT7, &CMFCSEGDlg::OnEnChangeEdit7)
END_MESSAGE_MAP()


// CMFCSEGDlg 消息处理程序

BOOL CMFCSEGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_EDIT2)->SetWindowText(L"127");
	GetDlgItem(IDC_EDIT3)->SetWindowText(L"7");
	GetDlgItem(IDC_EDIT4)->SetWindowText(L"10");
	GetDlgItem(IDC_EDIT5)->SetWindowText(L"D:");
	GetDlgItem(IDC_EDIT7)->SetWindowText(L"output.png");
	// 图像显示
	namedWindow("输入图像", WINDOW_NORMAL);

	CRect rect;
	GetClientRect(&rect);
	resizeWindow("输入图像", rect.Width(), rect.Height());
	HWND hWnd = static_cast<HWND>(cvGetWindowHandle("输入图像"));
	if (!hWnd)
	{
		return 0;
	}
	HWND hParent = ::GetParent(hWnd);
	if (!hParent)
	{
		return 0;
	}
	HWND hNewParent = GetDlgItem(IDC_PIC)->GetSafeHwnd();
	if (!hNewParent)
	{
		return 0;
	}

	HWND a = ::SetParent(hWnd, hNewParent);
	::ShowWindow(hParent,SW_HIDE);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCSEGDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCSEGDlg::OnPaint()
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
HCURSOR CMFCSEGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//点击浏览按钮
void CMFCSEGDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	cf.DoModal();
}

//选择
void CMFCSEGDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_str = cf.m_filewin_str;
	UpdateData(FALSE);
}


void CMFCSEGDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCSEGDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// cstring 转str
	string str_img_path = (LPCSTR)(CStringA)(m_str);
	Mat image = imread(str_img_path);
	src = image;
	if (image.empty())
	{
		MessageBox(L"图像不存在",TEXT("提示"));
		//退出当前对话框
		CDialogEx::OnOK();
	}
	else
	{

		//m_pic_ctrl.MoveWindow(CRect(500,10,500+image.cols,10+image.rows));

		imshow("输入图像",image);
		waitKey(0);
		destroyAllWindows();
	}



}

// 手动阈值法
void CMFCSEGDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);//先转为灰度图
	//Mat dst;
	threshold(gray, dst, m_threshold, 255, THRESH_BINARY);//二值化阈值处理
	//m_pic_ctrl.MoveWindow(CRect(500, 10, 500 + src.cols, 10 + src.rows));
	imshow("输入图像", dst);
	waitKey(0);
	destroyAllWindows();

}

// 反二值化
void CMFCSEGDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
		Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);//先转为灰度图
	//Mat dst;
	threshold(gray, dst, m_threshold, 255, THRESH_BINARY_INV);//反二值化阈值处理
	//m_pic_ctrl.MoveWindow(CRect(500, 10, 500 + src.cols, 10 + src.rows));
	imshow("输入图像", dst);
	waitKey(0);
	destroyAllWindows();
}

//截断阈值化
void CMFCSEGDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);//先转为灰度图
	//Mat dst;
	threshold(gray, dst, m_threshold, 255, THRESH_TRUNC);//二值化阈值处理
	//m_pic_ctrl.MoveWindow(CRect(500, 10, 500 + src.cols, 10 + src.rows));
	imshow("输入图像", dst);
	waitKey(0);
	destroyAllWindows();
}

//超阈值零处理
void CMFCSEGDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);//先转为灰度图
	//Mat dst;
	threshold(gray, dst, m_threshold, 255, THRESH_TOZERO_INV);//二值化阈值处理
	//m_pic_ctrl.MoveWindow(CRect(500, 10, 500 + src.cols, 10 + src.rows));
	imshow("输入图像", dst);
	waitKey(0);
	destroyAllWindows();
}

// 自适应阈值
void CMFCSEGDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);//先转为灰度图
	//Mat dst;
	adaptiveThreshold(gray, dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, m_blocksize, m_bias);//adaptiveThreshold
	//m_pic_ctrl.MoveWindow(CRect(500, 10, 500 + src.cols, 10 + src.rows));
	imshow("输入图像", dst);
	waitKey(0);
	destroyAllWindows();
}

//otsu
void CMFCSEGDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);//先转为灰度图
	//Mat dst;
	threshold(gray, dst, 0, 255, THRESH_OTSU);//OTSU
	//m_pic_ctrl.MoveWindow(CRect(500, 10, 500 + src.cols, 10 + src.rows));
	imshow("输入图像", dst);
	waitKey(0);
	destroyAllWindows();
}
// 利用图像的直方图计算各阈值分割图像时图像的熵值
float caculateCurrentEntropy(cv::Mat hist, int threshold)
{
	float BackgroundSum = 0, targetSum = 0;
	const float* pDataHist = (float*)hist.ptr<float>(0);
	for (int i = 0; i < 256; i++)
	{
		// 累计背景值
		if (i < threshold)
		{
			BackgroundSum += pDataHist[i];
		}
		else // 累计前景值
		{
			targetSum += pDataHist[i];
		}
	}

	//接下来计算图像在阈傎threshold分割情况下的熵值
	float BackgroundEntropy = 0, targetEntropy = 0;
	for (int i = 0; i < 256; i++)
	{
		// 计算图像熵的背景熵分量
		if (i < threshold)
		{
			if (pDataHist[i] == 0)
				continue;
			float ratio1 = pDataHist[i] / BackgroundSum;
			// 当循环完成后，BackgroundEntropy中存储的便是图像熵的背景熵分量
			BackgroundEntropy += -ratio1 * logf(ratio1);
		}
		else // 计算图像熵的前景熵分量
		{
			if (pDataHist[i] == 0)
				continue;
			float ratio2 = pDataHist[i] / targetSum;
			// 当循环完成后，targetEntrop中存储的便是图像熵的前景熵分量
			targetEntropy += -ratio2 * logf(ratio2);
		}
	}
	return (targetEntropy + BackgroundEntropy);
}
cv::Mat maxEntropySegMentation(cv::Mat inputImage)
{
	// 初始化直方图参数
	const int channels[1] = { 0 };
	const int histSize[1] = { 256 };
	float pranges[2] = { 0, 256 };
	const float* ranges[1] = { pranges };
	cv::Mat hist;
	// 计算直方图
	cv::calcHist(&inputImage, 1, channels,
		cv::Mat(), hist, 1, histSize, ranges);
	float maxentropy = 0;
	int    max_index = 0;
	cv::Mat result;
	// 遍历得到最大熵阈值分割的最佳阈值
	for (int i = 0; i < 256; i++)
	{
		float cur_entropy =
			caculateCurrentEntropy(hist, i);
		// 计算当前最大值的位置
		if (cur_entropy > maxentropy)
		{
			maxentropy = cur_entropy;
			max_index = i;
		}
	}
	cout << "利用最大熵法找到的阈值为:" << max_index << endl;
	//  二值化分割
	threshold(inputImage, result, max_index, 255,
		THRESH_BINARY); //max_index就是满足最大熵情况下的阈值
	return result;
}

void CMFCSEGDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);//先转为灰度图
	//Mat dst;
	dst = maxEntropySegMentation(gray); // 最大熵
	//m_pic_ctrl.MoveWindow(CRect(500, 10, 500 + src.cols, 10 + src.rows));
	imshow("输入图像", dst);
	waitKey(0);
	destroyAllWindows();
}

//定义全局阈值分割函数
void global_threshold_segmentation(Mat& input_image, Mat& output_image, int T0, int T)
{
	//使用初始值T进行分组并求每组的平均值m1和m2，并计算新的阈值T2
	int width = input_image.cols; //图像列数
	int height = input_image.rows; //图像行数
	uchar* Img = input_image.data; //图像指针
	int G1_mean, G2_mean; //定义每组像素的均值
	int G1_num = 1, G2_num = 1; //定义每组像素的数量，初始值设为1，以免后面出现除以0的问题
	int G1_sum = 0, G2_sum = 0; //定义每组灰度值之和

	for (int i = 0; i < height; i++)
	{
		uchar* Img = input_image.ptr(i); //图像每行数据的指针
		for (int j = 0; j < width; j++)
		{
			if (Img[j] < T)
			{
				G1_sum += Img[j];
				G1_num += 1;
			}
			else
			{
				G2_sum += Img[j];
				G2_num += 1;
			}
		}
	}
	G1_mean = G1_sum / G1_num;
	G2_mean = G2_sum / G2_num;
	int T2 = (G1_mean + G2_mean) * 0.5; //新阈值

	//迭代计算T
	if (abs(T2 - T) > T0)
	{
		global_threshold_segmentation(input_image, output_image, T0, T2);
	}
	else
	{
		threshold(input_image, output_image, T2, 255, 1);
	}

}
void CMFCSEGDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);//先转为灰度图
	//Mat dst;
	int T1 = 5; //任意值
	global_threshold_segmentation(gray, dst, 5, T1);
	//m_pic_ctrl.MoveWindow(CRect(500, 10, 500 + src.cols, 10 + src.rows));
	imshow("输入图像", dst);
	waitKey(0);
	destroyAllWindows();
}


void CMFCSEGDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);//先转为灰度图
	Mat dst;
	/*---------------------------------------------------------------------------*/
	/*上下阀值法：利用正态分布求可信区间*/
	dst = gray.clone();
	Scalar mean, std_dev;//平均值、 标准差  
	double u_threshold, d_threshold;
	meanStdDev(dst, mean, std_dev);
	u_threshold = mean.val[0] + 1 * std_dev.val[0];//上阀值  
	d_threshold = mean.val[0] - 1 * std_dev.val[0];//下阀值  
	//u_threshold = mean + 2.5 * std_dev; //错误  
	//d_threshold = mean - 2.5 * std_dev;  
	cout << "The TopThreshold of this Image in TopDown is:" << d_threshold << endl;//输出显示阀值  
	cout << "The DownThreshold of this Image in TopDown is:" << u_threshold << endl;
	threshold(gray, dst, d_threshold, u_threshold, THRESH_BINARY_INV);//上下阀值 ，这个方法好像有问题
	//m_pic_ctrl.MoveWindow(CRect(500, 10, 500 + src.cols, 10 + src.rows));
	imshow("输入图像", dst);
	waitKey(0);
	destroyAllWindows();
}


void CMFCSEGDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString str;
	GetDlgItemText(IDC_EDIT3, str);
	//MessageBox(str);
	m_blocksize = _ttoi(str);
}


void CMFCSEGDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//获取按钮的内容
	CString str;
	GetDlgItemText(IDC_EDIT2,str);
	//MessageBox(str);
	m_threshold = _ttoi(str);
}


void CMFCSEGDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str_bias;
	GetDlgItemText(IDC_EDIT4, str_bias);
	//MessageBox(str_bias);
	m_bias = _ttoi(str_bias);
}


void CMFCSEGDlg::OnStnClickedPic()
{
	// TODO: 在此添加控件通知处理程序代码
}





void CMFCSEGDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	cf2.DoModal();
}


void CMFCSEGDlg::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	save_path = cf2.m_filewin_str +"\\"+ m_savename;
	
	GetDlgItem(IDC_EDIT5)->SetWindowText(save_path);
	UpdateData(TRUE);
}


void CMFCSEGDlg::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src.empty())
	{
		MessageBox(L"没有图像,不能保存", L"提示");
	}
	else
	{
		UpdateData(TRUE);
		string str_save_path = (LPCSTR)(CStringA)(save_path);
		//MessageBox(save_path);
		//imwrite(str_save_path/* + "\\output.png"*/, dst);
		imwrite(str_save_path, dst);
		//MessageBox(TEXT("已保存到" + save_path), L"提示");
		GetDlgItem(IDC_EDIT5)->SetWindowText(TEXT("已保存到" + save_path));
		UpdateData(TRUE);
	}
}


void CMFCSEGDlg::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	GetDlgItemText(IDC_EDIT4, m_savename);
	UpdateData(TRUE);
}
