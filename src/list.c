/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:36:32 by dsatge            #+#    #+#             */
/*   Updated: 2025/03/24 14:47:46 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	cmds_list(t_token *list, t_list *cmds)
{
	t_list *tmp;
	int	skip;
	int	i;
	
	i = 0;
	skip = 0;
	skip = init_cmds_list(cmds, list, skip);
	if (skip == -1)
		return (-1);
	while (list)
	{
		if (i > 0)
		{
			tmp = cmds;
			cmds->next = malloc(sizeof(t_list));
			if (!cmds->next)
				return (ft_putstr_fd("ERROR : malloc fail", 2), -1);
			cmds = cmds->next; // remet cmd_nbr a 0
			cmds->head = tmp->head;
			skip = ft_cmd(list, cmds, tmp->head->cmd_nbr);//ft t_cmd add tab
			cmds->next = NULL;
			cmds->prev = tmp;
		}
		while (skip > 0)
		{
			list = list->next;
			skip--;
		}
		i++;
	}
	return (0);
}

int	init_cmds_list(t_list *cmds, t_token *list, int skip)
{
	cmds->next = NULL;
	cmds->prev = NULL;
	cmds->head = NULL;
	cmds->cmd_nbr = 1;
	cmds->cmd = NULL;
	if (!list)
		return (-1);
	else
	{
		skip += ft_cmd(list, cmds, 1);
		cmds->head = cmds;
		if (cmds->head->cmd_nbr != 1)
			printf("OUUUUPSSSIIIIII\n");
	}
	return (skip);
}

int	  ft_cmd(t_token *list, t_list *cmds, int	nbr_cmd)
{
	int	element;
	
	element = 0;
	cmds->cmd = malloc(sizeof(t_cmd));
	if (!cmds->cmd)
		return (-1);
	if (cmds && cmds->head == NULL)
	{
		cmds->head = cmds;
		cmds->head->cmd_nbr = nbr_cmd;
	}
	element = tab_cmds(list, cmds);
	if (element == -1)
		return (-1); //ajouter fonction tableau cmds
	return (element);
}

int	tab_cmds(t_token *list, t_list *cmds)
{
	int		list_element;
	int		run_loop;
	t_token	*current;
	t_list	*curr_cmds;

	list_element = 0;
	current = list;
	curr_cmds = cmds;
	run_loop = 0;
	if (current->type == pip)
	{
		list_element++;
		current = current->next;
		if (cmds->head)
		{
			cmds->head->cmd_nbr += 1;
		}
	}
	if (current->type == redir)
	{
		run_loop = 1;
		list_element += redir_cmds(current, curr_cmds);
	}
	if (run_loop == 0 && current->type == word)
	{
		list_element += word_cmds(current, curr_cmds);
		run_loop = 1;
	}
	return (list_element);
}

int	redir_cmds(t_token *list, t_list *cmds)
{
	int i;

	i = 0;
	if (!cmds)
		return (-1);
	cmds->cmd->type = redir;
	cmds->cmd->tab = ft_calloc(sizeof(char *), (3));
	if (!cmds->cmd->tab)
		return (-1);
	while (i < 2)
	{
		cmds->cmd->tab[i] = ft_strdup(list->str);
		i++;
		list = list->next;
	}
	cmds->cmd->tab[i] = 0;
	return (2);
}

int	word_cmds(t_token *list, t_list *cmds)
{
	int		tab_len;
	int		i;
	t_token	*current;
	
	tab_len = 0;
	i = 0;
	current = list;
	cmds->cmd->type = word;
	while (current && current->type == word)
	{
		tab_len++;
		current = current->next;
	}
	current = list;
	cmds->cmd->tab = ft_calloc(sizeof(char*), (tab_len + 1));
	if (!cmds->cmd->tab)
		return (-1);
	while (current && current->type == word)
	{
		cmds->cmd->tab[i] = ft_strdup(current->str);
		i++;
		current = current->next;
	}
	cmds->cmd->tab[i] = 0;
	return (tab_len);
}
