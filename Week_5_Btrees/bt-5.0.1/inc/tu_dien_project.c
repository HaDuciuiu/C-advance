#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<conio.h>
#include <termio.h>
#include <time.h>
#include "btree.h"
#include "bt.h"
#include "bc.h"
#define SIZE_WORD 150
#define SIZE_MEAN 1500
#define SIZE_MEAN1 100000

typedef struct
{
  char *s;
} String;

void docfile(BTA* root,BTA* btSoundex,FILE *f);
void ghifile(BTA* root,FILE* f);
void hienthi(BTA* root);
void insert(BTA* root,BTA* btSoundex);
void update(BTA* root);
void delete(BTA* root,BTA* btSoundex);
void search(BTA* root,BTA* btSoundex);
int search_tab(BTA *root,char *word,String *output);
void search_soundex(BTA* root,BTA* btSoundex,String string[],int n);
void search_full(BTA* root,BTA* btSoundex);
int menu();
char getch( void );


int SoundEx(char *SoundEx,char *WordString,int   LengthOption,int   CensusOption);
void soundex_insert(char *word, BTA *btSoundex);
void soundex_delete(char *word, BTA* btSoundex);
int soundex_search(char *word, BTA* btSoundex,String string[]);
void soundex_hienthi(BTA* btSoundex);



main(){
	FILE *f;
	BTA *root,*btSoundex;
	char d,e;
	char word[SIZE_WORD];
	char mean[SIZE_MEAN];
    char soundex[10];
	//char filename[]="sample.dic";
    char filename[30];
    time_t start,end;
	String *string;
	int c,n,i,rsize,j,k;

        root=btopn("dictionary.dat",0,0);
        btSoundex=btopn("Soundex.dat",0,0);
        if(root==NULL || btSoundex==NULL){
           
            printf("nhap file:");
            fgets(filename,30,stdin);
            filename[strlen(filename)-1]='\0';
            f=fopen(filename, "r");
            if(f==NULL){
                printf("Khong mo duoc file %s\n",filename);
                exit(1);
            } 
            btinit();
            root=btcrt("dictionary.dat",0,0);
            btSoundex=btcrt("Soundex.dat",0,0);
            start=time(NULL);
            docfile(root,btSoundex,f);
            end=time(NULL);
           // printf("thoi gian chay cau lenh them la:%f giay.\n",difftime(end,start));
            
        }
		

		do{
			c=menu();
			switch(c){
				case 1:
                    search_full(root,btSoundex);
                break;
				case 2:insert(root,btSoundex);
				break;
				case 3:delete(root,btSoundex);
				break;
				case 4:update(root);

				break;
                
				
                case 5:
                        printf("Ban co muon thoat khong(y/n):");scanf("%s",&d);
                         if(d=='y') 
                         	{
                         		c=10;
                         		printf("Cam on ban da su dung chuong trinh!\n");
                         		printf("Have a nice day!\n");
                         	}
                break;
                /*
                case 7:soundex_hienthi(btSoundex);
                break;
                case 8: printf("Nhap tu:");
                       fgets(word,SIZE_WORD,stdin);
                       word[strlen(word)-1] = '\0';
                        n=SoundEx(soundex,word,4,4);
                        soundex[n]='\0';
                       printf("ma soundex la:%s\n",soundex);
                break;
                case 9:hienthi(root);
                break;
                */

			}

		}while(c!=10);

    
    //f=fopen("sample1.dic", "w");
   // ghifile(root,f);
    
	btcls(root);
    btcls(btSoundex);
}

char getch( void ){
char ch;
int fd = fileno(stdin);
struct termio old_tty, new_tty;
ioctl(fd, TCGETA, &old_tty);
new_tty = old_tty;
new_tty.c_lflag &= ~(ICANON | ECHO | ISIG);
ioctl(fd, TCSETA, &new_tty);
fread(&ch, 1, sizeof(ch), stdin);
ioctl(fd, TCSETA, &old_tty);

return ch;
}


