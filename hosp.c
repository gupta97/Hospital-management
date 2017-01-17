#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//patient file : patient struct + doctor under whom registered + health status
//doctors file : doctor struct + patients under doctor

typedef struct pat_id{
	char username[50];
	char password[50];
} pat_id;

typedef struct doc_id{
	char username[50];
	char password[50];
} doc_id;

typedef struct patient{
	char name[50];
	char email[100];
	char username[50];
	char password[100];
	char DOB[20];
} patient;

typedef struct doctor{
	char name[50];
	char username[50];
	char email[50];
	char password[50];
} doctor;

typedef struct status{
	double temperature;
	double bp;
} status;

typedef struct request{
	char doc[100];
	char pat[100];
	int flag;
} request;

void register_patient();
void authenticate_patient();
void reg_pat_with_doc(char username[100]);

void print_doctors()
{
	printf("\nLIST OF REGISTERED DOCTORS : \n");
	FILE* ptr=fopen("doctor-log.bin","rb");
	fseek(ptr,0,SEEK_SET);
	doc_id temp;
	while (1)
	{
		fread(&temp,sizeof(doc_id),1,ptr);
		if (feof(ptr))break;

		fseek(ptr,-1*sizeof(doc_id),SEEK_CUR);
		fread(&temp,sizeof(doc_id),1,ptr);

		printf("%s\n",temp.username);
	}
	fclose(ptr);
	printf("\n");
}

void print_patients()
{
	printf("\nLIST OF REGISTERED PATIENTS : \n");
	FILE* ptr=fopen("patient-log.bin","rb");
	fseek(ptr,0,SEEK_SET);
	pat_id temp;
	while (1)
	{
		fread(&temp,sizeof(pat_id),1,ptr);
		if (feof(ptr))break;

		fseek(ptr,-1*sizeof(pat_id),SEEK_CUR);
		fread(&temp,sizeof(pat_id),1,ptr);

		printf("%s\n",temp.username);
	}
	fclose(ptr);
	printf("\n");
}

void init_patient()
{
	char x;
	
	do{
		printf("\nARE YOU A REGISTERED PATIENT (Y/N) : ");
		scanf(" %c",&x);
	}while (x!='Y' && x!='N');

	if (x=='N')
	{
		register_patient();
	}
	else if (x=='Y')
	{
		authenticate_patient();
	}
}

