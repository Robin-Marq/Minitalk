/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarquar <rmarquar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:31:01 by rmarquar          #+#    #+#             */
/*   Updated: 2024/02/07 12:16:14 by rmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// This struct will be used to store the bit and the set
// The bit will be used to store the bit position
// The set will be used to store the character
// from Robin Marquardt

static struct s_bit_writer
{
	int	bit;
	int	set;
} t_bit_writer;

// This function will write the bit to the BitWriter.set
// and when the bit is 0, it will print the character to the standard output
// from Robin Marquardt

static void	ft_write_the_bits(int sig_nr)
{
	t_bit_writer.set += (sig_nr << t_bit_writer.bit);
	if (t_bit_writer.bit == 0)
	{
		ft_putchar_fd(t_bit_writer.set, 1);
		fflush(stdout);
		t_bit_writer.bit = 7;
		t_bit_writer.set = 0;
	}
	else
		t_bit_writer.bit--;
}

// This function will be called when a signal is received
// If the signal is SIGUSR1, we will call ft_bit_write with 1
// If the signal is SIGUSR2, we will call ft_bit_write with 0
// The function ft_bit_write will write the bit to the BitWriter.set
// and when the bit is 0, it will print the character to the standard output
// from Robin Marquardt

static void	ft_signal_handling(int x)
{
	if (x == SIGUSR1)
		ft_write_the_bits(1);
	else
		ft_write_the_bits(0);
}

// In this function, we will print the pid of the server
// and then we will set the signal handler for SIGUSR1 and SIGUSR2
// and then we will pause the process
// The process will be paused until a signal is received
// When a signal is received, the signal handler will be called
// and the process will be paused again
// the struct sigaction is used to set the signal handler
// from Robin Marquardt

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = 0;
	pid = getpid();
	ft_printf("\033[32mPid--> %u\033[0m\n", pid);
	t_bit_writer.bit = 7;
	t_bit_writer.set = 0;
	sa.sa_handler = ft_signal_handling;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
