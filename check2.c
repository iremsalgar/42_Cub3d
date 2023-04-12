#include "cub3d.h"

int ft_check_last(t_data *data, char *s, int j)
{
    int i;
    int k;

    i = 0;
    k = 0;
    if (data->map[j + 1] == 0)
        return (0);
    while (s[i])
        i++;
    while (data->map[j + 1][k])
        k++;
    if (i != k)
        return (1);
    return (0);
}

void    ft_control_last_lines(t_data *data, char *s, int j)
{
    int i;
    int k;

    i = ft_strlen(s) - 1;
    k = ft_strlen(data->map[j + 1]) - 1;
    if (i > k)
    {
        while (i != k)
        {
            if (s[k] != '1' && s[k] != '\n')
            {
                printf("Error!\n");
                ft_clear(data);
            }
            k++;
        }
    }
    else
    {
        while (k != i)
        {
            if (data->map[j + 1][i] != '1' && data->map[j + 1][i] != '\n')
            {
                printf("Error!\n");
                ft_clear(data);
            }
            i++;
        }
    }
}

void ft_control_last_lines2(t_data *data)
{
    int last_line = data->last_line;
    int i;
    int j;

    j = data->first_line;
    while (j < last_line)
    {
        i = 0;
        while (data->map[j][i] && i < strlen(data->map[j]))
        {
            if (data->map[j][i] == '0')
            {
                if (data->map[j][i - 1] == ' ' || data->map[j][i + 1] == ' ' || data->map[j - 1][i] == ' ' || data->map[j + 1][i] == ' ')
                {
                    printf("Wall Error!\n");
                    ft_clear(data);
                }
            }
            i++;
        }
        j++;
    }
}

void    ft_check_for_long(t_data *data)
{
    int i;
    int j;

    i = 0;
    j = data->first_line - 1;
    while (++j < data->last_line && data->map[j][0] != '\n')
        if (ft_check_last(data, data->map[j], j))
            ft_control_last_lines(data, data->map[j], j);
    ft_control_last_lines2(data);
}