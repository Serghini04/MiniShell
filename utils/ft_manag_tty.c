/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manag_tty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:44:09 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/27 10:37:51 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	attribute_quit(struct termios save)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag = ~NOFLSH;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &save);
}
