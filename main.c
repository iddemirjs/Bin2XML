#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct record {
    char name[64];//utf16
    char surname[32];//utf8
    char gender;
    char email[32];
    char phone_number[16];
    char address[32];
    char level_of_education[8];
    unsigned int income_level;
    unsigned int expenditure;
    char currency_unit[16];
    char currentMood[32];
    float height;
    unsigned int weight;
};
typedef struct record Record;
typedef struct record *RecordPtr;
struct tags {
    char name[64];//utf16
    char surname[32];//utf8
    char gender[1];
    char email[32];
    char phone_number[16];
    char address[32];
    char level_of_education[8];
    char income_level[4];
    char expenditure[4];
    char currency_unit[16];
    char currentMood[32];
    char height[4];
    char weight[4];
};
typedef struct tags Tags;
typedef struct tags *TagsPtr;

void read_records_from_database(char *, RecordPtr,TagsPtr);

void print_array(RecordPtr);

unsigned LitToBigEndian(unsigned int);

unsigned BigToLitEndian(unsigned int);

void save_records(char *, RecordPtr, Tags);

FILE *fileReader;
int recordSize;

int main(int argc, char *argv[]) {


    char datFileName[15] = "records.dat";
    char exportFileName[15] = "records.xml";

    printf("\n\n\n%s\n",argv[0]);
    printf("%s\n",argv[1]);
    printf("%s\n\n\n",argv[2]);
    if (strcmp(argv[1],"")) {
        strcpy(datFileName,argv[1]);
        strcpy(exportFileName,argv[2]);
    }

    Record records[65];
    Tags tagsAll;
    read_records_from_database(datFileName, records, &tagsAll);


    print_array(records);

    save_records(exportFileName, records, tagsAll);

    return 0;
}

// Do read from dat
void read_records_from_database(char *argFileName, RecordPtr recordPtr,TagsPtr tagsAllPtr) {

    if ((fileReader = fopen(argFileName, "rb+")) == NULL) {
        //Error
        printf("File is not opened or founded ...");
        exit(0);
    } else {
        rewind(fileReader);
        // I read all line in dat file.
        Record tempTags;
        fread(tagsAllPtr, sizeof(Record), 1, fileReader);
        fclose(fileReader);
     }

    if ((fileReader = fopen(argFileName, "rb+")) == NULL) {
        //Error
        printf("File is not opened or founded ...");
        exit(0);
    } else {
        rewind(fileReader);
        int i = 0;
        // I read all line in dat file.
        while (!feof(fileReader)) {

            // Firstly, records_from will be read from dat file. Then transfer to struct of record
            if (i == 0) {
                i++;
                Record tempRecord;
                fread(&tempRecord, sizeof(Record), 1, fileReader);
            } else {
                Record tempRecord;
                fread(&tempRecord, sizeof(Record), 1, fileReader);
                // I define current user index for section.
                strcpy(recordPtr->name, tempRecord.name);
                strcpy(recordPtr->surname, tempRecord.surname);
                recordPtr->gender = tempRecord.gender;
                strcpy(recordPtr->email, tempRecord.email);
                strcpy(recordPtr->phone_number, tempRecord.phone_number);
                strcpy(recordPtr->address, tempRecord.address);
                strcpy(recordPtr->level_of_education, tempRecord.level_of_education);
                recordPtr->income_level = tempRecord.income_level;
                recordPtr->expenditure = tempRecord.expenditure;
                strcpy(recordPtr->currency_unit, tempRecord.currency_unit);
                strcpy(recordPtr->currentMood, tempRecord.currentMood);
                recordPtr->height = tempRecord.height;
                recordPtr->weight = tempRecord.weight;
                // I will add to my tree.
                    recordPtr++;
                i++;
            }
        }
        recordSize = i;
        fclose(fileReader);
    }
}

