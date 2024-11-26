#include <stdio.h>          //to use basic i/o functions
#include <stdlib.h>         //to use malloc(), free() and system() functions
#include <unistd.h>         //to use sleep() function

struct playlist{            //Structure to create linked-list of songs
    char song_name[50];     //contains song name
    int sec;                //contains the duration
    struct playlist *ptr;   //contains the location of next node
};
char songs[][50]={"Kya_Hua_Tera_Vada.mp3","Yeh_Raaten_Yeh_Mausam.mp3","Lag_Ja_Gale_Se_Phir.mp3","Main_Pal_Do_Pal_Ka_Shair_Hoon.mp3","Pal_Pal_Dil_Ke_Paas.mp3"}; // stores the name of available songs
int time_stamp[]={258,201,257,201,326}; // stores the duration of available songs
char main_menu_options[][50]={"Create Songs playlist","Delete the current playlist","Add a song to the playlist","Delete a song from the playlist","Sort playlist","Show playlist","Play playlist","Exit"}; // stores the data of main menu
int choice(){                                                       // Choice function returns the value according to the song selected by the user
    printf("Enter your choice according to the given menu:\n");
    for (int i = 0; i < 5; i++)                                     // loop to print the available songs option
        printf("%d. %s\n",i+1,songs[i]);                            
    int op;
    printf("Enter your choice:");
    scanf("%d",&op);
    printf("\n\n");
    return op;
}
int length_of_string(char *s){                                      // Recursive funcion to print length of string
    if (!(*s)) return 0;
    return 1+length_of_string(s+1);
}
int string_comparison(char *s,char *p){                             //A function to compare two strings [helps in aplhabetical sorting of the playlist]
    while (*s==*p){
        s++;p++;
        if (*s=='\0')
            return 0;
    }
    return *p-*s;
}
void copying_string(char *s,char *p){                               //this function is being used to copy first string into the second string [helps in swaping of string]
    while(*p++=*s++);
}
void swap(int *a,int *b){                                           //swap function two swap two value using pointers
    *a=(*a)+(*b);
    *b=(*a)-(*b);
    *a=(*a)-(*b);
}
void swap_string(char *s,char *p){                                  //this function helps in swapping two stings
    char *t=malloc(40);
    copying_string(s,t);
    copying_string(p,s);
    copying_string(t,p);
    free(t);
}
void play(struct playlist *head){                                   //function to play the songs in playlist
    system(head->song_name);                                       
    sleep((head->sec)+5);
    if(head->ptr) play(head->ptr);
}
void sort_time_asc(struct playlist *head){                          //helps in sorting the playlist according to shortest duration of song
    struct playlist *current=head;
    int *min=&(current->sec);
    char *s=&(current->song_name);
    while (current->ptr){
        current=current->ptr;
        if(current->sec<(*min)){
            min=&(current->sec);
            s=&(current->song_name);
        }
    }
    if (&(head->sec)!=min){
        swap(&(head->sec),min);
        swap_string(&(head->song_name),s);
    }
    if(head->ptr) sort_time_asc(head->ptr);
}
void sort_time_dsc(struct playlist *head){                          //helps in sorting the playlist according to the longest duration of song
    struct playlist *current=head;
    int *max=&(current->sec);
    char *s=&(current->song_name);
    while (current->ptr){
        current=current->ptr;
        if(current->sec>(*max)){
            max=&(current->sec);
            s=&(current->song_name);
        }
    }
    if (&(head->sec)!=max){
        swap(&(head->sec),max);
        swap_string(&(head->song_name),s);
    }
    if(head->ptr) sort_time_dsc(head->ptr);
}
void sort_alphabetically(struct playlist *head){                    //helps in alphabetical sorting of playlist
    struct playlist *current=head;
    char *s=&(current->song_name);
    int *t=&(current->sec);
    while (current->ptr){
        current=current->ptr;
        if(string_comparison(s,&(current->song_name))<0){
            t=&(current->sec);
            s=&(current->song_name);
        }
    }
    if (string_comparison(s,&(head->song_name))!=0){
        swap(&(head->sec),t);
        swap_string(&(head->song_name),s);
    }
    if(head->ptr) sort_alphabetically(head->ptr);
}
void sort_alphabetically_reverse(struct playlist *head){            //helps in reverse alphabetical sorting of playlist
    struct playlist *current=head;
    char *s=&(current->song_name);
    int *t=&(current->sec);
    while (current->ptr){
        current=current->ptr;
        if(string_comparison(s,&(current->song_name))>0){
            t=&(current->sec);
            s=&(current->song_name);
        }
    }
    if (string_comparison(s,&(head->song_name))!=0){
        swap(&(head->sec),t);
        swap_string(&(head->song_name),s);
    }
    if(head->ptr) sort_alphabetically_reverse(head->ptr);
}
void sort(struct playlist *head){                                   //function to ask user which kind of sorting he/she want to perform
    int option;
    printf("Enter the option to sort\n");
    printf("1.Sort by duration in Ascending order");printf("\n2.Sort by duration in Descending order");printf("\n3.Sort by Title\n4.Sort by Title in Reverse");
    scanf("%d",&option);
    switch (option)
    {
    case 1:
        sort_time_asc(head);break;
    case 2:
        sort_time_dsc(head);break;
    case 3:
        sort_alphabetically(head);break;
    case 4:
        sort_alphabetically_reverse(head);break;
    default:
        printf("Please enter valid choice\n");
        break;
    }
}
void add(struct playlist *head){                                    //function to add song at the of the playlist
    if(!(head->ptr)){
        int op=choice()-1;
        head->ptr=malloc(sizeof(struct playlist));
        head=head->ptr;
        copying_string(songs[op],&(head->song_name));
        head->sec=time_stamp[op];
        head->ptr=NULL;
    }
    else add(head->ptr);
}
void delete(struct playlist *head){                                 //function to delete a song from the playlist
    int option;
    struct playlist *current=head->ptr;
    printf("Do you wanna delete %s from your playlist? (1:yes/0:no): ",current->song_name);
    scanf("%d",&option);
    if (option)
    {
        head->ptr=current->ptr;
        free(current);
    }
    else if(current->ptr) delete(head->ptr);
    else printf("No more songs left in the playlist");
}
struct playlist *creating_node(struct playlist *p){                 //function to create node of the playlist
    p=malloc(sizeof(struct playlist));
    int op=choice();
    copying_string(&(songs[op-1]),&(p->song_name));
    p->sec=time_stamp[op-1];
    p->ptr=NULL;
    int op2;
    printf("Do you want to add more songs to your playlist (1:yes/0:no):");
    scanf("%d",&op2);
    if(op2==1) p->ptr=creating_node(p->ptr);
    return p;
}
void printing_the_playlist(struct playlist *p){                     //function to print the playlist
    printf("%50s\t%d:%d\n", p->song_name, (p->sec)/60,(p->sec)%60);
    if(p->ptr) printing_the_playlist(p->ptr);
}
void deallocating_playlist(struct playlist *p){                     //function to deallocate the memory used to store the playlist
    if(p->ptr) deallocating_playlist(p->ptr);
    free(p);                                                        // free function to deallocate the function {Exiting the program without deallocating the node will result in memory leakage}
}
int main(){                                                         
    printf("==Welcome==\n");
    int option;
    struct playlist *head=NULL;
    again:                                                          //goto loop to use the main menu again and again
    printf("Enter your option from the following menu:\n");
    for (int i = 0; i < 8; i++) printf("%d. %s\n",i+1,main_menu_options[i]);
    scanf("%d",&option);
    switch (option-1)
    {
    case 0:
        head=creating_node(head);break;
    case 1:
        deallocating_playlist(head);break;
    case 2:
        add(head);break;
    case 3:
        printf("Do you wanna delete %s from your playlist?(1:yes/0:no): ",head->song_name);scanf("%d",&option);
        if (option){
            struct playlist *current=head;
            head=head->ptr;
            free(current);
        }
        else delete(head);
        break;
    case 4:
        sort(head);break;
    case 5:
        printing_the_playlist(head);break;
    case 6:
        play(head);
    case 7:
        deallocating_playlist(head);
        return 0;
    default:
        printf("Please Enter valid option");
        goto again;
    }
    goto again;
    return 0;
}