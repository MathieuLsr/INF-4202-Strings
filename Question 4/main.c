#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

struct alignement
{
  char * x;
  char * y;
};


/* =============================================================== */
char * readtextfile(char * filename)
  /* Retourne le contenu du fichier texte filename */
/* =============================================================== */
{
  struct stat monstat;
  int N;
  char * text = NULL;
  FILE *fd = NULL;

  N = stat(filename, &monstat);
  if (N == -1)
  {
    fprintf(stderr, "error : bad file %s\n", filename);
    exit(0);
  }
  N = monstat.st_size;
  text = (char *)malloc(N+1);
  if (text == NULL)
  {   fprintf(stderr,"readtextfile() : malloc failed for text\n");
      exit(0);
  }
  fd = fopen(filename,"r");
  if (!fd)
  {
    fprintf(stderr, "readtextfile: can't open file %s\n", filename);
    exit(0);
  }
  
  fread(text, sizeof(char), N, fd);
  if((N>0) && (text[N-1] == '\n') ) text[N-1] = '\0';
  else text[N-1] = '\0';
  fclose(fd);
  return text;
}

/* =============================================================== */
int Imax(int a, int b)
/* Retourne  le maximum de a et b                                  */
/* =============================================================== */
{
  if (a < b) return b;
  else return a;	       
}

/* =============================================================== */
int Imin2(int a, int b)
/* Retourne  le minimum de a et b                                  */
/* =============================================================== */
{
  if (a < b) return a;
  else return b;	       
}

/* =============================================================== */
int Imin3(int a, int b, int c)
/* Retourne  le minimum de a, b et c                               */
/* =============================================================== */
{
  return Imin2(Imin2(a,b),c);
}

/* =============================================================== */
void retourne(char *c)
/* Retourner la chaîne de caractère c                              */
/* =============================================================== */
{
  char tmp;
  int m, j, i;
  m = strlen(c);
  j = m/2;
  for(i = 0; i < j; i++ ){
    tmp = c[i];
    c[i] = c[m-i-1];
    c[m-i-1] = tmp;
  }
}
/* =============================================================== */
void afficheSeparateurHorizontal(int nbcar)
/* =============================================================== */
{
  int i;
  printf("|-");
  for(i=0; i < nbcar; i++)
    printf("-");
  printf("-|-");
  for(i=0; i < nbcar; i++)
    printf("-");
  printf("-|\n");
}


/* =============================================================== */
void affiche(char* texte1, char* texte2, int nbcar)
  /* Affiche simultanément texte1 et texte 2 en positionnnant nbcar  
     caractères sur chaque ligne. */
/* =============================================================== */
{
  int i, l1, l2, l;
  
  char *t1,*t2;
  
  char out[512];
  
  l1 = strlen(texte1);
  l2 = strlen(texte2);

  t1 = (char*) malloc(sizeof(char) * (nbcar + 1));
  t2 = (char*)malloc(sizeof(char) * (nbcar + 1));

  l = Imax(l1, l2);
  afficheSeparateurHorizontal(nbcar);
  for(i = 0; i < l; i+= nbcar){
    if (i < l1) {
      strncpy(t1, &(texte1[i]), nbcar);
      t1[nbcar] = '\0';
    } else t1[0] = '\0';
    if (i < l2) {
      strncpy(t2, &(texte2[i]),nbcar);
      t2[nbcar] = '\0';
    } else t2[0] = '\0';
    
    sprintf(out, "| %c-%ds | %c-%ds |\n",'%', nbcar, '%', nbcar);
    printf(out, t1,t2);
  }
  afficheSeparateurHorizontal(nbcar);
  free(t1);
  free(t2);
}



/* =============================================================== */
void affiche2(char* texte1, char* texte2, int nbcar)
  /* idem affiche, mais avec un formattage différent */
/* =============================================================== */
{

  int i, l1, l2, l;
  
  char *t1,*t2;
  
  char out[512];
  
  l1 = strlen(texte1);
  l2 = strlen(texte2);

  t1 = (char*) malloc(sizeof(char) * (nbcar + 1));
  t2 = (char*)malloc(sizeof(char) * (nbcar + 1));

  l = Imax(l1, l2);

  for(i = 0; i < l; i+= nbcar){
    if (i < l1) {
      strncpy(t1, &(texte1[i]), nbcar);
      t1[nbcar] = '\0';
    } else t1[0] = '\0';
    if (i < l2) {
      strncpy(t2, &(texte2[i]),nbcar);
      t2[nbcar] = '\0';
    } else t2[0] = '\0';
    
    sprintf(out, "x: %c-%ds \ny: %c-%ds\n",'%', nbcar, '%', nbcar);
    printf(out, t1,t2);

  }
  free(t1);
  free(t2);
}

int Del(char x){
  return 1 ; 
}

int Ins(char x){
  return 1 ; 
}

int Sub(char x, char y){
  if(x == y) return 0 ;
  return 1 ; 
}

