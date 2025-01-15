#include "minishell.h"

int main(void)
{
    char *res;
    printf("TEST Minishell\n");
    int x= 123456;

    res = ft_itoa(x);
    printf("Test Libft: %s\n", res);
    return (0);
}
