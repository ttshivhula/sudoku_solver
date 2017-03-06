/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoku.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <ttshivhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:53:57 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/03/05 22:53:10 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int     solve(int **row, int mrow, int col);

void    ft_putstr(char *str)
{
    int i;

    i = -1;
    while (str[++i])
        write(1, &str[i], 1);
}

void    ft_putnbr(int num)
{
    char c;

    c = num + 48;
    write(1, &c, 1);
}

void    print_row(int   **row)
{
    int i;
    int j;
    
    ft_putstr("x-----x-----x-----x\n");
    i = -1;
    while (++i < 9)
    {
        j = -1;
        while (++j < 9)
        {
            if(j == 0)
                ft_putstr("|");
            ft_putnbr(row[i][j]);
            ft_putstr("|");
        }
        if (i == 2 || i == 5)
            ft_putstr("\nx-----x-----x-----x\n");
        else
            ft_putstr("\n");
    }
    ft_putstr("x-----x-----x-----x\n");
    
}

int    sudoku_err(void)
{
    ft_putstr("Error\n");
    return (0);
}

int     is_valid_move(int  move, int **row, int current_row, int position)
{
    int     index;
    int     row_s;
    int     col_s;
    
    index = -1;
    row_s = (current_row / 3) * 3;
    col_s = (position / 3) * 3;
    while (++index < 9)
    {
        if (row[current_row][index] == move)
            return (0);
        if (row[index][position] == move)
            return (0);
        if (row[row_s + (index % 3)][col_s + (index / 3)] == move)
            return (0);
    }
    return (1);
}

int     **init_row(void)
{
    int i;
    int j;
    int **row;

    row = (int **)malloc(sizeof(int *) * 9);
    i = 0;
    while (i < 9)
    {   
        row[i] = (int *)malloc(sizeof(int) * 9);
        j = 0;
        while (j < 9)
        {
            row[i][j] = 0;
            j++;
        }
        i++;
    }
    return (row);
}

void    free_row(int **row)
{
    int i;

    i = -1;
    while (++i < 9)
    {
        free(row[i]);
    }
    free(row);
}

int     activate_row(int **row, int size, char **str)
{   
    int i;
    int j;
    
    i = 0;
    while (i < size - 1)
    {
        j = 0;
        while (str[i + 1][j])
        {
            if (str[i + 1][j] == 46)
                row[i][j] = 0;
            else if (str[i + 1][j] >= '0' && str[i + 1][j] <= '9')
                if (is_valid_move(str[i + 1][j] - 48, row, i, j))
                    row[i][j] = str[i + 1][j] - 48;
                else
                    return (sudoku_err());
            j++;
        }
        if (j != 9)
            return (sudoku_err());
        i++;
    }
    return (1);
}

int     try_play(int **row, int mrow, int col)
{
    int i;
    
    i = -1;
    while (++i < 9)
    {
        if (is_valid_move(i + 1, row, mrow, col))
        {
            row[mrow][col] = i + 1;
            if ((col + 1) < 9)
                if (solve(row, mrow, col + 1))
                    return (1);
                else
                    row[mrow][col] = 0;
            else if ((mrow + 1) < 9)
                if (solve(row, mrow + 1, 0))
                    return (1);
                else
                    row[mrow][col] = 0;
            else
                return (1);
        }
    }
    return (0);
}

int     solve(int **row, int mrow, int col)
{
    if (!(mrow < 9 && col < 9))
        return (1);
    if (row[mrow][col] != 0)
    {
        if ((col + 1) < 9)
            return (solve(row, mrow, col + 1));
        else if ((mrow + 1) < 9)
            return (solve(row, mrow + 1, 0));
        else
            return (1);
    }
    else 
        return (try_play(row, mrow, col));
    return (0);
}

int     main(int argc, char **argv)
{
    int     **row;

    row = init_row();
    if (argc != 10)
    {
        sudoku_err();
        return (0);
    }
    if (activate_row(row, argc, argv))
    {
        solve(row, 0, 0);
        print_row(row);
    }
    free_row(row);
    return (0);
}
