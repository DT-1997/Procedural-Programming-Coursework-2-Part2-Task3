#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
	char date[50];
	char time[6];
	char steps[4];
} FITNESS_DATA;

typedef struct {
	char date[50];
	char time[6];
	char steps[4];
} DATA;

// Function to tokenize a record
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);
                    }


int main() {
    FILE *fp = NULL;
    FILE *Fp = NULL;
    printf("Enter Filename: ");
    char file_name[50];
    scanf("%s",&file_name);
    char right_name[] = "FitnessData_2023.csv";
    int namestatment = strcmp(file_name,right_name);

    if (namestatment != 0)
    {
        printf("Error: Could not find or open the file.");
    }
    else
    {
        fp = fopen("FitnessData_2023.csv","r");
        Fp = fopen("FitnessData_2023.csv.tsv","w+");
    }

    char buff[21],Buff[100],current_date[21];
    int current_steps,max_steps = 0,last_max_steps = 100000;
    int counter1 = 0,counter2,i = 0,repeatstatment;
    FITNESS_DATA FITNESS_DATAS;
    DATA DATAS;
    while (fscanf(fp, "%s", buff) != EOF)
        {
            counter1++;
        }
    for ( i; i < counter1; i++)
    {
        fseek(fp, 0, SEEK_SET);
        counter2 = 0;
        while (fscanf(fp, "%s", buff) != EOF)
        {
            tokeniseRecord(buff,",",FITNESS_DATAS.date,FITNESS_DATAS.time,FITNESS_DATAS.steps);
            current_steps = atoi(FITNESS_DATAS.steps);
            repeatstatment = 0;
            counter2++;
            if (max_steps < current_steps && current_steps < last_max_steps)
            {
                max_steps = current_steps;
                strcat(FITNESS_DATAS.date,"\t");
                strcat(FITNESS_DATAS.date,FITNESS_DATAS.time);
                strcat(FITNESS_DATAS.date,"\t");
                strcat(FITNESS_DATAS.date,FITNESS_DATAS.steps);
                strcat(FITNESS_DATAS.date,"\n");
                strcpy(current_date,FITNESS_DATAS.date);
                strcpy(FITNESS_DATAS.date,"");
            }
            else if (current_steps == last_max_steps)
            {
                fseek(Fp, 0, SEEK_SET);
                while (fgets(Buff, 100, Fp) != NULL)
                {
                    tokeniseRecord(Buff,"\t",DATAS.date,DATAS.time,DATAS.steps);
                    if (strcmp(DATAS.time,FITNESS_DATAS.time) == 0)
                    {
                        repeatstatment = 1;
                    }
                }

                if (repeatstatment == 1)
                {
                    continue;
                }
                else if (repeatstatment == 0)
                {
                    max_steps = current_steps;
                    strcat(FITNESS_DATAS.date,"\t");
                    strcat(FITNESS_DATAS.date,FITNESS_DATAS.time);
                    strcat(FITNESS_DATAS.date,"\t");
                    strcat(FITNESS_DATAS.date,FITNESS_DATAS.steps);
                    strcat(FITNESS_DATAS.date,"\n");
                    strcpy(current_date,FITNESS_DATAS.date);
                    strcpy(FITNESS_DATAS.date,"");
                    break;
                }
            }
            if (counter2 == counter1)
            {
                last_max_steps -= 1;
            }
        }
        fputs(current_date,Fp);
        last_max_steps = max_steps;
        max_steps = 0;
    }
}
