/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:02:00 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/09 13:51:00 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Функция `free_stack` освобождает память, выделенную под стек и           */
/*   сам двойной указатель на стек.                                           */
/*                                                                            */
/*   Параметры:                                                               */
/*   - `stack`: двойной указатель на стек, который представляет собой         */
/*     связный список.                                                        */
/*                                                                            */
/*   Работа функции:                                                          */
/*   1. Если `stack` равен NULL или указывает на NULL, функция завершает      */
/*      работу, так как нет необходимости в освобождении памяти.              */
/*   2. В цикле функция перебирает элементы стека, начиная с вершины.         */
/*   3. На каждом шаге функция освобождает память, выделенную для текущего    */
/*      элемента стека.                                                       */
/*                                                                            */
/*   Возвращаемое значение:                                                   */
/*   - Функция не возвращает значение. Она лишь освобождает память,           */
/*     выделенную под стек и указатель на стек.                               */
/*                                                                            */
/* ************************************************************************** */

void	free_stack(t_stack **stack)
{
	t_stack	*tmp;

	if (!stack || !(*stack))
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Функция `stack_sorted` проверяет, отсортирован ли стек в порядке         */
/*   возрастания.                                                             */
/*   Параметры:                                                               */
/*   - `stack`: двойной указатель на стек, который представляет собой связный */
/*     список.                                                                */
/*   Работа функции:                                                          */
/*   1. Сначала функция проверяет, не пуст ли стек и существует ли он.        */
/*      Если стек пуст или не существует, функция возвращает 1,               */
/*      поскольку пустой стек технически считается отсортированным.           */
/*   2. Далее, функция инициирует временный указатель `temp`,                 */
/*      который используется для итерации по стеку, начиная с его вершины.    */
/*   3. В цикле, функция перебирает элементы стека до его предпоследнего      */
/*      элемента.                                                             */
/*   4. На каждом шаге функция сравнивает значение текущего элемента          */
/*     (`temp->value`) со значением следующего элемента (`temp->next->value`).*/
/*   5. Если значение текущего элемента больше значения следующего, это       */
/*      означает, что стек не отсортирован в порядке возрастания,             */
/*      и функция возвращает 0.                                               */
/*   6. Если такая ситуация не обнаружена и цикл завершается, это означает,   */
/*      что все элементы стека отсортированы в порядке возрастания,           */
/*      и функция возвращает 1.                                               */
/*   Возвращаемое значение:                                                   */
/*   - Возвращает 1, если стек пуст, не существует или отсортирован           */
/*     в порядке возрастания.                                                 */
/*   - Возвращает 0, если стек не отсортирован в порядке возрастания.         */
/*                                                                            */
/* ************************************************************************** */

int	stack_sorted(t_stack **stack)
{
	t_stack	*temp;

	if (!stack || !(*stack))
		return (1);
	temp = *stack;
	while (temp->next)
	{
		if (temp->value > temp->next->value)
			return (0);
		temp = temp->next;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*   Функция `stack_size` вычисляет размер стека, на который указывает        */
/*   двойной указатель `stack`.                                               */
/*                                                                            */
/*   Параметры:                                                               */
/*   - `stack`: двойной указатель на стек, который представляет собой         */
/*     связный список.                                                        */
/*                                                                            */
/*   Работа функции:                                                          */
/*   1. Если `stack` равен NULL или указывает на NULL, функция возвращает 0,  */
/*      предполагая, что стек пуст.                                           */
/*   2. Функция инициализирует переменную `size` значением 0 и начинает       */
/*      перебор элементов стека, начиная с вершины.                           */
/*   3. В цикле функция перебирает каждый элемент стека, увеличивая           */
/*      счетчик `size`.                                                       */
/*   4. После перебора всех элементов возвращается общий размер стека.        */
/*                                                                            */
/*   Возвращаемое значение:                                                   */
/*   - Возвращает размер стека как целое число.                               */
/*                                                                            */
/* ************************************************************************** */

int	stack_size(t_stack **stack)
{
	int		size;
	t_stack	*tmp;

	if (!stack || !(*stack))
		return (0);
	size = 0;
	tmp = *stack;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}
