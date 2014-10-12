/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include <string.h>

#include "fmt_priv.h"


static inline int tok_is_type( fmt_tok_t *tok, jsmntype_t type )
{
	if ( tok && tok->type == type )
		return LIBFMT_TRUE;

	return LIBFMT_FALSE;
}

static inline int obj_is_type( fmt_t *obj, int type )
{
	if ( obj && obj->type == type )
		return LIBFMT_TRUE;

	return LIBFMT_FALSE;
}

inline int fmt_tok_is_object( fmt_tok_t *tok )
{
	return tok_is_type( tok, JSMN_OBJECT );
}

inline int fmt_tok_is_array( fmt_tok_t *tok )
{
	return tok_is_type( tok, JSMN_ARRAY );
}

inline int fmt_tok_is_string( fmt_tok_t *tok )
{
	return tok_is_type( tok, JSMN_STRING );
}

inline int fmt_is_object( fmt_t *obj )
{
	return fmt_tok_is_object( obj->tok );
}

inline int fmt_is_array( fmt_t *obj )
{
	return fmt_tok_is_array( obj->tok );
}

inline int fmt_is_string( fmt_t *obj )
{
	return fmt_tok_is_string( obj->tok );
}

inline int fmt_is_primitive( fmt_t *obj, fmt_tok_t *where )
{
	if ( !obj || !obj->js || !obj->tok )
		return LIBFMT_FALSE;

	if ( !tok_is_type( (where? where : obj->tok), JSMN_PRIMITIVE ) )
		return LIBFMT_FALSE;

	return LIBFMT_TRUE;
}

inline int fmt_is_bool( fmt_t *obj, fmt_tok_t *where, int tf )
{
	if ( !fmt_is_primitive( obj, where ) )
		return LIBFMT_FALSE;

	if ( !strncmp( obj->js + (where? where : obj->tok)->start,
				tf == LIBFMT_TRUE? "true" : "false",
				tf == LIBFMT_TRUE? 4 : 5 ) )
		return LIBFMT_TRUE;

	return LIBFMT_FALSE;
}

inline int fmt_is_null( fmt_t *obj, fmt_tok_t *where )
{
	if ( !fmt_is_primitive( obj, where ) )
		return LIBFMT_FALSE;

	if ( !strncmp( obj->js + (where? where : obj->tok)->start, "null", 4 ) )
		return LIBFMT_TRUE;

	return LIBFMT_FALSE;
}

inline int fmt_is_number( fmt_t *obj, fmt_tok_t *where, double *res )
{
	if ( !fmt_is_primitive( obj, where ) )
		return LIBFMT_FALSE;

	char *p;
	double tmp = strtod( obj->js + (where? where : obj->tok)->start, &p );
	if ( res )
		*res = tmp;

	if ( *p == '\0' )
		return LIBFMT_TRUE;

	return LIBFMT_FALSE;
}

inline int fmt_tok_valid( fmt_tok_t *tok )
{
	if ( !tok )
		return LIBFMT_FALSE;

	if ( tok->start < 0 || tok->end < 1 )
		return LIBFMT_FALSE;

	if ( tok->size < 0 || tok->start > tok->end )
		return LIBFMT_FALSE;

	return LIBFMT_TRUE;
}

inline int fmt_parser_valid( fmt_t *obj )
{
	if ( !obj )
		return LIBFMT_FALSE;

	if ( obj->type == FMT_TYPE_PARSER )
		return LIBFMT_TRUE;

	if ( obj->parser.toknext != -1 )
		return LIBFMT_TRUE;

	return LIBFMT_FALSE;
}
