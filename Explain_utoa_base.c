/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Explain_utoa_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsy <idsy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 00:44:15 by idsy              #+#    #+#             */
/*   Updated: 2020/02/11 13:40:28 by idsy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

Hoooo, so you want to know about utoa base? Well i'm glad you came here' That
might come in handy for your exam sessions.

The point of utoas_base est to take in a uintmax_t type, a base and a precision
in case its a float And return a string of this uintmax_t following the base.

First, we need to check that the base is a valid one:
	-that the string of the base is existing and non-empty and constituted of 
	at least 2 elements.
	-That this base is composed of "true elements", which are human read-able
	-That base must not contain any + or - As those are signes necessary to 
	express the sign of the number
	
Once the Base isestablished as a valid one, we need to evaluate the length of
the number that we are about to convert:

	-Store the number of elements that the base has
	-As long as the number we need to convert is above that number. divide it by it.
	-Take the number of iteration it took and BOOM, you're there.' you got COL

But we can't' stop here since our goal is to be able to convert floats too
So we need to account for the precision of display too.

	-basically if the precision is bigger than the number COL, then COL takes its value

Then we need to allow the right amount of memory to the new string.
Take the COL and put it in a malloc + 1 (for the \0)

Then you wanna start from the bottom of the string actually and make it so that you
take the modulo of the the value you got to that char, then you divide the value by
the base number and repeat.
