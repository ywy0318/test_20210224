#include "stdio.h"
int main()
{

	printf("\033[字背景颜色;字体颜色m 字符串 \033[0m" );
printf("\n");
printf("\033[31mThis text is red \033[0mThis text has default color\n");
printf("\n");
printf("\033[31;43mThis text is red with yellow background \033[0mThis text has default color\n");
printf("\n");
printf("\033[1m\033[45;33m HELLO_WORLD \033[0m\n");
printf("\n");

	return 0;

}
