#include <stdio.h>
#include <string.h>

int NOP=0;
int NOD=0;

typedef struct pat_id{
	char username[50];
	char password[50];
} pat_id;

typedef struct patient{
	char name[50];
	char email[100];
	char username[50];
	char password[100];
	char DOB[20];
} patient;

void register_patient();

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
		//authenticate_patient();
	}
}

void register_patient()
{
	int flag=0;
	do{
		patient x;
		printf("PLEASE ENTER YOUR PERSONAL DETAILS -\n");
		printf("  1. NAME : ");
		scanf("%s",x.name);
		printf("  2. USERNAME : ");
		scanf("%s",x.username);
		printf("  3. PASSWORD : ");
		scanf("%s",x.password);
		printf("  4. EMAIL-ID : ");
		scanf("%s",x.email);
		printf("  5. DOB (dd-mm-yyyy) : ");
		scanf("%s",x.DOB);

		if (NOP==0)
		{
			flag=1;
			NOP++;
			pat_id temp;
			strcpy(temp.username,x.username);
			strcpy(temp.password,temp.password);
			FILE *ptr;
			ptr=fopen("patient-log.bin","ab+");
			fseek(ptr,0,SEEK_END);
			fwrite(&temp,sizeof(struct pat_id),1,ptr);
			fclose(ptr);
		}
		else
		{
				FILE *ptr;
				ptr=fopen("patient-log.bin","ab+");
				for (int i=0;i<NOP;i++)
				{
					pat_id check;
					fread(&check,sizeof(struct pat_id),1,ptr);

					//printf("%d %s\n",i,check.username);

					if (strcmp(check.username,x.username)==0)
					{
						printf("THE USERNAME ALREADY EXISTS, PLEASE SELECT SOME OTHER USERNAME.\n");
					}
					else
					{
						flag=1;
						NOP++;
						pat_id temp;
						strcpy(temp.username,x.username);
						strcpy(temp.password,temp.password);
						fseek(ptr,0,SEEK_END);
						fwrite(&temp,sizeof(struct pat_id),1,ptr);
					}
				}
				fclose(ptr);
		}
	}while(!flag);
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
	return 0;
}