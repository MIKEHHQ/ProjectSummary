#coding:utf-8
#Python中声明文件编码的注释，编码格式指定为utf-
#edit by LEZHI ROBOT SSS-LIUsq
import RPi.GPIO as GPIO  #引入块
import time  #引入块
import signal  #引入块
import atexit   #引入块
from PIL import Image#引入块
import serial   #引入块
from socket import *#引入块
from time import ctime#引入块
import binascii#引入块
import threading#引入块
import cv2#引入块
import numpy as np
print("....LEZHIROBOTS START!!!...")#打印启动提示
global Path_Dect_px#定义全局变量
Path_Dect_px = 320#赋值全局变量初值
global Path_Dect_px1#定义全局变量
Path_Dect_px1 = 320#赋值全局变量初值
global Path_Dect_px2#定义全局变量
Path_Dect_px2 = 320#赋值全局变量初值
global Path_Dect_px3#定义全局变量
Path_Dect_px3 = 320#赋值全局变量初值
global Path_Dect_pxcun#定义全局变量，用来存储计算误差，程序中用于滤除干扰
Path_Dect_pxcun = 0#赋值全局变量初值
global Path_Dect_pxcun1#定义全局变量，用来存储计算误差，程序中用于滤除干扰
Path_Dect_pxcun1 = 0#赋值全局变量初值
global Path_Dect_pxcun2#定义全局变量，用来存储计算误差，程序中用于滤除干扰
Path_Dect_pxcun2 = 0#赋值全局变量初值
timet=0 #设置变量初始值为0
jishuT=0#设置变量初始值为0
jishuT2=0#设置变量初始值为0
jishuT3=0#设置变量初始值为0
jiaodu=0#设置变量初始值为0
ld=0#设置变量初始值为0
ld1=0#设置变量初始值为0
ld2=0#设置变量初始值为0
ld3=0#设置变量初始值为0
ld4=0#设置变量初始值为0
one=90#设置变量初始值为80
two=80#设置变量初始值为70
three=70#设置变量初始值为60
four=50#设置变量初始值为50
mind=60#设置变量初始值为
yx=60#设置变量初始值为
yz=200#设置变量初始值为
xian1=100#设置变量初始值为
xian2=200#设置变量初始值为
xian3=280#设置变量初始值为
zuo1=80#设置边界变量初始值为
zuo2=140#设置边界变量初始值为
zuo3=200#设置边界变量初始值为
zuo4=260#设置边界变量初始值为
you1=360#设置边界变量初始值为
you2=420#设置边界变量初始值为
you3=480#设置边界变量初始值为
you4=540#设置边界变量初始值为
#########串口控制初始化为AMA0##########
ser = serial.Serial('/dev/ttyAMA0', 9600)#ser = serial.Serial('/dev/ttyUSB0', 9600)//使用树莓派GPIO8端口作为串口时用AMA0,控制主控仓时，用USB0
if ser.isOpen == False:#串口启动判断
    ser.open()#串口启动 
ser.write(b"T")#串口发送数据
##########机器人方向控制###############
def Motor_Forward():#机器人前进子函数
    print ('motor_Forward')#机器人前进shell窗口打印字符用于提示程序运行状态
    ser.write(b"G")#串口发送数据，主要是给下位机主控仓发送控制指令

def Motor_Backward():#机器人运行子函数
    print ('motor_backward')#机器人前进shell窗口打印字符用于提示程序运行状态
     
def Motor_TurnLeft():#机器人运行子函数
    print ('motor_turnleft')#机器人前进shell窗口打印字符用于提示程序运行状态
    ser.write(b"F")#串口发送数据，主要是给下位机主控仓发送控制指令

def Motor_TurnLeft1():#机器人运行子函数
    print ('motor_turnleft1')#机器人前进shell窗口打印字符用于提示程序运行状态
    ser.write(b"D")#串口发送数据，主要是给下位机主控仓发送控制指令
    
def Motor_TurnLeft2():#机器人运行子函数
    print ('motor_turnleft2')#机器人前进shell窗口打印字符用于提示程序运行状态
    ser.write(b"S")#串口发送数据，主要是给下位机主控仓发送控制指令
    
def Motor_TurnLeft3():#机器人运行子函数
    print ('motor_turnleft3')#机器人前进shell窗口打印字符用于提示程序运行状态
    ser.write(b"A")#串口发送数据，主要是给下位机主控仓发送控制指令

