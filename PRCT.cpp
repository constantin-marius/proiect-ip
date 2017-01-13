#include<cstdlib>
#include<ctime>
#include<iostream>
#include<fstream.h>
#define NR_CARTI 52
using namespace std;
struct carte
{
	int numar;
	char simbol;
};
struct player
{
	string username;
	string password;
	long int chips;
	long long int totalEarnings;
	int handsWon;
	long handsPlayed;
	double procentaj;
};

player jucator[1000];
carte pachet[52];
int folosire[52];

int actualizeaza()
{
	ifstream fin("data.txt");
	int index=0;
	while(!fin.eof())
	{
		fin>>jucator[index].username;
		fin>>jucator[index].password;
		fin>>jucator[index].chips;
		fin>>jucator[index].totalEarnings;
		fin>>jucator[index].handsWon;
		fin>>jucator[index].handsPlayed;
		fin>>jucator[index].procentaj;
		index++;
	}
	fin.close();
	return index;
};
void salveaza(int playersReg)
{
	ofstream dout("data.txt");
	for(int index=0;index<playersReg;index+=1)
	{
		if(jucator[index].chips!=0)
		{
			dout<<jucator[index].username<<endl;
			dout<<jucator[index].password<<endl;
			dout<<jucator[index].chips<<endl;
			dout<<jucator[index].totalEarnings<<endl;
			dout<<jucator[index].handsWon<<endl;
			dout<<jucator[index].handsPlayed<<endl;
			dout<<jucator[index].procentaj<<endl;
		}
	}
	dout.close();
};
void registration(int playersReg)
{
	wrongUsername:
	system("cls");
	cout<<"-Registration-"<<endl<<endl;
	string usr,parola;
	cout<<"Username:";cin>>usr;
	for(int index=0;index<playersReg;index++)
	{
		if(jucator[index].username==usr)
		{
			cout<<"Acest username este dea folosit";
			cout<<endl<<"Apasa Enter pentru a reincerca.";
			cin.get();
			cin.get();
			goto wrongUsername;
		}
	}
	cout<<"Password:";cin>>parola;
	cout<<endl<<"Inregistrare reusita"<<endl<<"Apasa Enter pentru a merge mai departe";
	cin.get();
	cin.get();
	jucator[playersReg].username=usr;
	jucator[playersReg].password=parola;
	jucator[playersReg].chips=1000;
	jucator[playersReg].totalEarnings=0;
	jucator[playersReg].handsWon=0;
	jucator[playersReg].handsPlayed=0;
	jucator[playersReg].procentaj=0;
};
int login(int playersReg)
{
	logAgain:
	int k;
	system("cls");
	cout<<"-Login-"<<endl<<endl;
	string usr,parola;
	cout<<"Username:";cin>>usr;
	cout<<"Password:";cin>>parola;
	cout<<endl;
	int ok=0;
	for(int index=0;index<playersReg;index++)
	{
		if(jucator[index].username==usr)
		{
			if(jucator[index].password==parola)
			{
				ok=1;
				k=index;
			}
		}
	}
	if(ok==1)
	{
		cout<<"Logare reusita!"<<endl<<"Press Enter to continue";
		cin.get();
		cin.get();
	}
	else
	{
		int rsp;
		cout<<"Username sau parola gresite";
		cout<<endl<<"1.Reincercare"<<endl<<"2.Registration";
		cin>>rsp;
		if(rsp==1)
			goto logAgain;
		if(rsp==2)
		{
			registration(playersReg);
			playersReg++;
			goto logAgain;
		}
	}
	return k;
};
int dealCard()
{
	int m;
	srand(time(NULL));
	m=rand()%52;
	while(folosire[m]!=0)
	{
		m=rand()%52;
	}
	folosire[m]++;
	return m;
}
int makeTotal(int total, int adauga)
{
	if(adauga>9 && adauga<14)
		total=total+10;
	else
	{
		if(adauga==14)
			total=total+11;
		if(adauga<10)
			total=total+adauga;
	}
	return total;
};
void afiseaza(int afisareCarte)
{
	if(afisareCarte<11)
		{
			if(afisareCarte==1)
				cout<<"A";
			else
				cout<<afisareCarte;
		}
	else
	{
		if(afisareCarte==11)
		{
			cout<<"J";
		}
		if(afisareCarte==12)
		{
			cout<<"Q";
		}
		if(afisareCarte==13)
		{
			cout<<"K";
		}
		if(afisareCarte==14)
		{
			cout<<"A";
		}
	}
};
int verificamAs(int &total, int a[], int nrCarti)
{
	for(int index=0;index<nrCarti;index++)
		{
			if(pachet[a[index]].numar==14)
			{
				total=total-10;
				pachet[a[index]].numar=1;
				break;
			}
		}
	return total;
};
int joc(int totalP,int mana[],int &nrCarti,long int &bet,int ordPl,int dlMana[])
{
	cout<<"*Carti "<<jucator[ordPl].username<<" : ";
	afiseaza(pachet[mana[0]].numar);
	cout<<pachet[mana[0]].simbol;
	afiseaza(pachet[mana[1]].numar);
	cout<<pachet[mana[1]].simbol<<endl<<endl;
	cout<<"Total: "<<totalP<<endl;
	string raspuns;
	int bj=0;
	if(totalP==22)
		verificamAs(totalP,mana,nrCarti);
	if(totalP!=21)
	{
		wrongDouble:
		if(jucator[ordPl].chips-bet<0)
		{
			cout<<"hit, stand sau surrender?"<<endl;
		}
		else
			cout<<"hit, stand, double sau surrender?"<<endl;
		cin>>raspuns;
		cout<<endl;
	}
	else
	{
		raspuns="stand";
		bj=1;
	}
	if(raspuns=="double")
	{
		if(jucator[ordPl].chips-bet<0)
		{
			cout<<"Nu ai destui bani."<<endl;
			goto wrongDouble;
		}
		jucator[ordPl].chips=jucator[ordPl].chips-bet;
		bet=bet*2;
		mana[nrCarti]=dealCard();
		totalP=makeTotal(totalP, pachet[mana[nrCarti]].numar);
		nrCarti++;
		cout<<"Carti "<<jucator[ordPl].username<<" :";
		for(int index=0;index<nrCarti;index++)
		{
			afiseaza(pachet[mana[index]].numar);
			cout<<pachet[mana[index]].simbol<<" ";
		}	
		cout<<endl;
		
		if(totalP>21)
		{
			verificamAs(totalP,mana,nrCarti);
			if(totalP>21)
			{
				cout<<"Total: "<<totalP<<endl<<endl;
				return totalP;
			}
			else
			{
				cout<<"Total: "<<totalP<<endl<<endl;
				return totalP;
			}
		}
		else
		{
			cout<<"Total: "<<totalP<<endl<<endl;
			return totalP;
		}	
		cout<<endl;
	}
	while(raspuns=="hit")
	{
		mana[nrCarti]=dealCard();
		totalP=makeTotal(totalP, pachet[mana[nrCarti]].numar);
		nrCarti++;
		
		cout<<"Carti "<<jucator[ordPl].username<<" :";
		for(int index=0;index<nrCarti;index++)
		{
			afiseaza(pachet[mana[index]].numar);
			cout<<pachet[mana[index]].simbol<<" ";
		}
		cout<<endl;
		if(totalP==21)
		{
			cout<<"Total: "<<totalP<<endl<<endl;
			return totalP;
		}
		if(totalP>21)
		{
			verificamAs(totalP,mana,nrCarti);
			if(totalP>21)
			{
				cout<<"Total: "<<totalP<<endl<<endl;
				return totalP;
			}
		}
		if(totalP<21)
		{
			cout<<"Total: "<<totalP<<endl<<endl;
			cout<<"hit or stand?"<<endl<<endl;
			cin>>raspuns;
			cout<<endl;
		}
	}
	if(raspuns=="stand")
	{
		return totalP;
	}
	if(raspuns=="surrender")
	{
		jucator[ordPl].chips=jucator[ordPl].chips+bet/2;
	}
	
};
void singlePlayer(int ordPl)
{
	long int bet;
	
	for(int index=0;index<=52;index++)
		folosire[index]=0;

	int mana[10],nrCarti=0,dlMana[10],dlNrCarti=0,totalP=0,totalD=0,bj=0;
	string raspuns;
	betGresit:
	system("cls");
	cout<<"Your chips:"<<jucator[ordPl].chips<<endl<<"Ce suma pariati?"<<endl;
	cin>>bet;
	
	if(bet>jucator[ordPl].chips)
	{
		cout<<"Suma gresita"<<endl<<"Apasa enter pentru a reincerca"<<endl;
		cin.get();
		cin.get();
		goto betGresit;
	
	}
	jucator[ordPl].chips=jucator[ordPl].chips-bet;
	mana[0]=dealCard();
	mana[1]=dealCard();
	totalP=makeTotal(totalP, pachet[mana[0]].numar);
	totalP=makeTotal(totalP, pachet[mana[1]].numar);
	nrCarti=nrCarti+2;
	if(totalP>21)
	{
		verificamAs(totalP,mana,nrCarti);
	}
	
	dlMana[0]=dealCard();
	dlMana[1]=dealCard();
	totalD=makeTotal(totalD, pachet[dlMana[0]].numar);
	totalD=makeTotal(totalD, pachet[dlMana[1]].numar);
	dlNrCarti=dlNrCarti+2;
	
	cout<<"Cartile dealearului: ";afiseaza(pachet[dlMana[0]].numar);cout<<pachet[dlMana[0]].simbol<<" ?"<<endl<<endl;
	cout<<"Cartile tale: ";afiseaza(pachet[mana[0]].numar);cout<<pachet[mana[0]].simbol<<" ";afiseaza(pachet[mana[1]].numar);cout<<pachet[mana[1]].simbol<<endl<<"Total="<<totalP<<endl;
	cout<<endl;
	jucator[ordPl].handsPlayed++;
	if(totalP!=21)
	{
		wrongDouble:
		if(pachet[mana[0]].numar==pachet[mana[1]].numar)
		{
			if(jucator[ordPl].chips-bet<0)
			{
				cout<<"hit, stand sau surrender?"<<endl;
			}
			else
				cout<<"hit, stand, double, split sau surrender?"<<endl;
		}
		else
		{
			if(jucator[ordPl].chips-bet<0)
			{
				cout<<"hit, stand sau surrender?"<<endl;
			}
			else
				cout<<"hit, stand, double sau surrender?"<<endl;
		}
		cin>>raspuns;
	}
	else
	{
		raspuns="stand";
		jucator[ordPl].chips=jucator[ordPl].chips+1.5*bet;
		jucator[ordPl].handsWon++;
		jucator[ordPl].totalEarnings=jucator[ordPl].totalEarnings+bet;
		bj=1;
	}
	if(raspuns=="split" && pachet[mana[0]].numar==pachet[mana[1]].numar)
	{
		int total2=0;
		jucator[ordPl].chips=jucator[ordPl].chips-bet;
		system("cls");
		cout<<"Cartile dealearului: ";afiseaza(pachet[dlMana[0]].numar);cout<<pachet[dlMana[0]].simbol<<" ?"<<endl<<endl;
		int pastram;
		pastram=mana[1];
		mana[1]=dealCard();
		totalP=0;
		totalP=makeTotal(totalP,pachet[mana[0]].numar);
		totalP=makeTotal(totalP,pachet[mana[1]].numar);
		totalP=joc(totalP,mana,nrCarti,bet,ordPl,dlMana);
		cout<<endl;
		mana[0]=pastram;
		mana[1]=dealCard();
		total2=makeTotal(total2,pachet[mana[0]].numar);
		total2=makeTotal(total2,pachet[mana[1]].numar);
		nrCarti=2;
		total2=joc(total2,mana,nrCarti,bet,ordPl,dlMana);
		cout<<endl;
		
		while(totalD<17)
		{
			dlMana[dlNrCarti]=dealCard();
			totalD=makeTotal(totalD, pachet[dlMana[dlNrCarti]].numar);
			dlNrCarti++;
			if(totalD>21)
			verificamAs(totalD,dlMana,dlNrCarti);
		}
		cout<<endl<<"Cartile dealearului: ";
		for(int index=0;index<dlNrCarti;index++)
		{
			afiseaza(pachet[dlMana[index]].numar);
			cout<<pachet[dlMana[index]].simbol<<" ";
		}
		cout<<endl<<"Total dealer: "<<totalD<<endl;
		if(totalP>21)
			cout<<endl<<"Ai pierdut prima mana!";
		else
		{
			if(totalD>21 )
			{
				jucator[ordPl].chips=jucator[ordPl].chips+2*bet;
				cout<<endl<<"Ai castigat prima mana!";
				jucator[ordPl].handsWon++;
				jucator[ordPl].totalEarnings=jucator[ordPl].totalEarnings+bet;
			}
			else
			{
				if(totalP>totalD)
				{
					jucator[ordPl].chips=jucator[ordPl].chips+2*bet;
					cout<<endl<<"Ai castigat prima mana!";
					jucator[ordPl].handsWon++;
					jucator[ordPl].totalEarnings=jucator[ordPl].totalEarnings+bet;
				}
				if(totalP==totalD)
				{
					jucator[ordPl].chips=jucator[ordPl].chips+bet;
					cout<<endl<<"La prima mana a fost egalitate!";
				}
				if(totalP<totalD)
				{
					jucator[ordPl].chips=jucator[ordPl].chips+bet;
					cout<<endl<<"Ai pierdut prima mana!";
				}
			}
		}
		cout<<endl;
		if(total2>21)
		cout<<endl<<"Ai pierdut a doua mana!";
		else
		{
			if(totalD>21 )
			{
				jucator[ordPl].chips=jucator[ordPl].chips+2*bet;
				cout<<endl<<"Ai castigat a doua mana!";
				jucator[ordPl].handsWon++;
				jucator[ordPl].totalEarnings=jucator[ordPl].totalEarnings+bet;
			}
			else
			{
				if(total2>totalD)
				{
					jucator[ordPl].chips=jucator[ordPl].chips+2*bet;
					cout<<endl<<"Ai castigat a doua mana!";
					jucator[ordPl].handsWon++;
					jucator[ordPl].totalEarnings=jucator[ordPl].totalEarnings+bet;
				}
				if(total2==totalD)
				{
					jucator[ordPl].chips=jucator[ordPl].chips+bet;
					cout<<endl<<"La a doua mana a fost egalitate!";
				}
				if(total2<totalD)
				{
					jucator[ordPl].chips=jucator[ordPl].chips+bet;
					cout<<endl<<"Ai pierdut a doua mana!";
				}
			}
		}
		cout<<endl;
		
	}
	if(raspuns=="double")
	{
		if(jucator[ordPl].chips-bet<0)
		{
			cout<<"Nu ai destui bani."<<endl;
			goto wrongDouble;
		}
		jucator[ordPl].chips=jucator[ordPl].chips-bet;
		bet=bet*2;
		system("cls");
		mana[nrCarti]=dealCard();
		totalP=makeTotal(totalP, pachet[mana[nrCarti]].numar);
		nrCarti++;
		
		if(totalP>21)
		{
			verificamAs(totalP,mana,nrCarti);
			if(totalP>21)
			{
				system("cls");
				cout<<"Cartile dealearului: ";afiseaza(pachet[dlMana[0]].numar);cout<<pachet[dlMana[0]].simbol<<" ";afiseaza(pachet[dlMana[1]].numar);cout<<pachet[dlMana[1]].simbol<<endl;
				cout<<"Total dealer:"<<totalD<<endl<<endl;
			
				cout<<"Cartile tale: ";
				for(int index=0;index<nrCarti;index++)
				{
					afiseaza(pachet[mana[index]].numar);
					cout<<pachet[mana[index]].simbol<<" ";
				}	
				cout<<endl<<"total="<<totalP<<endl<<endl;
				cout<<"Ai pierdut";
			}
			else
			{
				raspuns="stand";
			}
		}
		else
		{
			raspuns="stand";
		}	
		cout<<endl;
	}
	while(raspuns=="hit")
	{
		system("cls");
		mana[nrCarti]=dealCard();
		totalP=makeTotal(totalP, pachet[mana[nrCarti]].numar);
		nrCarti++;
		
		cout<<"Cartile dealearului: ";afiseaza(pachet[dlMana[0]].numar);cout<<pachet[dlMana[0]].simbol<<" ?"<<endl<<endl;
		cout<<"Cartile tale: ";
		for(int index=0;index<nrCarti;index++)
		{
			afiseaza(pachet[mana[index]].numar);
			cout<<pachet[mana[index]].simbol<<" ";
		}
		cout<<endl;

		if(totalP==21)
		{
			cout<<"total="<<totalP<<endl;
			raspuns="stand";
			break;
		}
		if(totalP>21)
		{
			verificamAs(totalP,mana,nrCarti);
			if(totalP>21)
			{
				system("cls");
				cout<<"Cartile dealearului: ";
				for(int index=0;index<dlNrCarti;index++)
				{
					afiseaza(pachet[dlMana[index]].numar);
					cout<<pachet[dlMana[index]].simbol<<" ";
				}
				cout<<endl<<"Total dealer="<<totalD<<" "<<endl<<endl;
				cout<<endl<<"Cartile tale: ";
				for(int index=0;index<nrCarti;index++)
				{
					afiseaza(pachet[mana[index]].numar);
					cout<<pachet[mana[index]].simbol<<" ";
				}
				cout<<endl<<"Totalul tau:"<<totalP<<endl;
				cout<<endl<<"Ai pierdut!"<<endl;
				break;
			}
		}
		cout<<"total="<<totalP<<endl<<endl;
		if(totalP<21)
		{
			cout<<"hit or stand?"<<endl;
			cin>>raspuns;
		}
	}
	if(raspuns=="stand")
	{
		int insBet;
		string insurance;
		if(pachet[dlMana[0]].numar==14 || pachet[dlMana[0]].numar==1)
		{
			cout<<"Insurance? (da/nu)";
			cin>>insurance;
			insBet=bet/2;
		}
		system("cls");	
		while(totalD<17)
		{
			dlMana[dlNrCarti]=dealCard();
			totalD=makeTotal(totalD, pachet[dlMana[dlNrCarti]].numar);
			dlNrCarti++;
			if(totalD>21)
				verificamAs(totalD,dlMana,dlNrCarti);
		}
		if(insurance=="da")
		{
			jucator[ordPl].chips=jucator[ordPl].chips-insBet;
			if(totalD==21)
				jucator[ordPl].chips=jucator[ordPl].chips+insBet*2;
		}
		cout<<"Cartile dealearului: ";
		for(int index=0;index<dlNrCarti;index++)
		{
			afiseaza(pachet[dlMana[index]].numar);
			cout<<pachet[dlMana[index]].simbol<<" ";
		}
		cout<<endl<<"Total dealer="<<totalD<<" "<<endl<<endl;
		cout<<endl<<"Cartile tale: ";
		for(int index=0;index<nrCarti;index++)
		{
			afiseaza(pachet[mana[index]].numar);
			cout<<pachet[mana[index]].simbol<<" ";
		}
		cout<<endl<<"Totalul tau:"<<totalP<<endl;
		
		if(totalD>21)
		{
			cout<<endl<<"Ai castigat!"<<endl;
			jucator[ordPl].totalEarnings=jucator[ordPl].totalEarnings+bet;
			jucator[ordPl].handsWon++;
			if(bj!=1)
				jucator[ordPl].chips=jucator[ordPl].chips+2*bet;
		}
		else
		{
			if(totalP>totalD)
			{
				cout<<endl<<"Ai castigat!"<<endl;
				jucator[ordPl].handsWon++;
				jucator[ordPl].totalEarnings=jucator[ordPl].totalEarnings+bet;
				if(bj!=1)
					jucator[ordPl].chips=jucator[ordPl].chips+2*bet;
			}
			else
			{
				if(totalD==totalP)
				{
					cout<<endl<<"Egalitate"<<endl;
					if(bj!=1)
						jucator[ordPl].chips=jucator[ordPl].chips+bet;
				}
				else
				{
					cout<<endl<<"Ai pierdut!"<<endl;
					if(jucator[ordPl].chips<1)
					{
						cout<<"Ai ramas fara bani!"<<endl<<"Contul tau a fost realimentat cu 1000$"<<endl;
						jucator[ordPl].chips=1000;
					}
				}
			}
		}
	}
	if(raspuns=="surrender")
	{
		jucator[ordPl].chips=jucator[ordPl].chips+bet/2;
	}
};
void twoPlayers(int ordPl1,int ordPl2)
{
	long int bet1,bet2;
	jucator[ordPl1].handsPlayed++;
	jucator[ordPl2].handsPlayed++;
	for(int index=0;index<=52;index++)
		folosire[index]=0;

	int mana1[10],mana2[10],nrCarti1=0,nrCarti2=0,dlMana[10],dlNrCarti=0,totalP1=0,totalP2=0,totalD=0;
	string raspuns1;
	system("cls");
	bet1Gresit:
	cout<<jucator[ordPl1].username<<" turn"<<endl<<"Your chips:"<<jucator[ordPl1].chips<<endl<<"Ce suma vrei sa pariezi?"<<endl;
	cin>>bet1;
	if(bet1>jucator[ordPl1].chips)
	{
		cout<<"Suma gresit."<<endl<<"Apasa Enter pentru a reincerca"<<endl;
		cin.get();
		cin.get();
		goto bet1Gresit;
	}
	
	bet2Gresit:
	cout<<jucator[ordPl2].username<<" turn"<<endl<<"Your chips:"<<jucator[ordPl2].chips<<endl<<"Ce suma vrei sa pariezi?"<<endl;
	cin>>bet2;
	if(bet2>jucator[ordPl2].chips)
	{
		cout<<"Suma gresit."<<endl<<"Apasa Enter pentru a reincerca"<<endl;
		cin.get();
		cin.get();
		goto bet2Gresit;
	}
	jucator[ordPl1].chips=jucator[ordPl1].chips-bet1;
	jucator[ordPl2].chips=jucator[ordPl2].chips-bet2;
	mana1[0]=dealCard();
	mana2[0]=dealCard();
	mana1[1]=dealCard();
	mana2[1]=dealCard();
	dlMana[0]=dealCard();
	dlMana[1]=dealCard();
	nrCarti1=2;
	nrCarti2=2;
	dlNrCarti=2;
	
	totalP1=makeTotal(totalP1,pachet[mana1[0]].numar);
	totalP1=makeTotal(totalP1,pachet[mana1[1]].numar);
	totalP2=makeTotal(totalP2,pachet[mana2[0]].numar);
	totalP2=makeTotal(totalP2,pachet[mana2[1]].numar);
	totalD=makeTotal(totalD,pachet[dlMana[0]].numar);
	totalD=makeTotal(totalD,pachet[dlMana[1]].numar);
	
	system("cls");
	cout<<"Cartile dealearului: "<<pachet[dlMana[0]].numar<<pachet[dlMana[0]].simbol<<" ?"<<endl<<endl;
	totalP1=joc(totalP1,mana1,nrCarti1, bet1, ordPl1,dlMana);
	cout<<endl;
	totalP2=joc(totalP2,mana2,nrCarti2, bet2, ordPl2,dlMana);
	
	while(totalD<17)
	{
		dlMana[dlNrCarti]=dealCard();
		totalD=makeTotal(totalD, pachet[dlMana[dlNrCarti]].numar);
		dlNrCarti++;
		if(totalD>21)
		verificamAs(totalD,dlMana,dlNrCarti);
	}
	int insBet;
	string insurance;
	if(pachet[dlMana[0]].numar==14 || pachet[dlMana[0]].numar==1)
	{
		cout<<jucator[ordPl1].username<<"- Insurance? (da/nu)"<<endl;
		cin>>insurance;
		insBet=bet1/2;
		if(insurance=="da")
		{
			jucator[ordPl1].chips=jucator[ordPl1].chips-insBet;
			if(totalD==21)
				jucator[ordPl1].chips=jucator[ordPl1].chips+insBet*2;
		}
	}
	cout<<endl;
	
	if(pachet[dlMana[0]].numar==14 || pachet[dlMana[0]].numar==1)
	{
		cout<<jucator[ordPl2].username<<"- Insurance? (da/nu)"<<endl;
		cin>>insurance;
		insBet=bet2/2;
		if(insurance=="da")
		{
			jucator[ordPl2].chips=jucator[ordPl2].chips-insBet;
			if(totalD==21)
				jucator[ordPl2].chips=jucator[ordPl2].chips+insBet*2;
		}
	}
	
	system("cls");
	cout<<"Cartile dealearului: ";
	for(int index=0;index<dlNrCarti;index++)
	{
		afiseaza(pachet[dlMana[index]].numar);
		cout<<pachet[dlMana[index]].simbol<<" ";
	}
	cout<<endl;
	cout<<"Total: "<<totalD;
	cout<<endl;
	cout<<"Carti "<<jucator[ordPl1].username<<" :";
	for(int index=0;index<nrCarti1;index++)
	{
		afiseaza(pachet[mana1[index]].numar);
		cout<<pachet[mana1[index]].simbol<<" ";
	}
	cout<<endl;
	cout<<"Total: "<<totalP1<<endl;
	cout<<endl;
	cout<<"Carti "<<jucator[ordPl2].username<<" :";
	for(int index=0;index<nrCarti2;index++)
	{
		afiseaza(pachet[mana2[index]].numar);
		cout<<pachet[mana2[index]].simbol<<" ";
	}
	cout<<endl;
	cout<<"Total: "<<totalP2;
	cout<<endl;
	cout<<endl;
	if(totalP1>21)
		cout<<endl<<jucator[ordPl1].username<<" a pierdut!";
	else
	{
		if(totalD>21 )
		{
			jucator[ordPl1].chips=jucator[ordPl1].chips+2*bet1;
			cout<<endl<<jucator[ordPl1].username<<" a castigat!";
			jucator[ordPl1].handsWon++;
			jucator[ordPl1].totalEarnings=jucator[ordPl1].totalEarnings+bet1;
		}
		else
		{
			if(totalP1>totalD)
			{
				jucator[ordPl1].chips=jucator[ordPl1].chips+2*bet1;
				cout<<endl<<jucator[ordPl1].username<<" a castigat!";
				jucator[ordPl1].handsWon++;
				jucator[ordPl1].totalEarnings=jucator[ordPl1].totalEarnings+bet1;
			}
			if(totalP1==totalD)
			{
				jucator[ordPl1].chips=jucator[ordPl1].chips+bet1;
				cout<<endl<<jucator[ordPl1].username<<" a facut egalitate!";
			}
			if(totalP1<totalD)
			{
				jucator[ordPl1].chips=jucator[ordPl1].chips+bet1;
				cout<<endl<<jucator[ordPl1].username<<" a pierdut!";
			}
		}
	}
	cout<<endl;
	if(totalP2>21)
		cout<<endl<<jucator[ordPl2].username<<" a pierdut!";
	else
	{
		if(totalD>21 )
		{
			jucator[ordPl2].chips=jucator[ordPl2].chips+2*bet2;
			cout<<endl<<jucator[ordPl2].username<<" a castigat!";
			jucator[ordPl2].handsWon++;
			jucator[ordPl2].totalEarnings=jucator[ordPl2].totalEarnings+bet2;
			
		}
		else
		{
			if(totalP2>totalD)
			{
				jucator[ordPl2].chips=jucator[ordPl2].chips+2*bet2;
				cout<<endl<<jucator[ordPl2].username<<" a castigat!";
				jucator[ordPl2].handsWon++;
				jucator[ordPl2].totalEarnings=jucator[ordPl2].totalEarnings+bet2;
			}
			if(totalP2==totalD)
			{
				jucator[ordPl2].chips=jucator[ordPl2].chips+bet2;
				cout<<endl<<jucator[ordPl2].username<<" a facut egalitate!";
			}
			if(totalP2<totalD)
			{
				jucator[ordPl2].chips=jucator[ordPl2].chips+bet2;
				cout<<endl<<jucator[ordPl2].username<<" a pierdut!";
			}
		}
	}
	
	
	
	

};
int menu()
{
	int alegere;
	system("cls");
	cout<<"--Doamne ajuta-n bet de 100!--"<<endl<<endl;
	cout<<"1111  1       1    11111 1  1    1   1   11111 1  1"<<endl;
	cout<<"1  1  1      1 1   1     1 1     1  1 1  1     1 1"<<endl;
	cout<<"1111  1     1   1  1     11      1 1   1 1     11"<<endl;
	cout<<"1   1 1     11111  1   1 1 1  1  1 11111 1   1 1 1"<<endl;
	cout<<"1111  11111 1   1  11111 1  1 1111 1   1 11111 1  1"<<endl<<endl;
	cout<<"Meniu"<<endl<<endl;
	cout<<"1.Single player"<<endl;
	cout<<"2.Multiplayer"<<endl;
	cout<<"3.Statistics"<<endl;
	cout<<"4.Exit"<<endl;
	cout<<endl;
	cin>>alegere;
	return alegere;
};
int main()
{
	int playersReg=actualizeaza();
	int ct=0;
	for(int index=2;index<=14;index++)
	{
		pachet[ct].numar=pachet[ct+1].numar=pachet[ct+2].numar=pachet[ct+3].numar=pachet[ct+4].numar=index;
		pachet[ct].simbol=003;
		pachet[ct+1].simbol=004;
		pachet[ct+2].simbol=005;
		pachet[ct+3].simbol=006;
		ct+=4;
	}
	
	menu:
	int alegere=menu();
	if(alegere==1)
	{
		int ordPl;
		system("cls");
		cout<<"-Single player-"<<endl<<endl;
		cout<<"1.Login"<<endl;
		cout<<"2.Register"<<endl;
		cin>>alegere;
		
		if(alegere==2)
		{
			registration(playersReg);
			playersReg++;
			goto logare;
		}
		if(alegere==1)
		{
			logare:
			ordPl=login(playersReg);
			singlePlayer(ordPl);
			jucator[ordPl].procentaj=jucator[ordPl].handsWon*100/jucator[ordPl].handsPlayed;
			for(int index=0;index<=52;index++)
			{
				if(pachet[index].numar==1)
					pachet[index].numar=14;
			}
			cout<<endl<<"1.Play again"<<endl<<"2.Menu"<<endl<<"3.Exit"<<endl;
			int raspuns;
			cin>>raspuns;
			while(raspuns==1)
			{
				singlePlayer(ordPl);
				jucator[ordPl].procentaj=jucator[ordPl].handsWon*100/jucator[ordPl].handsPlayed;
				for(int index=0;index<=52;index++)
				{
					if(pachet[index].numar==1)
						pachet[index].numar=14;
				}
				cout<<endl<<"1.Play again"<<endl<<"2.Menu"<<endl<<"3.Exit"<<endl;
				cin>>raspuns;
			}
			if(raspuns==2)
			{
				goto menu;
			}
			if(raspuns==3)
			{
				salveaza(playersReg);
				return 0;
			}
		}
	}
	if(alegere==2)
	{
		int ordPl1,ordPl2,r;
		system("cls");
		cout<<"Player 1"<<endl<<"1.Login"<<endl<<"2.Register"<<endl;
		cin>>r;
		if(r==1)
			ordPl1=login(playersReg);
		if(r==2)
		{
			registration(playersReg);
			playersReg++;
			ordPl1=login(playersReg);
		}
		system("cls");
		cout<<"Player 2"<<endl<<"1.Login"<<endl<<"2.Register"<<endl;
		cin>>r;
		if(r==1)
			ordPl2=login(playersReg);
		if(r==2)
		{
			registration(playersReg);
			playersReg++;
			ordPl2=login(playersReg);
		}
		system("cls");
		twoPlayers(ordPl1,ordPl2);
		for(int index=0;index<=52;index++)
		{
			if(pachet[index].numar==1)
				pachet[index].numar=14;
		}
		jucator[ordPl1].procentaj=jucator[ordPl1].handsWon*100/jucator[ordPl1].handsPlayed;
		jucator[ordPl2].procentaj=jucator[ordPl2].handsWon*100/jucator[ordPl2].handsPlayed;
		cout<<endl<<"1.Play again"<<endl<<"2.Menu"<<endl<<"3.Exit"<<endl;
		int raspuns;
		cin>>raspuns;
		while(raspuns==1)
		{
			twoPlayers(ordPl1,ordPl2);
			jucator[ordPl1].procentaj=jucator[ordPl1].handsWon*100/jucator[ordPl1].handsPlayed;
			jucator[ordPl2].procentaj=jucator[ordPl2].handsWon*100/jucator[ordPl2].handsPlayed;
			for(int index=0;index<=52;index++)
			{
				if(pachet[index].numar==1)
					pachet[index].numar=14;
			}
			cout<<endl<<"1.Play again"<<endl<<"2.Menu"<<endl<<"3.Exit"<<endl;
			cin>>raspuns;
		}
		if(raspuns==2)
		{
			goto menu;
		}
		if(raspuns==3)
		{
			salveaza(playersReg);
			return 0;
		}
	}
	if(alegere==3)
	{
		system("cls");
		cout<<"-Statistics-"<<endl;
		string usr;
		cout<<"Username: ";
		cin>>usr;
		cout<<endl;
		for(int index=0;index<playersReg;index++)
		{
			if(jucator[index].username==usr)
			{
				cout<<"Chips: "<<jucator[index].chips<<endl;
				cout<<"Total earnings: "<<jucator[index].totalEarnings<<endl;
				cout<<"Hands won: "<<jucator[index].handsWon<<endl;
				cout<<"Hands played: "<<jucator[index].handsPlayed<<endl;
				cout<<"Hands won% :"<<jucator[index].procentaj<<endl;
				
			}
		}
		cout<<endl;
		cout<<"1.Menu"<<endl<<"2.Exit"<<endl;
		int r;
		cin>>r;
		if(r==1)
			goto menu;
		else
			return 0;
	}
	if(alegere==4)
	{
		salveaza(playersReg);
	}
}