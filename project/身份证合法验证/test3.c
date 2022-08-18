//5 0 0  2 4 0 1 9 9 6 0 5 0  2 1 1 7 2
//7 9 10 5 8 4 2 1 6 3 7 9 10 5 8 4 2

//0 1 2 3 4 5 6 7 8 9 10
//1 0 X 9 8 7 6 5 4 3 2
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_num(char str[]);
bool is_long(char str[]);
bool Judge(char str[]);
bool address(char str[], char diqu[]);
void Gender(char str[]);
bool specific_date(char str[], int *year, int *month, int *day);

void Gender(char str[])
{
	if((str[16]-48)%2 == 0)
	{
		printf("女\n");
	}
	else
	{
		printf("男\n");
	}
}

bool specific_date(char str[], int *year, int *month, int *day)
{	
	int i;
	int a=1000, b=10, c=10;
	for(i = 6; i<10; i++)
	{		
		*year+= (str[i]-48)*a;
		a/=10;
	}
	for(i = 10; i<12; i++)
	{		
		*month+= (str[i]-48)*b;
		b/=10;
	}	
	for(i = 12; i<14; i++)
	{		
		*day+= (str[i]-48)*c;
		c/=10;
	}
	if(*month > 12)
	{
		return false;
	}
	else
		if((*year%4==0 && *year%100!=0) || *year%400==0)
		{
			if(*month == 2)
				if(*day > 29)
					return false;
			else
				if(*month == 1||*month == 3||*month == 5||*month == 7||*month == 8||*month == 10||*month == 12)
				{
					if(*day > 31)
						return false;
				}
				else
					if(*day > 30)
						return false;
		}
		else
			if(*month == 2)
				if(*day > 28)
					return false;
			else
				if(*month == 1||*month == 3||*month == 5||*month == 7||*month == 8||*month == 10||*month == 12)
				{
					if(*day > 31)
						return false;
				}
				else
					if(*day > 30)
						return false;		
	return true;
}

bool is_lawful(char str[])
{
	char diqu[128];
	int year = 0;
	int month = 0;
	int day = 0;
	// 1.位数是18位
	if(is_long(str) != true)
	{
		return false;
	}
	else
	// 2.前17位的字符必须是数字字符；第18位必须是0-9或者x
		if(is_num(str) != true)
		{
			return false;
		}
	
	// 3.前0~5位，必须是合法的地址码《地区码.txt》
	if(address(str, diqu) == false)
	{
		return false;
	}
	else
	{
		printf("%s\n", diqu);
	}
	// 4.第6~13位获取生日信息，判断是否合法
	if(specific_date(str, &year, &month, &day))
	{
		printf("%d年%d月%d日\n", year, month, day);
	}
	else
	{
		return false;
	}
	// 5.第14~16位，不用判断合法，可以通过最后一位得到性别信息
	Gender(str);
	// 6.第17位是检验码。
	if(Judge(str) == false)
	{
		return false;
	}
	else		
		return true;
}

bool address(char str[], char diqu[])
{
	long int chongqing[] = {500101,500102,500103,500104,500105,500106,500107,500108,
							500109,500110,500110,500111,500111,500112,500113,500114,
							500115,500116,500117,500118,500119,500120,500151,500152,
							500153,500154,500155,500156,500229,500230,500231,500233,
							500235,500236,500237,500238,500240,500241,500242,500243};
	char *chongqing_diqu[] = {"万州区","涪陵区","渝中区","大渡口区","江北区","沙坪坝区","九龙坡区","南岸区",
							"北碚区","綦江区","万盛区","大足区","双桥区","渝北区","巴南区","黔江区",
							"长寿区","江津区","合川区","永川区","南川区","璧山区","铜梁区","潼南区",
							"荣昌区","开州区","梁平区","武隆区","城口县","丰都县","垫江县","忠县",
							"云阳县","奉节县","巫山县","巫溪县","石柱县","秀山县","酉阳县","彭水县"};
	char *name = malloc(sizeof(char));
	char ch[6] = {0};
	strncpy(ch, str, 6);
	long int diqu_num = atoi(ch);
	for(int i=0; i<40; i++)
	{
		if(diqu_num == chongqing[i])
		{
			sprintf(diqu, "%s%s", "重庆市", chongqing_diqu[i]);
		}
	}
	if(strlen(diqu)==0)
		return false;
	else
		return true;
	
}

bool is_num(char str[])   
{      
	int flag = 0;                   
	for(int i=0; i<17; i++)
	{                     
		if((str[i]-48)>'9' && (str[i]-48) <'0')
			flag = 1;
	}
	if(flag == 0)
		return true;
	else
		return false;
}                         
                          
bool is_long(char str[])  
{                         
	if(strlen(str) == 18) 
		return true;     
	else
		return false;
}

bool Judge(char str[])
{
	int i;
	int num = 0;
	int age = 0;
	int flag = 0;
	//5 0 0  2 4 0 1 9 9 6 0 5 0  2 1 1 7 2
	//7 9 10 5 8 4 2 1 6 3 7 9 10 5 8 4 2
	int m[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
	for(i = 0; i<17; i++)
	{
		num+=(str[i]-48)*m[i];
	}	
	age = num%11;
	switch(age)
	{
		case 0:if(str[17] == '1') flag = 1;break;
		case 1:if(str[17] == '0') flag = 1;break;
		case 2:if(str[17] == 'X') flag = 1;break;
		case 3:if(str[17] == '9') flag = 1;break;
		case 4:if(str[17] == '8') flag = 1;break;
		case 5:if(str[17] == '7') flag = 1;break;
		case 6:if(str[17] == '6') flag = 1;break;
		case 7:if(str[17] == '5') flag = 1;break;
		case 8:if(str[17] == '4') flag = 1;break;
		case 9:if(str[17] == '3') flag = 1;break;
		case 10:if(str[17] == '2') flag = 1;break;	
	}
	if(flag == 1)
		return true;
	else
		return false;
}

int main()
{
	char str[128];
	printf("输入需要检测的身份证号码\n");
	scanf("%s", str);
	if(is_lawful(str))
	{
		printf("身份证号码合法\n");
	}
	else
	{
		printf("身份证号码不合法\n");
	}
}