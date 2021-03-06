/*
 * Function.h
 *
 *  Created on: Jul 9, 2017
 *      Author: lzhangbj
 */

#ifndef SRC_6000_FUNCTION_H_
#define SRC_6000_FUNCTION_H_

/*
 * Function.cpp
 *
 *  Created on: Jul 3, 2017
 *      Author: lzhangbj
 */



#include "6000/Variable.h"



bool stop = 0;

double arrAvg(double arr[], int size, int& counter, double& total, double newVal) {

	total -= arr[counter];
	arr[counter] = newVal;
	total += arr[counter];
	counter++;
	if (counter == size) {
		counter = 0;
	}
	return round((total/size)*100)/100.0;
}

void CarInit(){
	curSpeedErr = 0;
	prevSpeedErr = 0;
	carbegin[0] =carbegin[1] = 0;
	 carinterval = false;
	 carindex = 0;

	 RoundaboutTag = false;
//	 FindCor = false;
	 time = 0;


	inputTargetSpeed = 0;
	leftPowSpeedP = 0; leftPowSpeedI = 0; leftPowSpeedD = 0;
	rightPowSpeedP = 0; rightPowSpeedI = 0; rightPowSpeedD = 0;
	speedAngP = 0; speedAngI = 0; speedAngD = 0;

	sumSpeedErrLim = 6000; sumAngErrLim = 100000;

	targetAng = balAngle;
	sumSpeedErr = 0; sumAngErr = 0; sumLeftSpeedErr = 0; sumRightSpeedErr = 0;
    differential = 0; curDiff = 0; prevDiff = 0;
	programRun = true; camEnable = true; tuneBal = false; tuneSpeed = false;



	startTime = System::Time();
	prevSampleTime = System::Time();
	camTime = System::Time();
	dt = 0;
	loopCounter = 0;

//Camera

	height = globalHeight, width = globalWidth;

//Speed
		leftPow = 0; rightPow = 0;
		leftForward = 1; rightForward = 0;

		curSpeed = 0; prevSpeed = 0;
		leftSpeed = 0; rightSpeed = 0;
		leftTempTargetSpeed = 0; rightTempTargetSpeed = 0; tempTargetSpeed = 0;
		leftSpeedArrCounter = 0; rightSpeedArrCounter = 0;
		leftSpeedTotal = 0; rightSpeedTotal = 0;


		leftSpeedErr = 0; rightSpeedErr = 0; curSpeedErr = 0;
		prevLeftSpeedErr = 0; prevRightSpeedErr = 0; prevSpeedErr = 0;
		leftSpeedErrRate = 0; rightSpeedErrRate = 0; speedErrRate = 0;
		leftSpeedErrRateCounter = 0; rightSpeedErrRateCounter = 0; speedErrRateCounter = 0;
		leftSpeedErrRateTotal = 0; rightSpeedErrRateTotal = 0; speedErrRateTotal = 0;

		//Constant

		targetSpeed = -8000;
		targetAng = balAngle-angDiff;	//Angle to run  70
		inputTargetSpeed = 8000;
//		leftPowSpeedP = 0.002;
//		leftPowSpeedI = 0;
//		leftPowSpeedD = 0.0001;
//		rightPowSpeedP = 0.002;
//		rightPowSpeedI = 0;
//		rightPowSpeedD = 0.0001;
//		speedAngP = 20000;//20000
//		speedAngI = 0;	//0
//		speedAngD = 80;//80
//		targetAngLim = 15;
//		targetSpeedAngK = 1500;
//		targetAngSpeedP = -0.0003; //-0.00035
//		targetAngSpeedI = 0;//-0.0002
//		targetAngSpeedD = 0.00001;//0.00002

		//mk 7/5/2017 10:21
		leftPowSpeedP = 0.002;
		leftPowSpeedI = 0;
		leftPowSpeedD = 0.00005;
		rightPowSpeedP = 0.002;
		rightPowSpeedI = 0;
		rightPowSpeedD = 0.00005;
		speedAngP = 30000;
		speedAngI = 0;
		speedAngD = 10;
		targetAngLim = 15;
		targetSpeedAngK = 1500;
		targetAngSpeedP = -0.0003;//-0.0002
		targetAngSpeedI = -0.0003;//-0.0003//5//2
		targetAngSpeedD = 0.00001;

		camEnable = 1;
		tuneBal = 0;
		tuneSpeed = 0;





//Angle
	accbine = 0;
	accAng = 0; gyroAng = 0;

	curAng = 0; prevAng = 0;
	tempTargetAng = 0;
	angCounter = 0;
	angTotal = balAngle*angArrSize;


	curAngErr = 0; prevAngErr = 0; angErrRate = 0;
	angErrRateCounter = 0;
	angErrRateTotal = 0;

	temp = 0;
	temp1 = 0;
	preDifferential = 0;
	count = 0;

	for(auto& i:leftSpeedArr){
		i = 0;
	}
	for(auto& i:rightSpeedArr){
		i = 0;
	}
	for(auto& i:leftSpeedErrRateArr){
		i = 0;
	}
	for(auto& i:rightSpeedErrRateArr){
		i = 0;
	}
	for(auto& i:speedErrRateArr){
		i = 0;
	}
	for(auto& i:angErrRateArr){
		i = 0;
	}
	for(auto& i:angArr){
		i = balAngle;
	}
}

