/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcarrara <vcarrara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:46:42 by vcarrara          #+#    #+#             */
/*   Updated: 2024/10/24 14:06:26 by vcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mutex_error_handler(int status, t_operations operation)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (operation == LOCK || operation == UNLOCK))
		print_error("Invalid mutex value");
	else if (status == EINVAL && operation == INIT)
		print_error("Invalid mutex attributes");
	else if (status == EDEADLK)
		print_error("Deadlock detected");
	else if (status == EPERM)
		print_error("Thread does not own the mutex");
	else if (status == ENOMEM)
		print_error("Not enough memory for mutex");
	else if (status == EBUSY)
		print_error("Mutex is already locked");
}

void	mutex_handler(t_mtx *mutex, t_operations operation)
{
	if (operation == INIT)
		mutex_error_handler(pthread_mutex_init(mutex, NULL), operation);
	else if (operation == LOCK)
		mutex_error_handler(pthread_mutex_lock(mutex), operation);
	else if (operation == UNLOCK)
		mutex_error_handler(pthread_mutex_unlock(mutex), operation);
	else if (operation == DESTROY)
		mutex_error_handler(pthread_mutex_destroy(mutex), operation);
	else
		print_error("Invalid operation");
}

static void	thread_error_handler(int status, t_operations operation)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		print_error("Insufficient resources to create a thread");
	else if (status == EPERM)
		print_error("Permission denied to perform thread operation");
	else if (status == EINVAL && operation == CREATE)
		print_error("Invalid thread attributes");
	else if (status == EINVAL && (operation == JOIN || operation == DETACH))
		print_error("Thread not joinable or invalid for operation");
	else if (status == ESRCH)
		print_error("Thread ID not found");
	else if (status == EDEADLK)
		print_error("Deadlock detected or operation on self-thread");
}

void	thread_handler(pthread_t *thread, void *(*foo)(void *), void *data,
		t_operations operation)
{
	if (operation == CREATE)
		thread_error_handler(pthread_create(thread, NULL, foo, data),
			operation);
	else if (operation == JOIN)
		thread_error_handler(pthread_join(*thread, NULL), operation);
	else if (operation == DETACH)
		thread_error_handler(pthread_detach(*thread), operation);
	else
		print_error("Invalid operation");
}
