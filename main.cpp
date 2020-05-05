#include<iostream>
#include<fstream>
#include<stdlib.h> //for exit() and system("clear")
#include<iomanip> //for setprecision()
using namespace std;
//global variable declaration
int k=7,r=0,flag=0;
struct date
{
    int mm,dd,yy;
};

ofstream fout;
ifstream fin;

class item
{
    protected:
    int itemno;
    char name[25];
    date d;
    public:
    void add()
    {
        cout<<"\n\n\tItem No: ";
        cin>>itemno;
        cout<<"\n\n\tName of the item: ";
        cin>>name;
        cout<<"\n\n\tManufacturing Date(dd-mm-yy): ";
        cout<<"\n\t\tEnter date :";cin>>d.dd;
        cout<<"\t\tEnter month :";cin>>d.mm;
        cout<<"\t\tEnter year :";cin>>d.yy;
    }
    void show()
    {
        cout<<"\n\tItem No: ";
        cout<<itemno;
        cout<<"\n\n\tName of the item: ";
        cout<<name;
        cout<<"\n\n\tDate : ";
        cout<<d.dd<<"-"<<d.mm<<"-"<<d.yy;
    }
    int retno()
    {
        return(itemno);

    }

};

class amount: public item
{
    float price,qty,tax,gross,dis,netamt;
    public:
    void add();
    void show();
    void report();
    void calculate();
    void pay();
    float retnetamt()
    {
        return(netamt);
    }
    void update(int);  
} amt;

void amount::add()
{
    item::add();
    cout<<"\n\n\tPrice: ";
    cin>>price;
    cout<<"\n\n\tQuantity: ";
    cin>>qty;
    cout<<"\n\n\tTax percent: ";
    cin>>tax;
    cout<<"\n\n\tDiscount percent: ";
    cin>>dis;
    calculate();
    fout.write((char *)&amt,sizeof(amt));
    fout.close();
}
void amount::calculate()
{
    gross=price+(price*(tax/100));
    netamt=qty*(gross-(gross*(dis/100)));
}
void amount::show()
{
    fin.open("itemstore.dat",ios::binary);
    fin.read((char*)&amt,sizeof(amt));
    item::show();
    cout<<"\n\n\tNet amount: ";
    cout<<netamt;
    fin.close();
}

void amount::report()
{
    cout<<"\t";cout<<itemno;
    cout<<"\t";cout<<name;
    cout<<"\t";cout<<price;cout<<"\t";
    cout<<qty;cout<<"\t\t";
    cout<<tax;cout<<"\t";
    cout<<dis;cout<<"\t";
    cout<<"     "<<netamt;cout<<"\n";
    k=k+1;
    if(k==50)
    {
        cout<<"PRESS ANY KEY TO CONTINUE...";
        k=7;
        cout<<" ITEM DETAILS ";
        cout<<"NUMBER";
        cout<<"NAME";
        cout<<"PRICE";
        cout<<"QUANTITY";
        cout<<"TAX";
        cout<<"DEDUCTION";
        cout<<"NET AMOUNT";
    }
}

void amount::pay()
{
    show();
    cout<<"\n\n\n\t\t*********************************************";
    cout<<"\n\t\t                 DETAILS                  ";
    cout<<"\n\t\t*********************************************";
    cout<<"\n\n\t\tPRICE                     :"<<price;
    cout<<"\n\n\t\tQUANTITY                  :"<<qty;
    cout<<"\n\t\tTAX PERCENTAGE              :"<<tax;
    cout<<"\n\t\tDISCOUNT PERCENTAGE         :"<<dis;
    cout<<"\n\n\n\t\tNET AMOUNT              :Rs."<<netamt;
    cout<<"\n\t\t*********************************************\n\n";
}
void amount::update(int ino) 
{ 
    // code to update and modify 
    // the content of the binary file 
    int t, flag = 0; 
  
    // rno=9 
    fstream fs; 
    fs.open("itemstore.dat", 
            ios::in | ios::binary | ios::out); 
  
    while (!fs.eof()) { 
        // storing the position of 
        // current file pointer i.e. at 
        // the end of previously read record 
        t = fs.tellg(); //returns the pointer position
  
        fs.read((char*)this, sizeof(amount)); 
        if (fs) { 
  
            // comparing the roll no with that 
            // of the entered roll number 
            if (ino == itemno) { 
                flag = 1; 
  
                // setting the new (modified ) 
                // data of the object or new record 
                cout<<"\n\n\t\t***************Enter New Details*************\n ";
                add(); 
  
                // placing the put(writing) pointer 
                // at the starting of the  record 
                fs.seekp(t); //to put the file pointer to the position specified by t
  
                // writing the object to the file 
                fs.write((char*)this, sizeof(amt)); 
  
                // display the data 
                cout<<"\n\t\tItem Details edited";
                show(); 
                break; 
            } 
        } 
    } 
    fs.close(); 
  
    if (flag == 1) 
        cout << "\nrecord successfully modified \n"; 
    else
        cout << "\nrecord not found \n"; 
}
int main()
{
    cout.setf(ios::fixed); //to fix the number of decimal points to 2
    cout.setf(ios::showpoint); //to show decimal point and trailing 0s of floating point numbers even if they are not needed
    cout<<setprecision(2);
    fstream tmp("temp.dat",ios::binary|ios::out);
menu:
    cout<<"\n===========================Super Market Billing ";
    cout<<"===========================\n\n";
    cout<<"\n\t\t1.Bill Report\n\n";
    cout<<"\t\t2.Add/Remove/Edit Item\n\n";
    cout<<"\t\t3.Show Item Details\n\n";
    cout<<"\t\t4.Exit\n\n";
    cout<<"\t\tPlease Enter Required Option: ";
    int ch,ff;
    float gtotal;
    cin>>ch;
    switch(ch)
    {
    case 1:
ss:
        cout<<"\n\n\t\t ================Bill Details";
        cout<<"================\n";
        cout<<"\n\t\t1.All Items\n\n";
        cout<<"\t\t2.Back to Main menu\n\n";
        cout<<"\t\tPlease Enter Required Option: ";
        int cho;
        cin>>cho;
        if(cho==1)
        {
            cout<<"\n\n\n\t    ***************BILL DETAILS*************\n ";
            cout<<"\n\tITEM NO";
            cout<<"\tNAME";
            cout<<"\tPRICE";
            cout<<"\tQUANTITY";
            cout<<"\tTAX %";
            cout<<"\tDISCOUNT %";
            cout<<"  NET AMOUNT\n";
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);//to bring the file pointer to the beginning of the file
            gtotal=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    amt.report();
                    gtotal+=amt.retnetamt();
                    ff=0;
                }
                if(ff!=0) gtotal=0;
            }
            cout<<"\n\t\t\tGrand Total="<<gtotal;
            fin.close();
        }
        if(cho==2)
        {
            goto menu;
        }
        goto ss;
    case 2:
