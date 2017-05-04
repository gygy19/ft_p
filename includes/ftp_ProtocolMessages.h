/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_ProtocolMessages.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 17:24:51 by jguyet            #+#    #+#             */
/*   Updated: 2017/05/04 17:24:53 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_PROTOCOLMESSAGES_H
# define IRC_PROTOCOLMESSAGES_H

# include <libft.h>

# define MAX_PROTOCOL_MESSAGE_LENGTH 20

typedef struct				s_ProtocolMessage
{
  char					name[MAX_PROTOCOL_MESSAGE_LENGTH];
	int					  key;
  BOOLEAN       (*execute)();
}                     t_ProtocolMessage;

#endif
