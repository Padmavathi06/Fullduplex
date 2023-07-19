#include<iostream> 
using namespace std; 
long double time1=0.0; 
double packetsize=1500.0; 
double total_data_size=2E+06; 
int trans=0; //Total Transmission Period 
int coord=0; //Total Coordination Period 
int gid=0; //Group ID 
int user_sta[57]; //The Station Numbers Which Have Data For AP  
int user_ap[57]; //The Station Numbers For Which AP Has Data  
int sta[57]; 
int channel[57]; 
int status[3][18]; //Indicates If The Station Has Data For The AP(Status is Set As 1 If It Has Data)  
int status_ap[3][18]; //Indicates If The AP Has Data For The Station (Status is Set As 1 If AP Has Data) 
int ap=0; 
int request[3][18]; 
int n=0; //Total Number of Stations 
int n1=0; //Stations In Each Group 
int n2=0; //Temporary Variable to Store The Group 2's First Station 
int n3=0; //Temporary Variable to Store The Group 3's First Station 
void remove() //Function To Remove Garbage Values 
{ 
 for(int i=0;i<57;i++) 
 { 
 user_sta[i]=0;
 user_ap[i]=0; 
 sta[i]=0; 
 } 
 for(int i=0;i<2;i++) 
 { 
 for(int j=0;j<18;j++) 
 { 
 status[i][j]=0; 
 status_ap[i][j]=0; 
 request[i][j]=0; 
 } 
 } 
} 
int transfer(int n4,int i) //This Function Calculates the Data Transferred 
{ 
 double size=2E+06; 
 int ans=int(size/packetsize); 
 channel[n4+i]+=ans; 
 return ans; } 
