#include "main.h"

int main(int argc, char **argv)
{
    int interactiveornon;

	interactiveornon = check_arguments_and_terminal(argc, argv);
    if (interactiveornon == 1)
	{
		main_interactive();
	} else if (interactiveornon == 0)
	{
		main_non_interactive(argc, argv);
	}
    else
    {
        printf("Error\n");
    }
	return 0;
}