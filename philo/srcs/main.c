#include "philo.h"

int main(int argc, char **argv)
{
	t_philo ph;

	if (ph_init(argc, argv, &ph))
		return (1);
	ph_main(&ph);
	ph_end(&ph);
}