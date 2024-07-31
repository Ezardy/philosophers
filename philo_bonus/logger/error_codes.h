/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:49:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/31 14:40:23 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CODES_H
# define ERROR_CODES_H

// main codes
# define MAIN_ERR_ARG_COUNT 1
# define MAIN_ERR_ARG_COUNT_DESC "Wrong arguments count"

// parser codes
# define PARSER_ERR_NEG_VAL 2
# define PARSER_ERR_NEG_VAL_DESC "A non-negative value expected"
# define PARSER_ERR_EMP_STR 3
# define PARSER_ERR_EMP_STR_DESC "An empty string presented"
# define PARSER_ERR_NON_DIG 4
# define PARSER_ERR_NON_DIG_DESC "A non-digit symbol has been met"
# define PARSER_ERR_NUM_BIG 5
# define PARSER_ERR_NUM_BIG_DESC "The number too big for the program parameter"
# define PARSER_ERR_BEGIN PARSER_ERR_NEG_VAL
# define PARSER_ERR_END PARSER_ERR_NUM_BIG

// philosopher codes
# define PHILOSOPHER_ERR_PROC_MEM 6
# define PHILOSOPHER_ERR_PROC_MEM_DESK "There is insufficient swap space for th\
e new process"
# define PHILOSOPHER_ERR_SEM_DL 7
# define PHILOSOPHER_ERR_SEM_DL_DESK "A dead lock was detected"
# define PHILOSOPHER_ERR_PROC_LIM 8
# define PHILOSOPHER_ERR_PROC_LIM_DESK "The system-imposed limit on the total n\
umber of processes under execution would be exceeded"
# define PHILOSOPHER_ERR_SEM_NOSPC 9
# define PHILOSOPHER_ERR_SEM_NOSPC_DESK "There is insufficient space availablet\
o create the semaphore"
# define PHILOSOPHER_ERR_SEM_ENFILE 10
# define PHILOSOPHER_ERR_SEM_ENFILE_DESK "Too many semaphores of file descripto\
rs are open on the system"
# define PHILOSOPHER_ERR_SEM_EMFILE 11
# define PHILOSOPHER_ERR_SEM_EMFILE_DESK "The process has already reached its l\
imit for semphores or file descriptors in use"
# define PHILOSOPHER_ERR_BEGIN PHILOSOPHER_ERR_PROC_MEM
# define PHILOSOPHER_ERR_END PHILOSOPHER_ERR_SEM_EMFILE

// logger codes
# define LOGGER_ERR_SEM_NOSPC 12
# define LOGGER_ERR_SEM_NOSPC_DESK PHILOSOPHER_ERR_SEM_NOSPC_DESK
# define LOGGER_ERR_SEM_ENFILE 13
# define LOGGER_ERR_SEM_ENFILE_DESK PHILOSOPHER_ERR_SEM_ENFILE_DESK
# define LOGGER_ERR_SEM_EMFILE 14
# define LOGGER_ERR_SEM_EMFILE_DESK PHILOSOPHER_ERR_SEM_EMFILE_DESK
# define LOGGER_ERR_SEM_DL 15
# define LOGGER_ERR_SEM_DL_DESK PHILOSOPHER_ERR_SEM_DL_DESK
# define LOGGER_ERR_BEGIN LOGGER_ERR_SEM_NOSPC
# define LOGGER_ERR_END LOGGER_ERR_SEM_EMFILE

# define HELP_MSG "Instructions how to use program:\nphilo number_of_philosophe\
rs time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must\
_eat]\nnumber_of_philosophers ∈ [0, 18446744073709551615]\ntime_to_die ∈ [0, 42\
94967]\ntime_to_eat ∈ [0, 4294967]\ntime_to_sleep ∈ [0, 4294967]\nnumber_of_tim\
es_each_philosopher_must_eat ∈ [0, 18446744073709551615]\n"

# define PHILOSOPHER_DIED 255
#endif
