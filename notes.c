/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:16:32 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/24 12:05:15 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Basic implementation blueprint

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int  position = 0;
	static int  bytes_read = 0;
	char		*message;


/*
Core operation flow

1. Channel Check
   ┌─────────────────┐
   │  Valid Channel? │
   └────────┬────────┘
           ↓
2. Buffer Status Check
   ┌─────────────────┐
   │  Data Present?  │──→ No ──→ Read More
   └────────┬────────┘
           ↓ Yes
3. Message Extraction
   ┌─────────────────┐
   │  Find Message   │
   └────────┬────────┘
           ↓
4. Memory Operations
   ┌─────────────────┐
   │  Store Message  │
   └────────┬────────┘
           ↓
5. Clean-up & Return
*/



/*
Constraints, parameters

// Reception rules

1. Buffer Management:
   [Old Data][New Data][Empty]
   Must preserve unprocessed data between calls

2. Memory Protocol:
   - Allocate only what's needed
   - Clean deallocation on errors
   - No leaks


// Return Protocol

Success: Complete message with \\\\n (if present)
End of Stream: NULL
Error: NULL

*/


/*

Basic testing scenarios

// Primary test cases
Single
Multiple
Empty
No marker (newline)

// Buffer size variations
Minimum (1)
Standard
Maximum (9999)

*/



/*
Further considerations

Data type: struct

*/
