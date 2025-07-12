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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int check_args(char *str)
{
    int i = 0;
    if(str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if(!ft_isdigit(str[i]))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

long	ft_atoi(char *str)
{
	long	result;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	result = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > 2147483647)
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
