# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Explain Handlers.sh                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idsy <idsy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/08 18:21:41 by idsy              #+#    #+#              #
#    Updated: 2020/02/13 18:40:03 by idsy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Alright, so you wanna know about them handlers, right? Don't worry' it's pretty
simple.'
There's' a lot of them but if you look at them individually, you should be able
to understand pretty much everything pretty fast... I mean, i'm the one explaining'
OF COURSE you'll understand pretty fast'

Alrrright, soooo. The way we'll be using them handlers is through calling them'
individually depending on the specifier. For that, the best way to avoid doing
a freaking if-forest is to do either an enum, or to do a struct containing an 
id (specifier) and having an applicaiton associated to it.

We'll do a typdef like this' in the .h

typedef struct	s_handler
{
	char		specifier
	char		*(*handler)(t_format info, t_data arg);
}				t_handler;

we're using a function pointer It's pretty handy, you should look it up if you
do not use it inyour project yet.

That way you can associate a function to an id.
Anyways, the first possible handle being called is the one supposed to treat
the modulo. Which is basically saying, do nt treat anything and just format the
"%%" to a single "%".

-------------------------------------------------------------------------------
								'c', c_handler
-------------------------------------------------------------------------------

this Handler is supposed to handle the case where a char is the formatted output
It does this exact thing while taking in account of the field width.
so instead of ust have a c being printed, we use a string that will be mamory
allocated to the side of the feild width - the space of the char + the \0 space

-Then if the field width is not to be treated, which is the case when you have
0 in the t_format struct.width or if the MINUS flag is active
	you simply put the first char of the string as the char passed down in the arg.

-if that's' not the case you have to put that char to str[format.width -1]
and use memset to switch up all the values between the start of the string until
the actual char to the arg receveid value

-------------------------------------------------------------------------------
								'%', mod_handler
-------------------------------------------------------------------------------

This handler calls the char_handler after modifying the t_data arg (union typedef)
value to '%'.

-------------------------------------------------------------------------------
								'i', i_handler
-------------------------------------------------------------------------------

This handler is supposed to take the int source from the arg and convert it to
a string. For that we just use a really usefull function called utoabase width
the appropriae base being the decimal one. "0123456789"

We also need to watchout on the "import" of the argument by puting it in a
different type, from int to intmax_t if the lengt of bits required to take the
argument is superior to a standard int (that's why union are hella cool')

do not forget to add the precision to it Anyways, check that sweet ft_utoa_base
explanation if you need it. You'll see it's pretty easy to be fair.

Anyways let's' go step by step and analysise each line:

	intmax_t	temp; 		// The holder of the arg, a temporary measure
	bool		sign; 		// IS the variable supposed to hold the sign
	char		*intstr;	// is the Str that will be displayed on the output

	temp = (format.length < L) ? arg.int_ : arg.intmax_;
		// Heere we just verify that the sixe of the arg we're supposed to'
		obtain is smaller than long int, which would mean that we don't need to use intmax_t'

	sign = (temp < 0);
		// Easy to understand, we set up the sign value for later

	intstr = ft_strdup("");
		// Easy to understand, we initiaalsize an empty string for later



	if (!(format.precision == 0 && temp == 0))
	// We check that either the precision or the temp are not = 0
	{
		temp = (temp < 0) ? -temp : temp; // temp take it's' absolute value
		intstr = ft_strappend(
			intstr, ft_utoa_base(temp, DECIMAL_BASE, format.precision), 1, 1);
		// the string gets to take a new value of "herself" plus the result of
			ft_utoa_base on a standard decimal base.
			The precision is handled in the utoa base thingy. (go check it out, seriously)
	}

	format.width -= ft_strlen(intstr) +
		(sign || (format.flags & PLUS || format.flags & SPACE) ? 1 : 0);
	// We susbstract the width from the length of the string we're about' to desiplay
	// So we can deduce the actual width needed to be displayed. (The we check if we're)
	'// account for the - sign or the space that would be displayed because of the flag

	if (format.width && format.pad == '0')
		intstr = apply_width(format, intstr);
	
	// if we're supposed to add' padding of 0's' We do it? verifying in the apply_width
	// if we have a MINUS as a flag -> padding in the other side
	
	intstr = (sign) ? ft_strprepend(intstr, "-", 1, 0) : intstr;
		//if we have a negative, he put it before the number
	
	if (format.flags & PLUS && !sign)
		intstr = ft_strprepend(intstr, "+", 1, 0);
	//if the + flag is on, you put it before the number in the string
	
	if (format.flags & SPACE && !(format.flags & PLUS) && !sign)
		intstr = ft_strprepend(intstr, " ", 1, 0);
	// if the Space flag is active and has the no other flag taking priority
	// we put the space before the number in the string
	
	if (format.width && format.pad != '0')
		intstr = apply_width(format, intstr);
	We treat the case were the padding is not a '0'.
	
	return (intstr);

-------------------------------------------------------------------------------
								'u', u_handler
-------------------------------------------------------------------------------

Alright so the u_handler is the handle charged of handling the unsigned number
coversion.

basically the same thing than the i handle but we need to handle a lot less flags
and no need to handle the sign thingy.

