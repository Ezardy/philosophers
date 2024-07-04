/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:40:27 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/04 17:16:52 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ERRORS_H
# define PARSER_ERRORS_H
# define PARSER_ERR_NEG_VAL 1
# define PARSER_ERR_NEG_VAL_DESC "a non-negative value expected"
# define PARSER_ERR_EMP_STR 2
# define PARSER_ERR_EMP_STR_DESC "an empty string presented"
# define PARSER_ERR_NON_DIG 3
# define PARSER_ERR_NON_DIG_DESC "a non-digit symbol has been met"
# define PARSER_ERR_NUM_BIG 4
# define PARSER_ERR_NUM_BIG_DESC "the number too big for unsigned long"
#endif
