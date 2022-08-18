//500240199605021172
//7 9 10 5 8 4 2 1 6 3 7 9 10 5 8 4 2

//0 1 2 3 4 5 6 7 8 9 10
//1 0 X 9 8 7 6 5 4 3 2

#include <stdio.h>
#include <stdlib.h>

void Judge(char str[])
{
	int num = 0;
	int flag = 0;
	
	num += (str[0]-48)*7;
	num += (str[1]-48)*9;
	num += (str[2]-48)*10;
	num += (str[3]-48)*5;
	num += (str[4]-48)*8;
	num += (str[5]-48)*4;
	num += (str[6]-48)*2;
	num += (str[7]-48)*1;
	num += (str[8]-48)*6;
	num += (str[9]-48)*3;
	num += (str[10]-48)*7;
	num += (str[11]-48)*9;
	num += (str[12]-48)*10;
	num += (str[13]-48)*5;
	num += (str[14]-48)*8;
	num += (str[15]-48)*4;
	num += (str[16]-48)*2;
	printf("num %% 11 = %d\n", num%11);
	switch(num%11)
	{
		case 0:if(str[17] == '1') {printf("这个身份证号码是合法的\n");flag = 1;}break;
		case 1:if(str[17] == '0') {printf("这个身份证号码是合法的\n");flag = 1;}break;
		case 2:if(str[17] == 'X') {printf("这个身份证号码是合法的\n");flag = 1;}break;
		case 3:if(str[17] == '9') {printf("这个身份证号码是合法的\n");flag = 1;}break;
		case 4:if(str[17] == '8') {printf("这个身份证号码是合法的\n");flag = 1;}break;
		case 5:if(str[17] == '7') {printf("这个身份证号码是合法的\n");flag = 1;}break;
		case 6:if(str[17] == '6') {printf("这个身份证号码是合法的\n");flag = 1;}break;
		case 7:if(str[17] == '5') {printf("这个身份证号码是合法的\n");flag = 1;}break;
		case 8:if(str[17] == '4') {printf("这个身份证号码是合法的\n");flag = 1;}break;
		case 9:if(str[17] == '3') {printf("这个身份证号码是合法的\n");flag = 1;}break;
		case 10:if(str[17] == '2') {printf("这个身份证号码是合法的\n");flag = 1;}break;	
	}

	if (flag == 0)
	{
		printf("这个身份证号码是不合法的\n");
	}
}

int main(int argc, char const *argv[])
{
	char *str = malloc(sizeof(char));
	printf("请输入需要判断的身份证号码:\n");
	scanf("%s", str);
	Judge(str);
	return 0;
}