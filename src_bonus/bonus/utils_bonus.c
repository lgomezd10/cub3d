#include "../../includes/bonus.h"

char	*load_img_bonus(t_game *data, int dir)
{
	char	*str;

	str = 0;
	if (dir == GameOver)
	{
		str = "textures/gameover.xpm";
		check_file(data, str);
	}
	if (dir == NextLevel)
	{
		str = "textures/nextlevel.xpm";
		check_file(data, str);
	}
	if (dir == Life)
	{
		str = "textures/life.xpm";
		check_file(data, str);
	}
	if (dir == Blood)
	{
		str = "textures/blood.xpm";
		check_file(data, str);
	}
	if (dir == Beer)
	{
		str = "textures/beer.xpm";
		check_file(data, str);
	}
	return (str);
}