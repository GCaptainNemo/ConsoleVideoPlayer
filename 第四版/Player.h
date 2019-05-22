#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;
//ʹ��opencv�������ռ�
using namespace cv;
class Player {
public:
	Player(HANDLE hd, HWND hwnd, string FileName);
	void GetFrameFromVideo(string FileName);
	void PlayVideo();
	int GetFramesNum();
	double GetFrameRate();
	//���������û������Ĳ���
	void SetPixelSize();
	void SetPixelSize(int Fontsize);
	void Setdelay();
	void Setdelay(int delay);
	void Output_to_file();
	void Gain_date_from_file();
	void Set_FrameSize(int width,int height);
	int Get_Myfontsize();
	int Get_mydelay();

private:
	vector<string> Frames;
	int FramesNum;
	int FrameWidth;
	int FrameHeight;
	double FrameRate;
	HWND MyHwnd;
	HANDLE MyHandle;
	//���������û������Ĳ���
	int Mydelay;
	int Myfontsize;

};

#endif // !1
