/**
 *@author:Grigorios Fekas, AEM:1045, fekas@uth.gr*
 
 *To programma apo8hkeuei thn grammatikh kai 
 *paragei to tuxaio keimeno se ena arxeio out.txt.
 *Dusthxws den katafera na ulopoihsw to arxeio eksodou
 *me thn apetoumenh morfh(ex. x1.out.txt)
 *Epeishs xrhshmopoiw kommatia kwdika sto syntax.h
 *apo to hash_table.c pou uparxei stnn 
 *selida tou ma8hmatos**/


/*************************
*******INCLUDES*********** 
*************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "syntax.h"



/******UNIVERSAL**********
*******VARIABLES********** 
*************************/

int i=-1;							//metavlhth gia thn 8esh twn listwn
FILE *filenm;							//to stream gia arxeio eksodou
int new_linecnt=0;						//counter giati max mege8os grammhs tou arxeiou

/*************************
*******STRUCTS************ 
*************************/

struct syntax{
  char *nonfinal;						//ta mh termatika mou(ousiastika oi "<epikefalides>" ka8e kanona)
  int j;							// o ari8mos ka8e komvou
  struct list *hash_table[HASH_SIZE];				//mia lista tupou list mege8ous HASH_ZISE=10
};
struct syntax *data=NULL;					//ston data 8a apo8hkeuw ola ta stoixeia


/*************************
*******FUNCTIONS********** 
*************************/


/********************************************************
 *H print_words den kaleitai apo thn main.
 *Deixnei ton tropo me ton poio exoun apo8hkeutei 
 *termatika kai ta mh termatika stoixeia ths grammatikhs.
 ********************************************************/
void print_words(){
  char *str;
  int a,b,key;
  for(a=0;a<=i;a++){
    printf("\n%s->\t",data[a].nonfinal);
    for(b=0;b<data[a].j;b++){
      key=1;
      while( (str = list_search(data[a].hash_table[b],key)) != NULL ){
	str = list_search(data[a].hash_table[b],key);
	printf("%d.\"%s\"\t",b,str);
	key++;
      }while(str!=NULL);
    }
  }
  printf("\n");
}


/***********************************
 * sunarthsh h opoia apodesmeuei 
 * tis kataxwrimenes 8eseis mnhmhs.
 * *********************************/
void free_memory(){
  int a,b;
  for(a=0;a<=i;a++){
    free(data[a].nonfinal);
    for(b=0;b<=data[a].j;b++){
      free(data[a].hash_table[b]);
    }
  }
}

/****************************************
 *H search_nonfinal anazhetei ena
 * string sthn lista me ta 
 * mh termatika kai an to vrei epistrefei
 *th 8esh tou mesa sthn lista.
 *Diaforetika epistrefei -1.
 ****************************************/
int search_nonfinal(char *str){
  int a;
  for(a=0;a<=i;a++){
    if(strcmp(data[a].nonfinal,str)==0){
      return a;
    }
  }
  return -1;
}



/******************************************************************/
 /*Anadrmomikh sunarthsh h opoia dexetai ena 
 *mh termiko string. Arxika to anazhetei sto 
 *pinaka twn mh termatikwn kai epistrefei thn 8esh tou.
 *Exontas thn 8esh tou (a) ston data, kanw rand
 *thn ton data[a].j , o opoios einai h tautothta ths kai ka8e
 *listas tou data[a].hash_table.Apo kei kai ustera "trexw thn lista"
 *me thn list_search kai pairnw to ekastote string apo thn lista 
 *me mia voh8htikh metavlhth str. An to str exei morfh mh-termatikou
 *tote kai kalw thn idia thn sunarthsh me orisma:str.
 *Diaforetika tupwnw sto arxeio eksodou.
*******************************************************************/
void print_text(char *word){
  
  int a,b,key;
  char *str;
  
  
  a = search_nonfinal(word);							//kalw thn search_nonfinal
  b = rand()%(data[a].j);							//kai rand sto data[a].j
  key=1;									//arxhkopoiw to key ths lista 
  
  
  while( (str = list_search(data[a].hash_table[b],key)) != NULL ){		//"trexw" thn lista
    if(str[0]=='<'){								//elenxw an einai mh termatiko				
      print_text(str);								//an einai kanw anadromh
    }else{
      fprintf(filenm,"%s ",str);						//diaforerika tupwnw sto arxeio eksodou
      new_linecnt=new_linecnt +strlen(str)+1;					//pros8etw to mhkos tou string ston line counter
	
      if(new_linecnt>=MAXCHARS){						//otan o line counter kseperasei tous 60 xarakthres 
	 new_linecnt=0;								//mhdenizetai 
	 fprintf(filenm," %s","\n");						//kai tuponetai nea grammh  sto arxeio eksodou
	 
      }
      
    }
    key++;
  }
  
} 


/******************************************************
 *H save_grammar einai o kormos tou programmatos
 *einai h synarthsh anoigei to arxeio ths grammatikhs
 *to opoio pairnei san orisma apo thn main,
 *kai apo8hkeuei ta mh-termatika(ston data[i].nonfinal)
 *kai tis ekastote paragwges twn mh termatikwn ston 
 *data[i].hash_table[]
 ******************************************************/
int save_grammar(char *filename){
  
  FILE *f;									//dhlwsh metavlhtwn
  char str[50];
  srand(time(NULL));								//kanw srand
  
  
  if(file_right_format(filename)){						//Elenxw an to filename einai sthn katallhlh morfh
  f=fopen(filename,"r");		     					//an nai, anoigw to arxeio
    while(fscanf(f,"%s",str)!=EOF){						//kanw fscanf mexri to telous tou arxeiou
      if(!strcmp(str,"{")){							// mexri na vrw kainourgia paragwgh ("{")
	  i++;									
	  fscanf(f,"%s",str);							
	  
	  data = (struct syntax *)realloc(data,sizeof(struct syntax)*(i+1));	//dhmiourgw 8esh sth lista
	  data[i].j=0;
	  data[i].nonfinal = strdup(str);					  //kai kataxwrw to mh termatiko sthn 8esh i
	  
	  init_hash_table(data[i].hash_table);					//arxikopoiw to hash_table(dimiourgw 10 nees listes gia to data[i])
	  
	  while(fscanf(f,"%s",str)!=EOF){
	    if (!strcmp(str,";")){						//an sto string pou diavazw einai diaforo tou ";"
		fscanf(f,"%s",str);						//
		data[i].j++;							//data[i].j  einai "tautothta" ths ka8e listas tou data[i]
	    }
	    if(strcmp(str,"}")==0){						//... otan  }
		break;
	    }
	   
	    list_add(data[i].hash_table[data[i].j], str);			//pros8etw to stirng sthn lista san neo komvo tou data[i].hash_table
	  } 
      }
    }
  }

  else return -1;
  return 0;
}


/*************************
*********MAIN************* 
*************************/


int main (int argc, char* argv[]){
 
  int flag=save_grammar(argv[1]);					//flag gia tnn periptwsh mou to argv[1] den einai ths morfhs x.y
        
   if(flag!=-1){				
    //print_words();							//mporeite na kalesete tnn print_words gia na deite ta periexomena twn listwn
    filenm=fopen("out.txt","w");					//anoigw to arxeio eksodou
    print_text("<start>");						//kalw thn print_text
  }
    else {
    printf("File Error\n");			
  }
  fflush(filenm);							//monimopoiw ths allages sto arxeio
  fclose(filenm);							//kai to kleinw
  free_memory();							//kalw tnn free_memory
  return 0;
}