Let''s also do a line by line analyse of this thing:

	uintmax_t	temp;		// The sacred vessel supposed to contain the arg
	char		*intstr;	// The Sacred vessel supposed to be the displayed string

	temp = (format.length < L && format.length != NONE) ?
		arg.uint_ :
		arg.uintmax_;
	// We just make sure that we can get the shit in a regular uint_ 
	
	intstr = ft_strdup("");
	// Initialise the string to an empty one.
	
	if (!(format.precision == 0 && temp == 0))
	{
		intstr = ft_strjoinfre(
			intstr, ft_utoa_base(temp, DECIMAL_BASE, format.precision), 1, 1);
		format.width -= ft_strlen(intstr);
	}
	//If temp or the precision isn't 0', turn it into intstr and substract the length
	// from the format.
	if (format.width)
		intstr = apply_width(format, intstr);
	//then finish applying the padding to the intstr
	return (intstr);
}

-------------------------------------------------------------------------------
							%b, bonus binary Handler
-------------------------------------------------------------------------------

This is a bonus hander supposedto support the display of a binary output.
As a special handler, we need it to be compatible with any and every entry
flags he might get.

**Note: the flags and fields that apply to this specifier are
**         the following:
**
**             Flags: '-', '+', ' ', '0', '#'
**             Width: defined or '*'
**             Precision: defined or '*'
**             Length: 'hh', 'h', 'l', 'll', 'j', 'z', 't'

let's do one more line by line explanation' ->

	intmax_t	temp;
	char		*intstr;

Those are the two sacred vessels supposed to take in the argument and the output
string.

----if (format.length < L && format.length != NONE)
----	temp = (format.length == HH) ? arg.uchar_ : arg.ushort_;
----else
----	temp = (format.length == NONE) ?
----		arg.uint_ :
----		arg.uintmax_;
----intstr = ft_strdup("");

Here, we check that the length of the arg is small enought to be attributed to
a short. If that's the case' We either put it in an unsigned short or an unsigned char.
depending on the appeareance of the HH flag.

** "BUT WHY AN UNSIGNED?" Well, don't you think it's easier to divide by 2 when not
** having to account for the bit assigned to the sign? "YEAH"
** "But why do we divide by two" cuz that's' the way utoa_base works "OH COOL..."
** "Wouldn't it be easier to bo some bit shifting?" Stfu. I'm lazy' so i'll' use 
** functions i've already implemented and the divison by 2 is basically some bit shifting.'

Then, if we need a bigger vessel for the arg, we'll see' if there is no length specified
in which cas we'll' get the arg in a uint. or in a uintmax_t if that's' not the case.

and finallly we initialise the intstr to an empty string.

	if (!(format.precision == 0 && temp == 0))
	{
		temp = (temp < 0) ? ~(-temp) + 1 : temp;
		intstr = ft_strjoinfre(
			intstr, ft_utoa_base(temp, BINARY_BASE, format.precision), 1, 1);
		format.width -= ft_strlen(intstr) +
			((format.flags & HASH && temp) ? 2 : 0);
	}

Then we do basically the same thing that we do in %i but with a BINARY_BASE this time

	if (format.width && format.pad == '0')
		intstr = apply_width(format, intstr);
	if (format.flags & HASH && temp)
		intstr = ft_strprepend(intstr, "0b", 1, 0);
	if (format.width && format.pad != '0')
		intstr = apply_width(format, intstr);

same here, but with a good prepend
	return (intstr);

BINK we done.

-------------------------------------------------------------------------------
								%o, O handler
-------------------------------------------------------------------------------

LITTERALLY THE SAME THING BUT WITH OCTAL

and a lil switch on the prepend

-------------------------------------------------------------------------------
								%d, D handler-
-------------------------------------------------------------------------------

#include "../ft_printf.h"

char	*d_handler(t_format format, t_data arg)
{
	return (i_handler(format, arg));
}

-------------------------------------------------------------------------------
								%x, X handler
-------------------------------------------------------------------------------

Same thing, just change the Base for hexadecimal with lower case.

~~Do you know the definition of madness?

-------------------------------------------------------------------------------
								%X, XX_handler
-------------------------------------------------------------------------------
Same thing, just change the Case for hexadecimal with Upper case

~~It's doing the same thing over and over and expecting a different result'

-------------------------------------------------------------------------------
								%S, S_handler
-------------------------------------------------------------------------------
Look! that's an easy one' This handler is the one supposed to handle the string
case:

Let's do a line by line analysis'

#	char		*fstr;

This will is the vessel that will hold the formatted string before the display

	fstr = (arg.str_ == NULL) ?
		ft_strdup("(null)") :
		ft_strdup(arg.str_);

Those line are basically saying: Hey, can you verify the string is a not a null
one ? Cuz if it is, we need to make it special. with the (null) thingy.

	if (format.precision != NONE)
		if (0 <= format.precision && format.precision < (long)ft_strlen(fstr))
			fstr[format.precision] = '\0';

Those lines are handling the precision which tell us how many chars we''re 
supposed to display

	format.width -= ft_strlen(fstr);
	if (format.width > 0 && format.pad == ' ')
		fstr = apply_width(format, fstr);
	return (fstr);
}

Those are supposed to Handle the Width, by first narrowing the width value to what
it is supposed to display. and handling the pading that goes with it.

----------------------------------------------------------------------------------
