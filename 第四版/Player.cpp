#include "pch.h"
#include "Player.h"

Player::Player(HANDLE hd, HWND hwnd, string FileName)
{
	this->MyHwnd = hwnd;
	this->MyHandle = hd;
	GetFrameFromVideo(FileName);

}

void Player::GetFrameFromVideo(string FileName)
{
	//Get the video by file name
	//ͨ���ļ���������Ƶ������·�������·����
	VideoCapture vc(FileName);

	//The unchanged frame from video
	//������ҪԤ�����֡
	Mat frameRaw;

	//Get the totoal amount of frames
	//�����Ƶ��֡��
	//CAP_PROP_FRAME_COUNT��opencv�궨���ץȡ֡������
	int totalFrameNum = FramesNum =  vc.get(CAP_PROP_FRAME_COUNT);

	//��ȡ֡��
	this->FrameRate = vc.get(CAP_PROP_FPS);

	//Get console handle to use the functions of it
	//�õ�����̨�������ʹ�ÿ���̨����
	//˵����ǰ�õĿ���̨���ĸ�
	HANDLE temp_hd = MyHandle;

	

	//Set the console cursor invisible for a better performance
	//�������Ϊ���ɼ�,1��ʾ����ȣ�false��ʾ���ɼ�
	_CONSOLE_CURSOR_INFO cf = { 1,false };


	//Use a vector to stored all the preprocess  frames 
	//ʹ��vector����������ÿһ֡
	//+3��Ϊ������
	vector<string> allframe(totalFrameNum + 3);

	//��¼��ʼʱ��
	double start = GetTickCount();

	//������
	int framediff = 0,width = FrameWidth=80,height = FrameHeight = 45,j,k;
	string output = "";

	//Grab and preprocess all frames 
	//CAP_PROP_POS_AVI_RATIO����Ƶ���λ��,0~1��һ��ֵ
	//����дһ����Ϊ������ 

	//������forѭ�����ڶ�ȡ��Ƶÿһ֡������ŵ������
	for (int i = 0; i < totalFrameNum&&vc.get(CAP_PROP_POS_AVI_RATIO) < (1 - 10E-6); i++) {
		Mat frameGray, frameOut;
		//Set the console cursor invisible for a better performance
		//�������Ϊ���ɼ�
		SetConsoleCursorInfo(temp_hd, &cf);

		//the frame changed in gray,and the one changed in size to match the console
		//����Ҷ�ֵ���󣬺��������

		//Grab the next frame from video
		//�����һ֡�������δ��ù������ȡ��һ֡
		vc >> frameRaw;

		//Change the RGB color to gray
		//����ǰRGB֡ת��Ϊ�Ҷ�ͼ��
		cvtColor(frameRaw, frameGray, 7);

		//Change the size of the frame
		//��С�ߴ�
		resize(frameGray, frameOut, Size(FrameWidth, FrameHeight));

		//Stored it in a vector
		//�洢������
		

		//��ȡ������ַ���
		//��һ��forѭ�����б������ڶ���forѭ�����б���
		for (j=0; j < FrameHeight; j++) {
			for (k=0; k < FrameWidth; k++) {

				//��ֵ����ʾ���أ��Ҷȴ���127����ʾ
				if (frameOut.at<bool>(j, k) > 127) {
					output += "#";
					//putchar(' ');
				}
				else {
					output += " ";
					//putchar(' ');
				}
			}
			output += "\n";
		}
		allframe[i] = output;
		//Show the number of the current processing frame
		//��ʾ��ǰ�����ڼ���֡�ˣ���ȡʱ�ĵڼ�֡��
		//SetConsoleCursorPosition�����������frame������ʾ֡������λ��
		SetConsoleCursorPosition(temp_hd, { 0,0 });
		cout << "frame��" << i;

		//����fps(��ȡʱ��fps)
		if (GetTickCount() - start >= 1000) {
			cout << "  fps��" << i - framediff;
			framediff = i + 1;
			start = GetTickCount();
		}
	}
	Frames = allframe;
}

void Player::PlayVideo()
{
	//Clear console
	//����
	system("cls");

	//���嵱ǰ֡��
	int framediff = 0, totalFrameNum = FramesNum,start = 0;
	_CONSOLE_CURSOR_INFO cf = { 1,false };
	for (int i = 0; i < totalFrameNum; i++) {
		//Make sure the cursor is invisible in every frame
		//ȷ��ÿһ֡����ʾ��궼���ɼ�
		SetConsoleCursorInfo(MyHandle, &cf);

		//�ѹ��λ�ö����ڣ�0,0��λ�ã�����ʵ������Ч��
		SetConsoleCursorPosition(MyHandle, { 0,0 });

		//����������ַ���

		//�����ȡ���ַ���

		//Set the current position of the displaying pixel
		//2*k ����ͬ�����ؼ�࣬����߿�Ȳ�����
		//ʹ�����ù��λ�õķ�����ֱ��putchar֡�ʸ�4-5
		COORD cd = { FrameHeight * 2,FrameWidth };
		SetConsoleCursorPosition(MyHandle, cd);
		cout << Frames[i] << endl;
		//����	
		Sleep(Mydelay);


		//Show the number of the current playing frame
		//չʾĿǰ��֡��������֡��
		cout << "frame��" << i;
		if (GetTickCount() - start >= 1000) {
			cout << "  fps��" << i - framediff;
			framediff = i + 1;
			start = GetTickCount();


		}
	}
}

void Player::SetPixelSize()
{
	cout << "Please enter the size of the font:" << endl;
	int size;
	cin >> size;
	Myfontsize = size;
	WCHAR myFont[] = TEXT("Arial");
	_CONSOLE_FONT_INFOEX fontinfo = { sizeof(CONSOLE_FONT_INFOEX) ,1,{Myfontsize,Myfontsize},TMPF_FIXED_PITCH,400, *myFont };
	SetCurrentConsoleFontEx(MyHandle, false, &fontinfo);
}

void Player::SetPixelSize(int FontSize)
{
	Myfontsize = FontSize;
	WCHAR myFont[] = TEXT("Arial");
	_CONSOLE_FONT_INFOEX fontinfo = { sizeof(CONSOLE_FONT_INFOEX) ,1,{Myfontsize,Myfontsize},TMPF_FIXED_PITCH,400, *myFont };
	SetCurrentConsoleFontEx(MyHandle, false, &fontinfo);
}

int Player::GetFramesNum()
{
	return this->FramesNum;
}

double Player::GetFrameRate()
{
	return this->FrameRate;
}

//�û������ӳ�
void Player::Setdelay() {
	cout << endl;
	cout << "Please enter the delay of every frame:" << endl;
	int delay;
	cin >> delay;
	Mydelay = delay;
}

void Player::Setdelay(int delay){ 
	Mydelay = delay;
}

//������ݵ��ļ�
void Player::Output_to_file() {
	ofstream file;
	file.open("set.txt", std::ios::out);
	file << Mydelay << endl;
	file << Myfontsize << endl;
	file.close();



}


void Player::Set_FrameSize(int width,int height)
{
	FrameHeight = height;
	FrameWidth = width;

}

int Player::Get_Myfontsize()
{
	return Myfontsize;
}

int Player::Get_mydelay()
{
	return Mydelay;
}

//���ļ��ж�ȡ����
void Player::Gain_date_from_file() {
	//��������洢����
	char data[10];
	ifstream file("set.txt");
	//��ȡ��������
	while (!file.eof()) {
		file.getline(data, 10);
	}
	Mydelay = data[0];
	Myfontsize = data[1];
	
}
