#ifndef RECEIVE_H
#define RECEIVE_H

#include <string>

using namespace std;

class ReceiveType
{
  public:
    static const int IDCard = 1;
    static const int ICCard = 2;
};

struct Receiver
{
    int type;

	char name[31];		 //姓名
	char gender[3];		 //性别
	char folk[10];		 //民族
	char birthDay[9];	//生日
	char code[19];		 //身份证号码
	char address[71];	//地址
	char agency[31];	 //签证机关
	char expireStart[9]; //有效期起始日期
	char expireEnd[9];   //有效期截至日期
};

#endif // RECEIVE_H