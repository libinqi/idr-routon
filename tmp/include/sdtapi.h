
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SDTAPI_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STDCALL SDTAPI_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#include "stdafx.h"

#ifdef SDTAPI_EXPORTS
#define SDTAPI_API __declspec(dllexport)
#else
#define SDTAPI_API __declspec(dllimport)
#endif

#ifdef  _WIN32
#define STDCALL  __stdcall
#else
#define STDCALL
#endif
//#ifndef SDTAPI_
//#define SDTAPI_

// This class is exported from the Sdtapi.dll
#ifdef __cplusplus

#define CPUCARD 0

extern "C"{
#endif

SDTAPI_API	int STDCALL SDT_SetMaxRFByte(int iPortID,unsigned char ucByte,int bIfOpen);
SDTAPI_API	int STDCALL SDT_GetCOMBaud(int iComID,unsigned int *puiBaud);
SDTAPI_API	int STDCALL SDT_SetCOMBaud(int iComID,unsigned int  uiCurrBaud,unsigned int  uiSetBaud);
SDTAPI_API	int STDCALL SDT_SetOpenCOMBaud(unsigned int setBaud);
SDTAPI_API	int STDCALL SDT_OpenPort(int iPortID);
SDTAPI_API	int STDCALL SDT_ClosePort(int iPortID);
SDTAPI_API	int STDCALL SDT_GetErrorString(int ErrorCode, char * ErrorString);

SDTAPI_API	int STDCALL SDT_GetSAMStatus(int iPortID,int iIfOpen);
SDTAPI_API	int STDCALL SDT_ResetSAM(int iPortID,int iIfOpen);
SDTAPI_API	int STDCALL SDT_GetSAMID(int iPortID,unsigned char *pucSAMID,int iIfOpen);
SDTAPI_API	int STDCALL SDT_GetSAMIDToStr(int iPortID,char *pcSAMID,int iIfOpen);
SDTAPI_API	int STDCALL	CardOn(void);
SDTAPI_API	int STDCALL	SDT_StartFindIDCard(int iPortID,unsigned char *pucIIN,int iIfOpen);
SDTAPI_API	int STDCALL	SDT_SelectIDCard(int iPortID,unsigned char *pucSN,int iIfOpen);
SDTAPI_API	int STDCALL SDT_ReadBaseMsg(int iPortID,unsigned char * pucCHMsg,unsigned int *	puiCHMsgLen,unsigned char * pucPHMsg,unsigned int  *puiPHMsgLen,int iIfOpen);
SDTAPI_API	int STDCALL SDT_ReadFPMsg(int iPortID,unsigned char * pucFPMsg,unsigned int *puiFPMsgLen,int iIfOpen);
SDTAPI_API	int STDCALL SDT_ReadIINSNDN(int iPortID,unsigned char * pucIINSNDN,int iIfOpen);
SDTAPI_API	int STDCALL SDT_ReadNewAppMsg(int iPortID,unsigned char * pucAppMsg,unsigned int *puiAppMsgLen,int iIfOpen);
SDTAPI_API	int STDCALL SDT_ReadMngInfo(int iPortID, unsigned char * pucManageMsg,int iIfOpen);  //读卡体管理号

SDTAPI_API	int STDCALL SDT_ReadBaseMsgToFile(int iPortID,char * pcCHMsgFileName,unsigned int *puiCHMsgFileLen,char * pcPHMsgFileName,unsigned int  *puiPHMsgFileLen,int iIfOpen);
SDTAPI_API	int STDCALL SDT_ReadIINSNDNToASCII(int iPortID, unsigned char *pucRecvData,int iIfOpen);

int SDTAPI_API STDCALL  InitComm( int iPort );
int SDTAPI_API STDCALL  CloseComm(void);
int SDTAPI_API STDCALL  Authenticate(void);

//int SDTAPI_API STDCALL  Read_Content(int  Active, char* Path);
int SDTAPI_API STDCALL  ReadBaseMsgWPhoto( unsigned char * pMsg, int * len,char * directory);
int SDTAPI_API STDCALL  ReadBaseMsgPhoto( unsigned char * pMsg, int * len,char * directory);
int SDTAPI_API STDCALL  ReadBaseInfosPhoto( char * Name, char * Gender, char * Folk,
						   char *BirthDay, char * Code, char * Address,
						   char *Agency, char * ExpireStart,char* ExpireEnd,char * directory);

int SDTAPI_API STDCALL  ReadBaseMsgW( unsigned char * pMsg, int * len);
int SDTAPI_API STDCALL  ReadBaseMsg( unsigned char * pMsg, int * len);
int SDTAPI_API STDCALL  ReadBaseInfos( char * Name, char * Gender, char * Folk,
						   char *BirthDay, char * Code, char * Address,
						   char *Agency, char * ExpireStart,char* ExpireEnd);

int SDTAPI_API STDCALL  ReadNewAppMsgW( unsigned char * pMsg, int * num );
int SDTAPI_API STDCALL  ReadNewAppMsg( unsigned char * pMsg, int * len );
int SDTAPI_API STDCALL ReadNewAppInfos( unsigned char * addr1, unsigned char * addr2,
							 unsigned char * addr3, unsigned char * addr4,
							 int * num );

int SDTAPI_API STDCALL ReadIINSNDN( char * pMsg );

int SDTAPI_API STDCALL GetSAMIDToStr(char *pcSAMID );

// 增加蓝牙设备系列接口
int SDTAPI_API STDCALL UsbOpenBt();  //通过usb发送蓝牙指令需调用此命令
int SDTAPI_API STDCALL UsbCloseBt(); //通过usb发送关闭蓝牙指令
int SDTAPI_API STDCALL ReadBtMac(char *macAddr, int BtType);  //macAddr:输出mac地址, BtType:蓝牙类型 0-2.1, 1-4.0
int SDTAPI_API STDCALL ConnectBtDevice(char *macAddr);     //通过蓝牙mac地址连接蓝牙
int SDTAPI_API STDCALL ConnectBtDeviceTimeOut(char *macAddr, int TimeOut);    //通过蓝牙mac地址连接蓝牙， 并可设置超时时间
int SDTAPI_API STDCALL DisConnectBtDevice();  //断开蓝牙
int SDTAPI_API STDCALL WriteBtDevice(char* pBuf, int iBufLen);  //写蓝牙设备
int SDTAPI_API STDCALL ReadBtDevice(char* pBuf, int iBufLen);    //读蓝牙设备
int SDTAPI_API STDCALL Routon_LT_BT_Handshake();   //联通蓝牙握手协议
int SDTAPI_API STDCALL Routon_LT_BT_ChangeBtName(char *name, int BtType);  //修改蓝牙设备名称
int SDTAPI_API STDCALL setBt3DESKey(char *key);  //设置3DESkey
int SDTAPI_API STDCALL setBtPin(char *pinStr, int BtType); //设置蓝牙pin
int SDTAPI_API STDCALL setBtSleep(int BtSleep); //设置蓝牙休眠时长
int SDTAPI_API STDCALL Routon_setBtKey_3DES();


int SDTAPI_API STDCALL Routon_GetBtName(char *name, int BtType);//获得蓝牙名称  0-android, 1-ios
int SDTAPI_API STDCALL Routon_GetBtPin(char *pinStr, int BtType); //得到蓝牙PIN
int SDTAPI_API STDCALL Routon_GetBtSleep(); //获得待机时长  单位: 分钟
int SDTAPI_API STDCALL Routon_GetMainVersion(char *ver);  //主控板 版本
int SDTAPI_API STDCALL Routon_GetCardVersion(char *ver);  //读卡板 版本
int SDTAPI_API STDCALL Routon_GetBtDevVersion(char *ver);  //蓝牙模块 版本
int  SDTAPI_API STDCALL Routon_GetBtDevBatteryPower();  //蓝牙设备电池量




//设置SAM_V与射频模块一帧通信数据最大字节数
int SDTAPI_API STDCALL Routon_Samv_Comm_MaxLen(int maxLen);
int SDTAPI_API STDCALL Routon_LED_BEEP_Control(int led, int beep); //led: 0-led灭, 1-led亮;  beep: 0-灭, 1-响


int SDTAPI_API STDCALL Routon_StartFindIDCard( unsigned char *err );
int SDTAPI_API STDCALL Routon_ReadBaseMsg( unsigned char * pucCHMsg,unsigned int *	puiCHMsgLen );
int SDTAPI_API STDCALL Routon_BeepLED(bool BeepON,bool LEDON,unsigned int duration);
int SDTAPI_API STDCALL Routon_SetNewVersion(bool flag);
int SDTAPI_API STDCALL Routon_IC_FindCard(void);
int SDTAPI_API STDCALL Routon_IC_HL_ReadCardSN(char * SN);
int SDTAPI_API STDCALL Routon_IC_HL_ReadCard (int SID,int BID,int KeyType,unsigned char * Key,unsigned char * data);
int SDTAPI_API STDCALL Routon_IC_HL_WriteCard (int SID,int BID,int KeyType,unsigned char * Key,unsigned char * data);
/*
int SDTAPI_API STDCALL Routon_IC_Halt();  //终止对该卡操作
int SDTAPI_API STDCALL Routon_IC_Request(int mode); //寻卡模式 0-Standard模式；1-All模式  返回值-射频卡返回的特征值
int SDTAPI_API STDCALL Rotuon_IC_Anticoll();   //防卡冲突，返回卡的序列号
int SDTAPI_API STDCALL Routon_IC_Select(char * SN); //从多个卡中选取一个给定序列号的卡   Sn-卡序列号
int SDTAPI_API STDCALL Routon_IC_Auth_PassAddr(int SID,int BID, int KeyType, unsigned char * Key, char * SN);//核对密码函数
int SDTAPI_API STDCALL Routon_IC_ReadCard(int SID,int BID, unsigned char * data);  //读取卡中数据
int SDTAPI_API STDCALL Routon_IC_WriteCard(int SID,int BID, unsigned char * data);  //向卡中写入数据
*/
int SDTAPI_API STDCALL Routon_IC_Format(int SID,int BID,int KeyType,unsigned char * Key, unsigned char * data, unsigned char * addr);  //格式化卡
int SDTAPI_API STDCALL Routon_IC_Value(unsigned char * type,  int sSID,int sBID, unsigned char * data, int tSID,int tBID); //


int SDTAPI_API STDCALL Routon_Get210Version(unsigned char *ver);
int SDTAPI_API STDCALL Routon_Set210Update(void);

int SDTAPI_API STDCALL dc_init(int port,long baud);
int SDTAPI_API STDCALL dc_exit(int dev);
int SDTAPI_API STDCALL dc_request(int icdev,unsigned char _Mode,unsigned int *TagType);
int SDTAPI_API STDCALL dc_anticoll(int icdev,unsigned char _Bcnt,unsigned long *_Snr);
int SDTAPI_API STDCALL dc_select(int icdev,unsigned long _Snr,unsigned char *_Size);
int SDTAPI_API STDCALL dc_authentication_passaddr(int icdev, unsigned char _Mode, unsigned char Addr, unsigned char *passbuff);
int SDTAPI_API STDCALL dc_read(int icdev,unsigned char _Adr,unsigned char *_Data);
int SDTAPI_API STDCALL dc_write(int icdev,unsigned char _Adr,unsigned char *_Data); 
int SDTAPI_API STDCALL dc_halt(int icdev);
int SDTAPI_API STDCALL dc_BeepLED(int icdev,bool BeepON,bool LEDON,unsigned int duration);
int SDTAPI_API STDCALL HID_BeepLED(bool BeepON,bool LEDON,unsigned int duration);

int SDTAPI_API STDCALL PSAM_FunTest(void);
int SDTAPI_API STDCALL	PSAM_ReadATR(unsigned char CardIndex,unsigned char SpeedIndex,unsigned char TypeIndex, unsigned char  *_Data);
int SDTAPI_API STDCALL PSAM_SendCMD(unsigned char CardIndex,unsigned char *_Cmd,int Len, unsigned char *_Data);
int SDTAPI_API STDCALL PSAM_PowerOff(unsigned char CardIndex);

int SDTAPI_API STDCALL GetHIDCount(void);
bool SDTAPI_API STDCALL HIDSelect(int index);
#if CPUCARD
int SDTAPI_API STDCALL Routon_ReadCitizenCard(char * CNo,char * Name,int * IDType,char *IDCode,char * AppInfo);
#endif
int SDTAPI_API STDCALL SDT_ReadBaseMsgFingerPrint(int iPortID,unsigned char * pucCHMsg,unsigned int *	puiCHMsgLen,unsigned char * pucPHMsg,unsigned int  *puiPHMsgLen,unsigned char * pucFPMsg,unsigned int  *puiFPMsgLen,int iIfOpen);
int SDTAPI_API STDCALL SDT_ReadBaseFPMsg(int iPortID,unsigned char * pucCHMsg,unsigned int *	puiCHMsgLen,unsigned char * pucPHMsg,unsigned int  *puiPHMsgLen,unsigned char * pucFPMsg,unsigned int  *puiFPMsgLen,int iIfOpen);

int SDTAPI_API STDCALL Routon_APDU (char * apdu,unsigned char * data,int * datalen);

int SDTAPI_API STDCALL SDT_ReadBaseFPMsgToFile(int iPort,char *pcCHMsgFileName, unsigned int *  puiCHMsgFileLen, char * pcPHMsgFileName, unsigned int  * puiPHMsgFileLen, char *pcFPMsgFileName, unsigned int  * puiFPMsgFileLen, int iIfOpen );
int SDTAPI_API STDCALL IsFingerPrintDevice(void);
int SDTAPI_API STDCALL ReadBaseFPMsg( unsigned char * pMsg, int * len ,unsigned char * pucFPMsg,int  *puiFPMsgLen);

int SDTAPI_API STDCALL Routon_CPUCard_PowerOFF(void);
int SDTAPI_API STDCALL Routon_CPUCard_Active(void);
int SDTAPI_API STDCALL Routon_CPUCard_ATS(unsigned char * ATSMsg,unsigned int * ATSLen);
int SDTAPI_API STDCALL Routon_CPUCard_PPS(unsigned char PPS0,unsigned char PPS1);
int SDTAPI_API STDCALL Routon_ShutDownAntenna(void);
int SDTAPI_API STDCALL Routon_Mute(bool isMute);
int SDTAPI_API STDCALL Routon_FindPassport(void);
int SDTAPI_API STDCALL Routon_ReadPassport(char * MRZL1,char * MRZL2,char * MRZL3);
int SDTAPI_API STDCALL Routon_RepeatRead(bool );
int SDTAPI_API STDCALL Routon_IsSaveWlt(bool );
bool SDTAPI_API STDCALL Routon_isComBase64(void);

int SDTAPI_API STDCALL Routon_ReadIINSNDN(char * pMsg);   //读燕南串口身份证卡体管理号

int SDTAPI_API STDCALL Routon_SetComtimeout(int timeout);

#ifdef __cplusplus
}
//#endif 
#endif

