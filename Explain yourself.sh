# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Explain yourself.sh                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idsy <idsy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/06 12:46:19 by idsy              #+#    #+#              #
#    Updated: 2020/01/08 10:51:22 by idsy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Alright here's the explanation of the entire code i've produced... if you are
a 42 student, know that this is possibly one of the most understable printf
tutoral You'll get to see':

Everything starts at ft_printf.c, since this is what we are currently doing.

///////////////////////////////////////////////////////////////////////////////
								S T A R T
///////////////////////////////////////////////////////////////////////////////

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

#YUP. PLUS YOU GET BONUS POINTS FOR HAVING ANOTHER FUNCTION Printf related in your
#library !!!!!!

Alright So anyways, what we are looking to code now isn't printf' but vdprintf.
Since this is what we are using now.

Now, the parameters taken by this function are filesdes, which is the file descriptor
format, which is the str you put in printf and a va_list or args that are the args
to be formatted.

/***********/
/*variables*/
/***********/

now let's' talk about the variables initated in this function:
We have:

-tt_bytes, 	an int32_t (if you want to have more fanciness and useless consistency)
			which is basically the return value of printf (the number of chars printed)

-i, 		which is a simple counter used to go though the part of the format string
			not affected by the formatting

-len,		A size_t used in the formatter function to get the size of what we are
			supposed to display after formating the output (you may ask why we are
			using a size_t and the answer is that it's' purpose is to relieve the
			developper of the implementation of the variable supposed to contain
			what is supposed to be a size)

-fstr		a char * which is a buffer of the formatted output of an argument.
			it's' printed afterwards before continuing the reading of format
			for more conversion flags.

/***********/
/*processus*/
/***********/

Alright so the processus of the vdprintf thingy is that you basically have a
string and that you are looking for a % in it, then you print eveything that
you 'read' before that point, and transform whatever is between % and the
conversion flags calling the function "formatter".

display whatever you converted with the len you received from formatted thingy
and do it all over again.

Now i guess you might want to know how the hell we convert the args and process?
Well we about to analyse that just now.

SIKE, before goinf into the formatting simplified processus we need to know we
collect information from the format string.

///////////////////////////////////////////////////////////////////////////////
							  P A R S I N G
///////////////////////////////////////////////////////////////////////////////

Alright! so the goal here is to collect the most infos we can on the specifier
thingy, now how do we do that? Well first we need to learn the basic things
that we NEED to save, what are the parameters that we need to identify in the
string?

Those are:
	- The flags: those are '+','-',' ','#','0'
		'+' : is a flag that affects signed arguments, it's purposed is solely'
		to put the signe of the signed thingy before it's appearance'. if this
		flag is not set, the sign will only be displayed in the case of the
		arguent being negative

		'-' : 

	- The Width:

	- The Precision:

	- The length:

	- The specifier:

	#- And the Style
they should show up in the order i explained them too.
Now that we know what evrything does, we need to think of an efficient way 
of stocking all that and the best solution here is probably a struct.



///////////////////////////////////////////////////////////////////////////////
							F O R M A T T I N G
///////////////////////////////////////////////////////////////////////////////

Nice, now that we have the infos, here is how we do the formatting process
alright, so here's' the micro man-like page i did in the code

/*
**		NAME
**			formatter -- formattied string conversion
**
**		SYNOPSIS
**			#include <libft.h>
**
**			char * *			formatter(const char **format, va_list *args, size_t *len
**
**		PARAMETERS
**
**		const char *format		format string.
**
**		va_list 	*args		argument list.
**
**		size_t		len			The variable supposed to store the length of the formatted
**							string
**
**	DESCRIPTION
**		Converts the specified format string into the formatted string
**
**	RETURN VALUES
**		If the format is correctly specified, returns a formatted string, a format string
**		otherwise.
*/

alright so once again let's speak about the roles of each variables'
:


/***********/
/*variables*/
/***********/

Among them e have a familiar face:

-fstr		a char * which is a buffer of the formatted output of an argument.
			it's' printed afterwards before continuing the reading of format
			for more conversion flags.

-info		a t_format containing all the information parsed that concerns the
			#formating. flags, width, precision, length, FORMAT_LENGTH, specifier,
			#the padding buffer and the char** style.

-arg		a t_data typedef, which is a union of a fucking lot of different types
			it will be used to receive the argument and put it in the good format
			from the get go since it's virtually all' the types:
			*str_ bool_ char_ short_ int_ long_ long_long_ uchar_ ushort_ uint_ ulong_ ulong_long_ 
			double_ long_double_ dbl_ ldbl_ intmax_ uintmax_ intptr_ uintptr_
			ptrdiff_ size_
			
-i 			a simple counter used to go through the function pointers associated
			for each specifier.

/***********/
/*processus*/
/***********/

Alright, so first, we need to parse the infos from the format string and put it in
the info struct. the first case we woudl want to treat woould be the fact that we
we could have no specifier.
	In that case, we'll' set the buffer of the formatted string to a a segment of 
	the initial format string, and set that length to the info.format_length identified

	if that's' not the case, we need to extract the argument in the t_data union
	we can just extract it as an intmax_t unless it's a float' then we just pass
	the specifier throught the handler associated to it.

	#More on Handlers is in "Explain Handlers.sh"

Once all of that is done we need to move the format string to the next char after
the flag specifer, and store the len of the fstr being careful to the special case
where the specifier would be %c and you pass a '\0' to it. in which case we the
len wouldn't' be the simple strlen of the formatted string but the space of the
'\0' which is 1 + the (info.width - 1). since we have to take account for it still.