int menu(){
   int c,i;
   char d,k;
   char s[300];
   printf("\n******************TU DIEN ANH VIET******************\n");
   printf("                   BANG CHUC NANG                    \n");
   printf("1.Tim kiem.\n2.Them tu.\n3.Xoa tu.\n4.Cap nhat.\n5.Thoat.\n");
   printf("****************************************************\n");
   do{
     printf("Moi ban chon:");scanf("%s",s);
     k=0;
     if(strlen(s)==1){
        if(s[0]>='1' && s[0]<='9') c=atoi(s);
        else c=0;
     }
     else c=0;
     //printf("c=%d\n",c );
     while(getchar()!='\n');
   }while(c<1||c>5);
   return c;
}
///*
void docfile(BTA *root, BTA *btSoundex, FILE *f){
    // char *line, *word, *mean;

    // line = (char *)malloc(sizeof(char) * SIZE_MEAN);
    // word = (char *)malloc(sizeof(char) * SIZE_WORD);
    // mean = (char *)malloc(sizeof(char) * SIZE_MEAN);
    char line[SIZE_MEAN];
    // ,line1[SIZE_MEAN];
    char word[SIZE_WORD];
    char mean[SIZE_MEAN];
   // fgets(line, SIZE_MEAN, f); // doc dong dau
    //printf("%s\n", line);
    //getch();
    int word_index = 0, mean_index = 0;
    int i = 0;
    while (1){
        fgets(line, SIZE_MEAN, f);
        //printf("%s", line);
        line[strlen(line) - 1] = '\0';
        //if (strcmp(line, "]") == 0) break;
        if(line[0]=='/' && line[1]=='/') continue;
        if(line[0]=='[') continue;
        if(line[0]==']') break;
        if(feof(f)==1) break;
        char *ptr;
        ptr = strtok(line, "{}:,");
       //printf("%s\n", ptr);
        strcpy(word, ptr);
        ptr = strtok(NULL, "{}:,");
        //printf("%s\n", ptr);

        strcpy(mean, ptr);
        i++;
        printf("%d\n", i);
        int result = btins(root,word,mean,SIZE_MEAN);
        if (result == 0) soundex_insert(word,btSoundex);       
    }

    // free(line);
    // free(word);
    // free(mean);

    fclose(f);
}
//*/
/*
//file tu dien theo dinh dang cua thay.file vidu:filename[]="sample.dic"
void docfile(BTA* root,BTA* btSoundex,FILE *f){
    char line[SIZE_MEAN],line1[SIZE_MEAN];
    char word[SIZE_WORD];
    char mean[SIZE_MEAN];
    char c;
    int i,j,k,n;
    n=0;
    //word=(char*)malloc(sizeof(char)*SIZE_WORD);
    //mean=(char*)malloc(sizeof(char)*SIZE_MEAN);
   // line=(char*)malloc(sizeof(char)*SIZE_MEAN);
    fgets(line, SIZE_MEAN,f);
    
    while(1){
        i=strlen(line)-1;
        while(line[i]=='\n' || line[i]==' '){
           i--;
           //j++;
           //printf("%d\n",j); 
        }
        line[i+1]='\0';
        i=0;
        while(line[i]==' ') i++;
        strcpy(line,line+i);
        //printf("line=(%s)\n",line);
        //printf("length=%d\n",strlen(line)); 
        if(line[0]=='/' && line[1]=='/'){
            //free(line);
            //line=(char*)malloc(sizeof(char)*SIZE_MEAN);
            fgets(line, SIZE_MEAN,f);
            //line[strlen(line)-1]='\0';
            
        }
        else{
            if(line[0]=='['){
                while(1){
                    i=0;
                    while(1){
                        c=fgetc(f); 
                        if(c=='{') break;
                        if(feof(f)==1){
                           printf("File tu dien ko hop le1.\n");
                           exit(1); 
                        }
                    }
                    while(1){
                        word[i]=fgetc(f);
                        if (word[i]=='}') break;
                        i++;
                         if(feof(f)==1){
                           printf("File tu dien ko hop le2.\n");
                           exit(1); 
                        }
                    }
                    word[i]='\0';
                    while(1){
                        c=fgetc(f);
                        if (c==':') break;
                        i++;
                         if(feof(f)==1){
                           printf("File tu dien ko hop le2.\n");
                           exit(1); 
                        }
                    }
                   // c=fgetc(f);
                    //if(c==':'){
                        i=0;
                         while(1){
                            c=fgetc(f);
                            if(c=='{') break;
                            if(feof(f)==1){
                                printf("File tu dien ko hop le3.\n");
                                exit(1); 
                            }
                        }
                        while(1){
                            mean[i]=fgetc(f);
                            if (mean[i]=='}') break;
                            i++;
                            if(feof(f)==1){
                                printf("File tu dien ko hop le4.\n");
                                exit(1); 
                            }
                        }
                        mean[i]='\0';
                        for(i=0;i<strlen(word);i++) word[i]=tolower(word[i]);
                        i=btins(root,word,mean,SIZE_MEAN);
                        //printf("i=%d\n",i);
                        //printf("word=%s\n",word);
                        //printf("mean=%s\n",mean);
                        n++;
                        printf("n=%d\n",n);
                        if(i==0) soundex_insert(word,btSoundex);
                        //free(word); free(mean);
                        //word=(char*)malloc(sizeof(char)*SIZE_WORD);
                        //mean=(char*)malloc(sizeof(char)*SIZE_MEAN);
                    //}
                    //else{
                      //  printf("file tu dien ko hop le5.\n");
                       // exit(1);
                   // }
                    
                    c=fgetc(f);
                   // printf("c=(%c)\n",c);
                    if(c!=',') break;
                }
                //line1=(char*)malloc(sizeof(char)*SIZE_MEAN);
                k=1;
                while (fgets(line1, SIZE_MEAN,f) != NULL ){
                    i=strlen(line1)-1;
                    while(line1[i]=='\n' || line1[i]==' '){
                    i--;
                    //j++;
                    //printf("%d\n",j); 
                     }
                    line1[i+1]='\0';
                    //printf("line1=(%s)\n",line1);
                    i=0;
                    while(line1[i]==' ') i++;
                    strcpy(line1,line1+i);
                    //printf("line1=(%s)\n",line1);
                    if(line1[0]==']'){
                        k=0;
                        break;
                    } 
                    //free(line1);
                    //line1=(char*)malloc(sizeof(char)*SIZE_MEAN);
                }
                if(k==1){
                    printf("File tu dien ko hop le4.\n");
                    exit(1);
                }
                else break;
            } 
            else{
                //printf("line=%s\n",line );
                printf("File tu dien ko hop le5.\n");
                exit(1);
            } 
            
        }
        
    }
    //free(word); free(mean);free(line);free(line1);
    fclose(f);
}
*/
void ghifile(BTA* root,FILE* f){
    char word[SIZE_WORD];
    char mean[SIZE_MEAN];
    int i,rsize;
    long j=0;
    fprintf(f, "%s\n","[");
   //word=(char*)malloc(sizeof(char)*30);
   i=bfndky(root,"1",&rsize);
   if(i==0){
    //printf("1\n");
    j++;
   } 
   //word=(char*)malloc(sizeof(char)*30);
   //mean=(char*)malloc(sizeof(char)*SIZE_MEAN);
   j=0;
   while(bnxtky(root,word,&i)==0)
    {
        btsel(root,word,mean,SIZE_MEAN,&rsize);
        if(j==0){
             fprintf(f,"{%s}:{%s}",word,mean);
             j=1;
        }
        else{
             fprintf(f,"%s\n",",");
            fprintf(f,"{%s}:{%s}",word,mean);
        }
      //printf("%s\n",word);
      j++;
      //free(word);
      //free(mean);
      //word=(char*)malloc(sizeof(char)*30);
      //mean=(char*)malloc(sizeof(char)*SIZE_MEAN);
    }
    printf("n=%ld\n",j);
    fprintf(f,"\n%s","]");
    //free(word);
    //free(mean);
    fclose(f);
}

