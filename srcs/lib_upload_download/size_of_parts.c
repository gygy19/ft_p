/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizesOfParts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 13:50:48 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/08 13:50:50 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_upload.h"
#include "libfile.h"

int	getsize(t_upload *upload)
{
	if (upload->size <= 10000)
		return (upload->size);
	if (upload->size <= 100000)
		return (upload->size / 10);
	if (upload->size <= 1000000)
		return (upload->size / 20);
	if (upload->size <= 100000000)
		return (upload->size / 100);
	if (upload->size <= 1000000000)
		return (100000);
	return (500000);
}

int	getmaxpart(t_upload *upload)
{
	if (upload->size <= 10000)
		return (1);
	if (upload->size <= 100000)
		return (10);
	if (upload->size <= 1000000)
		return (20);
	if (upload->size <= 100000000)
		return (100);
	if (upload->size <= 1000000000)
		return (upload->size / 100000);
	return (upload->size / 500000);
}
