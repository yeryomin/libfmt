/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <libfmt.h>

int main( int argc, char **argv )
{
	int i, count = 100;
	char *file = argv[1];
	if (argc > 2)
		count = atoi(argv[2]);

	for (i = 1; i <= count; i++) {
		fmt_t p=FMT_NULL;
		/*
		 * Here parser size is expected json token count, no matter of what size.
		 * Every key, string, object, array or their element counts as a token.
		 * Parser performs better when it's size is smaller.
		 */
		if (fmt_load_file( file, &p, 0 ) < 0) {
			printf("cannot load file\n");
			fmt_free( &p );
			exit(EXIT_FAILURE);
		}
		printf("JSON file %s loaded %i times\n", file, i);

		char *temp = NULL;
		if ( !fmt_del( &p, NULL, "config" ) ) {
			fmt_dump_string( &p, NULL, &temp );
			printf("\n%s\n",temp);
		}
		free(temp);

		char *key = NULL;
		fmt_tok_t obj_iter;
		memset( &obj_iter, 0, sizeof(fmt_tok_t) );
		printf("\niter start\n");
		while ( fmt_object_next( &p, NULL, &obj_iter, &key ) > 0) {
			char *obj = NULL;
			fmt_dump_string( &p, &obj_iter, &obj );
			printf("'%s' : '%s'\n", key, obj);
			free(obj);
			free(key);
		}
		printf("iter stop\n");

		fmt_free( &p );
	}
	printf("\n");

	exit(EXIT_SUCCESS);
}
