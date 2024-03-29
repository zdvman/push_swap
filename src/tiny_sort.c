/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:10:40 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/11 16:17:42 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Функция `sort_three` сортирует стек из трех элементов. Она определяет    */
/*   порядок первых двух элементов и выполняет необходимые операции для       */
/*   достижения отсортированного состояния.                                   */
/*                                                                            */
/*   Параметры:                                                               */
/*   - `stack_a`: двойной указатель на начало стека `a`.                      */
/*   - `fd`: файловый дескриптор для записи операций.                         */
/*                                                                            */
/*   Работа функции:                                                          */
/*   1. Определяется порядок элементов и выполняется серия операций для       */
/*      сортировки: обмен (swap), ротация (rotate) или обратная ротация       */
/*      (reverse rotate), в зависимости от текущего порядка элементов.        */
/*                                                                            */
/*   Возвращаемое значение:                                                   */
/*   - Функция не возвращает значение.                                        */
/*                                                                            */
/* ************************************************************************** */

static void	sort_three(t_stack **stack_a, int fd)
{
	if (stack_sorted(stack_a))
		return ;
	if ((*stack_a)->value < (*stack_a)->next->value)
	{
		if ((*stack_a)->value > (*stack_a)->next->next->value)
			reverse_rotate_rra(stack_a, 1, fd);
		else
		{
			swap_sa(stack_a, 1, fd);
			rotate_ra(stack_a, 1, fd);
		}
	}
	else
	{
		if ((*stack_a)->next->value > (*stack_a)->next->next->value)
		{
			swap_sa(stack_a, 1, fd);
			reverse_rotate_rra(stack_a, 1, fd);
		}
		else if ((*stack_a)->value < (*stack_a)->next->next->value)
			swap_sa(stack_a, 1, fd);
		else
			rotate_ra(stack_a, 1, fd);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Функция `remove_mins_from_stack_a` удаляет элементы с минимальным        */
/*   индексом из стека `a` и перемещает их в стек `b`. Операция продолжается, */
/*   пока стек `a` не будет отсортирован. Перед каждой операцией перемещения  */
/*   элементы в стеке `a` переиндексируются для определения текущего          */
/*   минимального элемента. Если элемент находится ближе к началу стека,      */
/*   используется операция rotate, иначе - reverse rotate для минимизации     */
/*   количества операций.                                                     */
/*                                                                            */
/*   Параметры:                                                               */
/*   - `stack_a`: двойной указатель на начало стека `a`.                      */
/*   - `stack_b`: двойной указатель на начало стека `b`.                      */
/*   - `fd`: файловый дескриптор для записи операций.                         */
/*                                                                            */
/*   Работа функции:                                                          */
/*   1. Переиндексация элементов стека `a` для определения порядка.           */
/*   2. Нахождение элемента с минимальным индексом.                           */
/*   3. Определение положения элемента относительно медианы размера стека.    */
/*   4. Использование операций rotate или reverse rotate для перемещения      */
/*      минимального элемента на вершину стека.                               */
/*   5. Перемещение элемента из стека `a` в стек `b`.                         */
/*   6. Повторение процедуры до сортировки стека `a` или до достижения размера*/
/*      стека `a`, равного 3, после чего выполняется его сортировка.          */
/*                                                                            */
/* ************************************************************************** */

void	remove_mins_from_stack_a(t_stack **stack_a, t_stack **stack_b, int fd)
{
	t_stack	*tmp;
	int		min;
	int		median;

	min = 0;
	while (*stack_a && !stack_sorted(stack_a))
	{
		index_order(stack_a);
		tmp = *stack_a;
		median = stack_size(stack_a) / 2;
		while (tmp->index != min && tmp)
			tmp = tmp->next;
		while ((*stack_a)->index != min)
		{
			if (tmp->order <= median)
				rotate_ra(stack_a, 1, fd);
			else
				reverse_rotate_rra(stack_a, 1, fd);
		}
		push_pb(stack_a, stack_b, 1, fd);
		min++;
		if (stack_size(stack_a) == 3)
			sort_three(stack_a, fd);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Функция `selection_sort` реализует сортировку выбором для стеков.        */
/*   Элементы с минимальным индексом последовательно удаляются из стека `a`   */
/*   с помощью функции `remove_mins_from_stack_a` и перемещаются в стек `b`.  */
/*   После того как стек `a` отсортирован, все элементы перемещаются обратно  */
/*   из стека `b` в стек `a`, восстанавливая исходный порядок элементов,      */
/*   но уже в отсортированном виде.                                           */
/*                                                                            */
/*   Параметры:                                                               */
/*   - `stack_a`: двойной указатель на начало стека `a`.                      */
/*   - `stack_b`: двойной указатель на начало стека `b`.                      */
/*   - `fd`: файловый дескриптор для записи операций.                         */
/*                                                                            */
/*   Работа функции:                                                          */
/*   1. Удаление элементов с минимальным индексом из стека `a` и их           */
/*      перемещение                                                           */
/*      в стек `b` до полной сортировки стека `a`.                            */
/*   2. Перемещение всех элементов обратно из стека `b` в стек `a`.           */
/*                                                                            */
/* ************************************************************************** */

static void	selection_sort(t_stack **stack_a, t_stack **stack_b, int fd)
{
	if (stack_a && *stack_a && stack_b)
	{
		remove_mins_from_stack_a(stack_a, stack_b, fd);
		while (*stack_b)
			push_pa(stack_a, stack_b, 1, fd);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Функция `tiny_sort` сортирует стек из двух или трех элементов. Для двух  */
/*   элементов достаточно одной операции обмена, если они находятся в         */
/*   неправильном порядке. Для трех элементов вызывается `sort_three`.        */
/*                                                                            */
/*   Параметры:                                                               */
/*   - `stack_a`: двойной указатель на начало стека `a`.                      */
/*   - `size`: размер стека.                                                  */
/*   - `fd`: файловый дескриптор для записи операций.                         */
/*                                                                            */
/*   Работа функции:                                                          */
/*   1. Проверка размера стека и выполнение соответствующей сортировки.       */
/*                                                                            */
/*   Возвращаемое значение:                                                   */
/*   - Функция не возвращает значение.                                        */
/*                                                                            */
/* ************************************************************************** */

void	tiny_sort(t_stack **stack_a, t_stack **stack_b, int size, int fd)
{
	if (stack_a && *stack_a && size == 2)
	{
		if ((*stack_a)->value > (*stack_a)->next->value)
			swap_sa(stack_a, 1, fd);
	}
	else if (stack_a && *stack_a && size == 3)
		sort_three(stack_a, fd);
	else
		selection_sort(stack_a, stack_b, fd);
}
