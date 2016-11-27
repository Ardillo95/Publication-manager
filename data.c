/**CFile***********************************************************************

	FileName    [data.c]

	Synopsis    [Auxiliar functions used by the principals to manage data structures]

	SeeAlso     [data.h]

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
	OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE CARLOS III
	UNIVERSITY OF MADRID HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	THE CARLOS III UNIVERSITY OF MADRID SPECIFICALLY DISCLAIMS ANY WARRANTIES,
	INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
	FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN
	"AS IS" BASIS, AND CARLOS III UNIVERSITY OF MADRID HAS NO OBLIGATION TO
	PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.]

******************************************************************************/

#include "data.h"

/*---------------------------------------------------------------------------*/
/* Definition of functions                                                   */
/*---------------------------------------------------------------------------*/
struct contribution_data * read_contrib()
{
	/*
	*	Read a contribution from stdin, if typed Ctrl-D,
	*	deallocate and return to calling functon.
	*/
	#ifdef DEBUG
		printf("\nDEBUG: Entered read_contrib() to read the data of a contribution");
	#endif
	struct contribution_data *dyn_data;
	char *read;
	int iread = 0, choose;
	dyn_data = (struct contribution_data *)malloc(sizeof(struct contribution_data));
	printf("\nInsert Title: ");
	read = data_read_str();
	dyn_data->Title = read;
	if (read == NULL)
	{
		#ifdef DEBUG
			printf("\nDEBUG: Invalid read");
		#endif
		free_data(dyn_data);
		return NULL;
	}
	printf("\nInsert Year: ");
	iread = data_read();
	dyn_data->year = iread;
	if (iread == -1){
		#ifdef DEBUG
			printf("\nDEBUG: Invalid read");
		#endif
		free_data(dyn_data);
		return NULL;
	}
	else if (iread <= 0){
		printf("\nNo negative years or characters allowed");
		free_data(dyn_data);
		return NULL;
	}
	else if (iread > 2014){
		printf("\nYou cant add a publication that is not wrote yet!!");
		free_data(dyn_data);
		return NULL;
	}
	printf("\nInsert Author Name: ");
	read = data_read_str();
	dyn_data->author_name = read;
	if (read == NULL){
		#ifdef DEBUG
			printf("\nDEBUG: Invalid read");
		#endif
		free_data(dyn_data);
		return NULL;
	}
	printf("\nInsert Source: ");
	read = data_read_str();
	dyn_data->source = read;
	if (read == NULL){
		#ifdef DEBUG
			printf("\nDEBUG: Invalid read");
		#endif
		free_data(dyn_data);
		return NULL;
	}
	printf("\nInsert Impact Factor: ");
	if (scanf("%f", &(dyn_data->impact_factor))!=1){
		data_read();
		#ifdef DEBUG
			printf("\nDEBUG: Invalid read");
		#endif
		free_data(dyn_data);
		return NULL;
	}
	data_read();


	printf("\nWanna insert a article (1) or a conference(2)?");
	iread = data_read();
	choose = iread;
	if (choose == 1)
	{ //article:
		dyn_data->article = 1;
		printf("\nInsert ISSN: ");
		read = data_read_str();
		dyn_data->ISSN = read;
		if (read == NULL)
		{
			#ifdef DEBUG
				printf("\nDEBUG: Invalid read");
			#endif
			free_data(dyn_data);
			return NULL;
		}
		printf("\nInsert Volume #: ");
		iread = data_read();
		dyn_data->volume = iread;
		if (iread == -1)
		{

			#ifdef DEBUG
				printf("\nDEBUG: Invalid read");
			#endif
			free_data(dyn_data);
			return NULL;
		}
		else if (iread <= 0){
			printf("\nNo negative volumes or characters allowed");
			free_data(dyn_data);
			return NULL;
		}
		printf("\nInsert Paper #: ");
		iread = data_read();
		dyn_data->number = iread;
		if (iread == -1)
		{
			#ifdef DEBUG
				printf("\nDEBUG: Invalid read");
			#endif
			free_data(dyn_data);
			return NULL;
		}
		else if (iread <= 0){
			printf("\nNo negative papers or characters allowed");
			free_data(dyn_data);
			return NULL;
		}
	}
	else if (choose == 2)
	{ //contribution
		dyn_data->article = 0;
		printf("\n Insert ISBN: ");
		read = data_read_str();
		dyn_data->ISBN = read;
		if (read == NULL)
		{
			#ifdef DEBUG
				printf("\nDEBUG: Invalid read");
			#endif
			free_data(dyn_data);
			return NULL;
		}
		printf("\n Insert Venue: ");
		read = data_read_str();
		dyn_data->venue = read;
		if (read == NULL)
		{
			#ifdef DEBUG
				printf("\nDEBUG: Invalid read");
			#endif
			free_data(dyn_data);
			return NULL;
		}
	}
	else
	{
		printf("Option invalid, not article (1) nor conference (2)");
		free_data(dyn_data);
		return NULL;
	}

return dyn_data;
}