void insert(BTA* root,BTA* btSoundex){
	char word[30];
	char mean[SIZE_MEAN];
	int i,rsize;
	printf("Nhap tu muon them:");
	fgets(word,SIZE_WORD,stdin);
    for(i=0;i<strlen(word);i++) word[i]=tolower(word[i]);
	word[strlen(word)-1] = '\0';
	if(btsel(root,word,mean,SIZE_MEAN,&rsize)==0){
		printf("Da co \'%s\' trong tu dien!\n",word);
		
	}else{
		printf("Nhap nghia cua tu:");
		fgets(mean,SIZE_MEAN,stdin);
        mean[strlen(mean)-1] = '\0';
		btins(root,word,mean,SIZE_MEAN);
		soundex_insert(word,btSoundex);
		printf("Da them tu \'%s\' thanh cong!\n",word);
	}


}


void update(BTA* root){
    char word[30];
    char mean[SIZE_MEAN];
    int i,rsize;
    printf("Nhap tu muon cap nhat: ");
    fgets(word,SIZE_WORD,stdin);
    word[strlen(word)-1] = '\0';
    //scanf("%s",word);
    //while(getchar() != '\n');
    for(i=0;i<strlen(word);i++) word[i]=tolower(word[i]);
    if(btsel(root,word,mean,SIZE_MEAN,&rsize)==0){
        printf("Nhap nghia moi:");fgets(mean,SIZE_MEAN,stdin);
        mean[strlen(mean)-1] = '\0';
        btupd(root,word,mean,SIZE_MEAN);
        printf("Da cap nhat \'%s\' thanh cong!\n",word);
        
    }else{

        printf("Khong co \'%s\' trong tu dien!\n",word);
    }   

}