void Pit_Interrupt(Pit* pit){
	if(System::Time() < 2000)
		return;
	loopCounter++;
	Led1Ptr->Switch();
	dt = 0.005;




	//speed
	LeftEncoderPtr->Update();
	temp = LeftEncoderPtr->GetCount()/dt;
	if (temp>30000 || temp<-30000) {
		temp = leftSpeed;
	}
//	leftSpeed = arrAvg(leftSpeedArr, speedArrSize, leftSpeedArrCounter, leftSpeedTotal, temp);
	leftSpeed = temp;
	RightEncoderPtr->Update();
	temp = -RightEncoderPtr->GetCount()/dt;
	if (temp>30000 || temp<-30000) {
		temp = rightSpeed;
	}
//	rightSpeed = arrAvg(rightSpeedArr, speedArrSize, rightSpeedArrCounter, rightSpeedTotal, temp);
	rightSpeed = temp;
	prevSpeed = curSpeed;
	curSpeed = (leftSpeed+rightSpeed)/2;

	//NEW speed 7/6/2017 14:38
//	LeftEncoderPtr->Update();
//	temp = LeftEncoderPtr->GetCount()/dt;
//	if (temp>50000) {
//		temp = 65535 - temp;
//	} else if (temp<-50000) {
//		temp = -65535 - temp;
//	}
////	leftSpeed = arrAvg(leftSpeedArr, speedArrSize, leftSpeedArrCounter, leftSpeedTotal, temp);
//	leftSpeed = temp;
//	RightEncoderPtr->Update();
//	temp = -RightEncoderPtr->GetCount()/dt;
//	if (temp>50000) {
//		temp = 65535 - temp;
//	} else if (temp<-50000) {
//		temp = -65535 - temp;
//	}
////	rightSpeed = arrAvg(rightSpeedArr, speedArrSize, rightSpeedArrCounter, rightSpeedTotal, temp);
//	rightSpeed = temp;
//	prevSpeed = curSpeed;
//	curSpeed = (leftSpeed+rightSpeed)/2;


	PrevSpeedErr = CurSpeedErr;
	CurSpeedErr = rightSpeed - leftSpeed;

	if(OutRoundStart)
		OutRoundEncoderValue += curSpeed*dt;
	if(InRoundStart)
		InRoundEncoderValue += curSpeed*dt;

	if(LeftObstacleBegin || RightObstacleBegin){
		ObstacleEncoderValue += curSpeed*dt;
	}

	if(StartEncoderValue > -6000)
		StartEncoderValue+=curSpeed;

	//angle
	MpuPtr->Update(1);
	acc[0] = MpuPtr->GetAccel()[0];
	acc[1] = MpuPtr->GetAccel()[1];
	acc[2] = MpuPtr->GetAccel()[2];
	accbine = sqrt(acc[0]*acc[0] + acc[1]*acc[1] + acc[2]*acc[2]);
	accAng = 90 - (atan(acc[0]/acc[2])*180)/3.1415;
//	accAng = (acos(acc[0]/accbine)*180)/3.1415;
	gyroAng = curAng + (MpuPtr->GetOmega()[1]/20960.0)*dt;
	prevAng = curAng;
	curAng = arrAvg(angArr, angArrSize, angCounter, angTotal, fabs((0.98*gyroAng)+(0.02*accAng)));


	if(!(curAng < 200 && curAng > -200))
		stop = 1;

//	if (loopCounter<500) {
//		targetAngLim = 0;
//	}

//	else {
		targetAngLim = 8;
//	}

	//targetAng-speedDiff PID
	prevSpeedErr = curSpeedErr;
	curSpeedErr =  curSpeed - targetSpeed;
	sumSpeedErr += curSpeedErr * dt;
	if (sumSpeedErr > sumSpeedErrLim) {
		sumSpeedErr = sumSpeedErrLim;
	} else if (sumSpeedErr < -1*sumSpeedErrLim) {
		sumSpeedErr = -1*sumSpeedErrLim;
	}
	speedErrRate = arrAvg(speedErrRateArr, speedErrRateArrSize, speedErrRateCounter, speedErrRateTotal, (curSpeedErr - prevSpeedErr) / dt);
	tempTargetAng = targetAng + targetAngSpeedP * curSpeedErr + targetAngSpeedI * sumSpeedErr + targetAngSpeedD * speedErrRate;
	tempTargetAng += angChange;
	if (tempTargetAng > targetAng+targetAngLim) {	//backward
		tempTargetAng = targetAng+targetAngLim;
	} else if (tempTargetAng < targetAng-targetAngLim) {			//forward
		tempTargetAng = targetAng-targetAngLim;
	}

	//tune balance
	if (tuneBal) {
		tempTargetAng = balAngle;
	}


	//tempSpeed-angle PID
	prevAngErr = curAngErr;
	curAngErr = curAng - tempTargetAng;
	sumAngErr += curAngErr * dt;
	if (sumAngErr > sumAngErrLim) {
		sumAngErr = sumAngErrLim;
	} else if (sumAngErr < -1*sumAngErrLim) {
		sumAngErr = -1*sumAngErrLim;
	}
//	angErrRate = arrAvg(angErrRateArr, angErrRateArrSize, angErrRateCounter, angErrRateTotal, (curAngErr-prevAngErr) / dt);
	angErrRate = (curAngErr-prevAngErr) / dt;
	tempTargetSpeed = curSpeed + speedAngP * curAngErr + speedAngI * sumAngErr + speedAngD * angErrRate;

//	if(differential > 0){
//		leftTempTargetSpeed = tempTargetSpeed * (1+differential);
//		rightTempTargetSpeed = tempTargetSpeed ;
//	}
//	else{
//		leftTempTargetSpeed = tempTargetSpeed ;
//		rightTempTargetSpeed = tempTargetSpeed * (1-differential);
//
//	}

	leftTempTargetSpeed = tempTargetSpeed * (1+differential);
	rightTempTargetSpeed = tempTargetSpeed * (1-differential);
	//tune speed
	if (tuneSpeed) {
		leftTempTargetSpeed = inputTargetSpeed + inputTargetSpeed*0.5*sin(temp1);
		rightTempTargetSpeed = inputTargetSpeed + inputTargetSpeed*0.5*sin(temp1);
		temp1 += 0.02;
	}

	//power-speed PID
	prevLeftSpeedErr = leftSpeedErr;
	leftSpeedErr = leftSpeed - leftTempTargetSpeed;
	sumLeftSpeedErr += leftSpeedErr * dt;
	if (sumLeftSpeedErr > sumSpeedErrLim) {
		sumLeftSpeedErr = sumSpeedErrLim;
	} else if (sumLeftSpeedErr < -1*sumSpeedErrLim) {
		sumLeftSpeedErr = -1*sumSpeedErrLim;
	}
	leftSpeedErrRate = arrAvg(leftSpeedErrRateArr, speedErrRateArrSize, leftSpeedErrRateCounter, leftSpeedErrRateTotal, (leftSpeedErr-prevLeftSpeedErr) / dt);
	leftPow += (int)(leftPowSpeedP * leftSpeedErr + leftPowSpeedI * sumLeftSpeedErr + leftPowSpeedD * leftSpeedErrRate);

	prevRightSpeedErr = rightSpeedErr;
	rightSpeedErr = rightSpeed - rightTempTargetSpeed;
	sumRightSpeedErr += rightSpeedErr * dt;
	if (sumRightSpeedErr > sumSpeedErrLim) {
		sumRightSpeedErr = sumSpeedErrLim;
	} else if (sumRightSpeedErr < -1*sumSpeedErrLim) {
		sumRightSpeedErr = -1*sumSpeedErrLim;
	}
	rightSpeedErrRate = arrAvg(rightSpeedErrRateArr, speedErrRateArrSize, rightSpeedErrRateCounter, rightSpeedErrRateTotal, (rightSpeedErr-prevRightSpeedErr) / dt);
	rightPow += (int)(rightPowSpeedP * rightSpeedErr + rightPowSpeedI * sumRightSpeedErr + rightPowSpeedD * rightSpeedErrRate);



	int powlimit =500;
	if(curSpeed < -9000)
		powlimit = 500;
	//power limit
	if (leftPow > powlimit) {
		leftPow = powlimit;
	} else if (leftPow < -powlimit) {
		leftPow = -powlimit;
	}
	if (rightPow > powlimit) {
		rightPow = powlimit;
	} else if (rightPow < -powlimit) {
		rightPow = -powlimit;
	}


	//set power
	if (leftPow > 0) {
		LeftMotorPtr->SetClockwise(!leftForward);
		LeftMotorPtr->SetPower(leftPow);
	} else {
		LeftMotorPtr->SetClockwise(leftForward);
		LeftMotorPtr->SetPower(-1*leftPow);
	}
	if (rightPow > 0) {
		RightMotorPtr->SetClockwise(!rightForward);
		RightMotorPtr->SetPower(rightPow);
	} else {
		RightMotorPtr->SetClockwise(rightForward);
		RightMotorPtr->SetPower(-1*rightPow);
	}
	return ;
}