void register_patient()
{
	FILE* fp=fopen("doctor-log.bin","rb");
	doc_id tmp;
	fread(&tmp,sizeof(doc_id),1,fp);
	if (feof(fp))
	{
		printf("\nSORRY, YOUR PROFILE COULD NOT BE CREATED, THERE ARE NO DOCTORS REGISTERED IN OUR SYSTEM YET!\n\n");
		fclose(fp);
		return;
	}

	int flag=0;
	patient x;

	do{
		flag=0;
		printf("\nPLEASE ENTER YOUR PERSONAL DETAILS -\n");
		printf("  1. FIRST NAME : ");
		scanf("%s",x.name);
		printf("  2. USERNAME : ");
		scanf("%s",x.username);
		printf("  3. PASSWORD : ");
		scanf("%s",x.password);
		printf("  4. EMAIL-ID : ");
		scanf("%s",x.email);
		printf("  5. DOB (dd-mm-yyyy) : ");
		scanf("%s",x.DOB);

				FILE *ptr;
				ptr=fopen("patient-log.bin","ab+");
				fseek(ptr,0,SEEK_SET);

				for (int i=0;;i++)
				{

					if (feof(ptr))break;

					pat_id check;
					fread(&check,sizeof(struct pat_id),1,ptr);

					if (strcmp(check.username,x.username)==0)
					{
						printf("\nTHE USERNAME ALREADY EXISTS, PLEASE SELECT SOME OTHER USERNAME.\n\n");
						flag=1;
						break;
					}
					
				}
				fclose(ptr);
	}while(flag);

	FILE* ptr2;
	ptr2=fopen("patient-log.bin","ab+");
	pat_id temp1;
	strcpy(temp1.username,x.username);
	strcpy(temp1.password,x.password);
	fseek(ptr2,0,SEEK_END);
	fwrite(&temp1,sizeof(struct pat_id),1,ptr2);
	fclose(ptr2);

	printf("\nWELCOME NEW USER! YOU ARE NOW LOGGED IN \n");

	FILE* ptr3;
	char h[100]="patients/";
	strcat(h,x.username);
	strcat(h,".bin");

	ptr3=fopen(h,"ab+");

	fwrite(&x,sizeof(struct patient),1,ptr3);
	fclose(ptr3);

	printf("\nYOU WILL HAVE TO REGISTER UNDER A DOCTOR TO PROCEED\n");
	printf("\nHERE IS A LIST OF REGISTERED DOCTORS\n");
	printf("\n%5s%20s%20s\n\n","SR NO","NAME","USERNAME");
	
	FILE* ptr=fopen("doctor-log.bin","rb");
	fseek(ptr,0,SEEK_SET);
	doc_id temp;
	for (int i=1;;i++)
	{
		fread(&temp,sizeof(doc_id),1,ptr);
		if (feof(ptr))break;

		fseek(ptr,-1*sizeof(doc_id),SEEK_CUR);
		fread(&temp,sizeof(doc_id),1,ptr);

		char h2[100]="doctors/";
		strcat(h2,temp.username);
		strcat(h2,".bin");
		
		FILE* ptr2=fopen(h2,"rb");

		doctor temp2;
		fread(&temp2,sizeof(doctor),1,ptr2);
		printf("%5d%20s%20s\n",i,temp2.name,temp.username);

		fclose(ptr2);
	}
	fclose(ptr);
	reg_pat_with_doc(x.username);

	ptr=fopen(h,"ab+");
	status val;


	//ENTER HEALTH STATUS
	printf("\nENTER YOUR CURRENT HEALTH STATUS\n\n1. BODY-TEMPERATURE (fahrenheit) : ");
	scanf("%lf",&val.temperature);
	printf("\n2. BLOOD PRESSURE (mm) : ");
	scanf("%lf",&val.bp);

	fseek(ptr,0,SEEK_END);
	fwrite(&val,sizeof(struct status),1,ptr);

	fclose(ptr);

	printf("\nWE PROVIDE THE FOLLOWING SERVICES\n");

	char choice[10];
	int flg=1;
	do{
		printf("\n  1. VIEW HEALTH STATUS\n  2. ASK DOCTOR TO CONSULT\n  3. LOG-OUT\n");
		printf("\nENTER YOUR CHOICE : ");
		scanf("%s",choice);

		if (strlen(choice)==1 && (choice[0]=='1' || choice[0]=='2' || choice[0]=='3'))
		{
			flg=0;break;
		}

		else 
		{
			printf("\nINVALID CHOICE ;\n");
		}
	} while (flg);

	if (choice[0]=='1')
	{
		FILE* ptr=fopen(h,"rb");
		fseek(ptr,0,SEEK_END);
		fseek(ptr,-1*sizeof(status),SEEK_CUR);

		status temp;
		fread(&temp,sizeof(status),1,ptr);
		fclose(ptr);

		printf("\nYOUR HEALTH STATUS : \n");
		printf("\n  1. BODY TEMPERATURE : %lf\n  2. BLOOD PRESSURE : %lf\n",temp.temperature,temp.bp);
	}

	else if (choice[0]=='2')
	{
		FILE* ptr=fopen(h,"rb");
		fseek(ptr,sizeof(struct patient),SEEK_SET);
		char temp[100];
		fread(&temp,sizeof(char)*100,1,ptr);
		printf("%s\n",temp);

		char my[100]="doctors/";
		strcat(my,temp);
		strcat(my,".bin");

		fclose(ptr);

		ptr=fopen(my,"rb");
		doctor temp2;
		fread(&temp2,sizeof(struct doctor),1,ptr);
		printf("\nYOUR DOCTOR IS : %s\n",temp2.name);
		printf("\nYOU CAN CONTACT HIM VIA E-MAIL : %s\n",temp2.email);

		fclose(ptr);

	}

	else if (choice[0]=='3')
	{
		printf("\nYOU HAVE SUCCESSFULLY LOGGED OUT!\n\n");
	}
}

