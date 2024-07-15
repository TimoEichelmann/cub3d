/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:46:59 by snegi             #+#    #+#             */
/*   Updated: 2024/07/15 13:42:34 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
#include "./libft/libft.h"
# include "nextline/get_next_line.h"
# include "print/ft_printf.h"
# include <math.h>

# include <unistd.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>

#define	SCREEN_WIDTH 900
#define SCREEN_HEIGHT 601

typedef	struct s_dda
{
	int	mapx;
	int	mapy;
	double	camx;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deldistx;
	double	deldisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
}	t_dda;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpb;
	int			sl;
	int			endian;
}		t_data;

typedef struct s_cubdata
{
    char *north;
    char *south;
    char *west;
    char *east;
    char **floor_color;
    char **ceiling_color;
    char **map;
    char    firstposition;
    double p_x;
    double p_y;
    int map_height;
}	t_cubdata;

typedef struct	s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef	struct s_player
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		time;
	double		old_time;
	int			end;
	t_data		*data;
	t_cubdata	*cubdata;
}	t_player;

void	err1(char *str, t_cubdata *cubdata);
void	err(char *str);
char	*ft_strdup1(char *s);
void	check_firstlastline(t_cubdata *cubdata, int i);
char	check_mapdata(char *line, char *temp);
void	checkerrormap(t_cubdata *cubdata);
int	key_hook(int keycode, t_data *data);
int	on_destroy(t_data *data);
void    window_create(t_data *data);
void	free_cubdata(t_cubdata *cubdata);
int	ft_atoi1(const char *p);
int	algorithm(t_cubdata *d);
void	draw_verline(t_data *data, int x, int line_height, int side);

#endif