void PrintEdges(const Point* LeftEdge, const Point* RightEdge, const Point* MidPoint, const uint8_t LeftEdgeNum,const uint8_t RightEdgeNum,const uint8_t MidPointNum, Point* LeftCorner[], Point* RightCorner[]){
	for(int i = 0 ; i < RightEdgeNum ; i ++){
		TftPtr->SetRegion(Lcd::Rect(RightEdge[i].x+1,RightEdge[i].y+1,1,1));
		TftPtr->FillColor(Lcd::kBlack);
	}
	for(int i = 0 ; i < LeftEdgeNum; i ++){
		TftPtr->SetRegion(Lcd::Rect(LeftEdge[i].x+1,LeftEdge[i].y+1,1,1));
		TftPtr->FillColor(Lcd::kRed);
	}
	for(int i = 0 ; i < MidPointNum ; i ++){
		TftPtr->SetRegion(Lcd::Rect(MidPoint[i].x + 1,MidPoint[i].y+1,2,1));
		TftPtr->FillColor(Lcd::kGray);
	}
	for(int i = 0 ; i < 60 ; i ++){
		TftPtr->SetRegion(Lcd::Rect(40,i+1,1,1));
		TftPtr->FillColor(Lcd::kGreen);
	}
	for(int i = 0 ; i < 2 ; i ++){
		if(LeftCorner[i]){
			TftPtr->SetRegion(Lcd::Rect(LeftCorner[i]->x,LeftCorner[i]->y, 2 ,2));
			if( i == 0 )
			TftPtr->FillColor(Lcd::kRed);
			else
				TftPtr->FillColor(Lcd::kPurple);
		}
		if(RightCorner[i]){
			TftPtr->SetRegion(Lcd::Rect(RightCorner[i]->x,RightCorner[i]->y, 2 ,2));
			if(i == 0)
			TftPtr->FillColor(Lcd::kBlack);
			else
				TftPtr->FillColor(Lcd::kBlue);
		}
	}
}