void free_node(struct contribution_node * cnode, bool f_data)
{
	/*	Deallocate a node, if f_data is true deallocate also the data.

	*/
	if (cnode != NULL){
		if (f_data)
			free_data(cnode->data);
		free(cnode);
	}
}

void free_data(struct contribution_data * cdata)
{
	if (cdata->DOI!=NULL)
		free(cdata->DOI);
	if (cdata->ISBN!=NULL)
		free(cdata->ISBN);
	if (cdata->Title!=NULL)
		free(cdata->Title);
	if (cdata->source!=NULL)
		free(cdata->source);
	if (cdata->author_name!=NULL)
		free(cdata->author_name);
	if (!(cdata->article))
		if (cdata->venue!=NULL)
			free(cdata->venue);
}

void free_table(struct table *table, bool free_data)
{
	int i;
		for (i = 0; i < table->size; i++)
		{
			if (table->contributions[i] != NULL)
				free_nodes(table->contributions[i], free_data);
		}

		free(table->contributions);

		#ifdef DEBUG
			printf("\nDEBUG: Free table successfully");
		#endif
		return;
}

void free_nodes(struct contribution_node * cnode, bool free_data)
{
	/*	This function recursively deallocate  all the nodes of a contribution_node
	*		list
	*/
	if (cnode->next != NULL)
		free_nodes(cnode->next, free_data);
	free_node(cnode, free_data);
	return;

}

struct contribution_node ** new_clean_table(int size)
{
	/*
	*		Make a new hash table of size 'size' and initialize it to all 0s
	*/
	int i;
	struct contribution_node ** contributions = (struct contribution_node **)malloc(size*sizeof(struct contribution_node *));
	for (i=0;i<size;i++)
	{
		contributions[i] = NULL;
	}
	return contributions;
}

void resize(struct table *table, int actual_size)
{
	/*	To resize the table we re-insert all the contrib of the preovious one in
	*		the new hash tabe, then put it where the old one was (table-contributions)
	*/
	int i;
	struct contribution_node * current_contribution;
	struct table resized_library;

	resized_library.size = actual_size;
	resized_library.num_elements = 0;
	resized_library.contributions = new_clean_table(actual_size);

	for (i=0;i<table->size;i++)
		for (current_contribution=table->contributions[i]; current_contribution!=NULL; current_contribution=current_contribution->next)
			new_contribution(current_contribution->data, &resized_library);

	free_table(table, false);
	table->size = actual_size;
	table->num_elements = resized_library.num_elements;
	table->contributions = resized_library.contributions;


	#ifdef DEBUG
		printf("\nDEBUG: Table resized!");
	#endif
	return;
}

int hash(char *str, int actual_size)
{
	char *mob_str;
	int hash = 13;

	for (mob_str=str; *mob_str!='\0'; mob_str++)
		hash = ((7*hash) + (int)*mob_str)%actual_size;

	hash = hash%actual_size;
	return hash;
}

long int data_read()
{
	int data;
	long int str_to_int;
	size_t bytes_number = 0;
	char *string = NULL, *ptr;
	data = getline(&string,&bytes_number,stdin);
	if (data == -1)
	{
		#ifdef DEBUG
			printf("\nUser wanna exit");
		#endif
		free(string);
		return -1;
	}
	else
	{
		string[strlen(string)-1] = '\0';
		str_to_int = strtol(string,&ptr,10);
	}
	free(string);

	return str_to_int;
}

char * data_read_str()
{
	int data;
	size_t bytes_number = 0;
	char *string = NULL;
	data = getline(&string,&bytes_number,stdin);
	string[strlen(string)-1] = '\0';
	if (data == -1){
		free(string);
		#ifdef DEBUG
			printf("\nUser wanna exit");
		#endif
		return NULL;
	}
	return string;
}

