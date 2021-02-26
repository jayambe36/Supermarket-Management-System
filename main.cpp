/*
*
* LG SUPER MARKET BILL MANAGEMENT SYSTEM USING CPP
*/

#include<iostream>
#include<fstream>
#include<stdlib.h> //for exit() and system("clear")
#include<iomanip> //for setprecision()

using namespace std;



int k=7,r=0,flag=0; //global variable declaration

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
        cout <<  endl <<  endl <<"\tItem No: ";
        cin>>itemno;
        cout <<  endl <<  endl <<"\tName of the item: ";
        cin>>name;
        cout <<  endl <<  endl <<"\tManufacturing Date(dd-mm-yy): ";
        cout <<  endl <<"\t\tEnter date :";cin>>d.dd;
        cout<<"\t\tEnter month :";cin>>d.mm;
        cout<<"\t\tEnter year :";cin>>d.yy;
    }


    void show()
    {
        cout <<  endl <<"\tItem No: ";
        cout<<itemno;
        cout <<  endl <<  endl <<"\tName of the item: ";
        cout<<name;
        cout <<  endl <<  endl <<"\tDate : ";
        cout<<d.dd<<"-"<<d.mm<<"-"<<d.yy;
    }


    int retno()
    {
        return(itemno);

    }

};



class amount : public item

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
    cout <<  endl <<  endl <<"\tPrice : "; cin>>price;
    cout <<  endl <<  endl <<"\tQuantity : "; cin>>qty;
    cout <<  endl <<  endl <<"\tTax percent : "; cin>>tax;
    cout <<  endl <<  endl <<"\tDiscount percent : "; cin>>dis;
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
    cout <<  endl <<  endl <<"\tNet amount: "; cout<<netamt;
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
    cout<<"     "<<netamt; cout << endl ;
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
    cout <<  endl <<  endl <<  endl <<"\t\t*********************************************";
    cout <<  endl <<"\t\t                 DETAILS                  ";
    cout <<  endl <<"\t\t*********************************************";
    cout <<  endl <<  endl <<"\t\tPRICE                     :"<<price;
    cout <<  endl <<"\t\tQUANTITY                  :"<<qty;
    cout <<  endl <<"\t\tTAX PERCENTAGE            :"<<tax;
    cout <<  endl <<"\t\tDISCOUNT PERCENTAGE       :"<<dis;
    cout <<  endl  <<  endl <<  endl <<"\t\tNET AMOUNT                :Rs."<<netamt;

    cout<< endl <<  endl << "\t\t*********************************************" <<  endl <<  endl ;
}



void amount::update(int ino)
{
    // code to update and modify
    // the content of the binary file
    int t, flag = 0;


    // rno=9
    fstream fs;
    fs.open("itemstore.dat", ios::in | ios::binary | ios::out);

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
                cout <<  endl <<  endl <<"\t\t***************Enter New Details*************"<<  endl;
                add();

                // placing the put(writing) pointer
                // at the starting of the  record
                fs.seekp(t); //to put the file pointer to the position specified by t

                // writing the object to the file
                fs.write((char*)this, sizeof(amt));

                // display the data
                cout <<  endl <<"\t\tItem Details edited";
                show();
                break;
            }
        }
    }

    fs.close();



    if (flag == 1)

        cout <<  endl << "record successfully modified "<<  endl ;

    else

        cout <<  endl << "record not found "<<  endl ;
}




int main()

