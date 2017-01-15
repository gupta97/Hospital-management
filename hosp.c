#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void register_patient();
void authenticate_patient();

void init_patient()
{
	char x;
	
	do{
		printf("ARE YOU A REGISTERED PATIENT (Y/N) : ");
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
	int flag=0;
	patient x;

	do{
		flag=0;
		printf("PLEASE ENTER YOUR PERSONAL DETAILS -\n");
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
	pat_id temp;
	strcpy(temp.username,x.username);
	strcpy(temp.password,x.password);
	fseek(ptr2,0,SEEK_END);
	fwrite(&temp,sizeof(struct pat_id),1,ptr2);
	fclose(ptr2);

	printf("\nWELCOME NEW USER! YOU ARE NOW LOGGED IN \n");

	FILE* ptr3;
	char h[100]="patients/";
	strcat(h,x.username);
	strcat(h,".bin");

	ptr3=fopen(h,"ab+");

	fwrite(&x,sizeof(struct patient),1,ptr3);
	fclose(ptr3);

}

void authenticate_patient()
{
	printf("ENTER YOUR USERNAME AND PASSWORD TO LOG-IN : \n");
	
	pat_id check;
	int flag=0;

	do{
		pat_id x;
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

	printf("YOU HAVE SUCCESSFULLY LOGGED-IN ! \n");
}


void register_doctor();
void authenticate_doctor();
void init_doctor()
{
	char x;
	
	do{
		printf("ARE YOU A REGISTERED DOCTOR (Y/N) : ");
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
		printf("PLEASE ENTER YOUR PERSONAL DETAILS -\n");
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
	printf("ENTER YOUR USERNAME AND PASSWORD TO LOG-IN : \n");
	
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
			printf("  INVALID LOGIN, PLEASE TRY AGAIN\n\n");

	}while (!flag);

	printf("YOU HAVE SUCCESSFULLY LOGGED-IN ! \n");
}

int main()
{
	printf("HI!\nWELCOME TO THE ONLINE PATIENT MONITORING SYSTEM\n\n");

	double choice;
	do{
		printf("PLEASE ENTER YOUR CHOICE\n");
		printf("  1. PATIENT (ENTER 1)\n");
		printf("  2. DOCTOR (ENTER 2)\n");
		printf("  ENTER CHOICE : ");
		scanf("%lf",&choice);
		printf("\n");
	}while(choice!=1 && choice!=2);

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