void reg_pat_with_doc(char username[100])
{
	printf("\nPLEASE ENTER THE USERNAME OF THE DOCTOR YOU WANT TO REGISTER WITH : \n");
	char inp[100];
	int flag=0;
	do{
		scanf("%s",inp);
		
		FILE* ptr=fopen("doctor-log.bin","rb");
		fseek(ptr,0,SEEK_SET);
		doc_id temp;
		while (1)
		{
			fread(&temp,sizeof(doc_id),1,ptr);
			if (feof(ptr))break;

			fseek(ptr,-1*sizeof(doc_id),SEEK_CUR);
			fread(&temp,sizeof(doc_id),1,ptr);

			if (strcmp(temp.username,inp)==0)
			{
				flag=1;
				break;
			}
		}
		(ptr);

		if (flag==0)
		{
			printf("\nINVALID USERNAME ENTERED, PLEASE TRY AGAIN\n");
			printf("\nENTER USER-NAME\n");
		}
	
	} while (!flag);

	char temp[100]="doctors/";
	strcat(temp,inp);
	strcat(temp,".bin");

	FILE* ptr=fopen(temp,"ab+");
	fseek(ptr,0,SEEK_END);
	fwrite(&username,sizeof(char)*100,1,ptr);
	fclose(ptr);

	char temp2[100]="patients/";
	strcat(temp2,username);
	strcat(temp2,".bin");

	ptr=fopen(temp2,"ab+");

	fwrite(&inp,sizeof(char)*100,1,ptr);
	fclose(ptr);
}

void authenticate_patient()
{
	printf("\nENTER YOUR USERNAME AND PASSWORD TO LOG-IN : \n");
	
	pat_id check;
	int flag=0;
	pat_id x;

	do{
		printf("  USERNAME : ");
		scanf("%s",x.username);
		printf("  PASSWORD : ");
		scanf("%s",x.password);

		FILE* ptr;
		ptr=fopen("patient-log.bin","rb");
		fseek(ptr,0,SEEK_SET);

		for (int i=0;;i++)
		{
			if (feof(ptr))break;

			fread(&check,sizeof(struct pat_id),1,ptr);

			if ((strcmp(x.username,check.username)==0) && (strcmp(x.password,check.password)==0))
				flag=1;
		}
		fclose(ptr);

		if (flag==0)
			printf("  INVALID LOGIN, PLEASE TRY AGAIN\n\n");

	}while (!flag);

	printf("\nYOU HAVE SUCCESSFULLY LOGGED-IN ! \n");

	char h[100]="patients/";
	strcat(h,x.username);
	strcat(h,".bin");

	//choices

	printf("\nCHOOSE FROM THE FOLLOWING SERVICES\n");

	char choice[10];
	int flg=1;
	do{
		printf("\n  1. VIEW HEALTH STATUS\n  2. ASK DOCTOR TO CONSULT\n  3. LOG-OUT\n");
		printf("\nENTER YOUR CHOICE : ");
		scanf("%s",choice);

		if (strlen(choice)==1 && (choice[0]=='1' || choice[0]=='2' || choice[0]=='3'))
		{
			flg=0;break;
		}

		else 
		{
			printf("\nINVALID CHOICE ;\n");
		}
	} while (flg);

	if (choice[0]=='1')
	{
		FILE* ptr=fopen(h,"rb");
		fseek(ptr,0,SEEK_END);
		fseek(ptr,-1*sizeof(status),SEEK_CUR);

		status temp;
		fread(&temp,sizeof(status),1,ptr);
		fclose(ptr);

		printf("\nYOUR HEALTH STATUS : \n");
		printf("\n  1. BODY TEMPERATURE : %lf\n  2. BLOOD PRESSURE : %lf\n",temp.temperature,temp.bp);
	}

	else if (choice[0]=='2')
	{
		FILE* ptr=fopen(h,"rb");
		fseek(ptr,sizeof(struct patient),SEEK_SET);
		char temp[100];
		fread(&temp,sizeof(char)*100,1,ptr);
		printf("%s\n",temp);

		char my[100]="doctors/";
		strcat(my,temp);
		strcat(my,".bin");

		fclose(ptr);

		ptr=fopen(my,"rb");
		doctor temp2;
		fread(&temp2,sizeof(struct doctor),1,ptr);
		printf("\nYOUR DOCTOR IS : %s\n",temp2.name);
		printf("\nYOU CAN CONTACT HIM VIA E-MAIL : %s\n",temp2.email);

		fclose(ptr);

	}

	else if (choice[0]=='3')
	{
		printf("\nYOU HAVE SUCCESSFULLY LOGGED OUT!\n\n");
	}
}


