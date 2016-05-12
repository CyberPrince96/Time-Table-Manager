//-----------------------time-table-manager-----------------//

#include<iostream.h>
#include<conio.h>
#include<process.h>
#include<string.h>
#include<ctype.h>
#include<fstream.h>
#include<stdio.h>

//---------class defs----------//
/*-------class TABLE-to holdl time table-----------
-----------''---CLASS_TABLE-to hold time table of classes along with teacher name------
-----------''---TEACH_TABLE-to hold time table of teachers along with class  name-----
-----------''---SUB_SUBTCH-to hold subject as well as name of teacher in corresponding array
------------------------*/

class SUB_SUBTCH
	{
	public:
		char sub[4];
		char subt[4];
	};

class TABLE //---------------------------------for holding time table data//
	{
	public:
	int tabl_of_;//0_for_teacher_and_1_for_class_table---------//
	char tbl[7][9][8];
	char infotbl[7][9][8];//-to_hold_classname_if_teacher'stabl_or_teacher_name_if_it is class table--////////
	TABLE();//------------------------------to initialise time table with days and periods
	void init_infotbl();//-to_initialise infotable------------//
	};

TABLE::TABLE()
	{
	int i,j;
	strcpy(tbl[0][0],"P/D");
	strcpy(tbl[1][0],"MON");
	strcpy(tbl[2][0],"TUE");
	strcpy(tbl[3][0],"WED");
	strcpy(tbl[4][0],"THU");
	strcpy(tbl[5][0],"FRI");
	strcpy(tbl[6][0],"SAT");
	strcpy(tbl[0][1],"I");
	strcpy(tbl[0][2],"II");
	strcpy(tbl[0][3],"III");
	strcpy(tbl[0][4],"IV");
	strcpy(tbl[0][5],"V");
	strcpy(tbl[0][6],"VI");
	strcpy(tbl[0][7],"VII" );
	strcpy(tbl[0][8],"VIII");
		for(i=1;i<=6;i++)
		{ 	for (j=1;j<=8;j++)
			{
			strcpy(tbl[i][j],"NIL");
			}
		}

	}

void TABLE::init_infotbl()
	{
	int i,j;
	if(tabl_of_)//-------execute_if it is class info table-------//
		{
		for(i=1;i<=6;i++)
			{
			for (j=1;j<=8;j++)
				{
				 strcpy(infotbl[i][j]," - ");
				}
			}
		for(i=1,j=0;i<=6;i++)
			{
			strcpy(infotbl[i][j],"TCH");
			}
		for(i=0,j=1;j<=8;j++)
			{
			strcpy(infotbl[i][j],"\0");
			}
		}
	else
		{
		for(i=1;i<=6;i++)
			{
			for (j=1;j<=8;j++)
				{
				 strcpy(infotbl[i][j]," - ");
				}
			}
		for(i=1,j=0;i<=6;i++)
			{
			strcpy(infotbl[i][j],"SUB");
			}
		for(i=0,j=1;j<=8;j++)
			{
			strcpy(infotbl[i][j],"\0");
			}
		}
	}

class CLASS_TABLE
	{
	public:
		int nsb;
		char clas_nm[8];
		SUB_SUBTCH sub_tch[20];
		TABLE tbl;
		CLASS_TABLE()
			{
			tbl.tabl_of_=1; //assining 1 for class tim tabl
			tbl.init_infotbl();
			}
	};

class TEACH_TABLE
	{
	public:
		char tch_nm[4];
		TABLE tbl;
		TEACH_TABLE()
			{
			tbl.tabl_of_=0; //assining 0 for Teacher's tim tabl
			tbl.init_infotbl();
			}
	};
//-----------------end_of_class_defs----------------------------//

//-----function prototypes-------//
/*------head()--for printing heading---
--------mainmenu()---for main menu printing
---------print_tabl()----for printing table
---------void creat_tabl()-for creating table---
---------print_clas_tch_tbl(TEACH_TABLE tch)-for printing teacher's table
print_clas_tch_tbl(CLASS_TABLE ctb)-for printing class time tbl--*/

void head();
void mainmenu();
void print_tabl(char tabl[7][9][8],char infotabl[7][9][8]);
void creat_tabl(void);
void print_clas_tch_tbl(CLASS_TABLE ctb);
void print_clas_tch_tbl(TEACH_TABLE tch);
void delet(CLASS_TABLE ctb);
void outtbl(CLASS_TABLE ctb);
void outtbl(TEACH_TABLE tch);
void mod(CLASS_TABLE ctb);

//----------end_of_function_declaration--------------//
//---------function definations -----//

