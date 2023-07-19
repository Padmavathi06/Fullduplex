import matplotlib.pyplot as plt 
def ans(n,h,psna): 
 local=0 
 for i in range(2): 
 local=local+((pow(psna,((n*h)-1-i)))*(pow((1-psna),i))*(((n*h)-1-i)/((n*h)-i))) 
 return local 
def Symmetric_Throughput(): 
 n=10 # Keeping The Number Of Stations Per Group As 10 
 tcc=73 # Tcc = PIFS + OFDM dur + SIFS + OFDM dur (i.e 25+16+16+16 = 73 micro sec) 
 h=0.2 
 ttx=232 # Ttx = SIFS + Ptx + SIFS + OFDM dur(i.e 16+184+16+16 = 232 micro sec) 
 psta=1 # Probability That Station Has Data 
 pap=1 # Probability That AP Has Data 
 paasy=0 
 for i in range(2): 
 x=[] 
 y=[] 
 psa=psta*pap # The Probability That Station And AP Have Data To Send To Each Other 
 psna=psta*(1-pap) # The Probability That a Station Has Data To Send, But The AP Does Not Have Data  
For The Station 
 pnsa=(1-psta)*pap # The Probability That a Station Does Not Have Data,But The AP Has Data For theStation
 paasy=ans(n,h,psna) 
 psasy=ans(n,h,pnsa) 
 esy=n*psa # The Expected Number Of Symmetric Transmissions Per Group 
 easy=n*psna*(1-(pow((1-(pap+psa)+(pnsa*paasy)),2))) # The Expected Number Of Asymmetric  
Transmissions Per Group 
 ehd=n*pnsa*(pow((1-(psta+psa+(pnsa*paasy))),2)) # The Expected Number Of Half Duplex Downlink  
Transmissions Per Group 
 ehu=n*psna*(pow((1-(pap+psa+(psna*psasy))),2)) # The Expected Number Of Half Duplex Uplink  
Transmissions Per Group 
 s=((2*esy)+(2*easy)+ehd+ehu)*9600 
 s/=tcc+((esy+easy+ehd+ehu)*ttx) #Throughput Of FDC MAC Protocol 
 for i in range(7): 
 x.append((i+1)*10) 
 y.append(s) 
 plt.plot(x,y,label ="FDC") 
 ttx=186 
 d=[57.3,56.2,55.6,55.2,54.5,53.8,53.3] # DFD Protocol Throughput Values Taken From Base Paper For  
Comparison 
 e=[46.3,46.2,45.9,45.9,45.8,45.8,45.8] #ASYM Protocol Throughput Values Taken From Base Paper For  
Comparison 
 plt.plot(x,d,label ="DFD") 
 plt.plot(x,e,label ="ASYM") 
 plt.xlabel('Number Of Stations') 
 plt.ylabel('Throughput') 
 plt.title('Symmetric') 
 plt.legend()
 plt.show() 
 print(x,y) 
def range_with_floats(start,stop,step): 
 while stop > start: 
 yield start 
 start += step 
def Asymmetric_Throughput(): 
 n=10 # Keeping The Number Of Stations Per Group As 10 
 h=0.2 # The Probability That a Station Has Hidden Relationship With Another 
 tcc=73 # Tcc = PIFS + OFDM dur + SIFS + OFDM dur (i.e 25+16+16+16 = 73 micro sec) 
 ttx=216 # Ttx = SIFS + Ptx + SIFS + OFDM dur(i.e 16+184+16+16 = 232 micro sec) 
 for i in range(2): 
 a=[] 
 b=[] 
 for k in range_with_floats(0.1,0.9,0.1): 
 psta=k # Probability That Station Has Data 
 pap=k # Probability That AP Has Data 
 paasy=0 
 psa=psta*pap # The Probability That Station And AP Have Data To Send To Each Other 
 psna=psta*(1-pap) # The Probability That a Station Has Data To Send, But The AP Does Not Have  
Data For The Station 
 pnsa=(1-psta)*pap # The Probability That a Station Does Not Have Data,But The AP Has Data For the  
Station 
 paasy=ans(n,h,psna) 
 psasy=ans(n,h,pnsa)
 esy=n*psa # The Expected Number Of Symmetric Transmissions Per Group 
 easy=n*psna*(1-(pow((1-(pap+psa)+(pnsa*paasy)),2))) # The Expected Number Of Asymmetric  
Transmissions Per Group 
 ehd=n*pnsa*(pow((1-(psta+psa+(pnsa*paasy))),2)) # The Expected Number Of Half Duplex  
Downlink Transmissions Per Group 
 ehu=n*psna*(pow((1-(pap+psa+(psna*psasy))),2)) # The Expected Number Of Half Duplex Uplink  
Transmissions Per Group 
 s=((2*esy)+(2*easy)+ehd+ehu)*9600 
 s/=tcc+((esy+easy+ehd+ehu)*ttx) #Throughput Of FDC MAC Protocol 
 a.append(k) 
 b.append(s) 
 plt.plot(a,b,label="FDC") 
 ttx=186 
 c=[43.2,53.4,55.7,57.2,57.3,57.4,57.4,57.5,57.5] 
 d=[42.1,44.7,44.7,44.8,44.8,44.9,45.1,45.1,45.1] 
 plt.plot(a,c,label="DFD") 
 plt.plot(a,d,label="ASYM") 
 plt.xlabel('Transmission Probability') 
 plt.ylabel('Throughput') 
 plt.title('Asymmetric') 
 plt.legend() 
 plt.show() 
Symmetric_Throughput() 
Asymmetric_Throughput()