int initD(int **D, int size1, int size2){

  printf("size1 = %d, size2 = %d\n", size1, size2) ;

  int r=size1+1, c=size2+1, len=0;
  int *ptr;
  int count = 0,i,j;

  len = sizeof(int *) * r + sizeof(int) * c * r;
  D = (int **)malloc(len);

  // ptr is now pointing to the first element in of 2D array
  ptr = (int *)(D + r);

  // for loop to point rows pointer to appropriate location in 2D array
    for(i = 0; i < r; i++)
        D[i] = (ptr + c * i);

  return 0 ; 

}

int DistanceDeLevenshtein(int **D, char* x, char* y) {

  int size1 = strlen(x), size2 = strlen(y) ;

  //int* D = (int*) calloc(size1 * size2, sizeof(int))   ;
  //int D[size1][size2] ;
  D[0][0] = 0 ;

  for(int i = 1 ; i<size1+1 ; i++) D[i][0] = D[i-1][0] + Del(x[i-1]) ;
  for(int j = 1 ; j<size2+1 ; j++) D[0][j] = D[0][j-1] + Del(x[j-1]) ;

  for(int i = 1 ; i<size1+1 ; i++){
    for(int j = 1 ; j<size2+1 ; j++){

      D[i][j] = Imin3(
        D[i][j - 1] + Ins(y[j-1]), 
        D[i - 1][j] + Del(x[i-1]), 
        D[i - 1][j - 1] + Sub(x[i - 1],y[j - 1])
      ) ;

      //printf("- %d ", D[i][j]) ;

    }
    //printf(" (%d)\n", i); 
  }

  return D[size1][size2] ;
}



/* =============================================================== */
int main(int argc, char **argv)
/* =============================================================== */
{
  char *x, *y; 
  
  if(argc != 3){
    printf("usage: %s text1 text2\n", argv[0]);
    exit(0);
  }  

  x = readtextfile(argv[1]);
  y = readtextfile(argv[2]);

  //affiche(x, y, 50);

  //#define DEBUG
  #ifdef DEBUG

  x = "chateau maison lalabbb papa" ;
  y = "chapeau papa" ;

  #endif

  int size1 = strlen(x), size2 = strlen(y) ;
  
  for(int i = 0 ; i<size1 ; i++)
    if(x[i] == '\n') x[i] = ' ' ;
  for(int i = 0 ; i<size2 ; i++)
    if(y[i] == '\n') y[i] = ' ' ;
  
  affiche2(x, y, 50);
  int** D ;

  int r=size1+1, c=size2+1, len=0;
  int *ptr;
  int count = 0,i,j;

  len = sizeof(int *) * r + sizeof(int) * c * r;
  D = (int **)malloc(len);

  // ptr is now pointing to the first element in of 2D array
  ptr = (int *)(D + r);

  // for loop to point rows pointer to appropriate location in 2D array
    for(i = 0; i < r; i++)
        D[i] = (ptr + c * i);



  int dist = DistanceDeLevenshtein(D, x, y) ;

  //printf("1.0\n") ;

  /*
  for(int i=0 ; i<=size1 ; i++){
    for(int j=0 ; j<=size2 ; j++)
      if(D[i][j] < 10) printf("0%d   ", D[i][j]) ;
      else printf("%d   ", D[i][j]) ;
    printf("\n") ;
  }
  */

  int decalage_y = 0 ;
  char y_prime[strlen(x)] ;
  int k = size1, l = size2;

  while(k > 0 && l > 0){
    
    //if(k <= 0) k = 1 ;
    //if(l <= 0) l = 1 ;
    
    //printf("k=%d, l=%d\n", k, l);
    int cell_diag = D[k-1][l-1];
    int cell_haut = D[k-1][l];
    int cell_gauche = D[k][l-1];

    /*
    if(cell_diag == cell_gauche == cell_haut){
      k-- ;
      l-- ;
    }
    else if(cell_gauche < cell_haut && cell_gauche < cell_diag){
      l-- ;
    }
    else if(cell_diag < cell_haut && cell_diag < cell_gauche){
      k-- ;
      l-- ;
    }
    else if(cell_haut < cell_gauche && cell_haut < cell_diag){
      k-- ;
    }
    */

    if(cell_haut >= cell_diag){
      k-- ;
      l-- ; 
      y_prime[k] = y[k-(size1-size2)+decalage_y] ;
    }
    else{
      k-- ;
      y_prime[k] = ' ' ;
      decalage_y++ ;
    }

  }
  
  /*
  printf("x       : %s\n", x) ;
  printf("y       : %s\n", y) ;
  printf("x_prime : %s\n", x) ;
  printf("y_prime : %s\n", y_prime) ;
  */
  affiche(x, y_prime, 80) ;
  affiche2(x, y_prime, 50) ;


  printf("Size texte1 = %d, size texte2 = %d\n", size1, size2) ; 
  printf("Distance : %d\n", dist) ;
  double d = 1-((double)dist/(double)(size1+size2)) ;
  printf("Ratio de similarite : %f\n", d*100);
  



}