#include<iostream>
#include<fstream>
#include<string.h>
#include<time.h>
#include<stdlib.h>
using namespace std;
struct user{
	int fiftyfifty=1,doubledip=1,flipques=1,qanswered=0;
	long balance=0;
};
char * gen_name(int n,int m){
			n+=64; 
			char ar[10],q[]="ques",c=(char)n;
			strcpy(ar,q);
			ar[4]=c;
			ar[5]='.';
			if(m==1)
				strcat(ar,"txt");
			else if(m==2)
				strcat(ar,"dat");
			return ar;
		}
long long pr_ar[]={5000,10000,25000,50000,100000,1000000,2500000,5000000,10000000,70000000};
class question{
	private:
		char ques[200];
		char opa[30],opb[30],opc[30],opd[30];
		char ans,chp;
	public:
		int qno;
		void getquestion(){
			ifstream fin;
			int count;
			fin.open("count.txt",ios::in);
			fin>>count;
			fin.close();
			++count;
			qno=count;
			ofstream fo;
			fo.open("count.txt",ios::out|ios::trunc);
			fo<<count;
			fo.close();
			cout<<"enter the question:\n";
			cin.getline(ques,200,'?');
			while(getchar()!='\n');
			cout<<"enter the options:\na: ";
			gets(opa);
			cout<<"b: ";
			gets(opb);
			cout<<"c: ";
			gets(opc);
			cout<<"d: ";
			gets(opd);
			cout<<"enter correct answer: ";
			cin>>ans;
			p_file();
		}
		void p_file(){
			ofstream fout;
			int l=strlen(ques);
			char * ar;
			ar=gen_name(qno,1);
			fout.open(ar,ios::out|ios::app);
			fout<<"q number: "<<qno;
			fout<<"\nquestion:\n";
			fout.write(ques,l);
			fout<<"\noptions:\na: ";
			fout<<opa;
			fout<<"\nb: ";
			fout<<opb;
			fout<<"\nc: ";
			fout<<opc;
			fout<<"\nd: ";
			fout<<opd;
			fout<<"\ncorrect answer: "<<ans;
			fout.close();
		}
		int disp_lifelines(user * u){
			int ch;
			if (u->fiftyfifty==1)
			cout<<"\nFIFTY FIFTY(1) ";
			if (u->doubledip==1)
			cout<<"\nDOUBLE DIP(2) ";
			if (u->flipques==1)
			cout<<"\nFLIP THE QUESTION(3) ";
			cout<<"\nOR IF YOU WANT TO LEAVE WITH RS: "<<u->balance<<" ENTER 4";
			cout<<"\nOR IF YOU WANT TO ANSWER THE QUESTION ENTER 5";
			cout<<"\nENTER CHOICE:";
			cin>>ch;
			return ch;
		}
		int answer_q(user * u){
				char c_ans;
				cout<<"enter correct option: ";
				cin>>c_ans;
				if(c_ans==ans){
					u->qanswered++;
					u->balance=pr_ar[u->qanswered-1];
					cout<<"\nCORRECT!! YOU HAVE EARNED "<<u->balance;
					return 0;
				}
				else{
					cout<<"\nWRONG ANSWER....\n";
					return 1;
				}
		}
		int f_fiftyfifty(user * u){
			if(ans=='a')
				chp='b';
			if(ans=='b')
				chp='c';
			if(ans=='c')
				chp='d';
			if(ans=='d')
				chp='a';
			cout<<"\nYOUR NEW POSSIBLE OPTIONS ARE AS FOLLOWS:\n"<<ans<<"\t"<<chp<<"\n";
			int c=answer_q(u);
			return c;	
		}
		int f_doubledip(user * u){
			int c=answer_q(u);
			if(c==0)
				return 0;
			else if(c==1){
				c=answer_q(u);
				return c;
			}
		}
		int f_flipques(user * u){
			int ch,inst_qno,count=0;//inst_qno for storing instantaneous question number and count for number of available questions
			ifstream fin;
			fin.open("count.txt",ios::in);
			fin>>count;
			fin.close();
			char * ar;
			inst_qno=(rand()%count)+1;//generates random questions
			ar=gen_name(inst_qno,2);//generates file name
			ifstream fi;
			ar[8]='t';
			question q;
			fi.open(ar,ios::in|ios::binary);
			fi.read((char*)&q,sizeof(question));
			u->flipques=0;
			ch=q.disp(u);
			fi.close();
			return ch;
			
		}
		int  disp(user * u){
			int ch=0,choice,l=strlen(ques);
			cout<<"\nquestion:\n";
			cout.write(ques,l);
			cout<<"\noptions:\na: ";
			cout<<opa;
			cout<<"\nb: ";
			cout<<opb;
			cout<<"\nc: ";
			cout<<opc;
			cout<<"\nd: ";
			cout<<opd;
			cout<<"\navailable lifelines: ";
			choice=disp_lifelines(u);
			if(choice==1&&u->fiftyfifty==1){
				ch=f_fiftyfifty(u);
				u->fiftyfifty=0;
			}
			else if(choice==2&&u->doubledip==1){
				ch=f_doubledip(u);
				u->doubledip=0;
			}
			else if(choice==3&&u->flipques==1){
				ch=f_flipques(u);
				u->flipques=0;
			}
			else if(choice==4)
				ch=1;
			else if(choice==5){
				ch=answer_q(u);
			}
			return ch;
		}	
};
void write_bin(question q){
	ofstream fio;
	char *ar;
	ar=gen_name(q.qno,2);
	fio.open(ar,ios::out|ios::binary);
	fio.write((char*)&q,sizeof(question));
	fio.close();
}
void read_f(question q){
	ifstream fio;
	char *ar;
	ar=gen_name(q.qno,2);
	fio.open(ar,ios::in|ios::binary);
	cout<<"\n";
	cout<<q.qno;
}
void play(){
	int inst_qno,count=0;//inst_qno for storing instantaneous question number and count for number of available questions
	ifstream fin;
	fin.open("count.txt",ios::in);
	fin>>count;
	fin.close();
	char name[40];
	char * ar;
	cout<<"enter name: ";
	cin>>name;
	while(getchar()!='\n');
	int ch;//controlling while loop's exit condition
	cout<<"\nWelcome to KAUN BANEGA CROREPATI "<<name;
	cout<<"\nRULES:";
	cout<<"\nAS YOU KEEP ANSWERING QUESTIONS YOU WILL KEEP WINNING MONEY PRIZES";
	cout<<"\nIF YOU ANSWER EVEN ONE QUESTION INCORRECTLY YOU LOSE ALL YOUR EARNED MONEY";
	cout<<"\nYOU WILL HAVE THREE LIFELINES:";
	cout<<"\nFIFTY FIFTY: you have 2 options to chose from instead of 4";
	cout<<"\nDOUBLE DIP: you have 2 tries at the question";
	cout<<"\nFLIP QUESTION: try another question";
	srand(time(0));
	user person;//creating a structure for storing user's data
	question q;
	do{
		inst_qno=(rand()%count)+1;//generates random questions
		ar=gen_name(inst_qno,2);//generates file name
		ifstream fin;
		ar[8]='t';
		fin.open(ar,ios::in|ios::binary);
		fin.read((char*)&q,sizeof(question));
		ch=q.disp(&person);//sees if the person answered correctly
	} while(ch==0);
	cout<<"\n-------------------------------------------";
	cout<<"\nyou have earned: "<<person.balance<<"\n";
}
int main()
{
	question q;
	char ch;
	int choice=0;
	do{
		// making a menu for the user to play the game
		cout<<"press 1 to enter more questions";
		cout<<"\npress 2 to start playing.";
		cout<<"\nenter choice: ";
		cin>>choice;
		if(choice==1){
			q.getquestion();//take question for later use
			write_bin(q);//store the questions into a binary file
		}
		else if (choice==2){
			play();//play the game
		}
		else{ 
			cout<<"\ninvalid input\n";
		}
		cout<<"\ndo you want to play again? ";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	return 0;
 }
