#ifndef PROJET_C_PART1_H
#define PROJET_C_PART1_H

typedef struct s_d_cell
{
    int value;
    int level;
    struct s_d_cell **next;
} t_d_cell, *p_d_cell;

typedef struct s_d_list
{
    int max_level;
    t_d_cell **heads;
} t_d_list, *p_d_list;

p_d_cell create_cell(int value, int level);
p_d_list create_empty_list(int max_level);
void insert_at_head(p_d_list list, p_d_cell new_cell);
void print_cells_at_level(p_d_list list, int level);
void print_all_levels(p_d_list list);
void print_all_levels_aligned(p_d_list list);
void insertSorted(p_d_list list, p_d_cell cell);


#endif //PROJET_C_PART1_H
