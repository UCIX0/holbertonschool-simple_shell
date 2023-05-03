#include "main.h"

int check_arguments_and_terminal(void)
{
		if (isatty(STDIN_FILENO))
		{
			return (0);
		}
		return (1);
	return (-1);
}

int main(int argc, char **arg)
{
	int interactiveornon;
	argc ++;
	interactiveornon = check_arguments_and_terminal();
	if (interactiveornon == 0)
	{
		main_interactive();
	} else if (interactiveornon == 1)
	{
		main_non_interactive(arg[0]);
	}
	else
	{
		printf("Error\n");
	}
	return 0;
}