db:
        cout<<"\n\t\t =================Bill Editor";
        cout<<"=================\n\n";
        cout<<"\n\t\t1.Add Item Details\n\n";
        cout<<"\t\t2.Edit Item Details\n\n";
        cout<<"\t\t3.Delete Item Details\n\n";
        cout<<"\t\t4.Back to Main Menu ";
        int apc;
        cout<<"\n\n\t\tPlease Enter Required Option: ";
        cin>>apc;
        switch(apc)
        {
        case 1:
            fout.open("itemstore.dat",ios::binary|ios::app);
            amt.add();
            cout<<"\n\t\tItem Added Successfully!";
            goto db;

        case 2:
            int ino;
            flag=0;
            cout<<"\n\n\tEnter Item Number to be Edited :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            r=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    int x=amt.item::retno();
                    if(x==ino)
                    {
                        flag=1;
                        fout.seekp(r*sizeof(amt));
                        cout<<"\n\n\t\t***************CURRENT DETAILS*************\n ";
                        amt.show();
                        amt.update(ino);
                        break;      
                    }
                }
                r++;
            }
            if(flag==0)
            {
                cout<<"\n\t\tItem No does not exist...Please Retry!";
                goto db;
            }
            fin.close();
            goto db;

        case 3:
            flag=0;
            cout<<"\n\n\tEnter Item Number to be deleted :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            while(fin.read((char*)&amt, sizeof(amt)))
            {
                int x=amt.item::retno();
                if(x!=ino)
                    tmp.write((char*)&amt,sizeof(amt));
                else
                {
                    flag=1;
                }
            }
            fin.close();
            tmp.close();
            fout.open("itemstore.dat",ios::trunc|ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat",ios::binary|ios::in);
            if(!tmp)
            {
                cout<<"Error in File";
                goto db;
            }
            while(tmp.read((char*)&amt,sizeof(amt)))
                fout.write((char*)&amt,sizeof(amt));
            tmp.close();
            fout.close();
            if(flag==1)
                cout<<"\n\t\tItem Succesfully Deleted";
            else if (flag==0)
                cout<<"\n\t\tItem does not Exist! Please Retry";
            goto db;
        case 4:
            goto menu;
        default:
            cout<<"\n\n\t\tWrong Choice!!! Retry";
            goto db;
        }
    case 3:
        system("clear");
        flag=0;
        int ino;
        cout<<"\n\n\t\tEnter Item Number :";
        cin>>ino;
        fin.open("itemstore.dat",ios::binary);
        if(!fin)
        {
            cout<<"\n\nFile Not Found...\nProgram Terminated!";
            goto menu;
        }
        fin.seekg(0);
        while(fin.read((char*)&amt,sizeof(amt)))
        {
            int x=amt.item::retno();
            if(x==ino)
            {
                amt.pay();
                flag=1;
                break;
            }
        }
        if(flag==0)
            cout<<"\n\t\tItem does not exist....Please Retry!";
        fin.close();
        goto menu;
    case 4:
        system("clear");
        cout<<"\n\tARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
        char yn;
        cin>>yn;
        if((yn=='Y')||(yn=='y'))
        {
            system("clear");
            cout<<"\n            ************************** THANKS **************************\n\n";
            exit(0);
        }
        else if((yn=='N')||(yn=='n'))
            goto menu;
        else
        {
            goto menu;
        }
    default:
        cout<<"\n\n\t\tWrong Choice....Please Retry!";
        goto menu;
    }
    return 0;
}

