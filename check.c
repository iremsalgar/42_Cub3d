#include "cub3d.h"

int ft_check_cub(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    i--;
    if (s[i] != 'b' && s[i - 1] != 'u' && s[i - 2] != 'c' && s[i - 3] != '.')
        return (1);
    return (0);
}

void    ft_check_map_next(t_data *data)
{
    int j;
    int k;

    j = data->first_line;
    k = 0;
    while (j >= 0)
    {
        if (data->map[j][0] == 'N' || data->map[j][0] == 'S' || \
            data->map[j][0] == 'W' || data->map[j][0] == 'E' || \
            data->map[j][0] == 'F' || data->map[j][0] == 'C')
            k++;
        j--;
    }
    if (k != 6)
    {
        printf("Map Error!\n");
        ft_clear(data);
    }
}

void    ft_check_map(t_data *data)
{
    int i;
    int j;

    j = data->first_line;
    while (j < data->last_line)
    {
        i = -1;
        while (data->map[j][++i] && i < strlen(data->map[j]))
        {
            if (data->map[j][i] != '1' && data->map[j][i] != '0' && \
            data->map[j][i] != 'N' && data->map[j][i] != 'S' && \
            data->map[j][i] != 'W' && data->map[j][i] != 'E' && \
            data->map[j][i] != '\n'&& data->map[j][i] != ' ')
            {
                printf("Wrong Map!\n");
                ft_clear(data);
            }
        }
        j++;
    }
    ft_check_map_next(data);
}

void    ft_check_wall_next(t_data *data)
{
    int i;
    int j;

    j = data->first_line;
    while (j < data->last_line)
    {
        i = 0;
        while (data->map[j][i] == ' ' && (i < strlen(data->map[j])))
         {
            i++;
         }
        if (data->map[j][i] != '1')
        {
            printf("Wrong Map!");
            ft_clear(data);
        }
        j++;
    }
}

void    ft_check_wall(t_data *data)
{
    int i;
    int j;

    i = data->first_line;
    j = -1;
    while (data->map[i][++j])
    {
        if ((data->map[i][j] != '1' && data->map[i][j] != ' ') && data->map[i][j] != 'N' && data->map[i][j] == '0' && data->map[i][j] != '\n')
        {
            printf("Wrong Map!\n");
            ft_clear(data);
        }
    }
    data->last_line = ft_get_line_count(MAP);
    i = data->first_line;
    j = -1;
    while (data->map[i][++j])
    {
        if (data->map[i][j] != '1' && data->map[i][j] != '\n' && data->map[i][j] != '\0' && data->map[i][j] != ' ')
        {
            printf("Wrong Map!");
            ft_clear(data);
        }
    }
    ft_check_wall_next(data);
}