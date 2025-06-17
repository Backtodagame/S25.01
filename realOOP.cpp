#include<iostream>
#include<string>
#include<iomanip>
#include<vector>
#include<map>
#include <algorithm> // để dùng sort
#include<fstream>
#include <sstream>


using namespace std;

class BangDiem {
    private:
        map<string, float> bangdiem; // <ten_mon, diem>
        
     public:
         void suaDiem(string mon, float diem);
         float layDiem(string mon);
        
        
     };
class SV {
    private:
        string id, ten, lop;
        BangDiem bd;
    public:
        SV(string id, string ten, string lop)
        {
            this->id = id;
            this->ten = ten;
            this->lop = lop;
        };
        void hienThi1();
        void hienThi2(fstream &Outputfile);
        string getID();
        BangDiem& getBangDiem();
        string getALL();
    };
    

    
    class QuanLySinhVien {
    private:
        vector<SV> danhSach;
        vector<string> tenmon;
    public:
        void themSV();
        void hienThi();
        void format();
        void nhapdiem();
        void hienthidiem();
        void Chinhsuathongtin();
        int luuthongtin(fstream &OutputFile);
        int docthongtin(fstream &InputFile);
    };


void QuanLySinhVien::format()
{
    cout<<left<<setw(10)<<"MSV"<<setw(10)<<"Ten"<<setw(10)<<"Lop";
            
            for(int i=0;i<tenmon.size();i++)
    {
        cout<<left<<setw(10)<<tenmon[i];
    }
        cout<<endl;
}


void QuanLySinhVien::nhapdiem()
{    cin.ignore();
    string monhoc;
  
    while(true)
    {  cout<<"Nhap ten mon hoc\n";
      getline(cin,monhoc);
      bool find=false;
    for(auto &mon:tenmon)
    {
        if(monhoc==mon) 
        {cout<<"Tên môn đã tồn tại\n";
        find=true;
        break;}

    }

       if(!find)  break;

    }
    tenmon.push_back(monhoc);
    sort(tenmon.begin(),tenmon.end());

    cout<<"Nhap diem cho tung sinh vien\n";
    for(auto & ds :danhSach)
    {   
        float diem;
        cout<<"MSV "<<ds.getID()<<endl;
        cout<<"Diem ";
        cin>>diem;
        ds.getBangDiem().suaDiem(monhoc,diem);
        
    }

    
}

void QuanLySinhVien::hienthidiem()
{   cout<<left<<setw(10)<<"MSV"<<setw(10)<<"Ten"<<setw(10)<<"Lop";
//lay cac mon ra truoc 
    for(int i=0;i<tenmon.size();i++)
    {
        cout<<left<<setw(10)<<tenmon[i];
    }
cout<<endl;
for(auto &ds : danhSach)
{   
   
    ds.hienThi1();
   for(int i=0;i<tenmon.size();i++)
   {
    float d=ds.getBangDiem().layDiem(tenmon[i]);
    if (d==9999 or d<0 ) cout<<left<<setw(10)<<"-";
    else cout<<left<<setw(10)<<d;
   }
   cout<<endl;
}


}

BangDiem & SV::getBangDiem()
{
    return bd;
}

float BangDiem::layDiem(string mon)
{
    if(bangdiem.find(mon) !=bangdiem.end())
        return bangdiem[mon];
    else
        return 9999;    
}

void BangDiem::suaDiem(string mon, float diem)
{
    bangdiem[mon]=diem;
}

string SV::getID()
{
    return id;
}

string SV::getALL()
{
    string allinformatin;
    allinformatin=id+"."+ten+"."+lop+".";
    return allinformatin;
}

void SV::hienThi1()
{
    cout<<left<<setw(10)<<id<<setw(10)<<ten<<setw(10)<<lop;
}

void SV::hienThi2(fstream &Outputfile)
{
    Outputfile<<left<<setw(10)<<id<<setw(10)<<ten<<setw(10)<<lop;
}



