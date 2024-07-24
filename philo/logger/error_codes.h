/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:49:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/23 20:45:57 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CODES_H
# define ERROR_CODES_H

// main codes
# define MAIN_ERR_ARG_COUNT 1
# define MAIN_ERR_ARG_COUNT_DESC "wrong arguments count"

// parser codes
# define PARSER_ERR_NEG_VAL 2
# define PARSER_ERR_NEG_VAL_DESC "a non-negative value expected"
# define PARSER_ERR_EMP_STR 3
# define PARSER_ERR_EMP_STR_DESC "an empty string presented"
# define PARSER_ERR_NON_DIG 4
# define PARSER_ERR_NON_DIG_DESC "a non-digit symbol has been met"
# define PARSER_ERR_NUM_BIG 5
# define PARSER_ERR_NUM_BIG_DESC "the number too big for unsigned long"

// philosopher codes
# define PHILOSOPHER_ERR_MEM_ALLOC 6
# define PHILOSOPHER_ERR_MEM_ALLOC_DESK "failed to allocate memory"
# define PHILOSOPHER_ERR_DL 7
# define PHILOSOPHER_ERR_DL_DESK "dead lock was detected"
# define PHILOSOPHER_ERR_MUT_DL 8
# define PHILOSOPHER_ERR_MUT_DL_DESK "there should be dead lock if mutex\
 will be locked"
# define PHILOSOPHER_ERR_MUT_BUSY 9
# define PHILOSOPHER_ERR_MUT_BUSY_DESK "a mutex, which was locked, has been \
tried to destroy"

// logger codes
# define LOGGER_ERR_MUT_DEAD_LOCK 10
# define LOGGER_ERR_MUT_DEAD_LOCK_DESK PHILOSOPHER_ERR_MUT_DL_DESK
# define LOGGER_ERR_MUT_BUSY 11
# define LOGGER_ERR_MUT_BUSY_DESK PHILOSOPHER_ERR_MUT_BUSY_DESK
# define LOGGER_ERR_MEM_ALLOC 12
# define LOGGER_ERR_MEM_ALLOC_DESK PHILOSOPHER_ERR_MEM_ALLOC_DESK

# define HELP_MSG "Instructions how to use program:\nphilo number_of_philosophe\
rs time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must\
_eat]\nnumber_of_philosophers ∈ [0, 18446744073709551615]\ntime_to_die ∈ [0, 42\
94967]\ntime_to_eat ∈ [0, 4294967]\ntime_to_sleep ∈ [0, 4294967]\nnumber_of_tim\
es_each_philosopher_must_eat ∈ [0, 18446744073709551615]\n"

# define EAT_ENOUGH 254
# define PHILOSOPHER_DIED 255
#endif
