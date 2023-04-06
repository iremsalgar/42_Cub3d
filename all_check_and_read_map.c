#include "cub3d.h"

void    ft_check_have_map(t_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (data->map[j] && data->map[j][0] != '1')
        j++;
    if (data->map[j] == 0)
    {
        printf("Map Error!\n");
        ft_clear(data);
    }
}

void    ft_read_map(t_data *data, char *cubfile)
{
    int     i;
    int     fd;
    char    *line;

    i = -1;
    fd = open(cubfile, O_RDONLY);
    data->map = malloc(10000);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        data->map[++i] = ft_strdup(line);
        free(line);
    }
    data->map[i + 1] = 0;
}

int ft_len(char **map)
{
    int j;
    int i;
    int max;

    j = 0;
    while (map[j] && map[j][0] != '1')
        j++;
    max = 0;
    while (map[j])
    {
        i = 0;
        while (map[j][i])
            i++;
        if (i > max)
            max = i;
        j++;
    }
    return (max);
}

void    ft_addjust2(t_data *data)
{
    int len;
    int j;
    int i;

    j =  data->first_line;
    while (data->map[j])
    {
        if (data->map[j][0] == '\n')
        {
            i = 0;
            len = ft_len(data->map);
            data->map[j] = (char *)malloc(sizeof(len + 1));
            while (i <= len)
                data->map[j][i++] = '1';
            data->map[j][i] = '\0';
        }
        j++;
    }
}

void    ft_adjust(t_data *data)
{
    int i;
    int j;

    i = 0;
    j = data->first_line;
    while (data->map[j])
    {
        i = -1;
        while (data->map[j][++i])
        {
            if (data->map[j][i] == ' ')
                data->map[j][i] = '1';
        }
        j++;
    }
    ft_addjust2(data);
}

void    ft_all_check_and_read_map(t_data *data, char *map)
{
    if (ft_check_cub(map))
    {
        free(data);
        printf("Extension Wrong!\n");
    }
    ft_read_map(data, map);
    ft_check_have_map(data);
    ft_find(data);
    ft_check_wall(data);
    ft_check_map(data);
    ft_check_for_long(data);
    ft_check_once_to_map(data);
    ft_check_file(data);
    ft_adjust(data);
}