void register_doctor();
void authenticate_doctor();
void init_doctor()
{
	char x;
	
	do{
		printf("\nARE YOU A REGISTERED DOCTOR (Y/N) : ");
		scanf(" %c",&x);
	}while (x!='Y' && x!='N');

	if (x=='N')
	{
		register_doctor();
	}
	else if (x=='Y')
	{
		authenticate_doctor();
	}
}

void register_doctor()
{
	int flag=0;
	doctor x;

	do{
		flag=0;
		printf("\nPLEASE ENTER YOUR PERSONAL DETAILS -\n");
		printf("  1. FIRST NAME : ");
		scanf("%s",x.name);
		printf("  2. USERNAME : ");
		scanf("%s",x.username);
		printf("  3. PASSWORD : ");
		scanf("%s",x.password);
		printf("  4. EMAIL-ID : ");
		scanf("%s",x.email);

				FILE *ptr;
				ptr=fopen("doctor-log.bin","ab+");
				fseek(ptr,0,SEEK_SET);

				for (int i=0;;i++)
				{

					if (feof(ptr))break;

					doc_id check;
					fread(&check,sizeof(struct doc_id),1,ptr);

					if (strcmp(check.username,x.username)==0)
					{
						printf("\nTHE USERNAME ALREADY EXISTS, PLEASE SELECT SOME OTHER USERNAME.\n\n");
						flag=1;
						break;
					}
					
				}
				fclose(ptr);
	}while(flag);

	FILE* ptr2;
	ptr2=fopen("doctor-log.bin","ab+");
	doc_id temp;
	strcpy(temp.username,x.username);
	strcpy(temp.password,x.password);
	fseek(ptr2,0,SEEK_END);
	fwrite(&temp,sizeof(struct doc_id),1,ptr2);
	fclose(ptr2);

	printf("\nWELCOME NEW USER! YOU ARE NOW LOGGED IN \n");

	FILE* ptr3;
	char h[100]="doctors/";
	strcat(h,x.username);
	strcat(h,".bin");

	ptr3=fopen(h,"ab+");

	fwrite(&x,sizeof(struct doctor),1,ptr3);
	fclose(ptr3);
}

void authenticate_doctor()
{
	printf("\nENTER YOUR USERNAME AND PASSWORD TO LOG-IN : \n");
	
	doc_id check;
	int flag=0;

	do{
		doc_id x;
		printf("  USERNAME : ");
		scanf("%s",x.username);
		printf("  PASSWORD : ");
		scanf("%s",x.password);

		FILE* ptr;
		ptr=fopen("doctor-log.bin","rb");
		fseek(ptr,0,SEEK_SET);

		for (int i=0;;i++)
		{
			if (feof(ptr))break;

			fread(&check,sizeof(struct doc_id),1,ptr);

			if ((strcmp(x.username,check.username)==0) && (strcmp(x.password,check.password)==0))
				flag=1;
		}
		fclose(ptr);

		if (flag==0)
			printf("\n  INVALID LOGIN, PLEASE TRY AGAIN\n");

	}while (!flag);

	printf("\nYOU HAVE SUCCESSFULLY LOGGED-IN ! \n");
}

int main()
{
	printf("HI!\nWELCOME TO THE ONLINE PATIENT MONITORING SYSTEM\n\n");

	print_doctors();
	print_patients();

	double choice;
	do{
		printf("\nPLEASE ENTER YOUR CHOICE\n");
		printf("  1. PATIENT (ENTER 1)\n");
		printf("  2. DOCTOR (ENTER 2)\n");
		printf("  3. EXIT\n");
		printf("  ENTER CHOICE : ");
		scanf("%lf",&choice);
		printf("\n");
	}while(choice!=1 && choice!=2 && choice!=3);

	if (choice==1)
	{
		init_patient();
	}

	else if (choice==2)
	{
		init_doctor();
	}

	return 0;
}