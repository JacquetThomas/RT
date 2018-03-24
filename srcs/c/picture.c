/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:54:15 by cjacquet          #+#    #+#             */
/*   Updated: 2018/03/17 17:12:07 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <time.h>

static void	search_replace(char *str, char s, char r)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == s)
			str[i] = r;
		i++;
	}
}

static char	*choose_name(void)
{
	int			fd;
	char		*name;
	char		*ito;
	time_t		timey;

	timey = time(&timey);
	ito = ctime(&timey);
	ito = &ito[4];
	ito[ft_strlen(ito) - 1] = '\0';
	name = ft_strjoin("Screen ", ito);
	search_replace(name, ' ', '_');
	name = ft_strcat(name, ".bmp");
	fd = open(name, O_WRONLY);
	if (fd != -1)
	{
		free(name);
		name = choose_name();
	}
	close(fd);
	return (name);
}

int			save_picture(t_sdl *sdl)
{
	char		*s;
	SDL_Surface	*screenshot;

	s = choose_name();
	screenshot = SDL_ConvertSurfaceFormat(sdl->filters ? \
	sdl->eff : sdl->draw_surface, SDL_PIXELFORMAT_RGB24, 0);
	if (SDL_SaveBMP(screenshot, s) != 0)
	{
		SDL_FreeSurface(screenshot);
		errors(42, "Can't save the screen\n");
		free(s);
	}
	free(s);
	SDL_FreeSurface(screenshot);
	ft_putendl("Screen save !");
	return (0);
}