void save_records(char *saveName, RecordPtr recordPtr,Tags tagsAll) {
    FILE *saveFilePointer;
    char exportFileNameWithExtension[15];
    strcpy(exportFileNameWithExtension, saveName);
    if ((saveFilePointer = fopen(exportFileNameWithExtension, "w")) == NULL) {
        puts("File could not be opened for writing....");
        return;
    }
    fprintf(saveFilePointer, "<records>\n");
    int columnId = 1;
    while (columnId < recordSize) {
        if (!strcmp(recordPtr->name, "")){
            columnId++;
            continue;
        }
        fprintf(saveFilePointer, "\t<row id=\"%d\">\n", columnId);
        fprintf(saveFilePointer, "\t\t<%s>%s</%s>\n",
                strcmp(tagsAll.name,"name")?"name":tagsAll.name,
                recordPtr->name,
                strcmp(tagsAll.name,"name")?"name":tagsAll.name);
        fprintf(saveFilePointer, "\t\t<%s>%s</%s>\n",
                strcmp(tagsAll.surname,"surname")?"surname":tagsAll.surname,
                recordPtr->surname,
                strcmp(tagsAll.surname,"surname")?"surname":tagsAll.surname);
        fprintf(saveFilePointer, "\t\t<%s>%c</%s>\n",
                strcmp(tagsAll.gender,"gender")?"gender":tagsAll.gender,
                recordPtr->gender,
                strcmp(tagsAll.gender,"gender")?"gender":tagsAll.gender);
        fprintf(saveFilePointer, "\t\t<%s>%s</%s>\n",
                strcmp(tagsAll.name,"email")?"email":tagsAll.email,
                recordPtr->email,
                (strcmp(tagsAll.email,"email")?"email":tagsAll.email));
        fprintf(saveFilePointer, "\t\t<%s>%s</%s>\n",
                strcmp(tagsAll.phone_number,"phone_number")?tagsAll.phone_number:"phone_number",
                recordPtr->phone_number,
                (strcmp(tagsAll.phone_number,"phone_number")?tagsAll.phone_number:"phone_number"));
        fprintf(saveFilePointer, "\t\t<%s>%s</%s>\n",
                strcmp(tagsAll.address,"address")?tagsAll.address:"address",
                recordPtr->address,
                (strcmp(tagsAll.address,"address")?tagsAll.address:"address"));
        fprintf(saveFilePointer, "\t\t<%s>%s</%s>\n",
                strcmp(tagsAll.level_of_education,"level_of_education")?tagsAll.level_of_education:"level_of_education",
                recordPtr->level_of_education,
                (strcmp(tagsAll.level_of_education,"level_of_education")?tagsAll.level_of_education:"level_of_education"));
        fprintf(saveFilePointer, "\t\t<%s bigEnd=\"%u\">%u</%s>\n",
                strcmp(tagsAll.income_level,"income_level")?"income_level":tagsAll.income_level,
                LitToBigEndian(recordPtr->income_level),
                recordPtr->income_level,
                strcmp(tagsAll.income_level,"income_level")?"income_level":tagsAll.income_level);
        fprintf(saveFilePointer, "\t\t<%s bigEnd=\"%u\">%u</%s>\n",
                strcmp(tagsAll.expenditure,"expenditure")?"expenditure":tagsAll.expenditure,
                recordPtr->expenditure,
                BigToLitEndian(recordPtr->expenditure),
                strcmp(tagsAll.expenditure,"expenditure")?"expenditure":tagsAll.expenditure);
        fprintf(saveFilePointer, "\t\t<%s>%s</%s>\n",
                strcmp(tagsAll.currency_unit,"currency_unit")?"currency_unit":tagsAll.currency_unit,
                recordPtr->currency_unit,
                strcmp(tagsAll.currency_unit,"currency_unit")?"currency_unit":tagsAll.currency_unit);
        fprintf(saveFilePointer, "\t\t<%s>%s</%s>\n",
                strcmp(tagsAll.currentMood,"currentMood")?"currentMood":tagsAll.currentMood,
                recordPtr->currentMood,
                strcmp(tagsAll.currentMood,"currentMood")?"currentMood":tagsAll.currentMood);
        fprintf(saveFilePointer, "\t\t<%s>%.2f</%s>\n",
                strcmp(tagsAll.height,"height")?"height":tagsAll.height,
                recordPtr->height,
                strcmp(tagsAll.height,"height")?"height":tagsAll.height);
        fprintf(saveFilePointer, "\t\t<%s>%d</%s>\n",
                strcmp(tagsAll.weight,"weight")?"weight":tagsAll.weight,
                recordPtr->weight,
                strcmp(tagsAll.weight,"weight")?"weight":tagsAll.weight);
        fprintf(saveFilePointer, "\t</row>\n");
        recordPtr++;
        columnId++;
    }
    fprintf(saveFilePointer, "</records>");
    fclose(saveFilePointer);
    printf("\nFile name %s is successfully created.\n", saveName);
}

void print_array(RecordPtr recordPtr) {
    for (int i = 0; i < 5; ++i) {
        printf("Name : %s \n", recordPtr->name);
        printf("Surname : %s \n", recordPtr->surname);
        printf("Gender : %c \n", recordPtr->gender);
        printf("Email : %s \n", recordPtr->email);
        printf("Phone Number : %s \n", recordPtr->phone_number);
        printf("Address : %s \n", recordPtr->address);
        printf("Level of Education : %s \n", recordPtr->level_of_education);
        printf("Income Level : %d \n", recordPtr->income_level);
        printf("Expenditure : %d \n", BigToLitEndian(recordPtr->expenditure));
        printf("Currency Unit : %s \n", recordPtr->currency_unit);
        printf("Current Mood : %s \n", recordPtr->currentMood);
        printf("Height : %f \n", recordPtr->height);
        printf("Weight : %d \n\n", recordPtr->weight);
        recordPtr++;
    }
}

unsigned int LitToBigEndian(unsigned int x) {
    return (((x >> 24) & 0x000000ff) | ((x >> 8) & 0x0000ff00) | ((x << 8) & 0x00ff0000) | ((x << 24) & 0xff000000));
}

unsigned BigToLitEndian(unsigned val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}
