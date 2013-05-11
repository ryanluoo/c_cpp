/*
Description 

Your task is to write a program that performs a simple form of run-length encoding, as described by the rules below. 

Any sequence of between 2 to 9 identical characters is encoded by two characters. The first character is the length of the sequence, represented by one of the characters 2 through 9. The second character is the value of the repeated character. A sequence of more than 9 identical characters is dealt with by first encoding 9 characters, then the remaining ones. 

Any sequence of characters that does not contain consecutive repetitions of any characters is represented by a 1 character followed by the sequence of characters, terminated with another 1. If a 1 appears as part of the 
sequence, it is escaped with a 1, thus two 1 characters are output. 

Input 

The input consists of letters (both upper- and lower-case), digits, spaces, and punctuation. Every line is terminated with a newline character and no other characters appear in the input. 

Output 

Each line in the input is encoded separately as described above. The newline at the end of each line is not encoded, but is passed directly to the output. 

输入样例
AAAAAABCCCC
12344



输出样例
6A1B14C
11123124



Source

Ulm Local 2004

来源：http://coder.buct.edu.cn/oj/Problem.aspx?pid=1331
*/

#include <cstdio>
#include <cstring>

#define INITIALIZATION 0
#define STARTING	   1
#define CONSECUTIVE    2
#define NONCONSECUTIVE 3

int main()
{
	char s[1024] = "11234467777777777";
	
	unsigned int state = INITIALIZATION;
	unsigned int index = 0;
	unsigned int counter = 0;
	char repChar;

	while (index != strlen(s))
	{
		if (state == INITIALIZATION)
		{
			counter = 1;
			repChar = s[index];
			state   = STARTING;
		} // end of : if(state == INITIALIZATION)
		else if (state == STARTING)
		{
			if (repChar == s[index])
			{				
				counter = 2;
				state = CONSECUTIVE;
			}
			else
			{				
				if (repChar == '1')
					printf("111");
				else
					printf("1%c", repChar);
				repChar = s[index];
				state = NONCONSECUTIVE;
			}
		} // end of : if(state = STARTING)
		else if (state == CONSECUTIVE)
		{
			if (repChar == s[index])
			{
				if(counter == 9)
				{
					printf("9%c", repChar);
					repChar = s[index];
					counter = 1;
					state = STARTING;
				}
				else
				{
					++counter;
				}
			}
			else
			{
				printf("%d%c", counter, repChar);
				counter = 1;
				repChar = s[index];
				state = STARTING;
			}
		} // end of : if (state == CONSECUTIVE)
		else if (state == NONCONSECUTIVE)
		{
			if(repChar == s[index])
			{
				printf("1");
				counter = 2;
				repChar = s[index];
				state = CONSECUTIVE;
			}
			else
			{				
				if(repChar == '1')
					printf("11");
				else
					printf("%c", repChar);
				repChar = s[index];
			}
		} // end of : if (state == NONCONSECUTIVE)
		else
			printf("Error occured!!\n");

		++index;
	}

	//Final Step
	if (state == STARTING)
	{
		if(repChar == '1')
			printf("1111");
		else
			printf("1%c1", repChar);
	}
	else if (state == CONSECUTIVE)
	{
		printf("%d%c", counter, repChar);
	}
	else if (state == NONCONSECUTIVE)
	{
		if (repChar == '1')
			printf("111");
		else
			printf("%c1");
	}

	getchar();
	getchar();
	return 0;
}