void outtbl(CLASS_TABLE ctb)
	{
	ofstream fout;
	char fname[9];
	strcpy(fname,ctb.clas_nm);
	strcat(fname,".xls");
	fout.open(fname,ios::out|ios::binary|ios::trunc);
	int b,c,d;//----------------------------for_loop_variabl----------//
	gotoxy(1,11);
	fout<<ctb.clas_nm;
	for(b=0;b<=6;b++)
		{
		fout<<"\n";
		for(c=0;c<=8;c++)
			{
			fout<<ctb.tbl.tbl[b][c]<<"\t";
			}
		fout<<"\n";
		for(c=0;c<=8;c++)
			{
			fout<<ctb.tbl.infotbl[b][c]<<"\t";
			}
		}
	fout.close();
	}

void outtbl(TEACH_TABLE tch)
	{
	ofstream fout;
	char fname[9];
	strcpy(fname,tch.tch_nm);
	strcat(fname,".xls");
	fout.open(fname,ios::out|ios::binary|ios::trunc);
	int b,c,d;//----------------------------for_loop_variabl----------//
	gotoxy(1,11);
	fout<<tch.tch_nm;
	for(b=0;b<=6;b++)
		{
		fout<<"\n";
		for(c=0;c<=8;c++)
			{
			fout<<tch.tbl.tbl[b][c]<<"\t";
			}
		fout<<"\n";
		for(c=0;c<=8;c++)
			{
			fout<<tch.tbl.infotbl[b][c]<<"\t";
			}
		}
	fout.close();
	}

void delet(CLASS_TABLE ctb)
	{
	fstream tchfile,temptch,tempctb,classfile;
	tchfile.open("tchtbl.tbl",ios::out|ios::in|ios::ate|ios::binary);
	temptch.open("tmptch",ios::out|ios::trunc|ios::binary);
	TEACH_TABLE tch[20],tchchk;
	int i,j,k;
	int ntch;
	tempctb.open("tmpctb.tbl",ios::out|ios::binary);
	CLASS_TABLE ctbchk;
	classfile.open("clstbl.tbl",ios::in|ios::ate|ios::binary);
		cout<<"\nSaving please wait";
		classfile.seekg(0,ios::beg);
		while(!classfile.eof())
			{
			classfile.read((char*)&ctbchk,sizeof(ctbchk));
			if(strcmpi(ctbchk.clas_nm,ctb.clas_nm)==0)
				{
				continue;
				}
			else tempctb.write((char*)&ctbchk,sizeof(ctbchk));
			}
		classfile.close();
		tempctb.close();
		remove("clstbl.tbl");
		rename("tmpctb.tbl","clstbl.tbl");
		cout<<"\nClass data saved \nSaving teacher's data\tPlease wait";
	for(i=0;i<20;i++)
		{
		strcpy(tch[i].tch_nm,ctb.sub_tch[i].subt);
		}
	cout<<"\nProcessing file...\tplease wait...";
			tchfile.seekg(0,ios::beg);
			while(!tchfile.eof())
				{
				tchfile.read((char*)&tchchk,sizeof(tchchk));
				if(strcmpi(ctb.sub_tch[i].subt,tchchk.tch_nm)==0)
					{
					tch[i]=tchchk;
					}
				}
			cout<<"\nStill processing\nPlease Wait";
			for(k=0;k<20;k++)
				{
				for(i=1;i<7;i++)
					{
					for(j=1;j<9;j++)
						{
						if(strcmpi(ctb.clas_nm,tch[k].tbl.tbl[i][j])==0)
							{
							strcpy(tch[k].tbl.tbl[i][j],"NIL");
							strcpy(tch[k].tbl.infotbl[i][j],"\0\0\0");
							}
						}
					}
				}
			cout<<"\nDeleting completed\nSaving data\tPlease Wait";
			tchfile.close();
			for(i=0;i<20;i++)
				{
				tchfile.open("tchtbl.tbl",ios::in|ios::ate|ios::binary);
				temptch.open("tmptch.tbl",ios::out|ios::binary|ios::trunc);
				tchfile.seekg(0,ios::beg);
				while(!tchfile.eof())
					{
					tchfile.read((char*)&tchchk,sizeof(tchchk));
					if(strcmpi(tchchk.tch_nm,tch[i].tch_nm)==0)
						{
						temptch.write((char*)&tch[i],sizeof(tch[i]));
						}
					else temptch.write((char*)&tchchk,sizeof(tchchk));
					}
				remove("tchtbl.tbl");
				rename("tmptch.tbl","tchtbl.tbl");
				temptch.close();
				tchfile.close();
				}
			cout<<"\nCompleted \nProceding further\tFollow instruction";
			}

void head()
	{
	clrscr();
	cout<<"\t\t\t\tARMY PUBLIC SCHOOL";
	cout<<"\n\t\t\t\tTIME TABLE MANAGER";
	}

