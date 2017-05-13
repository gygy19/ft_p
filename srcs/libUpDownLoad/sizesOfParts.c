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

//1ko = 1000octet
//1mo = 1000ko || 1 000 000octet

int     getsize(t_upload *upload)
{
    if (upload->size <= 10000)//10ko
      return (upload->size);
    if (upload->size <= 100000)//100ko
      return (upload->size / 10);
    if (upload->size <= 1000000)//1mb
      return (upload->size / 20);
    if (upload->size <= 100000000)//100mo
      return (upload->size / 100);
    if (upload->size <= 1000000000)//1000mo
      return (100000);
    return (500000);
}

int     getmaxpart(t_upload *upload)
{
  if (upload->size <= 10000)
    return (1);
  if (upload->size <= 100000)//100ko
    return (10);
  if (upload->size <= 1000000)//1mo
    return (20);
  if (upload->size <= 100000000)//100mo
    return (100);
  if (upload->size <= 1000000000)//1000mo
    return (upload->size / 100000);
  return (upload->size / 500000);
}
