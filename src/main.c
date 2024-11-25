/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/25 18:01:13 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_error_code = 0;

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[%i] = %s\n", i, tab[i]);
		i++;
	}
}

int	ft_print_list(struct s_token *list)
{
	int i;

	i = 0;
	if (!list->str)
		return (-1);
	while (list)
	{
		printf("list[%i] = %s  type = %d\n", i, list->str, list->type);
		i++;
		list = list->next;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char	*buffer;
	t_minish	*mini_struct;
	t_token		*head;
	
	(void)argc;
	(void)argv;
	head = NULL;
	mini_struct = malloc(sizeof(t_minish));
	if (!mini_struct)
		return (ft_putstr_fd("Error malloc minish in main\n", 2), -1);
	while (1)
	{
		signal_handle();
		buffer = readline(PROMPT);
		if (!buffer)
		{
			free_all(head, mini_struct);
			return (ft_putstr_fd("Exit with CTRL+D\n", 2), -1);
		}
		if (*buffer == '\0') // Segfault si on retourne a la ligne sur un prompt vide fixed
		{
			free(buffer);
			continue;
		}
		add_history(buffer);
		head = ft_split_word(buffer, mini_struct);
		free_list(head);
		free(buffer);
	}
	free(mini_struct);		
}
