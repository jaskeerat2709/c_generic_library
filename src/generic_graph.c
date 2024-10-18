#include<stdio.h>
#include<stdlib.h>
#include<tm_avl_tree.h>
#include<string.h>

typedef struct _city_
{
int code;
char name[52];
}City;

typedef struct __city_header
{
int lastGeneratedCode;
int recordCount;
}CityHeader;


void drawline(char m,int index)
{
int i;
for(i=0;i<=index;i++)
{
printf("%c",m);
}
printf("\n");
}

//GLOBAL DATA STRUCTURES

AVLTree *cities;
AVLTree *citiesByName;
CityHeader cityHeader;

int cityCodeComparator(void *left,void *right)
{
City *leftCity=(City *)left;
City *rightCity=(City *)right;
return (leftCity->code-rightCity->code);
}

int cityNameComparator(void *left,void *right)
{
City *leftCity=(City *)left;
City *rightCity=(City *)right;
return stricmp(leftCity->name,rightCity->name);
}

void populateDataStructures(int *success)
{
FILE *cityFile;
City *city;
City c;
int succ;
if(success) *success=false;
printf("Please Wait, Loading Data......................\n");
cities=createAVLTree(&succ,cityCodeComparator);
if(!succ)
{
printf("Unable to load data,low memory issue");
return;
}
citiesByName=createAVLTree(&succ,cityNameComparator);
if(!succ)
{
printf("Unable to load data,low memory issue");
destroyAVLTree(cities);
return;
}
cityFile=fopen("city.new","rb");
if(cityFile!=NULL)
{
fread(&cityHeader,sizeof(CityHeader),1,cityFile);
if(!(feof(cityFile)))
{
while(1)
{
fread(&c,sizeof(City),1,cityFile);
if(feof(cityFile)) break;
city=(City *)malloc(sizeof(City));
city->code=c.code;
strcpy(city->name,c.name);
insertIntoAVLTree(citiesByName,(void *)city,&succ);
insertIntoAVLTree(cities,(void *)city,&succ);
}
}
fclose(cityFile);
}
//Loading Data From File Ends Here
if(success) *success=true;
if(getSizeOfAVLTree(cities)==0)
{
cityHeader.lastGeneratedCode=0;
cityHeader.recordCount=0;
}
}


void releaseDataStructures()
{
destroyAVLTree(cities);
destroyAVLTree(citiesByName);
}


void addCity()
{
City c;
City *city;
FILE *File;
int succ;
char m;
char name[52];
printf("City Add Module.........\n");
printf("Enter City to add : ");
fgets(name,52,stdin);
fflush(stdin);
name[strlen(name)-1]='\0';
strcpy(c.name,name);
printf("Here\n");
city=(City *)getFromAVLTree(citiesByName,(void *)&c,&succ);
printf("Now Here\n");
if(succ)
{
printf("City %s Already Exists\n",name);
return;
}
printf("Save (Y/N) : ");
m=getchar();
fflush(stdin);
if(m!='Y' && m!='y') 
{
printf("City %s Not Saved\n",name);
return;
}
printf("Here\n");
File=fopen("city.new","rb+");
printf("Now Here\n");
if(File==NULL) 
{
File=fopen("city.new","wb+");
printf("Here\n");
fwrite(&cityHeader,sizeof(CityHeader),1,File);
}
else fseek(File,0,SEEK_END);
c.code=cityHeader.lastGeneratedCode+1;
printf("Here\n");
fwrite(&c,sizeof(City),1,File);
cityHeader.lastGeneratedCode++;
cityHeader.recordCount++;
fseek(File,0,SEEK_SET);
printf("Here\n");
fwrite(&cityHeader,sizeof(CityHeader),1,File);
fclose(File);
printf("Now Here\n");
city=(City *)malloc(sizeof(City));
city->code=c.code;
strcpy(city->name,c.name);
printf("Here\n");
insertIntoAVLTree(citiesByName,(void *)city,&succ);
printf("Here\n");
insertIntoAVLTree(cities,(void *)city,&succ);
printf("Here\n");
printf("%s Added, Press Enter to continue..................",name);
getchar();
fflush(stdin);
}



void searchCity()
{
City *city;
char name[52];
City c;
int succ;
printf("City(Search Module)\n");
printf("Enter name of City to Search : ");
fgets(name,52,stdin);
fflush(stdin);
name[strlen(name)-1]='\0';
strcpy(c.name,name);
city=(City *)getFromAVLTree(citiesByName,(void *)&c,&succ);
if(!succ)
{
printf("%s does not exists\n",name);
printf("Press enter to continue...............");
getchar();
fflush(stdin);
}
else
{
printf("%s Exists\n",city->name);
printf("Press enter to continue...............");
getchar();
fflush(stdin);
}
}
 
void displayListOfCities()
{
int sno,displayHeader;
AVLTreeInOrderIterator avlTreeInOrderIterator;
City *city;
int succ,sz,pageSize;
sz=getSizeOfAVLTree(cities);
if(sz==0)
{
printf("Cities (Display Module)\n");
printf("No City Exists, Press Enter to continue..............");
getchar();
fflush(stdin);
return;
}
displayHeader=1;
pageSize=5;
sno=0;
avlTreeInOrderIterator=getAVLTreeInOrderIterator(citiesByName,&succ);
while(hasNextInOrderElementInAVLTree(&avlTreeInOrderIterator))
{
if(displayHeader)
{
printf("Cities (Display Module)\n");
drawline('-',140);
printf("   S.No   City\n");
drawline('-',140);
displayHeader=0;
}
sno++;
city=(City *)getNextInOrderElementFromAVLTree(&avlTreeInOrderIterator,&succ);
printf("%10d  %-50s\n",sno,city->name);
if(sno%pageSize==0 || sno==sz)
{
drawline('-',70);
displayHeader=1;
printf("Press enter to continue..................");
getchar();
fflush(stdin);
}
}
}




int mainMenu()
{
int ch;
while(1)
{
printf("1.City Master\n");
printf("2.Get Route\n");
printf("3.Exit\n");
printf("Enter your Choice : ");
scanf("%d",&ch);
fflush(stdin);
if(ch<1 || ch>3)
{
printf("Invalid Input\n");
}
else return ch;
}
}

void cityMenu()
{
int ch;
while(1)
{
printf("City Master\n");
printf("1.Add\n");
printf("2.Edit\n");
printf("3.Delete\n");
printf("4.Search\n");
printf("5.List\n");
printf("6.Add adjacent vertex\n");
printf("7.Exit\n");
printf("Enter your Choice : ");
scanf("%d",&ch);
fflush(stdin);
if(ch<1 || ch>7)
{
printf("Invalid Input\n");
continue;
}
if(ch==1) addCity();
if(ch==4) searchCity();
if(ch==5) displayListOfCities();
if(ch==7) return;
}
}


int main()
{
int ch,succ;
populateDataStructures(&succ);
if(!succ) return 0;
while(1)
{
ch=mainMenu();
if(ch==1) cityMenu();
if(ch==2) 
if(ch==3) break;
return 0;
}
}