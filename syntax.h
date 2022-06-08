/* Create and manipulate a hash table for storing words. The hash table has   *
 * HASH_SIZE buckets, each being the head of a singly-linked non-circular list*
 * with sentinel. The nodes within a list are not sorted.                     */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_SIZE 10	/*allazw to HASH_SIZE gt exw mexri 10 paragwges(apo ekfwnhsh)*/
#define MAXCHARS 60


/* This is the struct describing of a list node */
struct list {
  char *word;			 //to key einai voh8htikh metavlhth h opoia me voh8aei
  int key;			 //sthn kataxwrhsh twn string sth lista kai sthn anazhthsh tous
  struct list *nxt;
};

/*sunarthsh h opoia elenxei an to onoma tou arxeiou exei thn swsth morfopoihsh*/
int file_right_format(char *filename){
  
  
  if (strstr(filename,".")){
      return 1;
    }
  
  else{ 
    return 0;
  }
}

/* Hash table initialization. After this step all lists, each starting from a *
 * cell of the table are initialized                                          *
 * Dhmiourgw 10 nees listes kai desmeuw xwro sthn mnhmh gia autes*/

void init_hash_table(struct list **hash_table) { //dilpa * gt exw pikana apo listes
  int i;
  
  for (i=0; i<HASH_SIZE; i++) {
    /* Allocate the sentinel */
    hash_table[i] = (struct list *)malloc(sizeof(struct list));			//desmeush mnhmhs
    /* Make the next pointer of the sentinel NULL to designate an empty list */
    hash_table[i]->nxt = hash_table[i];
    hash_table[i]->key = 0;
  }
}


/* Prints the words in the nodes of a list pointed to by head, seperated by   *
 * white spaces                                                               */
void print_list(struct list *head){
 
  struct list *curr;
  
  curr = head->nxt;
  while (curr != head) {
    printf("%d.%s ", curr->key,curr->word);
    curr = curr->nxt;
  }
}


/* Adds a new node, containing word as its data, to the beginning of the list *
 * pointed to by head                                                         */                                                                               
void list_add (struct list *head, char *word) {
  struct list *new_node;
  
  /* Allocate memory for the new node */
  new_node = (struct list *)malloc(sizeof(struct list));
  /* Allocate exactly as much memory as needed * 
   * for the string (the data in the node)     */

  new_node->word = (char *)malloc((strlen(word)+1)*sizeof(char));
  strcpy(new_node->word, word);
  
   new_node->key = head->nxt->key +1;
 
   
   /* Insert the new node in the list */
  new_node->nxt = head->nxt;
  head->nxt = new_node;
  
}

/* Looks in the list pointed to by head for a node containing word as its     *
 * data. If found, the function returns a pointer to the previous node in the *
 * list. Otherwise it returns NULL.                                           */                                                                                
char *list_search (struct list *head, int key) {
  struct list *curr;
  for(curr=head->nxt; curr!=head && curr->key!=key; curr=curr->nxt);
  if(curr!=head){
    return curr->word;
  }else{
    return NULL;
  }
}