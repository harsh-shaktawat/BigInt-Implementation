#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef enum{PLUS, MINUS} Sign;
typedef struct bigint_definition{
    char str[310];//store the number in character array 
    Sign s;//store the sign of number
}bigInt;
void get_bigInt(bigInt *num){
    scanf("%s", &num->str);//input is stored in form of character array
    if(num->str[0]=='-') {//if number is negative
        num->s=MINUS;//update the sign field
        int i=0;
        while(i<strlen(num->str)-1){
            num->str[i]=num->str[i+1];//shift each digit to left by 1 unit
            i++;
        }
        num->str[i]='\0';//terminate the string or char array
    }
    else{
        num->s=PLUS;
    }
}
void subtract(bigInt *a, bigInt *b,Sign c);
void subtract_bigInt(bigInt *a, bigInt *b);
void addition(bigInt *a, bigInt *b, Sign c);
void add_bigInt(bigInt *a, bigInt *b);
void multiply_bigInt(bigInt *a,bigInt *b){
    int len1=strlen(a->str);
    int len2=strlen(b->str);
    int ans[len1+len2];
    for(int i=0;i<len1+len2;i++){
		ans[i]=0;
	}
    int pos1=0,pos2=0,sum,carry;
    for(int i=len1-1;i>=0;i--){
        int multiplier=((a->str[i])-'0');
        carry=0;
        pos2=0;
        for(int j=len2-1;j>=0;j--){
            int curr_digit=((b->str[j])-'0');
            sum=curr_digit*multiplier+ans[pos1+pos2]+carry;
            carry=sum/10;
            ans[pos1+pos2]=sum%10;
            pos2++;
        }
        if(carry>0){
            ans[pos1+pos2]+=carry;
        }
        pos1++;
    }
    int i = len1+len2 - 1;
	while (i>=0 && ans[i] == 0){ i--;}
    if(i==-1) printf("ans:0\n");
    else{
        printf("ans:");
        if(a->s!=b->s) printf("-");
        while(i>=0){
            printf("%d", ans[i]);
            i--;
        }
    }
}
void subtract(bigInt *a, bigInt *b,Sign c){
        int len1=strlen(a->str);
        int len2=strlen(b->str);
        int finalLen=(len1>len2)? len1+1:len2+1;
        char ans[finalLen];
        int i=len1-1,j=len2-1,k=finalLen-1;
        int diff,borrow=0;
        while(i>=0 && j>=0){
            diff=(a->str[i]-'0')-(b->str[j]-'0')-borrow;
            if(diff<0){
                diff=diff+10;
                borrow=1;
            }else borrow=0;
            ans[k]=diff+'0';
            i--; j--; k--;
        }
        while(i>=0){
            diff=(a->str[i]-'0')-borrow;
            if(diff<0){
                diff=diff+10;
                borrow=1;
            } else borrow=0;
            ans[k]=diff+'0';
            i--; k--;
        }
        while(j>=0){
            diff=(b->str[j]-'0')-borrow;
            if(diff<0){
                diff=diff+10;
                borrow=1;
            } else borrow=0;
            ans[k]=diff+'0';
            j--; k--;
        }
        k++;
        printf("ans:");
        if(c==MINUS) printf("-");
        while(k<finalLen){
            printf("%c", ans[k]);
            k++;
        }
}
void subtract_bigInt(bigInt *a, bigInt *b){
    if(a->s==b->s){
        if(strlen(a->str)>strlen(b->str)){
            subtract(a,b,PLUS);
        }
        else if(strlen(a->str)<strlen(b->str)){
            subtract(b,a,MINUS);
        }
        else{
            int i=0;
            int len=strlen(a->str);
            while((a->str[i])==(b->str[i]) && i<len){
                i++;
            }
            if(i==len){//a a
                printf("ans:0\n");
            }
            else if((a->str[i])>(b->str[i]) ){
                if(a->s==PLUS) subtract(a,b,PLUS);// 12 10
                else subtract(a,b,MINUS);// -12 -10
            }
            else {
                if(b->s==PLUS) subtract(b,a,MINUS);
                else subtract(b,a,PLUS);
            }
        }
    }
    else{
        if(a->s==MINUS){
            addition(a,b,MINUS); //-12 10
        }
        else{
            addition(a,b,PLUS);
        }
    }
}
void addition(bigInt *a, bigInt *b, Sign c){
        int len1=strlen(a->str);
        int len2=strlen(b->str);
        int finalLen=(len1>len2)? len1+1:len2+1;//final length of ans will be 1 more than max lenght of a,b
        char ans[finalLen];
        
        int i=len1-1,j=len2-1,k=finalLen-1;
        int sum,carry=0;
        while(i>=0 && j>=0){
            sum=(a->str[i]-'0')+(b->str[j]-'0')+carry;
            if(sum>=10){
                sum=sum%10;
                carry=1;
            } else carry=0;
            ans[k]=sum+'0';
            i--; j--; k--;
        }
        while(i>=0){
            sum=(a->str[i]-'0')+carry;
            if(sum>=10){
                sum%=10;
                carry=1;
            } else carry=0;
            ans[k]=sum+'0';
            i--;
            k--;
        }
        while(j>=0){
            sum=(b->str[j]-'0')+carry;
            if(sum>=10){
                sum%=10;
                carry=1;
            }
            else carry=0;
            ans[k]=sum+'0';
            j--;
            k--;
        }
        if(carry==1){
            ans[k]='1';
            k--;
        }
        k++;
        printf("ans:");
        if(c==MINUS) printf("-");
        while(k<finalLen){
            printf("%c", ans[k]);
            k++;
        }
}
void add_bigInt(bigInt *a, bigInt *b){
    if(a->s==b->s){//if both numbers are of same sign
        addition(a,b, a->s);
    }
    else{//numbers have alternate sign
        
        if(strlen(a->str)>strlen(b->str)){//1st number is bigger
            subtract(a,b, a->s);
        }
        else if(strlen(a->str)<strlen(b->str)){//2nd number is bigger
            subtract(b,a, b->s);
        }
        else{//both numbers are of identical length
            int i=0;
            int len=strlen(a->str);
            while(a->str[i]==b->str[i] && i<len){//loop will check at which index both number differs 
                i++;
            }
            if(i==len){//this means that both numbers are identical
                printf("0\n");
            }
            else if(a->str[i]>b->str[i]){//1st number is bigger
                subtract(a,b,a->s);
            }
            else{//2nd number is bigger
                subtract(b,a,b->s);
            }
        }
        
    }
}
int main(){
    bigInt a,b;
    printf("Enter first number\n");
    get_bigInt(&a);
    printf("Enter second number\n");
    get_bigInt(&b);

    char choice;
    printf("Press\n1 for Addition operation\n2 for Subtraction operation\n3 for Multiplication operation\n");
    scanf(" %c", &choice);
    if(choice=='1'){
        add_bigInt(&a,&b);
    }
    else if(choice=='2'){
        subtract_bigInt(&a, &b);
    }
    else if(choice=='3'){
        multiply_bigInt(&a,&b);
    }
    else{
        printf("Inavlid operation\n");
    }

return 0;
}
