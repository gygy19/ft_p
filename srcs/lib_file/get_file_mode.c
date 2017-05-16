/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 02:50:56 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/16 02:52:51 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfile.h"

int	get_file_mode(const char *path)
{
	struct stat stats;

	if (!file_exists(path))
		return (0);
	stat(path, &stats);
	return (stats.st_mode);
}
