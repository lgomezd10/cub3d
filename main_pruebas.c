#include "cub3d.h"


int main(void)
{
    char **split;
    int i;

    split = ft_split_set("abbaPEPEaPIPIbaa", "ab");
    i = 0;
    while (split[i])
    {
        printf("%d %s\n", i, split[i]);
        i++;
    }
    printf("fin\n");
}