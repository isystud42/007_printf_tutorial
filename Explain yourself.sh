# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Explain yourself.sh                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idsy <idsy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/06 12:46:19 by idsy              #+#    #+#              #
#    Updated: 2020/01/06 13:08:19 by idsy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Alright here's the explanation of the entire code i've produced... if you are
a 42 student, know that this is possibly one of the most understable printf
tutoral You'll get to see':

Everything starts at ft_printf.c, since this is what we are currently doing.

Basycally, you're not using printf, but vd_printf. Cuz we fancy as hell and it's
and easy bonus. Okay now to understand the difference between printf and vd_printf
we first need to learn what the man says about vd_printf:

"The functions dprintf() and vdprintf() (as found in the glibc2 library) are exact
analogs of fprintf(3) and vfprintf(3) except that they output to a file descriptor
fd instead of to a stdio stream."

Sure buddy, but what even is fprintf and vfprintf... Well we just need to read
another man page:

"fprintf() and vfprintf() write output to the given output stream"

#Alright, but wait... So the point of using vdprint is nothing more than being
#fancy? 

#YUP.

Alright So anyways, what we are looking to code now isn't printf' but vdprintf.