void mainmenu()
	{
	head();//----------------------//for heading
	cout<<"\n\t1.	CREATE TIME TABLE";//option for creating time tabl
	cout<<"\n\t2.	PRIVIOUS TIME TABLES";//for already saved table:viewing option
	cout<<"\n\t3.	TEACHERS TIME TABLE";	//for viewing teachers time table
	cout<<"\n\t4.	MODIFY DATABASE";//for future modifications
	cout<<"\n\t5.	RESET";//---------to reset manager to itss default
	cout<<"\n\t6.	EXIT\n";//-------------to exit manager
	}

void print_tabl(char tabl[7][9][8],char infotabl[7][9][8])
	{
	int b,c,d;//----------------------------for_loop_variabl----------//
	gotoxy(1,11);
	for(b=0;b<=6;b++)
		{
		cout<<"\n";
		for(c=0;c<=8;c++)
			{
			cout<<tabl[b][c];
			char *str=tabl[b][c];//---count_of_no.of_alphabet--//
			int n=8-strlen(str);//---countto_give spaces-//
			for(d=0;d<n;d++)
				{
				cout<<".";
				}
			}
		cout<<"\n";
		for(c=0;c<=8;c++)
			{
			cout<<infotabl[b][c];
			char *str=infotabl[b][c]; //---count_of_no.of_alphabet--//
			int n=8-strlen(str);//---countto_give spaces-//
			for(d=0;d<n;d++)
				{
				cout<<"_";
				}
			}
		}
	}

void print_clas_tch_tbl(CLASS_TABLE ctb)
	{
	head();
	gotoxy(1,10);
	cout<<ctb.clas_nm;
	print_tabl(ctb.tbl.tbl,ctb.tbl.infotbl);
	}

void print_clas_tch_tbl(TEACH_TABLE tch)
	{
	head();
	gotoxy(1,10);
	cout<<tch.tch_nm;
	print_tabl(tch.tbl.tbl,tch.tbl.infotbl);
	}

