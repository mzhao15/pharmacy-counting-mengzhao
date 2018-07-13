# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAXNAME 100  //max length of drug names, prescriber's last names and first names
# define NDRUG 10000 //max number of drugs

struct record 
{
	int id;
	char last_name[MAXNAME];
	char first_name[MAXNAME];
	char drug_name[MAXNAME];
	double cost;
}; // the input data structure

struct drugcost
{
	char drug_name[MAXNAME];
	int num_prescriber;
	double total_cost;
}; // the new data structure for each drug

struct drugcost cost[NDRUG]; // all the drugs with their total cost and number of prescribers

/*initialize the string*/ 
void initstring(char*,int); 
/*search in 'cost', if there is rec.drug_name, update the number of prescribers and total cost;
otherwise, add current 'rec' to 'cost' as a new drug*/
int search(struct record temp,int num);

int main()
{
	int i = 0, j = 0, k = 0;
	char ch = '\0';

	int header = 1; //by default, there is a header line

	int wordnum = 0; //the n-th word in the a line
	int drugnum = 0; //numbder of drugs

	int id = 0; // id for the drug with max total cost
	double max = -10000.0; //used to find the max total cost of a drug
	int cond = 0;

	FILE *finput,*foutput;  //input and output files

	char temp[MAXNAME]; //store the word read from the input file
	struct record rec;

	//initialize the cost array
	for (i = 0;i < NDRUG; i++)
	{
		for (j = 0;j < MAXNAME; j++)
			cost[i].drug_name[j] = '\0';
		cost[i].num_prescriber = 0;
		cost[i].total_cost = 0.0;
	}
	//initialize the rec array
	rec.id = 0;
	for (j=0;j<MAXNAME;j++)
	{
		rec.last_name[j] = '\0';
		rec.first_name[j] = '\0';
		rec.drug_name[j] = '\0';
	}
	rec.cost = 0;
	
	// open intput and output files
	if ((finput = fopen("itcont.txt","r")) == NULL)
	{
		printf("Input file cannot be opened!\n");
		return -1;
	}
	if ((foutput = fopen("top_drug_cost.txt","w")) == NULL)
	{
		printf("Output file cannot be opened!\n");
		return -1;
	}

	// check if there is a header line
	ch = getc(finput);
	if (ch>'9' | ch <'0')
		header = 1;
	else 
		header = 0;
	
	do
	{
		if (header == 1)
		{
			// header line
			while (ch != '\n')
				ch = getc(finput);
			header = 0;
			ch = getc(finput);
			continue;
		}

		if (ch != '\n' & ch != '\0' )  
		{
			if (ch != ',')
			{
				// read the input file word by word and assign to temp
				temp[k] = ch;
				k++;
			}
			else if (ch == ',')
			{
				//end of a word, assign temp to rec
				if (wordnum == 0)
					rec.id = atoi(temp);    //convert string to int
				else if (wordnum == 1)
					strcpy(rec.last_name,temp);
				else if (wordnum == 2)
					strcpy(rec.first_name,temp);
				else if (wordnum == 3)
					strcpy(rec.drug_name,temp);
				else 
					// if the prescriber's name has more than two words
					strcpy(rec.drug_name,temp);
				
				// reset variables
				initstring(temp,MAXNAME);
				wordnum++;
				k = 0;			
			}
		}
		else
		{
			// end of line, ch == '\n'
			rec.cost = atof(temp);  //convert string to int
			//printf("%d,%s,%s,%s,%.2f\n",rec.id,rec.last_name,rec.first_name,rec.drug_name,rec.cost);

			/*search in 'cost', if there is rec.drug_name, update the number of prescribers and total cost;
			  otherwise, add current 'rec' to 'cost' as a new drug   */
			drugnum = search(rec, drugnum);
			// check if the number of drugs exceeds NDRUG
			if (drugnum > NDRUG)
			{
				printf("Too many drugs!\n");
				return 0;
			}

			// reset the variables
			initstring(temp,MAXNAME);
			wordnum = 0;
			k = 0;

			rec.id = 0;
			for (j=0;j<MAXNAME;j++)
			{
				rec.last_name[j] = '\0';
				rec.first_name[j] = '\0';
				rec.drug_name[j] = '\0';
			}
			rec.cost = 0;	
		}
		ch = getc(finput);
	} while (!(feof(finput)));

	//end of file, last record/line
	rec.cost = atof(temp);  //convert string to int
	//printf("%d,%s,%s,%s,%.2f\n",rec.id,rec.last_name,rec.first_name,rec.drug_name,rec.cost);
	drugnum = search(rec, drugnum);
	if (drugnum > NDRUG)
	{
		printf("Too many drugs!\n");
		return 0;
	}

	/*-------------order the drugs based on the total cost and drug name--------------------------*/
	/*-------------------save the information to output file-------------------------------------*/
	fprintf(foutput,"drug_name,num_prescriber,total_cost\n"); //print the header line
	//printf("drug_name,num_prescriber,total_cost\n");

	for (j = 0;j < drugnum; j++)
	{
		max = -10000.0;
		for (i = 0;i < drugnum; i++)
		{
			if (cost[i].total_cost > max)           
			//find the id for the drug with max total cost
			{
				max = cost[i].total_cost;
				id = i;
			}
			else if (cost[i].total_cost == max)     
			//if drugs have the same total cost, use drug name with lexicographical order
			{
				cond = strcmp(cost[i].drug_name,cost[id].drug_name);
				if (cond < 0)
					id = i;
			}
		}
		fprintf(foutput,"%s,%d,%.2f\n",cost[id].drug_name,cost[id].num_prescriber,cost[id].total_cost);
		//printf("%s,%d,%.2f\n",cost[id].drug_name,cost[id].num_prescriber,cost[id].total_cost);
		cost[id].total_cost = 0.0; //set the total_cost to zero so that it won't be the max in the following steps
	}

	// close all files
	fclose(finput);
	fclose(foutput);

	//getchar();
	return 1;
}

void initstring(char str[],int n)
{
	int i;
	for (i=0;i<n;i++)
		str[i]='\0';
	return;
}

/*search in 'cost', if there is rec.drug_name, update the number of prescribers and total cost;
otherwise, add current 'rec' to 'cost' as a new drug*/
int search(struct record temp, int drugnum)
{
	// count the number of prescribers and calculate the total cost of each drug
	int j;
	for (j=0;j<drugnum+1;j++)
	{
		if (strcmp(temp.drug_name,cost[j].drug_name)==0) 
		// drug name exists: update total cost and number of prescribers
		{
			cost[j].num_prescriber++;
			cost[j].total_cost += temp.cost;
			break;                        //finish the search
		}
		else if (j==drugnum) 
		//drug name does not exist in array 'cost': create a new entry
		{
			strcpy(cost[drugnum].drug_name,temp.drug_name);
			cost[drugnum].num_prescriber++;
			cost[drugnum].total_cost += temp.cost;
			drugnum++;
			break;                         //finish the search
		}
	}
	return drugnum;
}
