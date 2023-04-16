#include "../cub3d.h"

void    ft_read_map(t_data *data, char *cubfile, t_index *index)
{
    int     i;
    int     fd;
    char    *line;
    int     line_count;
    int		n_tex;

    n_tex = 0;
    i = -1;
    fd = open(cubfile, O_RDONLY);
    line_count = ft_get_line_count(cubfile);
    data->map = malloc(sizeof(char *) * (line_count + 1));
    while (1)
    {
        line = get_next_line(fd);
        if (line)
        {
            data->map[++i] = ft_strdup(line);
            line = ft_strtrim(line, "\n");
            if(line[0] != '\0' && line[0] != '1' && line[0] != '0' && line[0] != '2' && line[0] != ' ')
            {
                ft_check_text(data, line, n_tex, index);
                free(line);
            }
        }
        else
            break ;
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
    t_index *index;
    index = calloc(1, sizeof(t_index));
    if (ft_check_cub(map))
    {
        free(data);
        printf("Extension Wrong!\n");
    }
    ft_read_map(data, map, index);
    ft_check_have_map(data);
    ft_find(data);
    ft_check_wall(data);
    ft_check_map(data);
    ft_check_for_long(data);
    ft_check_once_to_map(data);
    ft_check_file(data);
    ft_adjust(data);
}