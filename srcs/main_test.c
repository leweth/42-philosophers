// #include "../includes/philo.h"
#include <stdbool.h>

/* void	*thread_subroutine(void *arg)
{
	int	index;
	char	*str;

	index = *(int *)arg;
	pthread_mutex_lock();
	pthread_mutex_unlock();
	if (index == 0)
		str = "OPS";
	else
		str = "Foo";
	printf("We got into the thread!\n");
	int start = 100;
	while (start--)
		printf("%s\n", str);
	printf("END?%d\n", index);
	return NULL;
}

int	main(int argc, char **argv)
{
	pthread_t	thread_id[2];
	// int i[2] = {0, 1};
	int	j = 0;
	int	i = 0;

	(void) argc;
	(void) argv;
	while (i < 2)
	{
		// pthread_create(thread_id + j, NULL, thread_subroutine, i + j);
		pthread_create(thread_id + i, NULL, thread_subroutine, i);
		i++;
	}
	for (int i=0; i < 44; i++)
		printf("The usual stuff\n");
	pthread_join(thread_id[0], NULL);
	pthread_join(thread_id[1], NULL);
} */
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

long long	extract_time(int *milli_start_time, int *micro_start_time)
{
	struct timeval	tmp;
	int				err;

	err = gettimeofday(&tmp, NULL);
	*milli_start_time = tmp.tv_usec * 1000;
	*micro_start_time = tmp.tv_usec;
	return (err);
}

int main(int argc, char **argv)
{
	int err;

	(void) argc;
	(void) argv;
	/* err = 0;
	uint32_t	ret = ft_atou32(argv[1], &err);
	if (err < 0)
		return (1);
	printf("%u\n", ret); */
	int timo;
	int timo2;

	while (true)
	{
		extract_time(&timo, &timo2);
		// printf("%u\n", timo);
		printf("%d\n", timo2);
	}
}
