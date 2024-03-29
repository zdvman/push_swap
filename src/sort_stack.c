/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:32:47 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/11 16:03:05 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Функция `get_max_steps` вычисляет количество шагов для сортировки        */
/*   методом поразрядной сортировки по битам. Оно определяется как количество */
/*   бит, необходимых для представления максимального индекса в стеке.        */
/*                                                                            */
/*   Параметры:                                                               */
/*   - `stack`: двойной указатель на начало стека.                            */
/*                                                                            */
/*   Работа функции:                                                          */
/*   1. Поиск максимального индекса в стеке.                                  */
/*   2. Вычисление количества шагов (бит), необходимых для представления      */
/*      максимального индекса.                                                */
/*                                                                            */
/*   Возвращаемое значение:                                                   */
/*   - Возвращает количество шагов (целое число).                             */
/*                                                                            */
/* ************************************************************************** */

static int	get_max_steps(t_stack **stack)
{
	t_stack	*head;
	int		max;
	int		max_steps;

	head = *stack;
	max = head->index;
	max_steps = 0;
	while (head)
	{
		if (head->index > max)
			max = head->index;
		head = head->next;
	}
	while ((max >> max_steps) != 0)
		max_steps++;
	return (max_steps);
}

/* ************************************************************************** */
/*                                                                            */
/*   Функция `radix_sort_bits` реализует сортировку стека `a` с использованием*/
/*   алгоритма поразрядной сортировки по битам.                               */
/*   Элементы стека `a` перекладываются в стек `b` в зависимости от значения  */
/*   текущего бита их индекса.                                                */
/*                                                                            */
/*   Параметры:                                                               */
/*   - `stack_a`: двойной указатель на начало стека `a`.                      */
/*   - `stack_b`: двойной указатель на начало стека `b`.                      */
/*   - `fd`: файловый дескриптор для вывода операций.                         */
/*                                                                            */
/*   Работа функции:                                                          */
/*   1. Определение количества шагов для сортировки, равное количеству битов  */
/*      в индексе максимального элемента.                                     */
/*   2. Поразрядное рассмотрение индексов элементов в стеке `a` с помощью     */
/*      цикла, перебирающего биты от младших к старшим.                       */
/*   3. Перекладывание элементов из `a` в `b` и обратно в зависимости от      */
/*      значения текущего бита индекса.                                       */
/*   4. Повторение процедуры для каждого бита.                                */
/*                                                                            */
/*   Возвращаемое значение:                                                   */
/*   - Функция не возвращает значение.                                        */
/*                                                                            */
/* ************************************************************************** */

static void	radix_sort_bits(t_stack **stack_a, t_stack **stack_b, int fd)
{
	int	i;
	int	j;
	int	max_steps;
	int	current_size;

	i = 0;
	max_steps = get_max_steps(stack_a);
	while (i < max_steps)
	{
		j = 0;
		current_size = stack_size(stack_a);
		while (j < current_size)
		{
			if ((((*stack_a)->index >> i) & 1) == 1)
				rotate_ra(stack_a, 1, fd);
			else
				push_pb(stack_a, stack_b, 1, fd);
			j++;
		}
		while (stack_size(stack_b) != 0)
			push_pa(stack_a, stack_b, 1, fd);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Функция `sort_stack` управляет процессом сортировки, выбирая метод       */
/*   сортировки в зависимости от размера стека `a`. Если размер стека меньше  */
/*   или равен трём, используется функция `tiny_sort`. В противном случае     */
/*   используется функция `radix_sort_bits` для более эффективной сортировки. */
/*                                                                            */
/*   Параметры:                                                               */
/*   - `stack_a`: двойной указатель на начало стека `a`.                      */
/*   - `stack_b`: двойной указатель на начало стека `b`.                      */
/*                                                                            */
/*   Работа функции:                                                          */
/*   1. Открытие файла "commands.txt" для записи операций сортировки.         */
/*   2. Вызов соответствующего метода сортировки в зависимости от размера     */
/*   стека.                                                                   */
/*   3. Вывод записанных операций на стандартный вывод и закрытие файла.      */
/*                                                                            */
/*   Возвращаемое значение:                                                   */
/*   - Функция не возвращает значение.                                        */
/*                                                                            */
/* ************************************************************************** */

void	sort_stack(t_stack **stack_a, t_stack **stack_b)
{
	int		fd;
	int		size;
	char	*line;

	fd = file_open("commands.txt");
	size = stack_size(stack_a);
	if (size <= 5)
	{
		tiny_sort(stack_a, stack_b, size, fd);
	}
	else
	{
		radix_sort_bits(stack_a, stack_b, fd);
	}
	close(fd);
	fd = file_open_old("commands.txt");
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_putstr_fd(line, 1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