double duration() // This Function Returns The Time Taken For Each Transmission 
{ 
 double rate=65E+06; 
 double size=2E+06; 
 double ans=(size*8)/rate; 
 ans=ans*(1E+06); 
 return ans; 
} 
void collection(int &n4,int &gid) //This Function Collects All The Transmission Requests And Reports It to  
AP( Happens Once Per Group) 
{ cout<<"\nCollection Period is Started for Group "<<gid+1<<"\n"; 
 time1+=16.1; // This is PIFS Time(16.1 microseconds) 
 for(int i=0;i<n1;i++) 
 { 
 if(status[gid][i]>=1) 
 { 
 request[gid][i]=1; 
 cout<<"\nStation "<<(n4+i+1)<<" Has Data To AP"; 
 cout<<"\nStation "<<(n4+i+1)<<" Notify Their Transmission Request To AP \n"; 
 } 
 } 
 cout<<"\nCollection Period Completed\n"; 
} 
void sym_transmission(int &n4,int i) // This Function Performs Symmetric Full Duplex Transmission Via  
Assigned Subchannels 
{ 
 trans++; 
 cout<<"\nSymmetric Full Duplex Transmission Between Station "<<n4+i+1<<" And AP"; 
 cout<<"\nData is Transmitted Via Sub-Channel "<<((n4+i)%n1)+1; 
 sta[n4+i]+=transfer(n4,i); 
 ap+=transfer(n4,i); 
 time1+=duration(); 
 request[gid][i]=999; 
 status[gid][i]=999; 
 status_ap[gid][i]=999; 
 cout<<"\nSymmetric Full Duplex Transmission Period Completed\n"; 
} 
void asym_transmission(int &n4,int i,int j) // This Function Performs Asymmetric Full Duplex Transmission Via Assigned Subchannels
{ 
 trans++; 
 cout<<"\nHidden Relationship Between "<<n4+i+1<<" And "<<n4+j+1; 
 cout<<"\nAsymmetric Full Duplex Transmission Between "<< n4+i+1<< "And "<<n4+j+1<<" Stations  
Via AP"; 
 cout<<"\nData is Transmitted Via Sub-Channels "<<((n4+i)%n1)+1<<" And "<<n4+j+1<<" Stations Via  
AP ";  
 ap+=transfer(n4,i); 
 sta[n4+j]+=transfer(n4,j); 
 time1+=duration(); 
 request[gid][i]=999; 
 status[gid][i]=999; 
 status_ap[gid][j]=999; 
 cout<<"\nAsymmetric Full Duplex Transmission Period Completed\n"; 
} 
void half_transmission(int &n4, int i) // This Function Performs Half Duplex Transmission Via Assigned  
Subchannels 
{ 
 trans++; 
 if(request[gid][i]==1) 
 { 
 cout<<"\nHalf Duplex Transmission Between Station "<<n4+i+1<<" And AP"; 
 cout<<"\nData is Transmitted Via Sub-Channel "<<((n4+i)%n1)+1; 
 ap+=transfer(n4,i); 
 time1+=duration(); 
 request[gid][i]=status[gid][i]=999; 
 } 
 else 
 { 
 if(status_ap[gid][i]==1){ 
 cout<<"\nHalf Duplex Transmission Between AP And Station "<<n4+i+1; 
 cout<<"\nData is Transmitted Via Sub-Channel "<<((n4+i)%n1)+1; 
 sta[n4+i]+=transfer(n4,i); 
 time1+=duration(); 
 status_ap[gid][i]=999; } } 
cout<<"\nHalf Duplex Transmission Completed\n"; } 
void coordination(int &n4) // This Function Coordinates All The Transmission Requests From Collection  
Period And Assigns The Order Of Transmission 
{ 
 cout<<"\nCoordination Period is Started\n"; 
 time1+=16.1; 
 for(int i=0;i<n1;i++) 
 { 
 if(request[gid][i]==1 && status_ap[gid][i]==1) 
 { 
 sym_transmission(n4,i); 
 }  
 } 
 for(int i=0;i<n1;i++) 
 { 
 if(request[gid][i]==1 && status_ap[gid][i]==0) 
 { 
 for(int j=0;j<n1;j++) 
 { 
 if(status_ap[gid][j]==1) 
 { 
 asym_transmission(n4,i,j); 
 break; 
 }
 } } }  
for(int i=0;i<n1;i++) 
{ 
 if(request[gid][i]==1 || status_ap[gid][i]==1)  
 half_transmission(n4,i); 
} 
cout<<"\nCoordination Period Ends\n"; 
} 
void throughput(int m1,int m2) // This Function Calculates Throughput 
{ 
 int packets_transfered = (total_data_size/packetsize); 
 long double time2 = time1/1000; 
 int total_no_of_transmissions =m1+m2; 
 long double throughput1 =  
((packets_transfered*total_no_of_transmissions*packetsize)/(time2))*(8.0/1000)*(2.0/3); 
 cout<<"\nThroughput is \t"<<throughput1<<"\n"; 
} 
int main() 
{ 
 remove(); 
 int m1; // The Number Of Stations Which Have Data for AP 
 int m2; // The Number Of Stations For Which AP Has Data 
 int c_gid=1; 
 cout<<"\nEnter The Number Of Stations(Between 1 And 57)\n"; 
 cin>>n; 
 n1=int(n/3); 
 n2=n1+1; 
 n3=(n1*2)+1; 
 cout<<"\nStations Are Divided Into 3 Groups And "<<n1<<" Stations In Each Group\n";  
 cout<<"\nEnter The Number Of Stations Which Have Data \n";
 cin>>m1; 
 cout<<"\nEnter The Station Numbers Which Have Data For AP \n"; 
 for(int i=0;i<m1;i++) 
 { 
 cin>>user_sta[i];// Getting Input From User For The Station Numbers 
 } 
 for(int k=0;k<m1;k++) 
 { 
 if(user_sta[k]<=n1) 
 { 
 for(int i=0,j=0;j<n1;j++) 
 { 
 if(user_sta[k]==j+1) 
 { 
 status[i][j]=1; //Setting Status As 1(Group 1) 
 } 
 } 
 } 
 if(user_sta[k]>n1 && user_sta[k]<(n1*2)) 
 { 
 for(int i=1,j=0;j<n1;j++) { 
 if(user_sta[k]%n1==j+1) 
 { 
 status[i][j]=1; //Setting Status As 1(Group 2) 
 } 
 } 
 } 
 if(user_sta[k]>(n1*2) && user_sta[k]<(n1*3)) 
 { for(int i=2,j=0;j<n1;j++) 
 { 
 if(user_sta[k]%n1==j+1) 
 { 
 status[i][j]=1; //Setting Status As 1(Group 3) 
 } 
 } 
 } 
 if(user_sta[k]==(n1*2)) 
 { 
 int last=n1-1; 
 status[1][last]=1;// Setting Status as 1 
 } 
 if(user_sta[k]==(n1*3)) 
 { 
 int last=n1-1; 
 status[2][last]=1; //Setting Status As 1 } } 
cout<<"\nEnter The Number Of Stations For Which AP Has Data \n"; 
cin>>m2; 
cout<<"\nEnter The Station Numbers For Which AP Has Data \n"; 
for(int i=0;i<m2;i++) 
{ 
 cin>>user_ap[i]; // Getting Input From User For The Station Numbers For Which AP Has Data 
} 
for(int k=0;k<m1;k++) 
{ 
 if(user_ap[k]<=n1) 
 { 
 for(int i=0,j=0;j<n1;j++){ 
 if(user_ap[k]==j+1) 
 { 
 status_ap[i][j]=1; //Setting AP_Status As 1(Group 1) 
 } 
 } 
 } 
 if(user_ap[k]>n1 && user_ap[k]<(n1*2)) 
 { 
 for(int i=1,j=0;j<n1;j++) 
 { 
 if(user_ap[k]%n1==j+1) { 
 status_ap[i][j]=1; //Setting AP_Status As 1(Group 2) 
 } 
 } } 
 if(user_ap[k]>(n1*2) && user_ap[k]<(n1*3)) 
 { 
 for(int i=2,j=0;j<n1;j++) 
 { 
 if(user_ap[k]%n1==j+1) 
 { 
 status_ap[i][j]=1; //Setting AP_Status As 1(Group 3) 
 } 
 } 
 } 
 if(user_ap[k]==(n1*2)) 
 { 
 int last=n1-1; 
 status_ap[1][last]=1; //Setting AP_Status As 1
 } 
 if(user_ap[k]==(n1*3)) 
 { 
 int last=n1-1; 
 status_ap[2][last]=1; //Setting AP_Status As 1 
 } 
 } 
for(int i=0;i<3;i++,gid++) 
{ 
 n2=n1*i; 
 collection(n2,gid); //Calling Collection Period 
 coordination(n2); //Calling Coordination Period 
 //After Completion Group ID(gid) is Incremented And Repeated 
 } 
 for(int i=0;i<n;i++) 
 { 
 cout<<"\nNumber Of Packets Received By Station "<<i+1<<" is " <<sta[i]; // Displays The Number Of  
Packets Received By Each Station 
 } 
 cout<<"\nGroup 1\n"; 
 for(int i=0;i<n;i++) 
 { 
 cout<<"\nNumber Of Packets Transmitted Via Sub-Channel "<<(i%n1)+1<<" is " <<channel[i];  
//Displays Packets Transmitted Via The Sub-channel In The Specific Group 
 if(i%n1 == 0 && i != 0) 
 { 
 cout<<"\nGroup "<<c_gid+1<<"\n"; 
 c_gid++; 
 } } 
cout<<"\nNumber Of Packets Received By AP is "<<ap; // Total Packets Received By AP
cout<<"\nTime Taken By The Whole Process is "<<time1; // Total Time Taken For Whole Process 
throughput(m1,m2); // Throughput 
}
