#include "philo.h"

bool input_check(int argc, char **argv)
{
	(void)argv;
	if (argc != 5)
		return (false);
	// TODO: argv 数値判定
	return (true);
}

int main(int argc, char **argv)
{
	if (!input_check(argc, argv))
	{
		put_endl_fd(ARG_ERR, STDERR_FILENO);
		return (1);
	}
}