void HandlerUp(const uint8_t id,const Joystick::State which ){
	if(dataIndex <= 3)
		FLASHARRAY[dataIndex] +=0.1;
	else if(dataIndex <= 9 )
		FLASHARRAY[dataIndex] +=0.01;
	else
		FLASHARRAY[dataIndex] +=0.1;
	FlashPtr->Write(FLASHARRAY,sizeof(FLASHARRAY));
	*(FlashArray[dataIndex]) = FLASHARRAY[dataIndex];
	return;
}
void HandlerDown(const uint8_t id,const Joystick::State which ){
	if(dataIndex <= 3)
		FLASHARRAY[dataIndex] -=0.1;
	else if(dataIndex <= 9 )
		FLASHARRAY[dataIndex] -=0.01;
	else
		FLASHARRAY[dataIndex] -=0.1;
	FlashPtr->Write(FLASHARRAY,sizeof(FLASHARRAY));
	*(FlashArray[dataIndex]) = FLASHARRAY[dataIndex];
	return;
}
void HandlerLeft(const uint8_t id,const Joystick::State which ){
	if(dataIndex <= 3)
		FLASHARRAY[dataIndex] +=1;
	else if(dataIndex <= 9 )
		FLASHARRAY[dataIndex] +=0.1;
	else
		FLASHARRAY[dataIndex] +=1;
	FlashPtr->Write(FLASHARRAY,sizeof(FLASHARRAY));
	*(FlashArray[dataIndex]) = FLASHARRAY[dataIndex];
	return;
}
void HandlerRight(const uint8_t id,const Joystick::State which ){
	if(dataIndex <= 3)
		FLASHARRAY[dataIndex] -=1;
	else if(dataIndex <= 9 )
		FLASHARRAY[dataIndex] -=0.1;
	else
		FLASHARRAY[dataIndex] -=1;
	FlashPtr->Write(FLASHARRAY,sizeof(FLASHARRAY));
	*(FlashArray[dataIndex]) = FLASHARRAY[dataIndex];
	return;
}
void HandlerSelect(const uint8_t id,const Joystick::State which ){
	dataIndex++;
	dataIndex = dataIndex%FLASHNUM;
	return;
}


void Button1(const uint8_t id){
	TftPtr->SetRegion(Lcd::Rect(0,0,128,160));
	TftPtr->FillColor(Lcd::kBlack);
	if(show_camera_image){
		show_camera_image = false;
		show_data1 = true;
		show_data2 = false;
	}
	else if(show_data1){
		show_camera_image = false;
		show_data1 = false;
		show_data2 = true;
	}
	else {
		show_camera_image = true;
		show_data1 = false;
		show_data2 = false;
	}


}

void Button2(const uint8_t id){
	car_run = !car_run;
	if(pitState)
		use_TFT = 1;
	else
		use_TFT=0;

	CarInit();
	LeftMotorPtr->SetPower(0);
	RightMotorPtr->SetPower(0);
	pitState = !pitState;
	Pit1Ptr->SetEnable(pitState);
}

void SetLimit(float& differ, float limit){
	if(differ > limit)
		differ = limit;
	else if(differ < -limit)
		differ = -limit;
	return;
}




#endif /* SRC_TIMFILE_FUNCTION_CPP_ */