void delete(BTA* root,BTA* btSoundex){
    char word[30];
    char mean[SIZE_MEAN];
    int i,rsize;
    printf("Nhap tu muon xoa:");
    fgets(word,SIZE_WORD,stdin);
    word[strlen(word)-1] = '\0';
    for(i=0;i<strlen(word);i++) word[i]=tolower(word[i]);
    i=btdel(root,word);
    if(i==0){
        printf("Da xoa \'%s\' thanh cong!\n",word);
        soundex_delete(word,btSoundex);
    } 
    else printf("Khong co \'%s\' trong tu dien!\n",word);
}
/*
void search(BTA* root,BTA* btSoundex){
   char word[SIZE_WORD];
   char mean[SIZE_MEAN];
   int i,rsize,n,j;
   String *string;
   printf("Nhap tu muon tim:");
    fgets(word,SIZE_WORD,stdin);
    word[strlen(word)-1] = '\0';
    for(i=0;i<strlen(word);i++) word[i]=tolower(word[i]);
  // while(getchar() != '\n');
      if(btsel(root,word,mean,SIZE_MEAN,&rsize)==0){
            //printf("%s\n",searchword );
            mean[strlen(mean)] = '\0';
            printf("Nghia cua tu \'%s\' la: %s \n", word,mean);
        }
        else{
                printf("Khong co tu \'%s\' trong tu dien.\n",word);
                i=soundex_search(word,btSoundex);
                if(i!=0)  search(root,btSoundex);  
        }
        //free(string); 
}
*/
void search_full(BTA* root,BTA* btSoundex){
    char *word,mean[SIZE_MEAN];
    int i,j,k,n,rsize;
    char e;
    String *string;
                        word=(char*)malloc(sizeof(char)*SIZE_WORD);
                        //mean=(char*)malloc(sizeof(char)*SIZE_MEAN);
                        string=(String*)malloc(sizeof(String)*1000);
                         printf("Nhap tu can tim:");
                          j=0;
                          i=0;
                        while(1){
                            e=tolower(getch());
                            if(e!='\n' && e!=127 && e!='\t' && e!=27){
                                word[j++]=e;
                                putchar(e);
                                i=0;
                            }
                            if(e=='\t'){
                                if(j!=0){
                                    if(i==0){
                                        word[j]='\0';
                                        free(string);
                                        string=(String*)malloc(sizeof(String)*1000);
                                        n=search_tab(root,word,string);
                                        if(n!=0){   
                                            for(k=0;k<j;k++){
                                                putchar('\b');
                                                printf("%c[0K", 27);
                                            };
                                            free(word);
                                            word=(char*)malloc(sizeof(char)*SIZE_WORD);
                                            strcpy(word,string[i].s);
                                            //j=0;
                                            for(k=0;k<strlen(word);k++){
                                                putchar(word[k]);
                                            }
                                            j=strlen(word);
                                            i++;

                                        }
                                    }
                                    else{
                                        for(k=0;k<strlen(word);k++){
                                            putchar('\b');
                                            printf("%c[0K", 27);
                                            
                                        }
                                        if(i==n) i=0;//tim den tu cuoi cung
                                        free(word);
                                        word=(char*)malloc(sizeof(char)*SIZE_WORD);
                                        strcpy(word,string[i].s);
                                        //j=0;
                                        for(k=0;k<strlen(word);k++){
                                            //e=word[k];
                                            putchar(word[k]);
                                            //j++;
                                        }
                                        j=strlen(word);
                                        i++;
                                    }
                                }

                            }
                            if(e==127){
                                if(j>0){
                                    putchar('\b');
                                    printf("%c[0K", 27);
                                    word[j--]='\0';
                                    i=0;
                                }
                                
                            }
                            if(e=='\n'){
                                printf("\n");
                                word[j]='\0';
                                if(btsel(root,word,mean,SIZE_MEAN,&rsize)==0){
                                    
                                    printf("Nghia cua tu \'%s\' la: %s\n",word,mean);
                                }
                                else{
                                        printf("Khong co tu \'%s\' trong tu dien.\n",word);
                                        free(string);
                                        string=(String*)malloc(sizeof(String)*1000);
                                        i=soundex_search(word,btSoundex,string);
                                        if(i!= 0) //search(root,btSoundex);
                                        //  search_full(root,btSoundex);
                                            search_soundex(root,btSoundex,string,i);
                                        
                                    }
                                free(string); 
                                free(word);  
                                break;
                            }
                        }  
}

