#include "philo.h"

long ft_gettime()
{
    struct timeval tv;
    long ms;
    gettimeofday(&tv,NULL);
    ms = (tv.tv_sec * 1000) + (tv.tv_usec/1000);
    return (ms);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = ft_gettime();
	while ((ft_gettime() - start) < milliseconds)
		usleep(500);
	return (0);
}