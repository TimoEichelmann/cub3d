/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:46:59 by snegi             #+#    #+#             */
/*   Updated: 2024/07/18 15:01:50 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include "./libft/libft.h"
# include "nextline/get_next_line.h"
# include "print/ft_printf.h"

# include <math.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>

# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 901
# define M 1000000.0

typedef struct s_dda
{
	int		x;
	int		mapx;
	int		mapy;
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

typedef struct s_image
{
	void	*img;
	int		*data;
	int		bpp;
	int		size_l;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpb;
	int			sl;
	t_image		*imgs[4];
	int			e;
}		t_data;

typedef struct s_cubdata
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	**floor_color;
	char	**ceiling_color;
	char	**map;
	char	firstposition;
	double	p_x;
	double	p_y;
	int		map_height;
}	t_cubdata;

typedef struct s_player
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
	double		move_speed;
	double		rot_speed;
	int			move_f;
	int			move_b;
	int			rotate_l;
	int			rotate_r;
	int			side;
	t_data		*data;
	t_cubdata	*cubdata;
}	t_player;

int			ft_free(void *pl);
void		err1(char *str, t_cubdata *cubdata);
void		err(char *str);
char		*ft_strdup1(char *s);
void		check_firstlastline(t_cubdata *cubdata, int i);
char		check_mapdata(char *li, char *temp);
void		checkerrormap(t_cubdata *cubdata);
void		store_images(t_data *data, t_cubdata *cubdata);
void		free_cubdata(t_cubdata *cubdata);
int			ft_atoi1(const char *p);
int			algorithm(void *p);
int			cub3d(t_cubdata *cdata);
void		ft_pxl_pos(t_data *img, int x, int y, int color);
void		reset_image(t_data *img, t_player *p, int ind);
int			get_color(char **color);
t_player	*start_values(t_cubdata *d);
void		dda(t_player *p);
void		paint_wall(t_dda *dda, t_player *p);
int			movement(int keycode, void *player);
void		update(t_player *p);
void		checkpatherror(t_cubdata *cubdata);
void		checkcolorerror(t_cubdata *cubdata);
int			check_case(t_player *p);
void		init_dda(t_player *p, t_dda *dda, int x);

#endif
