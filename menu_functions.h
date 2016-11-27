/**CHeaderFile*****************************************************************

  FileName    [menu_functions.h]

  Synopsis    [Declarations of the main file]

  Description [Here there are the declarations of the main file: menu_functions.c]

  SeeAlso     [menu_functions.c]

  Author      [Mariano González]

  Author      [Javier Manzano]

  Author      [Gabriele Gemmi]

  Author      [Jorge Peláez]

  Copyright   [Copyright (c) 2012 Carlos III University of Madrid
  All rights reserved.

  Permission is hereby granted, without written agreement and without license
  or royalty fees, to use, copy, modify, and distribute this software and its
  documentation for any purpose, provided that the above copyright notice and
  the following two paragraphs appear in all copies of this software.

  IN NO EVENT SHALL THE CARLOS III UNIVERSITY OF MADRID BE LIABLE TO ANY PARTY
  FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING
  OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF CARLOS III
  UNIVERSITY OF MADRID HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  CARLOS III UNIVERSITY OF MADRID SPECIFICALLY DISCLAIMS ANY WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN
  "AS IS" BASIS, AND CARLOS III UNIVERSITY OF MADRID HAS NO OBLIGATION TO
  PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.]

******************************************************************************/
#ifndef BASICS
#define BASICS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#endif

#ifndef MENU_F_H
#define MENU_F_H

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/
/**Function********************************************************************

  Synopsis           [Shows the information of a selected publication]

  Description        [This function shows the information of a publication. You will need
		     to insert a DOI while the function is running and then the function will
		     call print_contribution function in order to show the information of this
		     publication. A full version of the publication will be shown]

  Parameters         [struct table *table]

  SideEffects        [required]

  SeeAlso            [print_contribution function in data.h]

******************************************************************************/
void display_publication(struct table *table);
/**Function********************************************************************

  Synopsis           [Function called by option 9]

  Description        [Prints all the contributions sorting by the year, with an initial year and
         both display versions (short and long) can be shown depending on the user's decision]

  SideEffects        [The user can select if the information of each publicaton will be shown
         in a short version or not.
         The user will be asked about a starting year, publications of previous years
         won't be shown]

  Parameters         [bool summarized: If true, some data values will not be printed ]

  SeeAlso            [int contribution_cmp_year()]

  SeeAlso            [void print_contribution()]

******************************************************************************/

void display_sorted(struct table *table, bool summarized);
/**Function********************************************************************

  Synopsis           [Function called by option 5. Modify the information of a publication]

  Description        [This function allows the user to change the information of a selected publication ]

  SeeAlso            [struct contribution_node ** get_contribution()]

  SeeAlso            [void print_contribution()]

******************************************************************************/
void modify_publication(struct table *table);
/**Function********************************************************************

  Synopsis           [Function called by option 6]

  Description        [Erases a node given its DOI]

  SeeAlso            [struct contribution_node ** get_contribution()]

  SeeAlso            [void free_node()]

  SeeAlso            [void print_contribution()]

******************************************************************************/
bool delete_publication(struct table *table);
/**Function********************************************************************

  Synopsis           [Function called by option 7]

  Description        [Exports all the table to a file]

  SeeAlso            [void export_data()]

  SeeAlso            [int import ()]

******************************************************************************/
void export(struct table *table);
/**Function********************************************************************

  Synopsis           [Function called by option 8]

  Description        [Import nodes from a file]

  SeeAlso            [void export()]

******************************************************************************/
void import (struct table *table);
/**Function********************************************************************

  Synopsis           [Used to sort nodes in an array]

******************************************************************************/
int contribution_cmp_year(const void *a, const void *b);
/**Function********************************************************************

  Synopsis           [Function called by option 2]

  Description        [Inserts a new node in the table]

  SideEffects        [Table will increase its number on elements. If number of elements
         is equals to (size of the table)², then the table will increase her
         size calling the function resize (this call will take place in the main
         function)]

  SeeAlso            [struct contribution_node ** get_contribution()]

  SeeAlso            [struct contribution_data * read_contrib()]

  SeeAlso            [void new_contribution()]

  SeeAlso            [void resize()]

******************************************************************************/
bool insert(struct table *table);




#endif
