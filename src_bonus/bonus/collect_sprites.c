#include "../../includes/bonus.h"

void delete_sprite(t_game *data, int x, int y)
{
    t_sprite *sp;
    t_sprite *found;

    sp = data->sprites.begin;
    found = 0;
    while (sp && !found)
    {
        
        if ((int)sp->pos.x == x && (int)sp->pos.y == y)
        {
            found = sp;
            if (sp->next)
                sp->next->pre = sp->pre;
            else
                data->sprites.end = sp->pre;
            if (sp->pre)
                sp->pre->next = sp->next;
            else
                data->sprites.begin = sp->next;
            data->sprites.size--;

        }
        sp = sp->next;
    }
    if (found)
        free(found);
    else
        handle_error(data, "Not found sprite");
}

void load_next_level(t_game *data)
{
    int level;
    int levels;
    char **maps;

    level = data->bonus.level;
    levels = data->bonus.levels;
    maps = data->bonus.maps;
    data->bonus.end = 1;
    if (levels - 1 > level)
    {
        level++;
        check_file(data, maps[level]);
        free_components(data);
        data = (t_game *)ft_calloc(sizeof(t_game), 1);
        data->bonus.level = level;
        data->bonus.levels = levels;
        data->bonus.maps = maps;
        load_file(data, data->bonus.maps[data->bonus.level]);
        check_wall_closed(data);
        run_game(data);
    }
    else
        game_over(data);
}

void collect_sprite(t_game *data, int x, int y)
{
    t_point_int start;
    t_point_int end;
    data->table.table[y][x] = '0';
    delete_sprite(data, x, y);
    data->bonus.points += data->bonus.add_points;
    if (!data->sprites.size)
    {
        data->bonus.end = 1;
        set_point_int(&start, 0, 0);
        set_point_int(&end, data->width, data->height);
        draw_rectangle(data, start, end, color_int(0, 0, 0));
        printf("levels: %d level: %d\n", data->bonus.levels, data->bonus.level);
        if (data->bonus.levels - 1 > data->bonus.level)
            copy_img(data, start, end, NextLevel);
        else
            copy_img(data, start, end, GameOver);
    }
}

void init_collect_sp(t_game *data)
{
    t_bonus *bonus;

	bonus = &data->bonus;
	bonus->points = 0;
	bonus->lives = 1;
	bonus->len_bar = (data->width / 4) - 10;
	bonus->unit_bar = bonus->len_bar / POINTS;
    bonus->add_points = POINTS / data->sprites.size;
}