/*
 * lib/krb5/free/f_cred.c
 *
 * Copyright 1990 by the Massachusetts Institute of Technology.
 * All Rights Reserved.
 *
 * Export of this software from the United States of America may
 *   require a specific license from the United States Government.
 *   It is the responsibility of any person or organization contemplating
 *   export to obtain such a license before exporting.
 * 
 * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation, and that
 * the name of M.I.T. not be used in advertising or publicity pertaining
 * to distribution of the software without specific, written prior
 * permission.  M.I.T. makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is" without express
 * or implied warranty.
 * 
 *
 * krb5_free_cred()
 */


#include <krb5/krb5.h>
#include <krb5/ext-proto.h>

void INTERFACE
krb5_free_cred(context, val)
    krb5_context context;
    register krb5_cred *val;
{
    if (val->tickets)
        krb5_free_tickets(context, val->tickets);
    if (val->enc_part.ciphertext.data)
	krb5_xfree(val->enc_part.ciphertext.data);
    krb5_xfree(val);
    return;
}
