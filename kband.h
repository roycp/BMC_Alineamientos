#include "alignment_support.h"
#include "needleman_wunsch.h"


int match_Miss(char column_char_value, char row_char_value) {
  int match_value;
  match_value = (column_char_value == row_char_value) ? MATCH_SCORE : MISSMATCH_SCORE;
  return match_value;
}
int insideBand(int i , int j , int k){
	if (-k <= (i - j) <= k) 
		return 1;//true
	else
		return 0;//false
}
//M>N
int insideBandMxN(int n,int m,int i , int j , int k){
	if (n-m-k <= (i - j) <= k) 
		return 1;//true
	else
		return 0;//false
}
 
void init_Kband(int values[255][255],char *secuence1, char *secuence2,int d, int k) {
  int i, j;
  for(i = 1; i <= k; i++) 
    values[i][0] = -i*d;
  
  for(j = 1; j <= k; j++) 
    values[0][j] = -j*d;  
}
/*gap score d .asumme NXN 
 * Imput: x, y leght n ,integer k
 * OUtPut: best score B ofglobal aligment at most k diagonals away from main diagonal
 * before call init_Kband(int values[255][255],char *secuence1, char *secuence2,int d, int k); 
*/
int Kband(int n, int values[255][255], char *secuence1, char *secuence2, int d,int k) {
  
 int i, j, h;
 
 
 for(i = 1; i <= n; i++) {
	 
	for (h = -k ; h < k; h++){
		
		j = (i+h);
		
		if ( 1 <= j <= n ){
			values[i][j] = values[i-1][j-1] + match_Miss(secuence1[j], secuence2[i]);
			
			if (insideBand(i-1 , j , k))
				values[i][j] = max(values[i][j], values[i-1][j]-d);
			
			if (insideBand(i , j-1 , k))
				values[i][j] = max(values[i][j], values[i][j-1]-d);
		 
		}//insideband
		
	}
	
 }
 
 return	values[n][n];
}

/*gap score d .asumme MXN 
 * Imput: x, y leght nxm ,integer k
 * OUtPut: best score B ofglobal aligment at most k diagonals away from main diagonal
 * before call init_Kband(int values[255][255],char *secuence1, char *secuence2,int d, int k); 
*/
int KbandMxN(int m,int n, int values[255][255], char *secuence1, char *secuence2, int d,int k) {
  //M>N
 int i, j, h;
 
 
 for(i = 1; i <= n; i++) {
	 
	for (h = -k ; h < k; h++){
		
		j = (i+h);
		
		if ( 1 <= j <= n ){
			values[i][j] = values[i-1][j-1] + match_Miss(secuence1[j], secuence2[i]);
			
			if (insideBandMxN(n,m,i-1 , j , k))
				values[i][j] = max(values[i][j], values[i-1][j]-d);
			
			if (insideBandMxN(n,m,i , j-1 , k))
				values[i][j] = max(values[i][j], values[i][j-1]-d);
		 
		}//insideband
		
	}
	
 }
 
 return	values[n][n];
}
/*gap score d .asumme NXN 
 * Imput: x, y leght n ,integer k samll number, M macth value y d gap penalty
 * OUtPut: best score B 
 * before call init_Kband(int values[255][255],char *secuence1, char *secuence2,int d, int k); 
*/
int KBandOptimal(int n, int values[255][255], char *secuence1, char *secuence2, int d,int k, int M){
	int alfa;
	while(1==1){
		alfa =  Kband(n,values,secuence1,secuence2,d,k) ;
		if (alfa >= ((M *(n - k-1) )  - ((2 *(k+1))*d)) )
		  return alfa;
		  
		k = 2*k;  
	}
	return 0;
}

/*gap score d .asumme MxN 
 * Imput: x, y leght n ,integer k samll number, M macth value y d gap penalty
 * OUtPut: best score B 
 * before call init_Kband(int values[255][255],char *secuence1, char *secuence2,int d, int k); 
*/
int KBandOptimalMxN(int m,int n, int values[255][255], char *secuence1, char *secuence2, int d,int k, int M){
	int alfa;
	while(1==1){
		alfa = KbandMxN(m,n,values,secuence1,secuence2,d,k) ;
		if (alfa >= ((M *(n - k-1) )  - ( ((2 *(k+1)) + (m-n))*d) ) )
		  return alfa;
		  
		k = 2*k;  
	}
	return 0;
}
