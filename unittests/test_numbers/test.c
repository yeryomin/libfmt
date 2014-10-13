/*
 * Copyright (c) 2014 Roman Yeryomin <roman@advem.lv>
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libfmt.h>

#define TEST_FILE	"test.json"
#define RESULT_FILE	"result"
#define A(x)		assert((x) >= 0)

int main( int argc, char *argv[] )
{
	fmt_t p;
	fmt_tok_t numtok;
	double num;

	FILE *fp = fopen( RESULT_FILE, "w" );
	assert( fp != NULL );

	if ( fmt_load_file( TEST_FILE, &p, 0 ) != 0 ) {
		printf( "Cannot load file!\n" );
		goto exit;
	}

	fprintf( fp, "integer: " );
	A( fmt_get_tok( &p, NULL, "integer", &numtok ) );
	if ( fmt_is_number( &p, &numtok, &num ) )
		fprintf( fp, "%.0f\n", num );
	else
		fprintf( fp, "FAIL\n" );

	fprintf( fp, "negative: " );
	A( fmt_get_tok( &p, NULL, "negative", &numtok ) );
	if ( fmt_is_number( &p, &numtok, &num ) )
		fprintf( fp, "%.0f\n", num );
	else
		fprintf( fp, "FAIL\n" );

	fprintf( fp, "float: " );
	A( fmt_get_tok( &p, NULL, "float", &numtok ) );
	if ( fmt_is_number( &p, &numtok, &num ) )
		fprintf( fp, "%.12f\n", num );
	else
		fprintf( fp, "FAIL\n" );

exit:
	A( fmt_free( &p ) );
	fclose( fp );

	return 0;
}