void new_contribution(struct contribution_data *data, struct table *table)
{
	/*
	This function need to search for the author of the contrib. If it doesn't exist it has to be created.
	after it has to allocate the contrib_node, put it into the linked list (in head) and put the data inside.
	*/

	struct contribution_node * cnode = (struct contribution_node *)malloc(sizeof(struct contribution_node));
	cnode->data = data;
	if (data->DOI != NULL)
	{
		cnode->next = table->contributions[hash(data->DOI,table->size)];
		table->contributions[hash(data->DOI,table->size)] = cnode;
		++table->num_elements;
		table->saved = false;
		#ifdef DEBUG
			printf("\nDEBUG: Insertion complete.");
		#endif
	}
	return;

}

int print_contribution(struct contribution_data *data, bool summarized)
{
	if (summarized == true)
	{
		printf("\nDOI: %s", data->DOI);
		printf("\nTitle: %.30s", data->Title);
		printf("\nyear: %d", data->year);
	}
	else
	{
		printf("\nDOI: %s", data->DOI);
		printf("\nTitle: %s", data->Title);
		if (data->article == 0)
			printf("\nISBN: %s", data->ISBN);
		else
			printf("\nISSN: %s", data->ISSN);

		printf("\nAuthor: %s", data->author_name);
		printf("\nYear: %d", data->year);
		printf("\nSource: %s", data->source);
		if (data->article == 0)
			printf("\nVenue: %s", data->venue);
		else
			printf("\nVolumes: %d \nPublication: %d", data->volume, data->number);

	}
	printf("\n");
	return 0;
}

void print_contributions(struct table *table, bool summarized)
{
	int i;
	struct contribution_node * current_contribution;

	if (table->num_elements == 0) printf("\nThe table is empty");

	for (i = 0; i < table->size; i++)
		for (current_contribution = table->contributions[i]; current_contribution != NULL; current_contribution = current_contribution->next)
			print_contribution(current_contribution->data,summarized);


}

struct contribution_node ** get_contribution(struct table *table, char *DOI)
{
	/*
	Return pointer to pointer of contribution_node of a given DOI.
	Return address of the "*next" of the previous node, so we can edit it or delete it.
	*/
	struct contribution_node * cnode;
	int i = hash(DOI,table->size);

	for (cnode = table->contributions[i]; cnode != NULL; cnode = cnode->next)
	{
		if (cnode == NULL) return NULL;
		if ((cnode == table->contributions[i]) && (strcmp(DOI,  cnode->data->DOI)==0))
			//if is the first we must return the address of "first" in author_node
			return &(table->contributions[i]);
		else if (cnode->next != NULL)
			if (strcmp(DOI, cnode->next->data->DOI) == 0)
				return &cnode->next;
	}
	return NULL;

}


void export_data(struct table *table, char *file_name)
{
	//Export table to given filename
	FILE *file_ptr;
	int i;
	struct contribution_node *cnode;
	struct contribution_data *cdata, temp_cdata;
	size_t string_length;

	file_ptr=fopen(file_name, "w");

	if (file_ptr != NULL)
	{
		#ifdef DEBUG
			printf("\nDEBUG: File successfully opened in write mode");
		#endif
		fwrite(&table->num_elements, sizeof(int), 1,file_ptr);
		for (i = 0; i != table->size; i++)
		for (cnode = table->contributions[i]; cnode != NULL; cnode = cnode->next)
		{
			cdata = cnode->data;
			memcpy(&temp_cdata, cdata, sizeof(struct contribution_data));
			temp_cdata.DOI = NULL;
			temp_cdata.Title = NULL;
			temp_cdata.author_name = NULL;
			temp_cdata.source = NULL;
			temp_cdata.ISSN = NULL;
			if (!temp_cdata.article)
			{
				temp_cdata.venue = NULL;
			}

			fwrite(&temp_cdata, sizeof(struct contribution_data), 1, file_ptr);

			string_length = strlen(cdata->DOI)+1;
			fwrite(&string_length, sizeof(size_t), 1, file_ptr);
			fwrite(cdata->DOI, sizeof(char), string_length, file_ptr);

			string_length = strlen(cdata->Title)+1;
			fwrite(&string_length, sizeof(size_t), 1, file_ptr);
			fwrite(cdata->Title, sizeof(char), string_length, file_ptr);

			string_length = strlen(cdata->author_name)+1;
			fwrite(&string_length, sizeof(size_t), 1, file_ptr);
			fwrite(cdata->author_name, sizeof(char), string_length, file_ptr);

			string_length = strlen(cdata->source)+1;
			fwrite(&string_length, sizeof(size_t), 1, file_ptr);
			fwrite(cdata->source, sizeof(char), string_length, file_ptr);

			if (cdata->article)
			{
				string_length = strlen(cdata->ISSN)+1;
				fwrite(&string_length, sizeof(size_t), 1, file_ptr);
				fwrite(cdata->ISSN, sizeof(char), string_length, file_ptr);
			}
			else
			{
				string_length = strlen(cdata->ISSN)+1;
				fwrite(&string_length, sizeof(size_t), 1, file_ptr);
				fwrite(cdata->ISSN, sizeof(char), string_length, file_ptr);

				string_length = strlen(cdata->venue)+1;
				fwrite(&string_length, sizeof(size_t), 1, file_ptr);
				fwrite(cdata->venue, sizeof(char), string_length, file_ptr);
			}
			#ifdef DEBUG
				printf("\nDEBUG: Contribution exported!");
			#endif
		}
		fputc(EOF,file_ptr);
		table->saved=true;
	}
	else
	{
		printf("Error opening the file\n");
		return;
	}
	fclose(file_ptr);
		#ifdef DEBUG
			printf("\nDEBUG: File closed");
		#endif
	return;

}


