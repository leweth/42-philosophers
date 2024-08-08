#include "../includes/philo.h"

int main(int argc, char **argv)
{
	int err;

	(void) argc;
	err = 0;
	uint32_t	ret = ft_atou32(argv[1], &err);
	if (err < 0)
		return (1);
	printf("%u\n", ret);
}