{
    cout.setf(ios::fixed); //to fix the number of decimal points to 2
    cout.setf(ios::showpoint); //to show decimal point and trailing 0s of floating point numbers even if they are not needed
    cout<<setprecision(2);
    fstream tmp("temp.dat",ios::binary|ios::out);

menu:

    cout <<  endl <<"===========================Super Market Billing ";
    cout<<"==========================="<<  endl <<  endl ;
    cout <<  endl <<"\t\t1.Bill Report"<<  endl <<  endl ;
    cout<<"\t\t2.Add/Remove/Edit Item"<<  endl <<  endl ;
    cout<<"\t\t3.Show Item Details"<<  endl <<  endl ;
    cout<<"\t\t4.Exit"<<  endl <<  endl ;
    cout<<"\t\tPlease Enter Required Option: ";

    int ch,ff;
    float gtotal;
    cin>>ch;

    switch(ch)
    {
    case 1:

ss:

        cout <<  endl <<  endl <<"\t\t ================Bill Details";
        cout<<"================"<<  endl ;
        cout <<  endl <<"\t\t1.All Items"<<  endl <<  endl ;
        cout<<"\t\t2.Back to Main menu"<<  endl <<  endl ;
        cout<<"\t\tPlease Enter Required Option: ";

        int cho;
        cin>>cho;

        if(cho==1)
        {

            cout <<  endl <<  endl <<  endl <<"\t    ***************BILL DETAILS************* "<<  endl ;
            cout <<  endl <<"\tITEM NO";
            cout<<"\tNAME";
            cout<<"\tPRICE";
            cout<<"\tQUANTITY";
            cout<<"\tTAX %";
            cout<<"\tDISCOUNT %";
            cout<<"  NET AMOUNT"<<  endl ;

            fin.open("itemstore.dat",ios::binary);

            if(!fin)
            {

                cout <<  endl <<  endl <<"File Not Found...";
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

            cout <<  endl <<"\t\t\tGrand Total="<<gtotal;
            fin.close();
        }
        if(cho==2)
        {
            goto menu;
        }
        goto ss;
    case 2:

db:

        cout <<  endl <<"\t\t =================Bill Editor================="<<  endl <<  endl ;
        cout <<  endl <<"\t\t1.Add Item Details"<<  endl <<  endl ;
        cout<<"\t\t2.Edit Item Details"<<  endl <<  endl ;
        cout<<"\t\t3.Delete Item Details"<<  endl <<  endl ;
        cout<<"\t\t4.Back to Main Menu ";
        int apc;
        cout <<  endl <<  endl <<"\t\tPlease Enter Required Option: ";
        cin>>apc;

        switch(apc)
        {
        case 1:

            fout.open("itemstore.dat",ios::binary|ios::app);
            amt.add();
            cout <<  endl <<"\t\tItem Added Successfully!";
            goto db;

        case 2:

            int ino;
            flag=0;
            cout <<  endl <<  endl <<"\tEnter Item Number to be Edited :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<  endl <<  endl <<"File Not Found...";
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
                        cout <<  endl <<  endl <<"\t\t***************CURRENT DETAILS************* "<<  endl ;
                        amt.show();
                        amt.update(ino);
                        break;
                    }
                }
                r++;
            }

            if(flag==0)
            {
                cout <<  endl <<"\t\tItem No does not exist...Please Retry!";
                goto db;
            }

            fin.close();
            goto db;

        case 3:
            flag=0;
            cout <<  endl <<  endl <<"\tEnter Item Number to be deleted :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);

            if(!fin)
            {
                cout <<  endl <<  endl <<"File Not Found...";
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

            while(tmp.read((char*)&amt,sizeof(amt))) fout.write((char*)&amt,sizeof(amt));
            tmp.close();
            fout.close();

            if(flag==1)
                cout <<  endl <<  endl <<"\t\tItem Succesfully Deleted";
            else if (flag==0)
                cout <<  endl <<"\t\tItem does not Exist! Please Retry";
            goto db;

        case 4:
            goto menu;


        default:
            cout <<  endl <<  endl <<"\t\tWrong Choice!!! Retry";
            goto db;
        }

    case 3:
        system("clear");
        flag=0;

        int ino;
        cout <<  endl <<  endl <<"\t\tEnter Item Number :";
        cin>>ino;
        fin.open("itemstore.dat",ios::binary);
        if(!fin)
        {
            cout<<  endl <<  endl <<"File Not Found..." <<  endl << "Program Terminated!";
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
            cout <<  endl <<"\t\tItem does not exist....Please Retry!";
        fin.close();
        goto menu;

    case 4:
        system("clear");
        cout <<  endl <<"\tARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
        char yn;
        cin>>yn;
        if((yn=='Y')||(yn=='y'))
        {
            system("clear");
            cout <<  endl <<"            ******************* THANKS FOR VISITING ******************"<<  endl <<  endl ;
            exit(0);
        }
        else if((yn=='N')||(yn=='n'))
            goto menu;
        else
        {
            goto menu;
        }



    default:
        cout <<  endl <<  endl <<"\t\tWrong Choice....Please Retry!";
        goto menu;
    }


    return 0;
}
