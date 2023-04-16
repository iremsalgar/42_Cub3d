#include "../cub3d.h"

void    ft_clear(t_data *data)
{
    int i;

    (void)data;
    i = -1;
    while (data->map[++i])
        free(data->map[i]);
    free(data->map);
    free(data);
    exit(0);
}