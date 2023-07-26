#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INITIAL_STATUS };
	int file_d = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_d)
			: "r" (file_d));

	if (ac == 2)
	{
		file_d = open(av[1], O_RDONLY);
		if (file_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				eputs_(av[0]);
				eputs_(": 0: Can't open ");
				eputs_(av[1]);
				eputchar_('\n');
				eputchar_(FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_filedescripter = file_d;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
