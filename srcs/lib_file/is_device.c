/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdevice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 18:06:40 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/03 18:06:42 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfile.h"

int		is_device(const char *file)
{
	struct stat buf;

	if (!file_exists(file))
		return (0);
	stat(file, &buf);
	return (S_ISCHR(buf.st_mode));
}
