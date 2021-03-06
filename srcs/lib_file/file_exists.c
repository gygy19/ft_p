/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_exists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:33:01 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/03 15:33:03 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfile.h"

int		file_exists(const char *file)
{
	struct stat buf;

	return (stat(file, &buf) == 0);
}