void search_soundex(BTA* root,BTA* btSoundex,String string[],int n){
    char *word,mean[SIZE_MEAN];
    int i,j,k,rsize;
    char e;
                        word=(char*)malloc(sizeof(char)*SIZE_WORD);
                        //mean=(char*)malloc(sizeof(char)*SIZE_MEAN); 
                         printf("Nhap tu can tim:");
                          j=0;
                          i=0;
                        while(1){
                            e=tolower(getch());
                            if(e!='\n' && e!=127 && e!='\t' && e!=27){
                                word[j++]=e;
                                putchar(e);
                                i=0;
                            }
                            if(e=='\t'){
                                if(j!=0){   
                                    word[j]='\0';
                                    if(i==0){
                                        while(1){
                                            if(strncmp(string[i].s,word,strlen(word))==0){
                                                for(k=0;k<strlen(word);k++){
                                                    putchar('\b');
                                                    printf("%c[0K", 27);
                                            
                                                }
                                                //tim den tu cuoi cung
                                                free(word);
                                                word=(char*)malloc(sizeof(char)*SIZE_WORD);
                                                strcpy(word,string[i].s);
                                                //j=0;
                                                for(k=0;k<strlen(word);k++){
                                                    //e=word[k];
                                                    putchar(word[k]);
                                                    //j++;
                                                }
                                                j=strlen(word);
                                                i++;
                                                break;
                                                
                                            }
                                            i++;
                                            if(i==n) break;
                                               
                                        }
                                    }
                                    else{
                                        for(k=0;k<strlen(word);k++){
                                            putchar('\b');
                                            printf("%c[0K", 27);
                                            
                                        }
                                        if(i==n) i=0;//tim den tu cuoi cung
                                        free(word);
                                        word=(char*)malloc(sizeof(char)*SIZE_WORD);
                                        strcpy(word,string[i].s);
                                        //j=0;
                                        for(k=0;k<strlen(word);k++){
                                            //e=word[k];
                                            putchar(word[k]);
                                            //j++;
                                        }
                                        j=strlen(word);
                                        i++;
                                    }
                                    
                                    
                                }

                            }
                            if(e==127){
                                if(j>0){
                                    putchar('\b');
                                    printf("%c[0K", 27);
                                    word[j--]='\0';
                                    i=0;
                                }
                                
                            }
                            if(e=='\n'){
                                printf("\n");
                                word[j]='\0';
                                if(btsel(root,word,mean,SIZE_MEAN,&rsize)==0){
                                    
                                    printf("Nghia cua tu \'%s\' la: %s\n",word,mean);
                                }
                                else{
                                        printf("Khong co tu \'%s\' trong tu dien.\n",word);
                                        i=soundex_search(word,btSoundex,string);
                                        if(i!= 0) //search(root,btSoundex);
                                                //search_full(root,btSoundex);
                                                search_soundex(root,btSoundex,string,i);
                                    }
                                //free(string); 
                                free(word);  
                                break;
                            }
                        }  
}




