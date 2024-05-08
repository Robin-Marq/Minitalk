/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarquar <rmarquar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:31:11 by rmarquar          #+#    #+#             */
/*   Updated: 2024/02/07 12:34:59 by rmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Global variable to store the received bit
static int	g_received_bit = -1;

// This function will be called when a signal is received
// If the signal is SIGUSR1, we will set the received bit to 1
// If the signal is SIGUSR2, we will set the received bit to 0
// This function is used to receive the bits sent by the server
// regards from Robin Marquardt

static void	ft_sigusr_handler(int sig_nr)
{
	if (sig_nr == SIGUSR1)
		g_received_bit = 1;
	else if (sig_nr == SIGUSR2)
		g_received_bit = 0;
}

// This function will send a bit to the server
// If the bit is 1, we will send SIGUSR1
// If the bit is 0, we will send SIGUSR2
static void	ft_send_the_bit(int pid, int bit)
{
	if (bit == 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(200);
}

// This function will send a character to the server
// We will send the bits of the character one by one
static void	ft_send_the_char(int pid, unsigned char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		ft_send_the_bit(pid, (c >> bit) & 1);
		bit--;
	}
}

// This function will send a string to the server
// We will send the characters of the string one by one
static void	ft_send_the_signal(int pid, char *str)
{
	unsigned char		ch;
	struct sigaction	sa_usr;

	sa_usr.sa_handler = ft_sigusr_handler;
	sa_usr.sa_flags = 0;
	sigemptyset(&sa_usr.sa_mask);
	sigaction(SIGUSR1, &sa_usr, NULL);
	sigaction(SIGUSR2, &sa_usr, NULL);
	while (*str)
	{
		ch = *str;
		str++;
		ft_send_the_char(pid, ch);
	}
}

// This is the main function
// We will check if the number of arguments is correct
// If the number of arguments is correct, we will call ft_send_signal
int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
	{
		printf("\033[33m\nError: wrong number of arguments. Need 2 please\n");
		printf("Do: ./client (SERVER PID) + (STRING TO SEND)\033[0m\n\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	ft_send_the_signal(pid, argv[2]);
	return (0);
}
