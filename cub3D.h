#ifndef CUB3D_H
#define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <mlx.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_config
{
	char	*floor;
	char	*ceil;
	char	*path_north;
	char	*path_south;
	char	*path_east;
	char	*path_west;
}				t_config;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
}				t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*player;
	void		*img_north;
	void		*img_south;
	void		*img_east;
	void		*img_west;
	t_map		*map;
	t_config	*config;
}				t_game;
// utils function
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char *s, unsigned int index, size_t bytes);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
// parsing map
int	ft_check_map_extension(char *exten);
int	init_game(t_game **game);
int	ft_parse_config(t_game *game, char *map_name);
char	*get_next_line(int fd);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
#endif