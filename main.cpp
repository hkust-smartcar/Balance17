///*
// * mian.cpp
// *
// *  Created on: Jul 9, 2017
// *      Author: lzhangbj
// */
//
//
//
//
///*
// * TimFile.cpp
// *
// *  Created on: Jul 3, 2017
// *      Author: lzhangbj
// */
//
//
//
//
////														main.cpp
////
//
//#include <cassert>
//#include <vector>
//#include <stdio.h>
//#include <string>
//#include <cstring>
//#include <inttypes.h>
//#include <sstream>
//#include <cmath>
//#include <array>
//#include <libsc/system.h>
//#include <libbase/k60/mcg.h>
//#include <libutil/string.h>
//#include <libutil/misc.h>
//#include <libsc/tower_pro_mg995.h>
//#include <libbase/k60/pit.h>
//#include <fstream>
//
//#include "6000/Function.h"
//
////
////#include <libsc/led.h>
//////#include <libsc/k60/uart_device.h>
//////#include <libbase/k60/uart.h>
////#include <libsc/k60/ov7725.h>
////
////#include <libsc/alternate_motor.h>
////
////#include <libsc/dir_encoder.h>
////
////#include <libsc/button.h>
////
////#include <libsc/joystick.h>
////
//////#include <libsc/k60/jy_mcu_bt_106.h>
////#include <libbase/k60/flash.h>
////
////#include <libbase/k60/pit.h>
////
////
////#include <libsc/mpu6050.h>
////#include "CameraHeader/FindEdge.h"
////
//namespace libbase
//{
//    namespace k60
//    {
//
//        Mcg::Config Mcg::GetMcgConfig()
//        {
//            Mcg::Config config;
//            config.external_oscillator_khz = 50000;  //50000
//            config.core_clock_khz = 150000;			//150000
//            return config;
//        }
//
//    }
//}
//
//using namespace libsc;
//using namespace libbase::k60;
//using namespace libsc::k60;
//
////
//
//
//int main(){
// 	System::Init();
//	CarInit();
//
//	Ov7725::Config camera_config;
//	camera_config.id = 0;
//	camera_config.w = 80;
//	camera_config.h = 60;
//	camera_config.fps = Ov7725Configurator::Config::Fps::kHigh;
//	Ov7725 CAMERA(camera_config);
//	CameraPtr = &CAMERA;
//	float dif = 0;
//
//	Mpu6050::Config mpuConfig;
//	mpuConfig.gyro_range=Mpu6050::Config::Range::kSmall;
//	mpuConfig.accel_range=Mpu6050::Config::Range::kSmall;
//	Mpu6050 mpu(mpuConfig);
//	MpuPtr = &mpu;
//
//
//	AlternateMotor::Config LeftMotorConfig;
//	LeftMotorConfig.id = 1;
//	AlternateMotor motorLeft(LeftMotorConfig);
//	LeftMotorPtr = &motorLeft;
//	AlternateMotor::Config RightMotorConfig;
//	RightMotorConfig.id = 0;
//	AlternateMotor motorRight(RightMotorConfig);
//	RightMotorPtr = &motorRight;
//
//	DirEncoder::Config LeftEncoderConfig;
//	LeftEncoderConfig.id = 0;
//	DirEncoder encoderLeft(LeftEncoderConfig);
//	LeftEncoderPtr = &encoderLeft;
//	DirEncoder::Config RightEncoderConfig;
//	RightEncoderConfig.id = 1;
//	DirEncoder encoderRight(RightEncoderConfig);
//	RightEncoderPtr = &encoderRight;
//
//	motorLeft.SetClockwise(leftForward);
//	motorRight.SetClockwise(rightForward);
//	motorLeft.SetPower(0);
//	motorRight.SetPower(0);
//
//	JyMcuBt106::Config bluetooth_config;
//	bluetooth_config.id=0;
//	bluetooth_config.baud_rate=libbase::k60::Uart::Config::BaudRate::k115200;
//	JyMcuBt106 BT(bluetooth_config);
//	BluetoothPtr=&BT;
//	char buffer[100];
//
//	Led::Config led_config;
//	led_config.id=0;
//	led_config.is_active_low=false;
//	Led led1(led_config);
//	Led1Ptr = &led1;
//
//	led_config.id=1;
//	led_config.is_active_low=false;
//	Led led2(led_config);
//	Led2Ptr = &led2;
//
//	St7735r::Config tft_config;
//	tft_config.is_revert = true;
//	St7735r	tft(tft_config);
//	tft.SetRegion(Lcd::Rect(1,1,80,60));
//	TftPtr = &tft;
//	LcdTypewriter::Config writer_config;
//	writer_config.lcd = TftPtr;
//	LcdTypewriter typer(writer_config);
//	TyperPtr = &typer;
//
//	Joystick::Config joystick_config;
//	joystick_config.id = 0;
//	joystick_config.handlers[0] = &HandlerUp;
//	joystick_config.handlers[1] = &HandlerDown;
//	joystick_config.handlers[2] = &HandlerLeft;
//	joystick_config.handlers[3] = &HandlerRight;
//	joystick_config.handlers[4] = &HandlerSelect;
//	joystick_config.listener_triggers[0] = Joystick::Config::Trigger::kDown;
//	joystick_config.listener_triggers[1] = Joystick::Config::Trigger::kDown;
//	joystick_config.listener_triggers[2] = Joystick::Config::Trigger::kDown;
//	joystick_config.listener_triggers[3] = Joystick::Config::Trigger::kDown;
//	joystick_config.listener_triggers[4] = Joystick::Config::Trigger::kDown;
//	joystick_config.is_active_low = false;
////	Joystick JOYSTICK(joystick_config);
////	JoystickPtr = &JOYSTICK;
//
//	Button::Config button_config;
//	button_config.id = 0;
//	button_config.is_active_low = false;
//	button_config.is_use_pull_resistor = false;
//	button_config.listener  =&Button1;
//	button_config.listener_trigger= Button::Config::Trigger::kUp;
//	Button BUTTON1(button_config);
//	Button1Ptr = &BUTTON1;
//
//	button_config.id = 1;
//	button_config.is_active_low = false;
//	button_config.is_use_pull_resistor = false;
//	button_config.listener  =&Button2;
//	button_config.listener_trigger= Button::Config::Trigger::kUp;
//	Button BUTTON2(button_config);
//	Button2Ptr = &BUTTON2;
//
//
//	Pit::Config pit_config;
//	pit_config.channel = 0;
//	pit_config.count = 37500*10;
//	pit_config.is_enable = true;
//	pit_config.isr = & Pit_Interrupt;
//	Pit  pit1(pit_config);
//	Pit1Ptr = & pit1;
//
//
//	Flash::Config flash_config;
//	Flash flash(flash_config);
//	FlashPtr = &flash;
////	FlashPtr->Read(&FLASHARRAY,sizeof(FLASHARRAY));
////	FlashPtr->Write(&FLASHARRAY,sizeof(FLASHARRAY));
//	for(int i = 0 ; i < FLASHNUM; i ++){
//		*(FlashArray[i]) = FLASHARRAY[i];
//	}
//
//	uint32_t CurTime = System::Time(), PreTime = System::Time();
//	CAMERA.Start();
//	bool T = true;
//	int c = 0;
//
//	float zh = 0;
//	int stopStartTime = 0;
//
//	while(1){
//		CurTime = System::Time();
//
//			if (car_run && CurTime-PreTime >= 10) {
//				count++;
//
//				PreTime = CurTime;
//				//camera algorithm, change differential
//				const Byte* image = CAMERA.LockBuffer();
//				CAMERA.UnlockBuffer();
//
//
//				if (camEnable) {
//					FindEdge(image,LeftEdge,RightEdge,LeftEdgeNum,RightEdgeNum);
//					Trackstate = ModifyEdge(image,LeftEdge, RightEdge,MidPoint,LeftEdgeNum, RightEdgeNum,MidPointNum,LeftCornerOrder,RightCornerOrder,LeftCorner,RightCorner);
//					prevDiff = curDiff;
//					curDiff = -FindPath(image,LeftEdge,RightEdge,MidPoint,MidPointNum,Trackstate,LeftCorner,RightCorner,LeftEdgeNum, RightEdgeNum);
//					targetAng = balAngle-angDiff;
//					preDifferential = differential;
//
//					float S_P = 3;//2//5//6
//					float S_D = 5;//5//10//8
//					float S_BP = 3;
//					float S_BD = 5;
//					float S_LIMIT = 0.4;
//
//					float T_P = 2;//3//2.5//2.5
//					float T_D = 3;//8//6.2//5.5
//					float T_BP = 4;//2//5
//					float T_BD = 6;//6//10//7
//					float T_LIMIT = 0.4;//0.92
//
//					float RI_P = 2;//3
//					float RI_D = 2;//5
//					float RI_BP = 2;
//					float RI_BD = 5;
//					float RI_LIMIT = 0.4;
//
//
//					float RO_P = 4;
//					float RO_D = 5;
//					float RO_BP = 4;//4
//					float RO_BD = 5;//7
//					float RO_LIMIT = 0.4;
//
//
//					float C_P = 2;
//					float C_D = 6;//8
//					float C_BP = 2;
//					float C_BD = 6;//3  7//8
//					float C_LIMIT = 0.4;
//
//					float O_P = 6;
//					float O_D = 5;
//					float O_LIMIT = 0.4;
//
//					float limit = 1;
//
//					if(Trackstate == Straight)
//						targetSpeed = -6000;
//					else
//						targetSpeed = -6000;
//
//
//					std::string s;
//					switch(Trackstate){
//					case Straight:
//						s = "Straight";
//						break;
//					case Crossroad:
//						s = "Crossroad";
//						break;
//					case Crossroad2:
//						s = "Crossroad2";
//						break;
//					case Crossroad3:
//						s = "Crossroad3";
//						break;
//					case Crossroad4:
//						s = "Crossroad4";
//						break;
//					case Crossroad5:
//						s = "Crossroad5";
//						break;
//					case Crossroad6:
//						s = "Crossroad6";
//						break;
//
//					case Roundabout:
//						s = "Roundabout";
//						break;
//					case Go:
//						s = "Go";
//						break;
//					case LeftObstacle:
//						s = "LObstacle";
//						break;
//					case RightObstacle:
//						s = "RObstacle";
//						break;
//					}
//					BluetoothPtr->SendStr(s);
//
//
//					if(  Trackstate == Straight){//Trackstate == Crossroad || Trackstate == Crossroad2 || Trackstate == Crossroad3 ||
//						limit = S_LIMIT;
//						if(curDiff > 6 || curDiff < -6)
//							differential = S_BP* (curDiff/30) + S_BD*(curDiff-prevDiff);
//						else
//							differential = S_P* (curDiff/30) + S_D*(curDiff-prevDiff);
//
//						if(differential > limit)
//							differential = limit;
//						else if(differential < -limit)
//							differential = -limit;
//					}
//
//					else if(!ObstacleEnd){
//						limit = O_LIMIT;
//						differential = O_P * (curDiff/30) + O_D * (curDiff - prevDiff);
//						if(differential > limit)
//							differential = limit;
//						else if(differential < -limit)
//							differential = -limit;
//					}
//
//					else if(!RoundaboutTag && (Trackstate ==Crossroad || Trackstate ==Crossroad2 || Trackstate ==Crossroad3)){
//						if(curDiff > 6 || curDiff < -6)
//							differential = C_BP* (curDiff/30) + C_BD*(curDiff-prevDiff);
//						else
//							differential = C_P* (curDiff/30) + C_D*(curDiff-prevDiff);
//						limit = C_LIMIT;
//						if(differential > limit)
//							differential = limit;
//						else if(differential < -limit)
//							differential = -limit;
//					}
//
//					else if(!RoundaboutTag) {
//						limit = T_LIMIT;
//						if(curDiff > 3 || curDiff < -3)
//							differential = T_BP* (curDiff/30) + T_BD*(curDiff-prevDiff);
//						else
//							differential = T_P* (curDiff/30) + T_D*(curDiff-prevDiff);
//						if(differential > limit)
//							differential = limit;
//						else if(differential < -limit)
//							differential = -limit;
//					}
//
//					else if(!OutRoundStart && InRoundEnd){
//						limit = 0.4;
//						if(curDiff > 3.5 || curDiff < -3.5)
//							differential = T_BP* (curDiff/30) + T_BD*(curDiff-prevDiff);
//						else
//							differential = T_P* (curDiff/30) + T_D*(curDiff-prevDiff);
//						if(differential > limit)
//							differential = limit;
//						else if(differential < -limit)
//							differential = -limit;
//					}
//
//
//					else if(InRoundStart && ! InRoundEnd) {
//						if(curDiff > 3 || curDiff < -3 )
//							differential = RI_BP* (curDiff/30) + RI_BD*(curDiff-prevDiff);
//						else
//							differential = RI_P* (curDiff/30) + RI_D*(curDiff-prevDiff);
//						limit = RI_LIMIT;
//						if(differential > limit)
//							differential = limit;
//						else if(differential < -limit)
//							differential = -limit;
//					}
//
//					else if(OutRoundStart && ! OutRoundEnd) {
//						if(curDiff > 6 || curDiff < -6 )
//							differential = RO_BP* (curDiff/30) + RO_BD*(curDiff-prevDiff);
//						else
//							differential = RO_P* (curDiff/30) + RO_D*(curDiff-prevDiff);
//						limit = RO_LIMIT;
//						if(differential > limit)
//							differential = limit;
//						else if(differential < -limit)
//							differential = -limit;
//					}
//
//
//					if(carbegin[1] && stopStartTime==0){
//						stopStartTime = System::Time();
//					}
////					if((System::Time() - stopStartTime >= 1000 && stopStartTime != 0)){//Trackstate == Roundabout ||
////							motorLeft.SetPower(0);
////							motorRight.SetPower(0);
////							pitState = !pitState;
////							Pit1Ptr->SetEnable(false);
////					}
////					if(Trackstate == Roundabout)
////						stop = 0;
//					if(stop){
//						motorLeft.SetPower(0);
//						motorRight.SetPower(0);
//						pitState = !pitState;
//						Pit1Ptr->SetEnable(false);
//					}
//
//				}
////				use_TFT = 0;
//				if(use_TFT){
//					TftPtr->SetRegion(Lcd::Rect(2,135,120,12));
//					sprintf(buffer,"differ\t%.2f",differential);
//					TyperPtr->WriteString(buffer);
//					TftPtr->SetRegion(Lcd::Rect(2,147,80,12));
//					sprintf(buffer,"%.2f",curDiff);
//					TyperPtr->WriteString(buffer);
//				}
//				c++;
////				if(c == 5){
////					const Byte imagebyte = 85;
////					BluetoothPtr->SendBuffer(&imagebyte,1);
////					sprintf(buffer,"%.1f,%.2f,%.2f,%.2f\n",1.0,curDiff,2.5,balAngle - curAng);
////					BluetoothPtr->SendStr(s);
////					sprintf(buffer,"%.0f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.2f,%.2f\n",curSpeed,1.0, -1.0, 2.5, -2.5, 4.0, -4.0,curDiff,20*differential);
//					sprintf(buffer,"\t%.0f\t%.2f\t%.2f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",curSpeed,curDiff,curAng,InRoundStart,InRoundEncoderValue,InRoundEnd,OutRoundStart,OutRoundEncoderValue,OutRoundEncoderValue,ObstacleEnd);
////					sprintf(buffer,"%d\t%d\t%d\t%d\t%d\t%d\n",InRoundStart,InRoundEncoderValue,InRoundEnd,OutRoundStart,OutRoundEncoderValue,OutRoundEnd);
//					BluetoothPtr->SendStr(buffer);
//					c = 0;
////				}
//			}
//
//			else if(!car_run && CurTime - PreTime >= 5){
//				zh = (CurTime - PreTime)/1000.0;
//				PreTime = CurTime;
//
//			if(show_camera_image){
//				use_TFT = 1;
//				const Byte* image= CAMERA.LockBuffer();
//				CAMERA.UnlockBuffer();
//				LeftEncoderPtr->Update();
//				RightEncoderPtr->Update();
//				zhanglin += (LeftEncoderPtr->GetCount() - RightEncoderPtr->GetCount())/2;
//
//
//				TftPtr->SetRegion(Lcd::Rect(1,1,80,60));
//				TftPtr->FillBits(Lcd::kYellow,Lcd::kWhite,image,4800);
//				TftPtr->SetRegion(Lcd::Rect(81,61,47,59));
//				TftPtr->FillColor(Lcd::kBlack);
//				FindEdge(image,LeftEdge,RightEdge,LeftEdgeNum,RightEdgeNum);
//				Trackstate = ModifyEdge(image,LeftEdge, RightEdge,MidPoint,LeftEdgeNum, RightEdgeNum,MidPointNum,LeftCornerOrder,RightCornerOrder,LeftCorner,RightCorner);
//				dif = FindPath(image,LeftEdge,RightEdge,MidPoint,MidPointNum,Trackstate,LeftCorner,RightCorner,LeftEdgeNum, RightEdgeNum);
//				PrintEdges(LeftEdge,RightEdge,MidPoint,LeftEdgeNum,RightEdgeNum,MidPointNum,LeftCorner,RightCorner);
//				TftPtr->SetRegion(Lcd::Rect(81,61,47,59));
//				sprintf(buffer,"%d",zhanglin);
//				TyperPtr->WriteString(buffer);
//			}
//			else if(show_data1){
//				CarInit();
//				use_TFT=0;
//				TftPtr->SetRegion(Lcd::Rect(2,2,126,158));
//				sprintf(buffer,
//						"%s\n"
//						"ANG   %.2f\n"
//						"diffP %.2f\n"
//						"diffD %.2f\n"
//						"DMX   %.2f\n"
//						"b_k   %.2f\n"
//						"m_k   %.2f\n"
//						"t_k   %.2f\n"
//						"r_bk  %.2f\n"
//						,
//						data[dataIndex%FLASHNUM].second,
//						angDiff,
//						diffP,
//						diffD,
//						DiffMax,
//						bottomLine_k,
//						middleLine_k,
//						topLine_k,
//						r_bottomLine_k
//						);
//				TyperPtr->WriteString(buffer);
//			}
//			else{
//				TftPtr->SetRegion(Lcd::Rect(2,2,126,158));
//				sprintf(buffer,
//						"%s\n"
//						"r_mk  %.2f\n"
//						"r_tk  %.2f\n"
//						"r_bD  %.2f\n"
//						"r_mD  %.2f\n"
//						"r_tD  %.2f\n"
//						,
//						data[dataIndex%FLASHNUM].second,
//						r_middleLine_k,
//						r_topLine_k,
//						r_bottomLine_dis,
//						r_middleLine_dis,
//						r_topLine_dis
//						);
//				TyperPtr->WriteString(buffer);
//			}
//
//
//
//			}
//		}
//	CAMERA.Stop();
//
//
//return 0;
//
//}