void hienthi(BTA* root){
   char word[SIZE_WORD];
   char mean[SIZE_MEAN];
   int i,rsize;
   long j=0;
   //word=(char*)malloc(sizeof(char)*30);
   i=bfndky(root,"1",&rsize);
   if(i==0){
   	printf("1\n");
   	j++;
   } 
   //word=(char*)malloc(sizeof(char)*30);
   while(bnxtky(root,word,&i)==0)
    {

      printf("%s\n",word);
      j++;
     // free(word);
      //word=(char*)malloc(sizeof(char)*30);
    }
    printf("n=%ld\n",j);
}



int search_tab(BTA *root,char *word,String *output){
  /*
  - cac tu do duoc luu trong output
  - ham tra ve 1 gia tri nguyen
    . -1: neu tim thay tu word trong tu dien
      total: so luong tu co phan dau trung voi word
  */
  int i,total=0,value;
  char key[50];
  i=bfndky(root,word,&value);//tim kiem khoa
  if(i==0){                //neu tim thay
   // return -1;
  	output[total++].s=strdup(word); 
  }
  //else{
    while(1){
      i=bnxtky(root,key,&value);  //tim kiem khoa tiem thoe
      if(i!=0||strncmp(key,word,strlen(word))!=0)
	     break;
      output[total++].s=strdup(key);  //luu khoa tim thay vao output
      if(total==1000) break;
    }
    
  //}
  return total;
}

