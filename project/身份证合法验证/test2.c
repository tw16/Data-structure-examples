/*判断身份证合法性*/
/*500240199605021172*/
#include <stdio.h>
#include <stdbool.h>

bool is_lawful(char *ID)
{
	//1.位数是18位
	//2.前17位的字符必须是数字字符；第18位必须是0-9或者x
	//3.前0~5位，必须是合法的地址码《地区码.txt》
	//4.第6~13位获取生日信息，判断是否合法
	//5.第14~16位，不用判断合法，可以通过最后一位得到性别信息
	//6.第17位是检验码。
}

int main(int argc, char const *argv[])
{
	char ID[128];
	scanf("%s", ID);

	if(is_lawful(ID))
	{
		printf("合法\n");
	}
	else
	{
		printf("不合法\n");
	}

	return 0;
}


	// char ID[18];
	// int cf[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
	// int num = 0;
	// for (int i = 0; i < 17; ++i)
	// {
	// 	num += (ID[i]-48)*cf[i];
	// }