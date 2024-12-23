/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xunistd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:25 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 10:43:26 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XUNISTD_H
#define XUNISTD_H
#include <unistd.h>
#include "system.h"

void xfree(void **ptr);
int xclose(int *fd);
void xpipe(int pipfds[], t_info *info);

pid_t xfork(t_info *info);

void *xmalloc(size_t size,t_info *info);


#endif