int SoundEx(char *SoundEx,char *WordString,int   LengthOption,int   CensusOption){
      int  InSz = 31;
      char WordStr[32];     
      int  SoundExLen, WSLen, i;
      char FirstLetter, *p, *p2;

      SoundExLen = WSLen = 0;
      SoundEx[0] = 0;

      if(CensusOption) {
        LengthOption = 4;
      }

      if(LengthOption) {
          SoundExLen = LengthOption;
      }
      if(SoundExLen > 10) {
          SoundExLen = 10;
      }
      if(SoundExLen < 4) {
          SoundExLen = 4;
      }

      if(!WordString) {
          return(0);
      }
      for(p = WordString,p2 = WordStr,i = 0;(*p);p++,p2++,i++) {
        if(i >= InSz) break;
        (*p2) = (*p);
      }
      (*p2) = 0;
      for(p = WordStr;(*p);p++) {
        if( (*p) >= 'a' && (*p) <= 'z' ) {
            (*p) -= 0x20;
        }
      }
      for(p = WordStr;(*p);p++) {
        if( (*p) < 'A' || (*p) > 'Z' ) {
            (*p) = ' ';
        }
      }
      for(i = 0, p = p2 = WordStr;(*p);p++) {
          if(!i) {
              if( (*p) != ' ' ) {
                  (*p2) = (*p);
                  p2++;
                  i++;
              }
          }
          else {
              (*p2) = (*p);
              p2++;
          }
      }
      (*p2) = 0;
      for(i = 0,p = WordStr;(*p);p++) i++;
      for(;i;i--) {
          if(WordStr[i] == ' ') {
            WordStr[i] = 0;
          }
          else {
              break;
          }
      }
      for(WSLen = 0,p = WordStr;(*p);p++) WSLen++;

      if(!WSLen) {
        return(0);
      }
      if(!CensusOption) {
          if(WordStr[0] == 'P' && WordStr[1] == 'S') {
              WordStr[0] = '_';
          }

          if(WordStr[0] == 'P' && WordStr[1] == 'F') {
              WordStr[0] = '_';
          }
          if(WordStr[0] == 'G' && WordStr[1] == 'H') {
              WordStr[1] = '_';
          }

          for(i = 0;i < WSLen;i++) {
              if(WordStr[i] == 'D' && WordStr[i+1] == 'G') {
                  WordStr[i] = '_';
                  i++;
                  continue;
              }
              if( WordStr[i] == 'G' && WordStr[i+1] == 'H') {
                  WordStr[i] = '_';
                  i++;
                  continue;
              }
              if(WordStr[i] == 'K' && WordStr[i+1] == 'N') {
                  WordStr[i] = '_';
                  i++;
                  continue;
              }
              if(WordStr[i] == 'G' && WordStr[i+1] == 'N') {
                  WordStr[i] = '_';
                  i++;
                  continue;
              }
              if(WordStr[i] == 'M' && WordStr[i+1] == 'B') {
                  WordStr[i+1] = '_';
                  i++;
                  continue;
              }

              if(WordStr[i] == 'P' && WordStr[i+1] == 'H') {
                  WordStr[i] = 'F';
                  WordStr[i+1] = '_';
                  i++;
                  continue;
              }
              if(WordStr[i]  ==  'T'  &&
                 WordStr[i+1] == 'C' &&
                 WordStr[i+2] == 'H'
                ) {

                  WordStr[i] = '_';
                  i++; i++;
                  continue;
              }
              if(WordStr[i] == 'M' && WordStr[i+1] == 'P'
                 && (WordStr[i+2] == 'S' ||
                     WordStr[i+2] == 'T' ||
                     WordStr[i+2] == 'Z')
                ) {
                  WordStr[i+1] = '_';
                  i++;
              }
          }
      } 
      for(p = p2 = WordStr;(*p);p++) {
        (*p2) = (*p);
        if( (*p2) != '_' ) {
            p2++;
        }
      }
      (*p2) = 0;
      FirstLetter = WordStr[0];
      if(FirstLetter == 'H' || FirstLetter == 'W') {
          WordStr[0] = '-';
      }
      if(CensusOption == 1) {
          for(p = &(WordStr[1]);(*p);p++) {
             if((*p) == 'H' || (*p) == 'W') {
                 (*p) = '.';
             }
          }
      }

      for(p = WordStr;(*p);p++) {
          if( (*p) == 'A'   ||
              (*p) == 'E'   ||
              (*p) == 'I'   ||
              (*p) == 'O'   ||
              (*p) == 'U'   ||
              (*p) == 'Y'   ||
              (*p) == 'H'   ||
              (*p) == 'W'
            ){
              (*p) = '0';   
          }
          if( (*p) == 'B'   ||
              (*p) == 'P'   ||
              (*p) == 'F'   ||
              (*p) == 'V'
            ){
              (*p) = '1';
          }
          if( (*p) == 'C'   ||
              (*p) == 'S'   ||
              (*p) == 'G'   ||
              (*p) == 'J'   ||
              (*p) == 'K'   ||
              (*p) == 'Q'   ||
              (*p) == 'X'   ||
              (*p) == 'Z'
            ){
              (*p) = '2';
          }
          if( (*p) == 'D'   ||
              (*p) == 'T'
            ){
              (*p) = '3';
          }
          if( (*p) == 'L' ) {
              (*p) = '4';
          }

          if( (*p) == 'M'   ||
              (*p) == 'N'
            ){
              (*p) = '5';
          }
          if( (*p) == 'R' ) {
              (*p) = '6';
          }
      }
      
      if(CensusOption == 1) {
          for(p = p2 = &WordStr[1];(*p);p++) {
            (*p2) = (*p);
            if( (*p2) != '.' ) {
                p2++;
            }
          }
          (*p2) = 0;
      }
      for(p = p2 = &(WordStr[0]);(*p);p++) {
        (*p2) = (*p);
        if( (*p2) != p[1] ) {
            p2++;
        }
      }
      (*p2) = 0;
      for(p = p2 = &WordStr[1];(*p);p++) {
        (*p2) = (*p);
        if( (*p2) != ' ' && (*p2) != '0' ) {
            p2++;
        }
      }
      (*p2) = 0;
      for(WSLen = 0,p = WordStr;(*p);p++) WSLen++;
      for(i = WSLen;i < SoundExLen;i++ ) {
          WordStr[i] = '0';
      }
      WordStr[SoundExLen] = 0;
      WordStr[0] = FirstLetter;
      for(p2 = SoundEx,p = WordStr;(*p);p++,p2++) {
          (*p2) = (*p);
      }
      (*p2) = 0;      
      return(SoundExLen);
}



