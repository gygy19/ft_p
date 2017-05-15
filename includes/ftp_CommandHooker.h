/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_CommandHooker.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 17:34:11 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/04 17:34:12 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_COMMANDHOOKER_H
# define FTP_COMMANDHOOKER_H

# include <libft.h>

# define MAX_COMMAND_LENGTH 10

typedef struct				s_commandhooker
{
	char					name[MAX_COMMAND_LENGTH];
	int						key;
	BOOLEAN					(*execute)();
	size_t					args_min;
}							t_commandhooker;

#endif
