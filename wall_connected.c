#include "cub3d.h"

int is_connected(t_file *data, int y, int x, int up)
{
	char **table;
	int connected;
	int add;
	
	table = data->table->table;
	connected = y == 0;
	add = -1;
	if (!up)
	{
		connected = y == data->table->rows - 1;
		add = 1;
	}
	if (!connected)
	{
		if (x > 0)
			connected = table[y + add][x - 1] == '1';
		connected = connected || table[y + add][x] == '1';
		if (x < data->table->cols - 1)
			connected = connected || table[y + add][x + 1] == '1';
	}
	return (connected);
}

int check_connected(t_file *data, int y, int x, int right)
{
	char **table;
	int conn_up;
	int conn_down;
	int i;
	int add;

	conn_up = 0;
	conn_down = 0;
	table = data->table->table;
	i = x;
	add = 1;
	if (!right)
		add = -1;
	while ((!conn_down || !conn_up)  && i < data->table->cols && i >= 0 && table[y][i] == '1')
	{
		if (is_connected(data, y, i, 1))
			conn_up = 1;
		if (is_connected(data, y, i, 0))
			conn_down = 1;
		i += add;
	}	
	if (!conn_up || !conn_down)
	{
		printf("muros no conectados en fila %d\n", y);
		ft_errors("muros no conectados");
	}
	return (i);
}

int check_space(t_file *data, int y, int x)
{
	int up;
	int right;
	int down;
	int left;
	char **table;

	table = data->table->table;
	up = y == 0 || ft_strchr("*1", table[y - 1][x]);
	down = y == data->table->rows - 1 || ft_strchr(" 1", table[y + 1][x]);
	left = x == 0 || ft_strchr("*1", table[y][x - 1]);
	right = x == data->table->cols - 1 || ft_strchr(" 1", table[y][x + 1]);
	if (!up || !down || !left || !right)
	{
		printf("espacio en y: %d x: %d %d %d %d %d\n", y, x, up, down, left, right);
		ft_errors("Espacio dentro del muro");
	}
	return (1);
}

int through_space(t_file *data, int y, int x)
{
	char **table;

	table = data->table->table;
	if (x == 0 || ft_strchr("*1", table[y][x - 1]))
	{
		if (x == data->table->cols - 1 || ft_strchr(" 1", table[y][x + 1]))
		{
			while (table[y][x] == ' ' && check_space(data, y, x))
				table[y][x++] = '*';
			if (x < data->table->cols && table[y][x] != '1')
				ft_errors("el mapa tiene el muro abierto");
			else if (x < data->table->cols && table[y][x] == '1')
				x = check_connected(data, y, x, 1);
			return (x);
		}
	}
	printf("Error en y: %d x: %d\n", y, x);
	ft_errors("No se permiten los espacios entre muros");
	return (-1);
}

void check_conexions(t_file *data, int y, int x)
{
	char **table;

	table = data->table->table;

	if (ft_strchr("NSEW", table[y][x]))
	{
		load_gamer(data, y, x, table[y][x]);
		table[y][x] = '0';
	}
	if (x == 0 && table[y][x] == '1')
		check_connected(data, y, x, 1);
	if (x == data->table->cols - 1 && table[y][x] == '1')
		check_connected(data, y, x, 0);
	if (x > 0 && table[y][x] == ' ' && table[y][x - 1] == '1')
		check_connected(data, y, x - 1, 0);
}

void wall_connected(t_file *data)
{
	char **table;
	int i;
	int j;

	table = data->table->table;
	i = 0;
	while (i < data->table->rows)
	{
		j = 0;
		while (j < data->table->cols)
		{
			check_conexions(data, i, j);
			if (table[i][j] == ' ')
				j = through_space(data, i, j);
			else
			{
				if (table[i][j] != '1' && (i == 0 || j == 0 || i == data->table->rows - 1 || j == data->table->cols - 1))
					ft_errors("El muro no cerrado 2");
				j++;
			}
		}
		i++;
	}
}
