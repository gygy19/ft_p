/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:38:06 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/03 17:38:07 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfile.h"

int		is_dir(const char *file)
{
	struct stat buf;

	if (!file_exists(file))
		return (0);
	stat(file, &buf);
	return (S_ISDIR(buf.st_mode));
}
