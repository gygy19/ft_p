/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfile.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 07:12:40 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/06 07:12:41 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFILE_H
# define LIBFILE_H

# include <dirent.h>
# include <sys/stat.h>

int		file_exists(const char *file);
int		is_regular(const char *file);
int		is_device(const char *file);
int		is_dir(const char *file);

#endif
