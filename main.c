/**CFile***********************************************************************

	FileName    [main.c]

	Synopsis    [Efficent Bibmanager using Hashtable]

	Description [Main file of the program, that contains the menu and calls the necesarity functions on menu_functions.c]

	SeeAlso     [main.h, menu_functions.c]

	Author      [Gabriele Gemmi]

	Author      [Jorge Peláez]

	Author      [Mariano González]

	Author      [Javier Manzano]

	Copyright   [Copyright (c) 2011 Carlos III University of Madrid
	All rights reserved.

	Permission is hereby granted, without written agreement and without license
	or royalty fees, to use, copy, modify, and distribute this software and its
	documentation for any purpose, provided that the above copyright notice and
	the following two paragraphs appear in all copies of this software.

	IN NO EVENT SHALL THE CARLOS III UNIVERSITY OF MADRID BE LIABLE TO ANY PARTY
	FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING
	OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE CARLOS III
	UNIVERSITY OF MADRID HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	THE CARLOS III UNIVERSITY OF MADRID SPECIFICALLY DISCLAIMS ANY WARRANTIES,
	INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
	FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN
	"AS IS" BASIS, AND CARLOS III UNIVERSITY OF MADRID HAS NO OBLIGATION TO
	PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.]

******************************************************************************/

#include "main.h"

/*---------------------------------------------------------------------------*/
/* Definition of functions                                                   */
/*---------------------------------------------------------------------------*/
int main(int arg_count, char *arg_strings[])
{
	int exit = 0;
	int option;
	struct table library;
	library.size = INITIAL_SIZE_HASH_TABLE;
	library.num_elements = 0;
	library.saved = true;
	int actual_size = INITIAL_SIZE_HASH_TABLE;
	library.contributions = new_clean_table(INITIAL_SIZE_HASH_TABLE);

	while (exit == 0)
	{
		system("clear");
		print_menu();
		option = data_read(&library);
		if (option == -1)
			option = 1;
		if (option < 1 || option > 9)
			printf("Invalid option");
		switch (option)
		{
			case 1:
				if (library.saved == false)
				{
					char *election;
					printf("Do you want to save changes? (y/n)");
					election = data_read_str();
					if (election[0] == 'y')
					{
						export(&library);
					}
					free(election);
				}
				free_table(&library, true);
				exit=1;
				break;
			case 2:
				insert(&library);
				break;
			case 3:
				print_contributions(&library, 1);
				break;
			case 4:
				display_publication(&library);
				break;
			case 5:
				modify_publication(&library);
				break;
			case 6:
				delete_publication(&library);
				break;
			case 7:
				export(&library);
				break;
			case 8:
				import(&library);
				break;
			case 9:
				display_sorted(&library, 1);
				break;
		}
		if (library.num_elements >= ((library.size+1)*(library.size+1)))
		{
			while (library.num_elements >= ((actual_size+1)*(actual_size+1)))
				++actual_size;
			resize(&library, actual_size);
		}
		printf("\n\nPress a key to continue...");
		data_read();
	}
	system("clear");
	printf("\n\nHasta Luego!\n");
	return 0;
}

/*---------------------------------------------------------------------------*/
/* Definition of static functions                                            */
/*---------------------------------------------------------------------------*/
void print_menu()
{

	#ifdef DEBUG
		printf("\n\n *** DEBUG MODE *** ");
	#endif
	printf("=HASH-BIBMANAGER (Efficient Edd.)=\n\n"
	"[1]\tExit\n"
	"[2]\tInsert\n"
	"[3]\tDisplay all\n"
	"[4]\tDisplay a publication\n"
	"[5]\tModify a publication\n"
	"[6]\tDelete a publication\n"
	"[7]\tExport to file\n"
	"[8]\tImport from file\n"
	"[9]\tDisplay shorted publications (by year)\n\n");
	printf("Enter an option: ");
	return;
}