def Motor_TurnRight():#机器人运行子函数
    print ('motor_turnright')#机器人前进shell窗口打印字符用于提示程序运行状态
    ser.write(b"H")#串口发送数据，主要是给下位机主控仓发送控制指令

def Motor_TurnRight1():#机器人运行子函数
    print ('motor_turnright1')#机器人前进shell窗口打印字符用于提示程序运行状态
    ser.write(b"J")#串口发送数据，主要是给下位机主控仓发送控制指令
   
def Motor_TurnRight2():#机器人运行子函数
    print ('motor_turnright2')#机器人前进shell窗口打印字符用于提示程序运行状态
    ser.write(b"K")#串口发送数据，主要是给下位机主控仓发送控制指令
    
def Motor_TurnRight3():#机器人运行子函数
    print ('motor_turnright3')#机器人前进shell窗口打印字符用于提示程序运行状态
    ser.write(b"L")#串口发送数据，主要是给下位机主控仓发送控制指令
   
def Motor_Stop():#机器人运行子函数
    print ('motor_stop')#机器人前进shell窗口打印字符用于提示程序运行状态
    ser.write(b"T")#串口发送数据，主要是给下位机主控仓发送控制指令

##########机器人相对方向控制###############
def jiance2():         #屏幕横向640个像素点，中间值为320
    if (Path_Dect_px3 < int(zuo4))&(Path_Dect_px3 > int(zuo3)): #判断图像处理后计算出来的点位与屏幕中像素点位置关系，同时执行校正。
            Motor_TurnLeft()#调用子函数，执行控制程序
    if (Path_Dect_px3 <= int(zuo3))&(Path_Dect_px3 > int(zuo2)):  #判断图像处理后计算出来的点位与屏幕中像素点位置关系，同时执行校正。
            Motor_TurnLeft1()#调用子函数，执行控制程序
    if (Path_Dect_px3 <= int(zuo2))&(Path_Dect_px3 > int(zuo1)):  #判断图像处理后计算出来的点位与屏幕中像素点位置关系，同时执行校正。
            Motor_TurnLeft2()#调用子函数，执行控制程序
    if (Path_Dect_px <= int(zuo1))&(Path_Dect_px3 >= 0):  #判断图像处理后计算出来的点位与屏幕中像素点位置关系，同时执行校正。
            Motor_TurnLeft3()#调用子函数，执行控制程序  
    if (Path_Dect_px3 > int(you1))&(Path_Dect_px3 <= int(you2)):  #判断图像处理后计算出来的点位与屏幕中像素点位置关系，同时执行校正。
            Motor_TurnRight()#调用子函数，执行控制程序
    if (Path_Dect_px3 > int(you2))&(Path_Dect_px3 <= int(you3)):  #判断图像处理后计算出来的点位与屏幕中像素点位置关系，同时执行校正。
            Motor_TurnRight1()#调用子函数，执行控制程序
    if (Path_Dect_px3 > int(you3))&(Path_Dect_px3 <= int(you4)):  #判断图像处理后计算出来的点位与屏幕中像素点位置关系，同时执行校正。
            Motor_TurnRight2()#调用子函数，执行控制程序
    if (Path_Dect_px3 > int(you4))&(Path_Dect_px3 <= 640):  #判断图像处理后计算出来的点位与屏幕中像素点位置关系，同时执行校正。
            Motor_TurnRight3()#调用子函数，执行控制程序                 
    if (Path_Dect_px3 >= int(zuo4))&(Path_Dect_px3 <= int(you1)):  #判断图像处理后计算出来的点位与屏幕中像素点位置关系，同时执行校正。
            Motor_Forward()#调用子函数，执行控制程序
