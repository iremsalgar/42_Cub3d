#include "cub3d.h"

void    ft_find(t_data *data)
{
    int i;
    int j;

    i = -1;
    while (data->map[++i])
    {
        j = 0;
        while (data->map[i][j])
        {  
            if (data->map[i][j] == 'N' || data->map[i][j] == 'W' || data->map[i][j] == 'E' || data->map[i][j] == 'S')
                break ;
            if (data->map[i][j] == 'F' || data->map[i][j] == 'C' || data->map[i][j] == '\n')
                break ;
            if (data->map[i][j] == ' ' || data->map[i][j] == '1' || data->map[i][j] == '0')
            {
                while ((data->map[i][j] != '1' || data->map[i][j] != '0') && data->map[i][j])
                {
                    if (data->map[i][j] == '1' || data->map[i][j] == '0')
                    {
                        data->first_line = i;
                        return ;
                    }
                    j++;
                }
            }
        }
    }
}
