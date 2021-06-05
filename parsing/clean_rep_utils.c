/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_rep_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 19:38:17 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/05 14:58:38 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	special_checker(char **str, int *i, int cmd_return, int *just_char)
{
	if (str[0][(*i)] == '|' && (*i) > 0 && str[0][(*i) - 1] == '\\'
		&& *just_char != (*i) - 1)
		char_remove(str, i, just_char);
	else if (str[0][(*i)] == ';' && (*i) > 0 && str[0][(*i) - 1] == '\\'
		&& *just_char != (*i) - 1)
		char_remove(str, i, just_char);
	else if ((str[0][(*i)] == '>' || str[0][(*i)] == '<') && i > 0
		&& str[0][(*i) - 1] == '\\' && *just_char != (*i) - 1)
		char_remove(str, i, just_char);
	else if (str[0][(*i)] == '\\')
		char_remove(str, i, just_char);
	else if (str[0][(*i)] == ' ' && i > 0 && str[0][(*i) - 1] == '\\'
		&& *just_char != (*i) - 1)
		char_remove(str, i, just_char);
}

char	*dollar_status(char *str, int *i, int cmd_return)
{
	char	*ret;

	ret = insert_var_value(ft_substr(str, 0, (*i)),
			ft_itoa(cmd_return), ft_strdup(&str[(*i) + 2]));
	free(str);
	return (ret);
}

int	special_chars(char **str, t_env **s_env, int cmd_return)
{
	int		i;
	int		just_char;
	char	*tmp;

	i = -1;
	just_char = -1;
	while (*str != NULL && str[0][++i] != '\0')
	{
		if (str[0][i] == '"' || str[0][i] == '\'')
			quotes_function(str, s_env, &i, just_char);
		else if (str[0][i] == '$' && str[0][i + 1] == '?')
			str[0] = dollar_status(str[0], &i, cmd_return);
		else if (str[0][i] == '$')
			dollar_founded(str, s_env, &i, just_char);
		else
			special_checker(str, &i, cmd_return, &just_char);
	}
	return (0);
}

t_args	*arg_to_head(t_args *arg, char *cmd, int from, int *i)
{
	t_args	*args;
	t_args	*tmp;
	char	*str;

	str = ft_substr(cmd, from, (*i) - from);
	args = (t_args *)malloc(sizeof(t_args));
	if (args == NULL)
		error();
	args->arg = str;
	args->next = NULL;
	tmp = ft_lastarg(arg);
	if (tmp == NULL)
	{
		*i += space_count(&cmd[*i]) - 1;
		return (args);
	}
	else
		tmp->next = args;
	(*i) += space_count(&cmd[*i]) - 1;
	return (arg);
}

void	look_for_args(t_cmd *cmd, char *tmp, int i)
{
	int		from;
	t_args	*arg;
	t_args	*tmp_arg;

	from = -1;
	arg = NULL;
	i += space_count(&tmp[i]) - 1;
	while (tmp[++i] != '\0')
	{
		if (from == -1)
			from = i;
		if (tmp[i] == ' ')
		{
			arg = arg_to_head(arg, tmp, from, &i);
			from = -1;
		}
	}
	if (from != -1)
		arg = arg_to_head(arg, tmp, from, &i);
	tmp_arg = ft_lastarg(arg);
	if (tmp != NULL)
	{
		tmp_arg->next = cmd->args;
		cmd->args = arg;
	}
}
