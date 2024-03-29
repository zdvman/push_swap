/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:01:38 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/10 19:32:38 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Функция `file_open` открывает файл для записи. Если файл не существует,  */
/*   он будет создан. Если файл уже существует, его содержимое будет удалено. */
/*   В случае ошибки открытия файла, функция выводит сообщение об ошибке и    */
/*   завершает программу.                                                     */
/*                                                                            */
/*   Параметры:                                                               */
/*   - `file`: имя файла для открытия.                                        */
/*                                                                            */
/*   Работа функции:                                                          */
/*   1. Открытие файла с правами только для записи, создание, если он не      */
/*      существует, и обрезание до нулевой длины, если он существует.         */
/*   2. Проверка успешности операции открытия файла.                          */
/*   3. Возврат файлового дескриптора открытого файла.                        */
/*                                                                            */
/*   Возвращаемое значение:                                                   */
/*   - Возвращает файловый дескриптор открытого файла.                        */
/*                                                                            */
/* ************************************************************************** */

int	file_open(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		write(1, "Error: file open failed\n", 24);
		exit(1);
	}
	return (fd);
}

/* ************************************************************************** */
/*                                                                            */
/*   Функция `file_open_old` открывает существующий файл только для чтения.   */
/*   В случае ошибки открытия файла, функция выводит сообщение об ошибке и    */
/*   завершает программу.                                                     */
/*                                                                            */
/*   Параметры:                                                               */
/*   - `file`: имя файла для открытия.                                        */
/*                                                                            */
/*   Работа функции:                                                          */
/*   1. Открытие существующего файла с правами только для чтения.             */
/*   2. Проверка успешности операции открытия файла.                          */
/*   3. Возврат файлового дескриптора открытого файла.                        */
/*                                                                            */
/*   Возвращаемое значение:                                                   */
/*   - Возвращает файловый дескриптор открытого файла.                        */
/*                                                                            */
/* ************************************************************************** */

int	file_open_old(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
	{
		write(1, "Error: file open failed\n", 24);
		exit(1);
	}
	return (fd);
}
