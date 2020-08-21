#include <iostream>  
#include <cstring> 
#include <cstdlib> 
#include <string>
#include <cstring>
#include <math.h>  
using namespace std; 
const int MAX = 10001;  

//Evens up the two arrays by adding zeros to the front of the smaller array
void addZero(char* arr, int n) 
{ 
  int lena = strlen(arr); 
  for (int i = lena - 1 + n; i >= n; --i) 
  { 
    arr[i] = arr[i - n]; 
  } 
  arr[lena + n] = 0; 
  for (int i = 0; i < n; ++i) 
  { 
    arr[i] = '0'; 
  } 
} 

//removes leading zeros
void remZero(char* arr) 
{ 
  int lena = strlen(arr); 
  int count = 0; 
  while ((count < lena) and (arr[count] == '0')) 
  { 
    count++; 
  } 
  for (int i = count; i < lena; ++i) 
  { 
    arr[i - count] = arr[i]; 
  } 
  arr[lena - count] = 0; 
} 

//School addition function for large ints 
void schooladd(char* first, char* second, char* res, int B) {

  int lena = strlen(first); 
  int lenb = strlen(second); 
  int n = abs(lena-lenb);

  if(lena < lenb){
    addZero(first,n);
  }else if(lena > lenb){
    addZero(second,n);
  }
  int l = strlen(first);
  int s = 0;
  int carry = 0;
  int count = 0;
  for (int i = l-1 ; i>-1 ; i--){
    int sum = (first[i] - '0') + (second[i] - '0' ) + carry;
    carry = floor(sum/B);
    s = sum - carry*B;
    res[i] = s + '0';
    count++;
  }
  if(carry!=0 and count == l){
    char sup[MAX];
    sup[0] = '\0';
    strcpy(sup,res);
    memset(res,'\0',MAX);
    res[0] = 1 + '0';
    strcat(res,sup);
  }
} 

//School addition subtraction
void subtract(char* first, char* second, char* res, int B) 
{ 
  int lena = strlen(first); 
  int lenb = strlen(second); 
  int n = abs(lena-lenb);

  if(lena<lenb){
    addZero(first,n);

  }else if(lena>lenb){
    addZero(second,n);
  }

  int l = strlen(first);

  for (int i = l-1;i>-1;i--){

    int s = 0;
    s = (first[i] - '0')-(second[i] - '0');
    if (s < 0){
      s = s + B;
      first[i-1] = (first[i-1]-'0') - (1-'0');
    }
    res[i] = s + '0';
}} 

//Multply by base 10
void base10(char* arr, int n) 
{ 
  int lena = strlen(arr); 
  if (lena == 1 && arr[0] == '0') 
  { 
    return; 
  } 
  for (int i = lena; i < lena + n; ++i) 
  { 
    arr[i] = '0'; 
  } 
  arr[lena + n] = 0; 
} 


char* CreateArray(int l) 
{ 
  char* res = new char[l]; 
  memset(res, 0, l); 
  return res; 
} 

//Karatsuba recursive function for long ints
void karatsuba(char* first, char* second, char* res,int B) 
{ 
  int lenx = strlen(first);
  int leny = strlen(second);
  int diff = lenx - leny;
  diff = abs(diff);
  if(lenx<leny){
    addZero(first,diff);
  }else{
    addZero(second,diff);
  }

  int len = strlen(first); 
  if (len == 1){ 
    int val = (first[0] - '0') * (second[0] - '0'); 
    if (val < 10) { 
      if(val < B){
        res[0] = val + '0'; 
      }
      else{
        res[0] = (val/B) + '0';
        res[1] = (val%B) + '0';
      } 
    }
    else{ 
      res[0] = (val / B) + '0'; 
      res[1] = (val % B) + '0';
    } 
  } 
  else if(len > 1)
  { 
    char* xl = CreateArray(len); 
    char* xr = CreateArray(len); 
    char* yl = CreateArray(len); 
    char* yr = CreateArray(len); 
    int rightSize = len / 2; 
    int leftSize = len - rightSize; 

    strncpy(xl, first, leftSize); 
    strcpy(xr, first + leftSize);
    strncpy(yl, second, leftSize); 
    strcpy(yr, second + leftSize); 
    int maxl = 3 * len; 
    char* P1 = CreateArray(MAX); 
    char* P2 = CreateArray(MAX); 
    char* P3 = CreateArray(MAX); 

    karatsuba(xl, yl, P1,B); 
    karatsuba(xr, yr, P2,B); 

    char* tmp1 = CreateArray(maxl); 
    char* tmp2 = CreateArray(maxl); 
    char* tmp3 = CreateArray(MAX); 
    char* tmp4 = CreateArray(MAX); 
    schooladd(xl, xr, tmp1,B); 
    schooladd(yl, yr, tmp2,B); 

    karatsuba(tmp1, tmp2, P3,B); 

    subtract(P3, P1, tmp3,B); 
    subtract(tmp3, P2, tmp4,B);

    base10(tmp4, rightSize); 
    base10(P1, 2 * rightSize); 
    schooladd(P1, P2, res,B); 
    schooladd(res, tmp4, res,B);
    
    remZero(res); 
  } 
} 

int main() 
{ 
  char first[MAX], second[MAX]; 
  int B;

  cout<<"(number1 number2 base): "<<endl;
  cin>>first>>second>>B; 

  char* mult = CreateArray(MAX); 
  char* add = CreateArray(MAX); 

  schooladd(first,second,add,B);
  karatsuba(first, second, mult,B);

  cout<<add << " " <<mult; 
} 