/**CFile***********************************************************************

  FileName    [menu_functions.c]

  Synopsis    [Contains the functions called by the menu]

  Description [This function are called from the main to perform the main functionalities.
							 I/O is always done here]

  SeeAlso     [menu_functions.h, data.c]

  Author      [Gabriele Gemmi]

  Author      [Jorge Peláez]

  Author      [Mariano González]

  Author      [Javier Manzano]

  Copyright   [Copyright (c) 2012 Carlos III University of Madrid
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

#include "menu_functions.h"

/*---------------------------------------------------------------------------*/
/* Definition of functions                                                   */
/*---------------------------------------------------------------------------*/

bool insert(struct table *table)
{
	/*
	Read from stdinput, Put values inside of contribution data, without allocating it. [could be interruppted]
	Then call new contribution passing contrib_data.
		*/
	char *DOI;
	struct contribution_data  *dyn_data;
	printf("\nInsert DOI: ");
	DOI = data_read_str();
	if (DOI != NULL)
	{
		if (get_contribution(table, DOI) == NULL)
		{
			dyn_data = read_contrib();
			if (dyn_data != NULL)
			{
				dyn_data->DOI=DOI;
				new_contribution(dyn_data, table);
				table->saved = false;				
				#ifdef DEBUG
					printf("\nDEBUG: Contribution added successfully");
				#endif
				return true;
			}
		}
		else
		{
			printf("DOI Already Exist");
		}
		free(DOI);
	}
	return false;
}

int contribution_cmp_year(const void *a, const void *b)
{
	struct contribution_data *a1 = *((struct contribution_data **)a);
	struct contribution_data *b1 = *((struct contribution_data **)b);
	#ifdef DEBUG
		printf("\nDEBUG\t DOI: %s %s, \tYb: %d, Ya: %d",b1->DOI, a1->DOI, b1->year, a1->year);
	#endif
	return (b1->year)-(a1->year);
}

void display_sorted(struct table *table, bool summarized)
{
	int i,j = 0,num_contributions = 0, year;
	struct contribution_node *contrib;

	if (table->num_elements == 0)
	{
		printf("\nThe table is empty");
		return;
	}

	printf("\nWhat is the starting year? ");
	year = data_read();
	if (year==-1)
		return;

	//count how many contributions do we have with year>starting year
	for (i=0;i<table->size;i++)
		for (contrib=table->contributions[i]; contrib!=NULL; contrib=contrib->next)
			if (contrib->data->year >= year) num_contributions++;

	if (num_contributions > 0)
	{
		struct contribution_data *valid_contributions[num_contributions];
		for (i=0;i<table->size;i++)
			for (contrib=table->contributions[i]; contrib!=NULL; contrib=contrib->next)
				if (contrib->data->year >= year)
					valid_contributions[j++] = contrib->data;
		#ifdef DEBUG
			printf("ordering: %d contributions", num_contributions);
		#endif
		qsort(valid_contributions, num_contributions, sizeof(struct contribution_data *), contribution_cmp_year);
		for (i=0;i<num_contributions;i++)
		{
			print_contribution(valid_contributions[i], summarized);
		}
	}
	return;
}

void display_publication(struct table *table)
{
	//Search for the contribution and print it
	char *DOI;
	struct contribution_node **publication;
	printf("\nIntroduce the DOI of the publication to display: ");
	DOI = data_read_str();
	if (DOI != NULL)
	{
		publication = get_contribution(table, DOI);
		if (publication != NULL && *publication != NULL)
			print_contribution((*publication)->data, false);
		else
			printf("Do Not Exist");
	}
	free (DOI);
	return;
}

void modify_publication(struct table *table)
{

	/*
	Read DOI
	Get the contrib_node's address using get_contrib.
	Print then read what u wanna change from stdin. [could be interruppted]
	Apply the changes in the contrib
	*/
	char *DOI, *election;
	struct contribution_node **publication;
	struct contribution_data *dyn_data;

	printf("\nIntroduce the DOI of the publication to modify: ");
	DOI = data_read_str();
	if (DOI != NULL)
	{
		publication=get_contribution(table, DOI);
		if (publication != NULL && *publication != NULL)
		{
			print_contribution((*publication)->data, false);
			printf("\nYou want to modify this publication? (y/n):   ");
			election = data_read_str();
			if (election[0] == 'y')
			{
				dyn_data = read_contrib();
				dyn_data->DOI = (*publication)->data->DOI;
				(*publication)->data->DOI = NULL;
				free_data((*publication)->data);
				(*publication)->data = dyn_data;
			}
			free(election);
			table->saved = false;

			#ifdef DEBUG
				printf("\nDEBUG: Contribution modified successfully");
			#endif
		}
		else
		{
			printf("Publication don't exist");
		}
	}
	free (DOI);
	return;
}

bool delete_publication(struct table *table)
{

	/*
	Read DOI
	Search for the pointer to the memory cell that contains the pointer to the contrib_node,
	this memory cell is where is memorized the pointer to that node, it can be the head or any pointer.
	Working on this memory location we can remove that cell mantaining the data structure.
	*/

	char *DOI, *election;
	struct contribution_node *to_free, **publication;
	bool removed=false;

	printf("\nIntroduce the DOI of the publication to delete:  ");
	DOI = data_read_str();
	if (DOI != NULL)
	{
		publication = get_contribution(table, DOI);
		if (publication != NULL && *publication != NULL)
		{
			print_contribution((*publication)->data, false);
			printf("\nYou want to delete this publication? (y/n):   ");
			election = data_read_str();
			if (election[0] == 'y')
			{
				to_free = *publication;
				*publication = to_free->next;
				free_node(to_free, true);
				removed = true;
			}
			free(election);
			--table->num_elements;
			table->saved = false;

			#ifdef DEBUG
				printf("\nDEBUG: Contribution deleted successfully");
			#endif
		}
		else
			printf("Publication don't exist");

	}
	free(DOI);
	return removed;
}

void export(struct table *table)
{
	char *file_name;
	#ifdef DEBUG
		printf("\nDEBUG: Entering export");
	#endif
	printf("Insert the name of the file you want to write:  \n");
	file_name = data_read_str();
	if (file_name != NULL)
		export_data(table,file_name);
		free(file_name);
	return;
}

void import(struct table *table)
{
	char *file_name;
	#ifdef DEBUG
		printf("\nDEBUG: Entering import");
	#endif

	printf("\nInsert the name of the file you want to read:  \n");
	file_name = data_read_str();
	if (file_name != NULL)
		import_data(table, file_name);
	return;
}