void QuanLySinhVien::themSV()
{   
    //Them moi 1 sinh vien, can kiem tra MSV da co hay chua ? 
    string id_sv,ten_sv,lop_sv;
    cin.ignore();
    
 
    while(true)     
    {//Kiem tra MSV da ton tai chua
        bool findID=false;
        cout<<"Nhap MSV\n";
        getline(cin,id_sv);
        for(auto &ds:danhSach)
        {   
           
            if (id_sv==ds.getID())
                {   findID=true;
                    cout<<"ID da ton tai, vui long chon 1 ID khac\n";
                    break;
                }          
        }
        
        if(!findID) break;
    } 
    
    //Nhap ten va lop cua sinh vien
    cout<<"Nhap ten cho sinh vien\n";
    getline(cin,ten_sv);
    cout<<"Nhap lop cho sinh vien\n";
    getline(cin,lop_sv);
    danhSach.push_back({id_sv,ten_sv,lop_sv});   
}

void QuanLySinhVien::hienThi()
{   cout<<left<<setw(10)<<"MSV"<<setw(10)<<"Ten"<<setw(10)<<"Lop";
    cout<<endl;
    
    for(int i=0; i<danhSach.size();i++)
    {
        danhSach[i].hienThi1();
        cout<<endl;
    }
}

void QuanLySinhVien::Chinhsuathongtin()
{   
    hienthidiem();
    cout<<"Hay nhap MSV\n";
    string msv;
    cin.ignore();
    getline(cin,msv);
    for(auto &ds : danhSach)
    {
        if(msv==ds.getID())
        {   format();
            ds.hienThi1();
            for(int i=0;i<tenmon.size();i++)
            {
             float d=ds.getBangDiem().layDiem(tenmon[i]);
             if (d==9999 ) cout<<left<<setw(10)<<"-";
             else cout<<left<<setw(10)<<d;
            }
            cout<<endl;
            cout<<"Hay nhap ten mon hoc can cap nhat diem\n";
            for(int i=0;i<tenmon.size();i++)
            {
                cout<<tenmon[i]<<endl;
            }
            string mon;
            getline(cin,mon);
            cout<<"Diem cu "<<ds.getBangDiem().layDiem(mon)<<endl;
            cout<<"Xin moi nhap diem moi ";
            float diemmoi;
            cin>>diemmoi;
            ds.getBangDiem().suaDiem(mon,diemmoi);
            cout<<"Bang diem sau khi cap nhat\n";
            format();
            ds.hienThi1();
            for(int i=0;i<tenmon.size();i++)
            {
             float d=ds.getBangDiem().layDiem(tenmon[i]);
             if (d==9999 ) cout<<left<<setw(10)<<"-";
             else cout<<left<<setw(10)<<d;
            }
            cout<<endl;
        }

        else cout<<"MSV khong ton tai, vui long thu lai\n";
    }
    
    
}

int QuanLySinhVien::luuthongtin(fstream &OutputFile)
{   
    if(!OutputFile.is_open()) 
     {
        cerr<<"Khong The Mo File\n";
        return -1;
     }
     /*   for(auto&ds:danhSach)
        {
            OutputFile<<ds.getALL();
            for(int i=0;i<tenmon.size();i++)
            {
        
             float d=ds.getBangDiem().layDiem(tenmon[i]);
             if (d==9999 ) OutputFile<<left<<"-"<<"_";
             else OutputFile<<left<<d<<"_";

            }
            
        }
        */
       OutputFile<<left<<setw(10)<<"MSV"<<setw(10)<<"Ten"<<setw(10)<<"Lop";
       //lay cac mon ra truoc 
           for(int i=0;i<tenmon.size();i++)
           {
              OutputFile<<left<<setw(10)<<tenmon[i];
           }
       OutputFile<<endl;
       for(auto &ds : danhSach)
       {   
          
        
        ds.hienThi2(OutputFile);
          for(int i=0;i<tenmon.size();i++)
          {
           float d=ds.getBangDiem().layDiem(tenmon[i]);
           if (d==9999 ) OutputFile<<left<<setw(10)<<"-";
           else OutputFile<<left<<setw(10)<<d;
          }
          OutputFile<<endl;
       }


    OutputFile.close();

    return 1;
}
string getstring(string line)
{   string newline;
    for(char c:line)
    {
        if(c>64 and c<123)
        {
            newline.push_back(c);
        }
        if(c>47 and c<58)
        {
          newline.push_back(c);
        }

    }
    return newline;
}