void import_data(struct table *table, char *file_name)
{
	// import data to table from a given filname
	FILE *file_ptr;
	struct contribution_data *cdata;
	int read,books;
	size_t string_length;

	file_ptr = fopen(file_name, "r");
	free(file_name);

	if (file_ptr != NULL)
	{
		#ifdef DEBUG
			printf("\nDEBUG: File successfully opened in reading mode");
		#endif

		fread(&books, sizeof(int), 1,file_ptr);
		for (read = 0;!feof(file_ptr) && read<books;read++)
		{
			cdata = (struct contribution_data *)malloc(sizeof(struct contribution_data));
			fread(cdata, sizeof(struct contribution_data), 1, file_ptr);
			fread(&string_length, sizeof(size_t), 1, file_ptr);
			cdata->DOI = (char*)malloc(sizeof(char)*string_length);
			fread(cdata->DOI, sizeof(char), string_length, file_ptr);
			fread(&string_length, sizeof(size_t), 1, file_ptr);
			cdata->Title = (char*)malloc(sizeof(char)*string_length);
			fread(cdata->Title, sizeof(char), string_length, file_ptr);
			fread(&string_length, sizeof(size_t), 1, file_ptr);
			cdata->author_name = (char*)malloc(sizeof(char)*string_length);
			fread(cdata->author_name, sizeof(char), string_length, file_ptr);
			fread(&string_length, sizeof(size_t), 1, file_ptr);
			cdata->source = (char*)malloc(sizeof(char)*string_length);
			fread(cdata->source, sizeof(char), string_length, file_ptr);
			if (cdata->article)
			{
				fread(&string_length, sizeof(size_t), 1, file_ptr);
				cdata->ISSN = (char*)malloc(sizeof(char)*string_length);
				fread(cdata->ISSN, sizeof(char), string_length, file_ptr);
			}
			else
			{
				fread(&string_length, sizeof(size_t), 1, file_ptr);
				cdata->ISBN = (char*)malloc(sizeof(char)*string_length);
				fread(cdata->ISBN, sizeof(char), string_length, file_ptr);
				fread(&string_length, sizeof(size_t), 1, file_ptr);
				cdata->venue = (char*)malloc(sizeof(char)*string_length);
				fread(cdata->venue, sizeof(char), string_length, file_ptr);
			}
			#ifdef DEBUG
				printf("\nDEBUG: Creating contribution");
			#endif
			if (get_contribution(table, cdata->DOI)==NULL)
				new_contribution(cdata, table);
			else
			{
				#ifdef DEBUG
					printf("\nDOI Already Existing\n");
				#endif
				free_data(cdata);
			}
		}
		fclose(file_ptr);
		#ifdef DEBUG
			printf("\nDEBUG: File closed");
		#endif
	}
	else {
		printf("\nError opening the file. Does it exist? ");
	}
	return;
}
