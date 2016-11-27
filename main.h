/**CHeaderFile*****************************************************************

  FileName    [main.h]

  Synopsis    [Header file for main.c]

  Description [Loads the basic libraries and other files, and contains the prototype functions for main.c]

  SeeAlso     [main.c]

  Author      [Javier Manzano]

  Author      [Gabriele Gemmi]

  Author      [Jorge Peláez]

  Author      [Mariano González]

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

#ifndef MAIN
#define MAIN

#include "data.c"
#include "menu_functions.c"
/*#include "autosave.c"*/

#endif

#ifndef MAIN_H
#define MAIN_H
/*--------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/
/**Function********************************************************************

  Synopsis           Main function of the program

  Description        Creates the table and has a loop to use the menu

  Parameters         char *arg_strings[]:

  SideEffects        Creates and allocates the hash table

******************************************************************************/
int main(int arg_count, char *arg_strings[]);
/**Function********************************************************************

  Synopsis           Prints the menu

  Description        This function show the menu. This menu looks like this:

         =HASH-BIBMANAGER (Efficient Edd.)=

         [1]     Exit
         [2]     Insert
         [3]     Display all
         [4]     Display a publication
         [5]     Modify a publication
         [6]     Delete a publication
         [7]     Export to file
         [8]     Import from file
         [9]     Display shorted publications (by year)

         Enter an option:


******************************************************************************/
void print_menu();

#endif