int QuanLySinhVien::docthongtin(fstream &input)
{   
    if(!input.is_open())
        {
            cerr<<"Khong The Mo File\n";
            return 1;
        }

   /* string line;
    int k=0;
    string msv,ten,lop;
    while(getline(input,line,'.'))
    {
        
        
            switch(k)
        {
            case 0: msv=line;
                    k++; 
            break;

            case 1: ten=line;
                    k++;  
            break;

            case 2: lop=line;
                    danhSach.push_back({msv,ten,lop});
                    k=0;
            break;

            
        }

          


    }   */

   

    int k=0;
    string line;
    int i=0;
    int a[100];
    while(getline(input,line))
    {   
        
        if(k==0) {
                string cacmonhoc=line;
                cacmonhoc.erase(0,30);
                int d=cacmonhoc.size();
                while(d>0)
                {   
                string monhoc=cacmonhoc.substr(0,10);
                cacmonhoc.erase(0,10);
                monhoc=getstring(monhoc);
                d=d-10;
                tenmon.push_back(monhoc);
                } 
            k++;
                }   
        
        else {  

                float diem;
                
                string msv=getstring(line.substr(0,5)); 
                string ten=getstring(line.substr(10,9)); 
                string lop=getstring(line.substr(20,9));  
                danhSach.push_back({msv,ten,lop});
                line.erase(0,30);
                int d=line.size();
               
                while(d>0)
                
                {   
                    int z=0;
                    string newline;
                
                    string line1=line.substr(0,2);
                    line.erase(0,10);
                    for(char c:line1)
                    {   
                    if(c>47 and c<58)
                    {
                      newline.push_back(c);
                    }
                    
                    if(c=='-')
                    {   
                        a[i]=9999;
                        i++;
                        z++;
                    }   
                    
                }
                    d=d-10;
                    if(z==0) {
                    int num;
                    stringstream ss(newline);
                    ss>>num;                   
                    a[i]=num;
                    i++;
                    }
                }
                
             
            }        
 
        
            
    }
    int dem=0;
    for(auto &ds:danhSach)
    {   
        for(int i=0;i<tenmon.size();i++)
        {
            ds.getBangDiem().suaDiem(tenmon[i],a[dem]);
            dem++;
        }
    }


    return 0;
}


int main()
{   
    QuanLySinhVien QL;
    fstream inputFile("E:/TXT/TET.txt",ios::in|ios::out); 
    int choice;
    QL.docthongtin(inputFile);
    
    while(true)
    {   cout<<"CHUONG TRINH QUAN LY SINH VIEN BY MINH TRI CODER\n";
        cout<<"CAC TINH NANG DUOC LIET KE BEN DUOI\n";
        cout<<"1. THEM MOI 1 SINH VIEN\n";
        cout<<"2. HIEN THI DANH SACH SINH VIEN\n";
        cout<<"3. THEM 1 MON HOC VA CHO DIEM SINH VIEN\n";
        cout<<"4. XEM DIEM SINH VIEN\n";
        cout<<"5. CHINH SUA DIEM SO \n";
        cout<<"6. LUU DU LIEU \n";
        cout<<"MAKE CHOICE !!\n";
        cin>>choice;

        switch(choice)
        {   


            case 1: QL.themSV();
            break;

            case 2:QL.hienThi();
            break;
            
            case 3: QL.nhapdiem();
            break;

            case 4: QL.hienthidiem();
            break;

            case 5: QL.Chinhsuathongtin();
            break;

            case 6: {fstream outputFile("E:/TXT/TET.txt",ios::out|ios::trunc); 
                    QL.luuthongtin(outputFile);
            break;}

            case 0: 
            return 0;
        }
    }



    return 0;
}