void creat_tabl()
	{
	head();
	CLASS_TABLE ctb,ctbchk;
	TEACH_TABLE tch[20],tchchk;
	fstream tchfile;
	fstream classfile;
	classfile.open("clstbl.tbl",ios::out|ios::in|ios::ate|ios::binary);
	tchfile.open("tchtbl.tbl",ios::out|ios::in|ios::ate|ios::binary);
	char subtch[4],bcktch[4],bcksub[4];
	int row=12,col=1,i,j,nsb;
	int k,pos,fnd=0,chdel=0,ntch;
	clasnm:cout<<"\nEnter class\t";
	strcpy(ctb.clas_nm,"\0\0\0\0");
	cin>>ctb.clas_nm;
	cout<<"\nSearching in file";
	classfile.seekg(0,ios::beg);
	while(!classfile.eof())
		{
		classfile.read((char*)&ctbchk,sizeof(ctbchk));
		if(strcmp(ctbchk.clas_nm,ctb.clas_nm)==0)
			{
			print_clas_tch_tbl(ctbchk);
			fnd=1;
			gotoxy(4,4);
			cout<<"\npress any key to cont..";
			getch();
			break;
			}
		}
	classfile.close();
	if(fnd)
		{
		head();
		cout<<"\n1 Delete this";
		cout<<"\n2 Modify this";
		cout<<"\n3 Enter new class";
		cin>>chdel;
		if(chdel==1)
			{
			cout<<"\nDeleting please wait..";
			delet(ctbchk);
			cout<<"\nDeleted!";
			goto del;
			}
		else if(chdel==2)
			{
			mod(ctbchk);
			return;
			}
		else
			goto clasnm;
		}
	del:cout<<"\nEnter no. of subjects\t";
	cin>>nsb;
	ctb.nsb=nsb;
	ntch=0;
	i=0;
	int lm,np;
	for(k=0;k<20;k++)
		{
		strcpy(tch[k].tch_nm,"\0\0\0");
		}
	tchfr:for(;i<nsb;i++)
		{
		cout<<"\nEnter subject:"<<(i+1)<<"\t";
		cin>>ctb.sub_tch[i].sub;
		thnm:cout<<"\nEnter name of the teacher\t";
		cin>>ctb.sub_tch[i].subt;
		for(k=0;k<20;k++)
			{
			if(strcmp(tch[k].tch_nm,ctb.sub_tch[i].subt)==0)
				{
				++i;
				goto tchfr;
				}
			else continue;
			}
		cout<<"\nProcessing file...\tplease wait...";
		tchfile.seekg(0,ios::beg);
		fnd=0;
		while(!tchfile.eof())
			{
			tchfile.read((char*)&tchchk,sizeof(tchchk));
			if(strcmpi(ctb.sub_tch[i].subt,tchchk.tch_nm)==0)
				{
				cout<<"\nfound\tenter to cont...";
				getch();
				print_clas_tch_tbl(tchchk);
				fnd=1;
				getch();
				for(lm=0;lm<7;lm++)
					{
					for(np=0;np<9;np++)
						{
						strcpy(tch[ntch].tbl.tbl[lm][np],tchchk.tbl.tbl[lm][np]);
						strcpy(tch[ntch].tbl.infotbl[lm][np],tchchk.tbl.infotbl[lm][np]);
						}
					}
				tch[ntch].tbl.tabl_of_=tchchk.tbl.tabl_of_;
				ntch++;
				break;
				}
			}
		head();
		cout<<"\nfile processed";
		if(!fnd)
			{
			cout<<"\nNot found\nre-enter";
			cout<<"\nDo you want to create new teacher's data 0/1\t";
			cin>>chdel;
			if(chdel)
				{

				strcpy(tch[ntch].tch_nm,ctb.sub_tch[i].subt);
				cout<<"\ttest:tch[i].tch_nm\t"<<tch[ntch].tch_nm;
				ntch++;
				}
			else
				goto thnm;

			}

		}		
	for(i=0;i<nsb;i++)//-test loop
		{
		print_clas_tch_tbl(tch[i]);
		gotoxy(6,6);
		cout<<"testing teacher's table\t"<<i+1;
		getch();
		}
		char sub[4];
	for(i=1;i<7;i++)
		{
		for(j=1;j<9;j++)
			{
			colsm:col=j*8+1;
			row=i*2+12;
			sub_rng:print_clas_tch_tbl(ctb);
			gotoxy(col,row);
			cin>>sub;//----getting subject in table
			pos=0;
			if(strcmp(sub,".up")==0)
				{
				strcpy(sub,"\0\0\0");
				if(i==1)
				       {
					i=6;
					goto colsm;
					}
				else   {
					--i;
					goto colsm;
					}
				}
			else if(strcmp(sub,".dn")==0)
				{
				strcpy(sub,"\0\0\0");
				if(i==6)
				       {
					i=1;
					goto colsm;
					}
				else {
					++i;
					goto colsm;
					}
				}
			else if(strcmp(sub,"/")==0)
				{
				bck2:strcpy(sub,"\0\0\0");
				if(j==8)
				       {
					j=1;
					if(i==6)
						i=1;
					else
						++i;
					goto colsm;
					}
				else {
					++j;
					goto colsm;
					}
				}
			else if(strcmp(sub,"\\")==0)
				{
				strcpy(sub,"\0\0\0");
				if(j==1)
				       {
					j=8;
					if(i==1)
						i=6;
					else
						--i;
					strcpy(sub,"\0\0\0");
					goto colsm;
					}
				else
					{
					--j;
					goto colsm;
					}
				}
			else if(strcmp(sub,".")==0)
				{
				if(strcmp(ctb.tbl.tbl[i-1][j],"NIL")==0)
					{
					if(i==6&&j==8)
						goto sav;
					else
						goto bck2;
					}
				strcpy(ctb.tbl.tbl[i][j],ctb.tbl.tbl[i-1][j]);
				strcpy(ctb.tbl.infotbl[i][j],ctb.tbl.infotbl[i-1][j]);//assining teacher name to info table of class
				for(k=0;k<nsb;k++)
					{
					if(strcmp(ctb.tbl.tbl[i][j],ctb.sub_tch[k].sub)==0)
						{
						pos=k;
						break;
						}
					}
				for(k=0;k<nsb;k++)
					{
					if(strcmp(ctb.sub_tch[pos].subt,tch[k].tch_nm)==0)
						{
						pos=k;
						break;
						}
					}
				strcpy(tch[pos].tbl.tbl[i][j],ctb.clas_nm);//assining class name to teacher's table
				strcpy(tch[pos].tbl.infotbl[i][j],ctb.tbl.tbl[i][j]);//assining subject to teacher's infotable
				continue;
				}
			else if(strcmp(sub,".xt")==0)
				{
				exit(0);
				}
			else if(strcmp(sub,".mm")==0)
				{
				return;
				}
			else if(strcmp(sub,".bk")==0)
				{       strcpy(ctb.tbl.tbl[i][j],sub);
					if(j>1)
						{
						strcpy(bcktch,ctb.tbl.infotbl[i][j-1]);
						strcpy(ctb.tbl.infotbl[i][j],"\0\0\0");
						strcpy(ctb.tbl.tbl[i][j],"NIL");
						strcpy(ctb.tbl.infotbl[i][j-1],"\0\0\0");
						strcpy(ctb.tbl.tbl[i][j-1],"NIL");
						for(k=0;k<nsb;k++)
							{
							if(strcmpi(ctb.clas_nm,tch[k].tbl.tbl[i][j-1])==0)
								{
								strcpy(tch[k].tbl.infotbl[i][j],"\0\0\0");
								strcpy(tch[k].tbl.tbl[i][j],"NIL");
								strcpy(tch[k].tbl.infotbl[i][j-1],"\0\0\0");
								strcpy(tch[k].tbl.tbl[i][j-1],"NIL");
								break;
								}
							else continue;
							}
						--j;
						goto colsm;
						}
					else if(j==1&&i==1)
						{
						strcpy(ctb.tbl.infotbl[i][j],"\0\0\0");
						strcpy(ctb.tbl.tbl[i][j],"NIL");
						goto sub_rng;
						}
					else
						{
						strcpy(bcktch,ctb.tbl.infotbl[i-1][8]);
						strcpy(ctb.tbl.infotbl[i-1][8],"\0\0\0");
						strcpy(ctb.tbl.tbl[i-1][8],"NIL");
						for(k=0;k<nsb;k++)
							{
							if(strcmpi(ctb.clas_nm,tch[k].tbl.tbl[i-1][8])==0)
								{
								strcpy(tch[k].tbl.infotbl[i-1][8],"\0\0\0");
								strcpy(tch[k].tbl.tbl[i-1][8],"NIL");
								}
							else continue;
							}
						--i;
						j=8;
						goto colsm;
						}
					}
				else
					{
					strcpy(ctb.tbl.tbl[i][j],sub);
					for(k=0;k<nsb;k++)
						{
						if(strcmp(ctb.tbl.tbl[i][j],ctb.sub_tch[k].sub)==0)
							{
							pos=k;
							break;
							}
						else
							{
							pos=10000;
							continue;
							}
						}
					if(pos==10000)
						{
						gotoxy(4,4);
						cout<<"\nEntered subject/command is invalid\tRe-enter";
						strcpy(ctb.tbl.tbl[i][j],"NIL");
						goto sub_rng;
						}
					strcpy(ctb.tbl.infotbl[i][j],ctb.sub_tch[pos].subt);//assining teacher name to info table of class
					for(k=0;k<nsb;k++)
						{
						if(strcmp(ctb.tbl.tbl[i][j],ctb.sub_tch[k].sub)==0)
							{
							pos=k;
							break;
							}
						}
					for(k=0;k<nsb;k++)
						{
						if(strcmp(ctb.sub_tch[pos].subt,tch[k].tch_nm)==0)
							{
							pos=k;
							break;
							}
						}
					if(!strcmpi(tch[pos].tbl.tbl[i][j],"NIL")==0)
						{
						gotoxy(5,5);
						cout<<"\nteacher is not free\t"<<tch[pos].tbl.tbl[i][j]<<"\nre-enter subject\n\tpress key to cont";
						getch();
						goto sub_rng;
						}
					else
						{
						strcpy(tch[pos].tbl.tbl[i][j],ctb.clas_nm);//assining class name to teacher's table
						strcpy(tch[pos].tbl.infotbl[i][j],ctb.tbl.tbl[i][j]);//assining subject to teacher's infotable
						}
				}
		col=1;
		}
	}
	sav:print_clas_tch_tbl(ctb);
	for(k=0;k<nsb;k++)
		{
		getch();
		print_clas_tch_tbl(tch[k]);
		}
	getch();
	head();
	tchfile.close();
	fstream temptch;
	cout<<"\nSaving please wait";
	classfile.open("clstbl.tbl",ios::out|ios::app|ios::binary);
	classfile.write((char*)&ctb,sizeof(ctb));
	classfile.close();
	outtbl(ctb);
		for(i=0;i<nsb;i++)
			{
			tchfile.open("tchtbl.tbl",ios::in|ios::ate|ios::binary);
			temptch.open("tmptch.tbl",ios::out|ios::binary);
			tchfile.seekg(0,ios::beg);
			while(!tchfile.eof())
				{
				tchfile.read((char*)&tchchk,sizeof(tchchk));
				if(strcmpi(tchchk.tch_nm,tch[i].tch_nm)!=0)
					temptch.write((char*)&tchchk,sizeof(tchchk));
				}
			temptch.close();
			tchfile.close();
			remove("tchtbl.tbl");
			rename("tmptch.tbl","tchtbl.tbl");
			}
		tchfile.open("tchtbl.tbl",ios::in|ios::app|ios::binary);
		for(i=0;i<nsb;i++)
			{
			outtbl(tch[i]);
			tchfile.write((char*)&tch[i],sizeof(tch[i]));
			}
		tchfile.close();
	cout<<"\nall record's saved";
	cout<<"\nPress key to cont...";
	}

 void mod(CLASS_TABLE ctb)
	{
	head();
	CLASS_TABLE ctbchk;
	TEACH_TABLE tch[20],tchchk;
	fstream tchfile;
	fstream classfile;
	classfile.open("clstbl.tbl",ios::out|ios::in|ios::ate|ios::binary);
	tchfile.open("tchtbl.tbl",ios::out|ios::in|ios::ate|ios::binary);
	char subtch[4],bcktch[4],bcksub[4];
	int row=12,col=1,i,j,nsb;
	int k,pos,fnd=0,chdel=0,ntch;
	cout<<"\nPresent no. of subjects\t"<<ctb.nsb;
	cout<<"\nEnter new no. of subjects or 0 for retaining previous value\t";
	cin>>nsb;
	if(nsb)
		ctb.nsb=nsb;
	ntch=0;
	char subj[4];
	i=0;
	int lm,np;
	for(k=0;k<20;k++)
		{
		strcpy(tch[k].tch_nm,"\0\0\0");
		}
	tchfr:for(;i<nsb;i++)
		{
		cout<<"\nSubject:"<<(i+1)<<"\t"<<ctb.sub_tch[i].sub;
		cout<<"\nEnter new subject or . for retaining previous";
		cin>>subj;
		if(strcmp(subj,".")!=0)
				strcpy(ctb.sub_tch[i].sub,subj);
		strcpy(subj,"\0\0\0");
		cout<<"\nTeacher:"<<(i+1)<<"\t"<<ctb.sub_tch[i].subt;
		thnm:cout<<"\nEnter new teacher or . for retaining previous\t";
		cin>>subj;
		if(strcmp(subj,".")!=0)
				strcpy(ctb.sub_tch[i].subt,subj);
		strcpy(subj,"\0\0\0");
		for(k=0;k<20;k++)
			{
			if(strcmp(tch[k].tch_nm,ctb.sub_tch[i].subt)==0)
				{
				++i;
				goto tchfr;
				}
			else continue;
			}
		cout<<"\nProcessing file...\tplease wait...";
		tchfile.seekg(0,ios::beg);
		fnd=0;
		while(!tchfile.eof())
			{
			tchfile.read((char*)&tchchk,sizeof(tchchk));

			if(strcmpi(ctb.sub_tch[i].subt,tchchk.tch_nm)==0)
				{
				cout<<"\nfound\tenter to cont...";
				getch();
				print_clas_tch_tbl(tchchk);
				fnd=1;
				getch();
				for(lm=0;lm<7;lm++)
					{
					for(np=0;np<9;np++)
						{
						strcpy(tch[ntch].tbl.tbl[lm][np],tchchk.tbl.tbl[lm][np]);
						strcpy(tch[ntch].tbl.infotbl[lm][np],tchchk.tbl.infotbl[lm][np]);
						}
					}
				tch[ntch].tbl.tabl_of_=tchchk.tbl.tabl_of_;
				ntch++;
				break;
				}
			}
		head();
		cout<<"\nfile processed";
		if(!fnd)
			{
			cout<<"\nteacher Not found\nre-enter";
			cout<<"\nDo you want to create new teacher's data 0/1\t";
			cin>>chdel;
			if(chdel)
				{
				strcpy(tch[ntch].tch_nm,ctb.sub_tch[i].subt);
				cout<<"\ttest:tch[i].tch_nm\t"<<tch[ntch].tch_nm;
				ntch++;
				}
			else
				goto thnm;

			}
		}
	for(i=0;i<nsb;i++)//-test loop
		{
		print_clas_tch_tbl(tch[i]);
		gotoxy(6,6);
		cout<<"testing teacher's table\t"<<i+1;
		getch();
		}		
		char sub[4];
	for(i=1;i<7;i++)
		{
		for(j=1;j<9;j++)
			{
			colsm:col=j*8+1;
			row=i*2+12;
			sub_rng:print_clas_tch_tbl(ctb);
			gotoxy(col,row);
			cin>>sub;//----getting subject in table
			pos=0;
			if(strcmp(sub,".up")==0)
				{
				strcpy(sub,"\0\0\0");
				if(i==1)
				       {
					i=6;
					goto colsm;
					}
				else   {
					--i;
					goto colsm;
					}
				}
			else if(strcmp(sub,".dn")==0)
				{
				strcpy(sub,"\0\0\0");
				if(i==6)
				       {
					i=1;
					goto colsm;
					}
				else {
					++i;
					goto colsm;
					}
				}
			else if(strcmp(sub,"/")==0)
				{
				bck:strcpy(sub,"\0\0\0");
				if(j==8)
				       {
					j=1;
					if(i==6)
						i=1;
					else
						++i;
					goto colsm;
					}
				else {
					++j;
					goto colsm;
					}
				}
			else if(strcmp(sub,"\\")==0)
				{
				strcpy(sub,"\0\0\0");
				if(j==1)
				       {
					j=8;
					if(i==1)
						i=6;
					else
						--i;
					strcpy(sub,"\0\0\0");
					goto colsm;
					}
				else
					{
					--j;
					goto colsm;
					}
				}
			else if(strcmp(sub,".")==0)
				{
				if(strcmp(ctb.tbl.tbl[i-1][j],"NIL")==0)
					{
					if(i==6&&j==8)
						goto sav2;
					else
						goto bck;
					}
				strcpy(ctb.tbl.tbl[i][j],ctb.tbl.tbl[i-1][j]);
				strcpy(ctb.tbl.infotbl[i][j],ctb.tbl.infotbl[i-1][j]);//assining teacher name to info table of class
				for(k=0;k<nsb;k++)
					{
					if(strcmp(ctb.tbl.tbl[i][j],ctb.sub_tch[k].sub)==0)
						{
						pos=k;
						break;
						}
					}
				for(k=0;k<nsb;k++)
					{
					if(strcmp(ctb.sub_tch[pos].subt,tch[k].tch_nm)==0)
						{
						pos=k;
						break;
						}
					}
				strcpy(tch[pos].tbl.tbl[i][j],ctb.clas_nm);//assining class name to teacher's table
				strcpy(tch[pos].tbl.infotbl[i][j],ctb.tbl.tbl[i][j]);//assining subject to teacher's infotable
				continue;
				}
			else if(strcmp(sub,".xt")==0)
				{
				exit(0);
				}
			else if(strcmp(sub,".mm")==0)
				{
				return;
				}
			else if(strcmp(sub,".bk")==0)
				{      
					 strcpy(ctb.tbl.tbl[i][j],sub);
					if(j>1)
						{
						strcpy(bcktch,ctb.tbl.infotbl[i][j-1]);
						strcpy(ctb.tbl.infotbl[i][j],"\0\0\0");
						strcpy(ctb.tbl.tbl[i][j],"NIL");
						strcpy(ctb.tbl.infotbl[i][j-1],"\0\0\0");
						strcpy(ctb.tbl.tbl[i][j-1],"NIL");
						for(k=0;k<nsb;k++)
							{
							if(strcmpi(ctb.clas_nm,tch[k].tbl.tbl[i][j-1])==0)
								{
								strcpy(tch[k].tbl.infotbl[i][j],"\0\0\0");
								strcpy(tch[k].tbl.tbl[i][j],"NIL");
								strcpy(tch[k].tbl.infotbl[i][j-1],"\0\0\0");
								strcpy(tch[k].tbl.tbl[i][j-1],"NIL");
								break;
								}
							else continue;
							}
						--j;
						goto colsm;
						}
					else if(j==1&&i==1)
						{
						strcpy(ctb.tbl.infotbl[i][j],"\0\0\0");
						strcpy(ctb.tbl.tbl[i][j],"NIL");
						goto sub_rng;
						}
					else
						{
						strcpy(bcktch,ctb.tbl.infotbl[i-1][8]);
						strcpy(ctb.tbl.infotbl[i-1][8],"\0\0\0");
						strcpy(ctb.tbl.tbl[i-1][8],"NIL");
						for(k=0;k<nsb;k++)
							{
							if(strcmpi(ctb.clas_nm,tch[k].tbl.tbl[i-1][8])==0)
								{
								strcpy(tch[k].tbl.infotbl[i-1][8],"\0\0\0");
								strcpy(tch[k].tbl.tbl[i-1][8],"NIL");
								}
							else continue;
							}
						--i;
						j=8;
						goto colsm;
						}
					}
				else
					{
					strcpy(ctb.tbl.tbl[i][j],sub);
					for(k=0;k<nsb;k++)
						{
						if(strcmp(ctb.tbl.tbl[i][j],ctb.sub_tch[k].sub)==0)
							{
							pos=k;
							break;
							}
						else
							{
							pos=10000;
							continue;
							}
						}
					if(pos==10000)
						goto sub_rng;
					strcpy(ctb.tbl.infotbl[i][j],ctb.sub_tch[pos].subt);//assining teacher name to info table of class
					for(k=0;k<nsb;k++)
						{
						if(strcmp(ctb.tbl.tbl[i][j],ctb.sub_tch[k].sub)==0)
							{
							pos=k;
							break;
							}
						}
					for(k=0;k<nsb;k++)
						{
						if(strcmp(ctb.sub_tch[pos].subt,tch[k].tch_nm)==0)
							{
							pos=k;
							break;
							}
						}
					if(!strcmpi(tch[pos].tbl.tbl[i][j],"NIL")==0)
						{
						gotoxy(5,5);
						cout<<"\nteacher is not free\t"<<tch[pos].tbl.tbl[i][j]<<"\nre-enter subject\n\tpress key to cont";
						getch();
						goto sub_rng;
						}
					else
						{
						strcpy(tch[pos].tbl.tbl[i][j],ctb.clas_nm);//assining class name to teacher's table
						strcpy(tch[pos].tbl.infotbl[i][j],ctb.tbl.tbl[i][j]);//assining subject to teacher's infotable
						}
				}
		col=1;
		}
	}
	sav2:print_clas_tch_tbl(ctb);
	for(k=0;k<nsb;k++)
		{
		getch();
		print_clas_tch_tbl(tch[k]);
		}
	getch();
	head();
	tchfile.close();
	fstream temptch;
	cout<<"\nSaving please wait";
	classfile.open("clstbl.tbl",ios::out|ios::app|ios::binary);
	classfile.write((char*)&ctb,sizeof(ctb));
	classfile.close();
	outtbl(ctb);
		for(i=0;i<nsb;i++)
			{
			tchfile.open("tchtbl.tbl",ios::in|ios::ate|ios::binary);
			temptch.open("tmptch.tbl",ios::out|ios::binary);
			tchfile.seekg(0,ios::beg);
			fnd=0;
			while(!tchfile.eof())
				{
				tchfile.read((char*)&tchchk,sizeof(tchchk));
				if(strcmpi(tchchk.tch_nm,tch[i].tch_nm)!=0)
					{
					temptch.write((char*)&tchchk,sizeof(tchchk));
					}
				}
			temptch.close();
			tchfile.close();
			remove("tchtbl.tbl");
			rename("tmptch.tbl","tchtbl.tbl");
			}
		tchfile.open("tchtbl.tbl",ios::in|ios::app|ios::binary);
		for(i=0;i<nsb;i++)
			{
			outtbl(tch[i]);
			tchfile.write((char*)&tch[i],sizeof(tch[i]));
			}
		tchfile.close();
	cout<<"\nall record's saved";
	cout<<"\nPress key to cont...";
	}