##########机器人测试数据显示###############    
def xianshi_shuju():
    #print ('ld %d '%ld)   #打印巡线中心点坐标值
    #print ('ld1 %d '%ld1)   #打印巡线中心点坐标值
    #print ('ld2% d '%ld2)   #打印巡线中心点坐标值
    #print ('ld3 %d '%ld3)   #打印巡线中心点坐标值
    #print ('ld4 %d '%ld4)   #打印巡线中心点坐标值
    #print ('_h% d '%_h)   #打印巡线中心点坐标值
    #print (' 点1数求和 %d '%Path_Dect_fre_count)   #打印巡线中心点坐标值
    #print (' 点2数求和 %d '%Path_Dect_fre_count1)   #打印巡线中心点坐标值
    print (' 中心点1 %d '%Path_Dect_px)#在shell窗口打印Path_Dect_px数据
    '''print("yx",yx)#shell窗口打印变量
    print("yz",yz)#shell窗口打印变量
    print("one",one)#shell窗口打印变量
    print("two",two)#shell窗口打印变量
    print("three",three)#shell窗口打印变量
    print("four",four)#shell窗口打印变量
    print("mind",mind)#shell窗口打印变量
    print("xian1",xian1)#shell窗口打印变量
    print("xian2",xian2)#shell窗口打印变量
    print("xian3",xian3)#shell窗口打印变量
    print("jiaodu",jiaodu)#shell窗口打印变量'''
    cv2.circle(frame,(int(Path_Dect_px),int(xian1)),10,(255,0,255),2)#在原始图像中画出圆点位置
    cv2.circle(frame,(int(Path_Dect_px+50),int(xian1)),10,(255,0,255),2)#在原始图像中画出圆点位置
    cv2.circle(frame,(int(Path_Dect_px-50),int(xian1)),10,(255,0,255),2)#在原始图像中画出圆点位置
    cv2.circle(frame,(int(Path_Dect_px+30),int(xian1)),10,(255,0,255),2)#在原始图像中画出圆点位置
    cv2.circle(frame,(int(Path_Dect_px-30),int(xian1)),10,(255,0,255),2)#在原始图像中画出圆点位置
    cv2.circle(frame,(int(Path_Dect_px1),int(xian2)),10,(255,0,255),2)#在原始图像中画出圆点位置
    cv2.circle(frame,(int(Path_Dect_px2),int(xian3)),10,(255,0,255),2)#在原始图像中画出圆点位置
    cv2.circle(frame,(int(Path_Dect_px3),int(xian1)),10,(255,255,0),2)#在原始图像中画出圆点位置
    
    cv2.line(frame, (int(Path_Dect_px),int(xian1)), (int(Path_Dect_px1),int(xian2)), (0,0,255), 3);#在原始图像中画线
    cv2.line(frame, (int(Path_Dect_px1),int(xian2)), (int(Path_Dect_px2),int(xian3)), (0,0,255), 3);#在原始图像中画线
    cv2.line(frame, (int(Path_Dect_px),int(xian1)), (int(Path_Dect_px2),int(xian3)), (0,0,255), 3);#在原始图像中画线
    
    cv2.line(frame, (int(zuo4),0), (int(zuo4),480), (0,255,0), 1);#在原始图像中画线
    cv2.putText(frame,str(zuo4), (int(zuo4), 480), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符 
    cv2.line(frame, (int(zuo3),0), (int(zuo3),480), (0,255,0), 1);#在原始图像中画线
    cv2.putText(frame,str(zuo3), (int(zuo3), 480), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符 
    cv2.line(frame, (int(zuo2),0), (int(zuo2),480), (0,0,255), 1);#在原始图像中画线
    cv2.putText(frame,str(zuo2), (int(zuo2), 480), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符 
    cv2.line(frame, (int(zuo1),0), (int(zuo1),480), (0,0,255), 1);#在原始图像中画线
    cv2.putText(frame,str(zuo1), (int(zuo1), 480), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符 
   
    cv2.putText(frame,"1max", (540, 420), cv2.FONT_HERSHEY_COMPLEX, 0.5, (0, 0, 255))#打印字符 
    cv2.putText(frame,"2max", (540, 400), cv2.FONT_HERSHEY_COMPLEX, 0.5, (0, 0, 255))#打印字符 
    cv2.putText(frame,"3max", (540, 380), cv2.FONT_HERSHEY_COMPLEX, 0.5, (0, 0, 255))#打印字符 
    cv2.putText(frame,"4max", (540, 360), cv2.FONT_HERSHEY_COMPLEX, 0.5, (0, 0, 255))#打印字符 
    cv2.putText(frame,"||max", (540, 440), cv2.FONT_HERSHEY_COMPLEX, 0.5, (0, 0, 255))#打印字符 
   
    cv2.putText(frame,str(one), (600, 420), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符 
    cv2.putText(frame,str(two), (600, 400), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符 
    cv2.putText(frame,str(three), (600, 380), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符 
    cv2.putText(frame,str(four), (600, 360), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符 
    cv2.putText(frame,str(mind), (600, 440), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符 
   
    
    cv2.line(frame, (int(you4),0), (int(you4),480), (0,0,255), 1);#在原始图像中画线
    cv2.putText(frame,str(you4), (int(you4), 480), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符 
    cv2.line(frame, (int(you3),0), (int(you3),480), (0,0,255), 1);#在原始图像中画线
    cv2.putText(frame,str(you3), (int(you3), 480), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符 
    cv2.line(frame, (int(you2),0), (int(you2),480), (0,255,0), 1);#在原始图像中画线
    cv2.putText(frame,str(you2), (int(you2), 480), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符 
    cv2.line(frame, (int(you1),0), (int(you1),480), (0,255,0), 1);#在原始图像中画线
    cv2.putText(frame,str(you1), (int(you1), 480), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符 
   
 
  
    cv2.putText(frame,str(Path_Dect_px2), (int(Path_Dect_px2), int(xian3)), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符
    cv2.putText(frame,str(Path_Dect_px1), (int(Path_Dect_px1), int(xian2)), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符
    cv2.putText(frame,str(Path_Dect_px), (int(Path_Dect_px), int(xian1)), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255))#打印字符
    cv2.imshow('erzhihua',thresh1)        #树莓派桌面显示二值化图像，比较占资源调试完成后注释掉即可
    cv2.imshow('baisexunguan',frame)        #树莓派桌面显示原图像，比较占资源调试完成后注释掉即可
##########图像处理主程序###############   
cap = cv2.VideoCapture(0)   #启动摄像头
width=640 #设置采集的图像宽度为640像素点     
height=480 #设置采集的图像的高度为480像素点    
cap.set(cv2.CAP_PROP_FRAME_WIDTH,width) #设置采集的图像宽度为640像素点
cap.set(cv2.CAP_PROP_FRAME_HEIGHT,height) #设置采集的图像的高度为480像素点
while True:#无限循环执行
##########白色巡管主程序###############    
    #print (' 中心点2 %d '%Path_Dect_px1)#在shell窗口打印Path_Dect_px1数据
    ret,img = cap.read()#读取img图像
    frame=img#img图像转存至frame
    imgGrey = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)#将img图像进行灰度处理
    #cv2.imshow("huidu",imgGrey )#显示灰度图像
    _, thrash = cv2.threshold(imgGrey, yx, 255, cv2.THRESH_BINARY)#二值化处理img灰度图像，大于60处理为白色，小于60处理为黑色
    #cv2.imshow("erzhihua888",thrash)#显示二值化图像
    _, thresh1 = cv2.threshold(imgGrey, yz, 255, cv2.THRESH_BINARY)#二值化处理imGrey灰度图像，大于20处理为白色，小于200处理为黑色
    Path_Dect_fre_count = 1#设置变量初始值为0
    Path_Dect_fre_count1 = 1#设置变量初始值为0
    Path_Dect_fre_count2 = 1#设置变量初始值为0
    Path_Dect_px2_sum = 0#设置变量初始值为0
    Path_Dect_px_sum = 0#设置变量初始值为0
    Path_Dect_px1_sum = 0#设置变量初始值为0
    for j in range(0,640,5):        #采样像素点，5为步进，一共128个点
        if thresh1[int(xian1),j] == 255:     #判断该行中是否为有白色点，如果判断黑色点，将255换成0即可
            Path_Dect_px_sum = Path_Dect_px_sum + j     #像素点坐标值求和
            Path_Dect_fre_count = Path_Dect_fre_count + 1   #像素点个数求和
        if thresh1[int(xian2),j] == 255:     #判断该行中是否为有白色点，如果判断黑色点，将255换成0即可
            Path_Dect_px1_sum = Path_Dect_px1_sum + j     #像素点坐标值求和
            Path_Dect_fre_count1 = Path_Dect_fre_count1 + 1   #像素点个数求和
        if thresh1[int(xian3),j] == 255:      #判断该行中是否为有白色点，如果判断黑色点，将255换成0即可
            Path_Dect_px2_sum = Path_Dect_px2_sum + j     #像素点坐标值求和
            Path_Dect_fre_count2 = Path_Dect_fre_count2 + 1   #像素点个数求和   
    Path_Dect_px2 = (Path_Dect_px2_sum )/(Path_Dect_fre_count2)    #像素中心点为坐标和除以个数计算白色管道坐标中间值   
    Path_Dect_px = (Path_Dect_px_sum )/(Path_Dect_fre_count)    #像素中心点为坐标和除以个数计算白色管道坐标中间值  
    Path_Dect_px1 = (Path_Dect_px1_sum )/(Path_Dect_fre_count1) #像素中心点为坐标和除以个数计算白色管道坐标中间值 
    if thresh1[int(xian1),int(Path_Dect_px)] == 0: #判断计算出来的像素点位是否为错误黑点   
       Path_Dect_px = Path_Dect_pxcun #当该点为黑色时，自动将上一个位置存储数据赋给当前变量  
    if thresh1[int(xian2),int(Path_Dect_px1)] == 0:  #判断计算出来的像素点位是否为错误黑点     
       Path_Dect_px1 = Path_Dect_pxcun1  #当该点为黑色时，自动将上一个位置存储数据赋给当前变量  
    if thresh1[int(xian3),int(Path_Dect_px2)] == 0: #判断计算出来的像素点位是否为错误黑点      
       Path_Dect_px2 = Path_Dect_pxcun2  #当该点为黑色时，自动将上一个位置存储数据赋给当前变量  
    #像素中心点为坐标和除以个数计算白色管道坐标中间值  
    Path_Dect_pxcun = Path_Dect_px#坐标
    Path_Dect_pxcun1 = Path_Dect_px1#坐标
    Path_Dect_pxcun2 = Path_Dect_px2#坐标
    Path_Dect_px3 = (Path_Dect_px+Path_Dect_px1+Path_Dect_px2)/3  #像素点坐标均值     
    '''if(Path_Dect_pxcun1>200):#比较两个坐标做差的数据大小，此程序为了抗环境爆点干扰而设置
        Path_Dect_px=Path_Dect_px1#强制缩小数据漂移范围
    if(Path_Dect_pxcun>200):#比较两个坐标做差的数据大小，此程序为了抗环境爆点干扰而设置
        Path_Dect_px=Path_Dect_px2 #强制缩小数据漂移范围  ''' 
    jiance2()#执行点位判断，并控制转向
    ld = thresh1[int(xian1),int(Path_Dect_px)]#强制取出该点位的灰度数据值
    ld1 = thresh1[int(xian1),int(Path_Dect_px+30)]#强制取出该点位的灰度数据值
    ld2 = thresh1[int(xian1),int(Path_Dect_px-30)]#强制取出该点位的灰度数据值
    ld3 = thresh1[int(xian1),int(Path_Dect_px+50)]#强制取出该点位的灰度数据值
    ld4 = thresh1[int(xian1),int(Path_Dect_px-50)]#强制取出该点位的灰度数据值
    jiaodu=(Path_Dect_px-Path_Dect_px2)
    xianshi_shuju()#显示图像数据
    ser.flushInput() #释放串口资源
    Path_Dect_px_sum = 0#设置变量为0
    Path_Dect_px1_sum = 0#设置变量为0
    Path_Dect_px2_sum = 0 #设置变量为0


###########形状识别主程序###############     
        
    kernel = np.ones((5,5),np.uint8)#卷积核设置 
    erosion = cv2.erode(thrash,kernel,iterations = 10)#腐蚀处理
    #cv2.imshow("fushi",erosion )#显示腐蚀图像
    kernel = np.ones((10,10),np.uint8)#卷积核设置
    thrash = cv2.dilate(erosion,kernel,iterations =1)#膨胀处理
    #cv2.imshow("pengzhang",thrash )#显示膨胀图像
    contours, _ = cv2.findContours(thrash, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)#轮廓寻找
    for contour in contours:#遍历轮廓
        approx = cv2.approxPolyDP(contour, 0.008* cv2.arcLength(contour, True), True)#计算轮廓线
        #cv2.drawContours(img, [approx], 0, (0, 0, 0), 5)#绘制轮廓线
        x = approx.ravel()[0]#廓线坐标
        y = approx.ravel()[1] - 5  #廓线坐标
    
        if (timet>10000):#变量大于等于1000，执行清零运算
           timet=0#设置变量初始值为0
           jishuT2=0#设置变量初始值为0
           jishuT3=0#设置变量初始值为0
        timet=timet+1     #变量自加运算
        if len(approx) <= 3:#如果轮廓线小于等于3条
            ser.write(b"c")#串口发送c字符
            print("LED OPEN")#shell窗口打印open
            
        elif len(approx) < 13:#如果轮廓线小于等于13条
            jishuT2=jishuT2+1
            if (jishuT2>=5)&(y<420)&(y>300):#如果识别到小于13条轮廓线的轮廓次数大于5次，且轮廓y坐标在300-420之间
                ser.write(b"q")#串口发送q字符
                print("Square")#shell窗口打印Square
                jishutT2=0
                cv2.drawContours(img, [approx], 0, (0, 0, 0), 5)#绘制轮廓
                cv2.putText(img, "FangKuai", (x, y), cv2.FONT_HERSHEY_COMPLEX, 0.5, (255, 0, 0))#打印字符
        else:#如果轮廓线大于13条
            jishuT3=jishuT3+1
            if (jishuT3>=5)&(y<420)&(y>300):#如果识别到小于13条轮廓线的轮廓次数大于5次，且轮廓y坐标在300-420之间
                ser.write(b"y")#串口发送y字符
                print("Circule")#shell窗口打印Circule
                jishutT3=0
                cv2.drawContours(img, [approx], 0, (0, 0, 0), 5)#绘制轮廓
                cv2.putText(img, "YuanXing", (x, y), cv2.FONT_HERSHEY_COMPLEX, 0.5, (0, 0, 255))#打印字符
    cv2.imshow("xingzhuangshibie", img)#显示形状识别图像

###########第一条线位按钮调试程序###############
    if cv2.waitKey(1)&0XFF ==ord('a'):#检测到按键a
        xian1=xian1-1
    if cv2.waitKey(1)&0XFF ==ord('s'):#检测到按键s
        xian1=xian1+1
###########第二条线位按钮调试程序###############        
    if cv2.waitKey(1)&0XFF ==ord('d'):#检测到按键d
        xian2=xian2-1  
    if cv2.waitKey(1)&0XFF ==ord('f'):#检测到按键f
        xian2=xian2+1
###########第三条线位按钮调试程序###############        
    if cv2.waitKey(1)&0XFF ==ord('g'):#检测到按键g
        xian3=xian3-1
    if cv2.waitKey(1)&0XFF ==ord('h'):#检测到按键h
        xian3=xian3+1
########### Forward范围区间按钮调试程序###############    
    if cv2.waitKey(1)&0XFF ==ord('A'):#检测到按键A
        zuo4=zuo4+1
        you1= you1-1
    if cv2.waitKey(1)&0XFF ==ord('S'):#检测到按键S
        zuo4=zuo4-1
        you1= you1+1
########### Four-Three范围区间按钮调试程序###############         
    if cv2.waitKey(1)&0XFF ==ord('D'):#检测到按键D
        zuo3=zuo3+1
        you2= you2-1 
    if cv2.waitKey(1)&0XFF ==ord('F'):#检测到按键F
        zuo3=zuo3-1
        you2= you2+1
########### Three-Two范围区间按钮调试程序###############         
    if cv2.waitKey(1)&0XFF ==ord('G'):#检测到按键G
        zuo2=zuo2+1
        you3= you3-1 
    if cv2.waitKey(1)&0XFF ==ord('H'):#检测到按键H
        zuo2=zuo2-1
        you3= you3+1
########### Two-one范围区间按钮调试程序###############         
    if cv2.waitKey(1)&0XFF ==ord('J'):#检测到按键J
        zuo1=zuo1+1
        you4= you4-1 
    if cv2.waitKey(1)&0XFF ==ord('K'):#检测到按键K
        zuo1=zuo1-1
        you4= you4+1    
########### One-Four速度按钮调试程序###############               
    if cv2.waitKey(1)&0XFF ==ord('w'):#检测到按键w
        one=one-1
        ser.write(b"w")
    if cv2.waitKey(1)&0XFF ==ord('e'):#检测到按键e
        two=two-1
        ser.write(b"e")
    if cv2.waitKey(1)&0XFF ==ord('r'):#检测到按键r
        three=three-1
        ser.write(b"r")
    if cv2.waitKey(1)&0XFF ==ord('t'):#检测到按键t
        four=four-1
        ser.write(b"t")
    if cv2.waitKey(1)&0XFF ==ord('z'):#检测到按键z
        mind=mind+1
        ser.write(b"Z")
    if cv2.waitKey(1)&0XFF ==ord('x'):#检测到按键x
        mind=mind-1
        ser.write(b"X")
    if cv2.waitKey(1)&0XFF ==ord('p'):#检测到按键p
        two=80#设置变量初始值为
        one=90#设置变量初始值为
        three=70#设置变量初始值为
        four=50#设置变量初始值为
        xian1=100#设置变量初始值为
        xian2=200#设置变量初始值为
        xian3=280#设置变量初始值为
        ser.write(b"p")
########### 巡管道阈值按钮调试程序############### 
    if cv2.waitKey(1)&0XFF ==ord('n'):#检测到按键n
        yz=yz-1
    if cv2.waitKey(1)&0XFF ==ord('m'):#检测到按键n
        yz=yz+1
    if cv2.waitKey(1)&0XFF ==ord('q'):#检测到按键q退出
       break
cv2.destroyAllWindows()