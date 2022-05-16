#ifndef MINIRT_H
# define MINIRT_H

# include <sys/types.h>
# include "../mlx/mlx.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				winwidth;
	int				winlength;
}					t_data;

typedef struct s_var
{
	void	**struc;
	t_data	*data;
}				t_var;

typedef struct s_a
{
	double			ratio;
	unsigned char	rgb[3];
	int				exist;
}				t_a;

typedef struct s_c
{
	double	xyz[3];
	double	way[3];
	int		fov;
	int		exist;
}				t_c;

typedef struct s_l
{
	double			xyz[3];
	double			ratio;
	unsigned char	rgb[3];
	int				exist;
}				t_l;

typedef struct s_sp
{
	double			xyz[3];
	double			height;
	unsigned char	rgb[3];
	int				exist;
}				t_sp;

typedef struct s_pl
{
	double			xyz[3];
	double			way[3];
	unsigned char	rgb[3];
	int				exist;
}				t_pl;

typedef struct s_cy
{
	double			xyz[3];
	double			way[3];
	double			height;
	double			width;
	unsigned char	rgb[3];
	int				exist;
}				t_cy;

//PRINT
void	print_everything(t_var *p);

//FREE
void	free_struc(t_var *p);

//FT_JOIN
char	*ft_joinc(char *s1, char c);
char	*ft_joins(char *a, char *b);
char	*ft_joinsfree(char *a, char *b);

//FT_SPLIT
char	**ft_split(char const *s, char c);
char	**ft_split2(char const *s, char c, char c1);

//GET_NEXT_LINE
int		ft_strlen(char *a);
int		ft_strlenn(char *a);
char	*ft_join(char *a, char *b);
int		ft_search(char *a, char c);
void	ft_cut(char *a);
char	*ft_free(char *a);
char	*get_next_line(int fd);

//WINDOWS PARAMETERS
int		windowsop(t_var *p);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
