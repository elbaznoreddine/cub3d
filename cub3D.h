#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
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
	void			*mlx;
	void			*win;
	void			*player;
	double			direction;
	unsigned int	ceil;
	unsigned int	floor;
	void			*img_north;
	void			*img_south;
	void			*img_east;
	void			*img_west;
	t_map			*map;
	t_config		*config;
}					t_game;
// utils function
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char *s, unsigned int index, size_t bytes);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
// parsing map
int		ft_check_map_extension(char *exten);
int		init_game(t_game **game);
int		parse_complete_map_file(t_game *game, char *map_filename);
char	*get_next_line(int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_game(t_game *game);
void	free_config(t_config *config);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	**ft_split(char const *s, char c);
void	free_split(char **split);
int		ft_atoi(const char *str);
void	print_all_map(t_game *game);
int		setup_empty_config(t_config *config);
int		process_config_line(t_game *game, char *line, int *element_type,
			char **first_map_line);
int		check_config_completeness(t_config *config);
int		read_entire_map_content(t_game *game, int fd, char *first_map_line);
int		count_players_and_validate_chars(t_game *game, t_map *map);
int		is_border_position(int i, int j, t_map *map);
int		has_invalid_border_character(char c);
int		space_touches_empty_cell(t_map *map, int i, int j);
int		store_floor_color(t_game *game, char *color_string, t_config *config);
int		store_ceiling_color(t_game *game, char *color_string, t_config *config);
int		are_rgb_values_valid(char **rgb_array);
char	*extract_file_path(char *line);
int		config_element_already_exists(t_config *config, int element_type);
int		save_config_element(char *element_value, int element_type,
			t_config *config, t_game *game);
int		can_open_texture_file(char *file_path);

#endif