void soundex_insert(char *word, BTA *btSoundex){  //khai bao 1 BTA la sdex va create o bien toan cuc.
                                            //su dung SIZE_MEAN  hang o bai cua quan
  char s[SIZE_MEAN1],soundEx[10];
  int i, k, h, l,rsize;
  //soundEx=(char*)malloc(10*sizeof(char));
  l=SoundEx(soundEx,word,4,4);
  soundEx[l]='\0';
  //s=(char*)malloc(SIZE_MEAN*sizeof(char));
  i=btsel(btSoundex, soundEx, s, SIZE_MEAN1, &rsize);
  if(i!=0){
    if(btins(btSoundex, soundEx, word,SIZE_WORD)!=0) printf("Nhap soundex that bai!");
  }
  else{
    /*
    k=strlen(s);
    s[k]='\n';s[k+1]='\0';
    for(h=k+1;h<(k+strlen(word)+1);h++){
      s[h]=word[h-k-1];
    }
    s[h]='\0';
    */
    //k=strlen(s);
    //s[k]='\n';
    strcat(s,"\n");
    strcat(s,word);
    s[strlen(s)]='\0';
    btupd(btSoundex, soundEx, s,SIZE_MEAN1);
   
  }
  //free(s);
  //free(soundEx);
}

void soundex_delete(char *word, BTA* btSoundex){   //ham can dau vao tu tieng anh va jbr
  char s[SIZE_MEAN1],soundEx[10],*ptr;
  int l,i,rsize,j;
  //soundEx=(char*)malloc(SIZE_WORD*sizeof(char));
  l=SoundEx(soundEx,word,4,4);
  soundEx[l]='\0';
  //s=(char*)malloc(SIZE_MEAN*sizeof(char));
  i=btsel(btSoundex, soundEx, s, SIZE_MEAN1, &rsize);
  if(i!=0){
    //printf("Da xoa tu va khong tim thay soundex!\n");
  }else{
    
    if(strcmp(s,word)==0){
        btdel(btSoundex, soundEx); //printf("Da xoa thanh cong!\n");
    }
    
    else{
        //s1=(char*)malloc(SIZE_MEAN*sizeof(char));
        ptr = strtok(s,"\n");
        //j=0;
        btdel(btSoundex, soundEx);
        while(ptr){
            //printf("%s\n",ptr);
            if(strcmp(ptr,word)!=0){
                //printf("%s\t",ptr);
                soundex_insert(ptr,btSoundex);
            }
            ptr = strtok(NULL, "\n");    
        }
        free(ptr);
    }
    
  }

  //free(s);
  
}
// can khai bao bien toan cuc va thu vien #include <curses.h>
int soundex_search(char *word, BTA* btSoundex,String string[]){
  int l, bn,rsize,i;
  char en[SIZE_MEAN1],soundEx[10],*ptr;
  //soundEx=(char*)malloc(10*sizeof(char));
  l=SoundEx(soundEx,word,4,4);
  soundEx[l]='\0';
  //en=(char*)malloc(SIZE_MEAN *sizeof(char));
  bn=btsel(btSoundex,soundEx,en,SIZE_MEAN1,&rsize);
  if(bn==0){
        printf("Y cua ban co phai la:\n");
        printf("%s\n",en);
        if(strcmp(en,word)==0){
            string[0].s=strdup(word);
            return 1;
        }
        else{
            ptr = strtok(en,"\n");
            i=0;
            while(ptr){
                string[i++].s=strdup(ptr);
                ptr = strtok(NULL, "\n");    
            }
            free(ptr);   
            return i;
        }
        
  }
  //free(soundEx);//free(en);
  return 0;
}


void soundex_hienthi(BTA* btSoundex){
    char SoundEx[10];
    //char word[SIZE_MEAN];
    int i,rsize;
    long j=0;
  // SoundEx=(char*)malloc(sizeof(char)*30);
   //printf("nhap tu bat dau:");gets(word);
   i=bfndky(btSoundex,"1",&rsize);
   while(bnxtky(btSoundex,SoundEx,&i)==0)
    {
      printf("%s\n",SoundEx);
      j++;
      //printf("n=%ld\n", j);
     // SoundEx=(char*)malloc(sizeof(char)*30);
      //word=(char*)malloc(sizeof(char)*SIZE_MEAN);
    }
    printf("n=%ld\n",j);
    //free(SoundEx);free(word);
}
