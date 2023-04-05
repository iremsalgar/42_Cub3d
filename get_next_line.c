#include "cub3d.h"

int	getline2(int fd, t_list *y)
{
	char	*str;
	int		rd;

	rd = 1;
	str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str)
		return (0);
	while (rd > 0 && ft_chk(y->x, 1, '\n') == 1)
	{
		rd = read(fd, str, BUFFER_SIZE);
		if (rd == -1)
		{
			free(str);
			return (0);
		}
		str[rd] = '\0';
		y->x = ft_strjoin(y->x, str);
	}
	free(str);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*y;
	t_list			*tmp;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(y);
		return (0);
	}
	if (!y)
		y = ft_lstnew();
	if (!getline2(fd, y))
		return (0);
	line = ft_controller (y->x, '\n', y);
	tmp = y->next;
	free(y);
	y = tmp;
	if (!*line)
	{
		free(line);
		line = (void *)0;
	}
	return (line);
}

t_list	*ft_lstnew(void)

{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == (void *)0)
		return (0);
	new->x = (void *)0;
	new->next = 0;
	return (new);
}