#coding:utf-8
from struct import *
from datetime import datetime, timedelta
import os  
import copy
import os.path
from vtObject import *
import threading  
import imp
import csv
import multiprocessing
lock=multiprocessing.Lock()#一个锁
EMPTY_STRING = ''
EMPTY_UNICODE = u''
EMPTY_INT = 0
jcb={"ru":5;"cu":10;"rb":1;""}
class readt(object):
    def __init__(self):
	bars=[]
   
  	    
    def readbar(self,path):
	pass
 
def writebar(bar,filen):
      filen.write(pack("6sffffii4s4s", bar.symbol,bar.open,bar.high,bar.low,bar.close,bar.volume,bar.openInterest,bar.date,bar.time[0:6]))
   #   print bar.close
def writecsv(bar,filen,tz):
    bcsv=[]
    bcsv.append( bar.symbol)
    bcsv.append( bar.open)
    bcsv.append( bar.high)
    bcsv.append( bar.low)
    bcsv.append( bar.close)
    bcsv.append( bar.volume)
    bcsv.append( bar.openInterest)
    bcsv.append( bar.date)
    bcsv.append( bar.time[0:5])
    qc=bar.close
    if (qc !=0):
	(bae.close-qc()
    tz=tz+""
  #  print bcsv
    filen.writerow(bcsv)
def geth(tk,myfile,date):
    try :
	  h=ord(myfile.read(1))
	  m=ord(myfile.read(1))
	  s=ord(myfile.read(1))
	  ms=ord(myfile.read(1))*10
	  if (ms==0):
		imp.acquire_lock()
		tk.time=str(h+100)[1:3]+':'+str(m+100)[1:3]+':'+str(s+100)[1:3]
		tk.datetime=datetime.strptime(' '.join([date, tk.time]), '%Y%m%d %H:%M:%S') 
		imp.release_lock()
		   # print 'date1' ,self.tk.datetime
	  else:
		imp.acquire_lock()
		tk.time=str(h+100)[1:3]+':'+str(m+100)[1:3]+':'+str(s+100)[1:3]+'.'+str(ms)
		tk.datetime=datetime.strptime(' '.join([date, tk.time]), '%Y%m%d %H:%M:%S.%f')  
		imp.release_lock()
		   # print 'date2',self.tk.datetime
    except TypeError:
	  pass
        
def getp(myfile,tk,date):
      (d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11)=unpack("iiiiiiiiiii",myfile.read(4+4+4+4+4+4+4+4+4+4+4))
      f=float(d1/1000)
      tk.LastPrice=f
	
      f=float(d2/1000)
      tk.HighestPrice=f
      f=float(d3/1000)
      tk.LowestPrice=f
	
      tk.OpenInterest=d4
      tk.Volume=d5
      tk.date=date
      tk.BidVolume1=d8
      tk.AskVolume1=d9
      tk.BidPrice1=d10
      tk.AskPrice1=d11
      
def pretick(tick,barfile,bar,tz,qc):  
    #  print bar.date, tick.vtSymbol,bar.datetime,bar.vtSymbol
      if not bar.vtSymbol:
		    
	  bar.vtSymbol = tick.vtSymbol
	  bar.symbol = tick.vtSymbol
				   #    bar.exchange = tick.exchange
#	  print bar.symbol,bar.datetime
      if not bar.datetime:  
	  bar.open = tick.LastPrice
	  bar.high = tick.LastPrice
	  bar.low = tick.LastPrice
	  bar.close = tick.LastPrice
			    
	  bar.date = tick.date
	  bar.time = tick.time
	  bar.datetime = tick.datetime#.replace(second=0, microsecond=0)
	  bar.volume = tick.Volume
	  bar.openInterest = tick.OpenInterest        
			    # 则继续累加新的K线
      else:      
	  if( bar.datetime.minute != tick.datetime.minute or bar.datetime.hour != tick.datetime.hour):    
	     newBar = copy.copy(bar)  
	     bar.open = tick.LastPrice
	     bar.high = tick.LastPrice
	     bar.low = tick.LastPrice
	     bar.close = tick.LastPrice
				       
	     bar.date = tick.date
	     bar.time = tick.time
	     bar.datetime = tick.datetime#.replace(second=0, microsecond=0)
	     bar.volume = tick.Volume
	     bar.openInterest = tick.OpenInterest  
	     
	  #   print bar.open,bar.high,bar.low,bar.close,bar.datetime,bar.volume,bar.openInterest
	   #  writebar(newBar,barfile) 记录ＢＡＲ
	     writecsv(newBar,barfile,tz,qc)
	     
	  else:
	     bar.high = max(bar.high, tick.LastPrice)
	     bar.low = min(bar.low, tick.LastPrice)
	     bar.volume = tick.Volume
	     bar.openInterest = tick.OpenInterest   
	   #  print	bar.close ,tick.LastPrice	
def gethead(myfile,cm):
      s=myfile.read(8)
      (y)=unpack("h",myfile.read(2))
      yy=y[0]
      m=100+ord(myfile.read(1))
      d=100+ord(myfile.read(1))
      ms=str(m)[1:3]
      ds=str(d)[1:3]
      (d1,d2,d3,d4,d5,d6,d7)=unpack("iiiiiii",myfile.read(4+4+4+4+4+4+4))
      LastPrice = d6/1000        # 今日开盘价
				   
      cm.openInterest =d4          # 持仓量	  
      cm.preClosePrice =d4/1000
				 
      cm.date = str(yy)+ms+ds              # 日期 20151009
				 #  print yy,'|',ms,'|',ds
      cm.datetime = None                    # python的datetime时间对象	  
      cm.upperLimit = d5/1000          # 涨停价
      cm.lowerLimit =d6/1000        # 跌停价	s  
      s=myfile.read(36)
			     
      # print 'self.tk',self.tk.LastPrice  
def protick(filen):
    cm =readt()
      
    vl=os.path.basename(filen)
    tf,ext= os.path.splitext(filen)  
    ext=ext[1:3]
			  
    if not(ext=='tk'):
	return
    dirp=tf+'.csv'
    if  os.path.isfile(dirp):
	  return
    else:		      
      #barfile=open(dirp,'wb')
      f=file(dirp,'wb')
      barfile=csv.writer(f)
      tk=VtTickData()
      
      vln,ext= os.path.splitext(vl)  
  #    print filen,vln,vl,dirp,tf
      tk.vtSymbol=vln
      cm.myfile=open(filen,'rb')
      cm.myfile.seek(0,0)
      cm.myfile.seek(0,2)
      lens =cm.myfile.tell()
      cm.myfile.seek(0,0)
      gethead(cm.myfile,cm)
      i=76
      bar=VtBarData()
      tz=""
      qc=0
      while (True):      
	    geth(tk,cm.myfile,cm.date)
	    getp(cm.myfile,tk,cm.date)
	    
	    pretick(tk,barfile,bar,tz,qc)
	#    print bar.close
	    i=i+48		    
	    if (i==lens):
		  f.close()
		  break   	   		      
def getfile(dirpath): 
      list=[]
      for (root, dirs, files) in os.walk(dirpath):
	    for filen in files:
		  pathf= os.path.join(root,filen)
		  list.append(pathf)
      return list

def main():    
    list=getfile("f:\\tmp")#("G:\\ticks\\SW_NewTick_201301")
   # protick(list[0])
    pool=multiprocessing.Pool(processes=3)#限制并行进程数为3
    pool.map(protick,list)   
     
if __name__ == '__main__':
    main()