//----------------end_of_function_definations------------//

void main()
	{
	TABLE testtbl;//------------------to_check_printing_of_table----//
	testtbl.tabl_of_=1;
	testtbl.init_infotbl();
	CLASS_TABLE ctb,ctbchk;
	TEACH_TABLE tch,tchchk;
	fstream classfile;
	classfile.open("clstbl.tbl",ios::in|ios::ate|ios::binary);
	fstream tchfile;
	int fnd=0;
	tchfile.open("tchtbl.tbl",ios::in|ios::ate|ios::binary);
	int ch;//--------------------------for taking users choice--//
	remm:mainmenu();
	lb:cin>>ch;
	switch(ch)
		{
		case 1:
			creat_tabl();
			getch();
			goto remm;
		case 2:
			head();
			fnd=0;
			cout<<"\nEnter class\t";
			cin>>ctb.clas_nm;
			classfile.seekg(0);
			while(classfile)
				{
				classfile.read((char*)&ctbchk,sizeof(ctbchk));
				if(strcmp(ctbchk.clas_nm,ctb.clas_nm)==0)
					{
					print_clas_tch_tbl(ctbchk);
					fnd=1;
					getch();
					break;
					}
				}
			if(!fnd)
				{
				cout<<"\nNot found\nre-enter";
				getch();
				}
				goto remm;
		case 3:
			head();
			fnd=0;
			cout<<"\nEnter name\t";
			cin>>tch.tch_nm;
			cout<<"\nProcessing file";
			tchfile.seekg(0,ios::beg);
			cout<<"\tPlease Wait";
			while(!tchfile.eof())
				{
				tchfile.read((char*)&tchchk,sizeof(tchchk));
				if(strcmpi(tch.tch_nm,tchchk.tch_nm)==0)
					{
					cout<<"\nfound\tenter to cont...";
					getch();
					print_clas_tch_tbl(tchchk);
					fnd=1;
					getch();
					break;
					}
				}
				head();
			cout<<"\nfile processed";
			getch();
			if(!fnd)
				{
				cout<<"\nNot found\nre-enter";
				getch();
				}
			goto remm;

		case 4:
			cout<<"\n\t\t\t\toption under process\n\t\t\t\tERROR!!";
			cout<<"\nNot available with this version";
			getch();
			goto remm;
		case 5:
			head();
			remove("clstbl.tbl");
			remove("tchtbl.tbl");
			goto remm;
		case 6:
			exit(0);
		default:cout<<"Wrong choice\nre-enter:\t";
			goto lb;
			break;
		}
	}



