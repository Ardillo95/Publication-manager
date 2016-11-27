/**CHeaderFile*****************************************************************

	FileName    [data.h]

	Synopsis    [Header file for data.h]

	Description [Contains the basic structs used by the program, and the function prototypes of data.c]

	SeeAlso     [data.c]

	Author      [Jorge Peláez]

	Author      [Mariano González]

	Author      [Javier Manzano]

	Author      [Gabriele Gemmi]

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

#ifndef DATA
#define DATA

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/
/**Variable********************************************************************

	Synopsis    Initial size for the hash table

	Description The nodes of the table will be distributed according to this value

******************************************************************************/


#define INITIAL_SIZE_HASH_TABLE 3

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/
/**Enum************************************************************************

	Synopsis    Enum used to define the boolean type

******************************************************************************/

typedef enum { false, true } bool;

/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/
/**Struct**********************************************************************

	Synopsis    [Struct that contains the data of a contribution]

	Description [It will have a different distribution if article or conference]

	SeeAlso     [struct contribution_node]

******************************************************************************/
struct contribution_data
{
	char *DOI;
	char *Title;
	bool article;
	union
	{
		char *ISBN;
		char *ISSN;
	};
	char *source;
	int year;
	float impact_factor;
	char *author_name;
	union
	{
		char *venue;
		struct
		{
			int volume;
			int number;
		};
	};
};

/**Struct**********************************************************************

	Synopsis    [Main struct of the node]

	Description [Contains its data and a pointer to next node]

	SeeAlso     [struct contribution_data]

******************************************************************************/
struct contribution_node
{
	struct contribution_data *data;
	struct contribution_node *next;
};

/**Struct**********************************************************************

	Synopsis    [Struct of the hash table]


******************************************************************************/
struct table
{
	int size;
	int num_elements;
	int density;
	bool saved;
	struct contribution_node ** contributions;
};

#endif
#ifndef DATA_TYPES_F_H
#define DATA_TYPES_F_H
/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/
//Data structure function
/**Function********************************************************************

	Synopsis           Reads all data of a contribution

******************************************************************************/
struct contribution_data * read_contrib();

/**Function********************************************************************

	Synopsis           Reads a string from the keyboard and transform it into a integer

	SeeAlso            char * data_read_str()

******************************************************************************/
long int data_read();
/**Function********************************************************************

	Synopsis           Used to free the full hash table, if free_data is true
										 it will free also the contrib_data, if it's false just the structure.

	SideEffects        A new table will be needed to continue using the program

	SeeAlso            void free_nodes()
	seeAlso            void resize()

******************************************************************************/

void free_table(struct table *table, bool free_data);
/**Function********************************************************************

	Synopsis           Creates a new node, with content *data

	SideEffects        Node will be added to the hash table

******************************************************************************/
void new_contribution(struct contribution_data *data, struct table *table);
/**Function********************************************************************

	Synopsis           Prints the data of a node

	Description        This function show the information of a selected publication.
				The user can select the display format (short or long version),
				if short not all the information will be shown.

				Full information format:

					- DOI
					- Title
					- ISBN/ISSN
					- Author name
					- Year
					- Source
					- Venue/Volume and number

				Short version format:

					- DOI
					- Title
					- Year

	Parameters         bool summarized: If true, some data values will not be printed

******************************************************************************/
int print_contribution(struct contribution_data *data, bool summarized);
/**Function********************************************************************

	Synopsis           [Function called by option 3. Prints all the nodes in the table]

	Description        [This function shows a short version of each publication.]

	SeeAlso            void print_contributions()

******************************************************************************/
void print_contributions(struct table *table, bool summarized);
/**Function********************************************************************

	Synopsis           Search a node with a given DOI. Returns address of the "*next" of the previous node, so we can edit it.

******************************************************************************/
struct contribution_node ** get_contribution(struct table *table, char *DOI);
/**Function********************************************************************

	Synopsis           Hash function used to make the hash table with a ergonimic distribution

******************************************************************************/
int hash(char *DOI, int actual_size);
/**Function********************************************************************

	Synopsis           Used to free a single node, if f_data is false don't free it's data field

	SideEffects        Node cnode won't not operative again

	SeeAlso            void free_data()

******************************************************************************/
void free_node(struct contribution_node * cnode, bool f_data);
/**Function********************************************************************

	Synopsis           Increases the size of the hash table, creating a new one and erasing the old

	Description        This function will be called when the number of publication rise the size of
				the table powered by two (number of elements = size²). Then, a new table with
				size equals to actual_size +1 will be created and every element of the initial
				table will be copied to this new table. Finally, the initial table will be deleted.

	SideEffects        Old table won't be reachable again

	SeeAlso            free_table()

******************************************************************************/
void resize(struct table *table, int actual_size);

/**Function********************************************************************

	Synopsis           Used to free a row of the table, if free_data is false contrib data will remain allocated

	SideEffects        Any of the nodes in the row will be reachable

	SeeAlso            free_node()

******************************************************************************/
void free_nodes(struct contribution_node * cnode, bool free_data);
/**Function********************************************************************

	Synopsis           Used to free the data content of a node

	SideEffects        Data cdata won't be reachable again

******************************************************************************/
void free_data(struct contribution_data * cdata);
/**Function********************************************************************

	Synopsis           Reads a string from the keyboard

	SeeAlso            long int data_read()

******************************************************************************/
char * data_read_str();

/**Function********************************************************************

	Synopsis           Used to export data to a filename, called by autosave and export

	SeeAlso            export()

******************************************************************************/
void export_data(struct table *table, char *file_name);
/**Function********************************************************************

	Synopsis           Used to import data from a filename, called by import

	SeeAlso            import()

******************************************************************************/
void import_data(struct table *table, char *file_name);


/**Function********************************************************************

	Synopsis           Return a new hash table initialized to NULL

******************************************************************************/
struct contribution_node ** new_clean_table(int size);

#endif
