/*
 * gssapi.h --- header file for the Kerberos 5 GSS API layer
 */

#include <krb5/krb5.h>
#include <krb5/osconf.h>
#include <krb5/ext-proto.h>
#include <krb5/los-proto.h>
#include <krb5/func-proto.h>
#include <com_err.h>

/*
 * Some compilers can't handle void *
 */
#ifdef __STDC__
#define Voidptr void *
#else
#define Voidptr char *
#endif

typedef unsigned int	OM_uint32;
typedef unsigned short	OM_uint16;

typedef struct gss_buffer_desc_struct {
	size_t	length;
	Voidptr value;
} gss_buffer_desc, *gss_buffer_t;

typedef struct gss_OID_desc {
	OM_uint32	length;
	void	*elements;
} *gss_OID;

typedef struct gss_OID_set_desc {
	OM_uint32	count;
	struct gss_OID_desc	*elements;
} *gss_OID_set;

typedef struct gss_ctx_id_desc {
	gss_OID		mech_type;
	int		state;
	int		flags;		/* gss_init_sec_context flags */
	krb5_boolean	am_client; 	/* True if I am the client */
	krb5_principal	me;
	krb5_principal	him;		/* Principal of the other side */
	krb5_address	my_address;
	krb5_address	his_address;
	krb5_keyblock	*session_key;
	krb5_rcache	rcache;
	krb5_int32	my_seq_num;
	krb5_int32	his_seq_num;
	krb5_int32	cusec;		/* Client usec portion */
	krb5_timestamp	ctime;		/* Client sec portion */
} *gss_ctx_id_t;

/* structure for address */
typedef struct gss_channel_bindings_desc {
    OM_uint32		initiator_addrtype;
    gss_buffer_desc	initiator_address;
    OM_uint32		acceptor_addrtype;
    gss_buffer_desc	acceptor_address;
    gss_buffer_desc	application_data;
} *gss_channel_bindings;

#define	GSS_C_AF_INET	0x0002
#define	GSS_C_AF_CHAOS	0x0005
#define	GSS_C_AF_XNS	0x0006
#define	GSS_C_AF_ISO	0x0007
#define GSS_C_AF_DDP	0x0010

#define GSS_KRB_STATE_DOWN	1
#define GSS_KRB_STATE_MUTWAIT	2
#define GSS_KRB_STATE_UP	3

typedef krb5_principal gss_name_t;

typedef struct gss_cred_id_desc {
	krb5_principal		principal;
	gss_OID			mech_type;
	int			cred_flags;
	/* Client information */
	krb5_ccache		ccache;
	/* Server information */
	krb5_kvno 		kvno;
	krb5_keyblock		srvtab;
} gss_cred_id_t;

#define GSS_KRB_HAS_CCACHE	0x0001
#define GSS_KRB_HAS_SRVTAB	0x0002

/*
 * Optional parameters
 */

#define GSS_C_NO_BUFFER		((gss_buffer_t) 0)
#define GSS_C_NULL_OID	       	((gss_OID) 0)
#define GSS_C_NULL_OID_SET	((gss_OID_set) 0)
#define GSS_C_NO_CREDENTIAL	(gss_default_credentials)

extern gss_cred_id_t	gss_default_credentials;

/*
 * Indefinite time
 */
#define GSS_TIME_REC_INDEFINITE 2147483647

/*
 * Token format:
 *
 * Byte 0:	GSS API Implementation Version (currently 1)
 * Byte 1:	Mechanism Identifier (currently 1 means Kerberos V5)
 * Byte 2:	Token type
 * Byte 3:	Reserved
 * Byte 4--n:	Mechanism/Token information
 */

#define GSS_API_IMPL_VERSION	1

#define GSS_API_KRB5_TYPE	1

/* Token types */
#define GSS_API_KRB5_REQ	1
#define GSS_API_KRB5_REP	2
#define GSS_API_KRB5_SAFE	3
#define GSS_API_KRB5_PRIV	4
#define GSS_API_KRB5_SIGN	5
#define GSS_API_KRB5_ERROR	6
#define GSS_API_KRB5_SHUTDOWN	31

/*
 * Calling errors
 */
#define GSS_S_CALL_INACCESSIBLE_READ	(1 << 24)
#define GSS_S_CALL_INACCESSIBLE_WRITE	(2 << 24)
#define GSS_S_CALL_BAD_STRUCTURE	(3 << 24)

/*
 * Routine Errors
 */
#define GSS_S_BAD_MECH			(1 << 16)
#define GSS_S_BAD_NAME			(2 << 16)
#define GSS_S_BAD_NAMETYPE		(3 << 16)
#define GSS_S_BAD_BINDINGS		(4 << 16)
#define GSS_S_BAD_STATUS		(5 << 16)
#define GSS_S_BAD_SIG			(6 << 16)
#define GSS_S_NO_CRED			(7 << 16)
#define GSS_S_NO_CONTEXT		(8 << 16)
#define GSS_S_DEFECTIVE_TOKEN		(9 << 16)
#define GSS_S_DEFECTIVE_CREDENTIAL	(10 << 16)
#define GSS_S_CREDENTIALS_EXPIRED	(11 << 16)
#define GSS_S_CONTEXT_EXPIRED		(12 << 16)
#define GSS_S_FAILURE			(13 << 16)

/*
 * Supplementary Status Bits
 */
#define GSS_S_CONTINUE_NEEDED	(1 << 0)
#define GSS_S_DUPLICATE_TOKEN	(1 << 1)
#define GSS_S_OLD_TOKEN		(1 << 2)
#define GSS_S_UNSEQ_TOKEN	(1 << 3)

#define GSS_S_COMPLETE		0

/*
 * Macros to break apart a return code
 */

#define gss_calling_error(r) 		((r) & 0xff000000)
#define gss_routine_error(r) 		((r) & 0x00ff0000)
#define gss_supplementary_info(r)	((r) & 0x0000ffff)

/*
 * gss_acquire_cred --- cred_usage values
 */
#define GSS_C_INITIATE	0x0001
#define GSS_C_ACCEPT	0x0002
#define GSS_C_BOTH	0x0003
	
/*
 * gss_init_sec_context flags
 */
#define GSS_C_DELEG_FLAG	0x0001
#define GSS_C_MUTUAL_FLAG	0x0002
#define GSS_C_REPLAY_FLAG	0x0004
#define GSS_C_SEQUENCE_FLAG	0x0008
#define GSS_C_CONF_FLAG		0x0010

/*
 * Values for qop_req
 */
#define GSS_C_QOP_DEFAULT	0

/*
 * Values for gss_display_status
 */
#define GSS_C_GSS_CODE	1
#define GSS_C_MECH_CODE 2

/*
 * OID declarations
 */
extern struct gss_OID_desc gss_OID_krb5;
extern struct gss_OID_desc gss_OID_krb5_name;

/*
 * XXX Stuff to make Kannan's flogin stuff happy.
 */
#define GSS_C_MAX_TOKEN 1024
#define GSS_C_MAX_PRINTABLE_NAME 1024

#define GSS_C_READ       (1 << 0)
#define GSS_C_WRITE      (1 << 1)
#define GSS_C_EXECUTE    (1 << 2)

/*
 * Function declaragions, generated by mkptypes
 */
/* ac_cred.c */
OM_uint32 gss_acquire_cred PROTOTYPE((OM_uint32 *minor_status,
				      gss_name_t desired_name,
				      OM_uint32 time_req,
				      gss_OID_set desired_mechs,
				      int cred_usage,
				      gss_cred_id_t *output_cred_handle,
				      gss_OID_set *actual_mechs,
				      OM_uint32 *time_rec)); 

/* acc_sec.c */
OM_uint32 gss_accept_sec_context PROTOTYPE((OM_uint32 *minor_status,
					    gss_ctx_id_t *context_handle,
					    gss_cred_id_t verifier_cred_handle,
					    gss_buffer_t input_token,
					    gss_channel_bindings channel,
					    gss_name_t *src_name,
					    gss_OID *mech_type,
					    gss_buffer_t output_token,
					    int *ret_flags,
					    OM_uint32 *time_rec,
					    gss_cred_id_t *delegated_cred_handle));

/* check_tok.c */
OM_uint32 gss_check_token PROTOTYPE((OM_uint32 *minor_status,
				     gss_buffer_t input_token,
				     unsigned int mechanism,
				     unsigned int type));

/* cmp_name.c */
OM_uint32 gss_compare_name PROTOTYPE((OM_uint32 *minor_status,
				      gss_name_t name1,
				      gss_name_t name2,
				      int *name_equal));

/* comp_oid.c */
int gss_compare_OID PROTOTYPE((gss_OID oid1,
			       gss_OID oid2));

/* dsp_name.c */
OM_uint32 gss_display_name PROTOTYPE((OM_uint32 *minor_status,
				      gss_name_t input_name,
				      gss_buffer_t output_name_buffer,
				      gss_OID *output_name_type));

/* imp_name.c */
OM_uint32 gss_import_name PROTOTYPE((OM_uint32 *minor_status,
				     gss_buffer_t input_name_buffer,
				     gss_OID input_name_type,
				     gss_name_t *output_name));
OM_uint32 gss_service_import_name PROTOTYPE((OM_uint32 *minor_status,
					     gss_buffer_t input_name_buffer,
					     gss_name_t *output_name));

/* ind_mechs.c */
OM_uint32 gss_indicate_mechs PROTOTYPE((OM_uint32 *minor_status,
					gss_OID_set *mech_set));

/* init_sec.c */
OM_uint32 gss_init_sec_context PROTOTYPE((OM_uint32 *minor_status,
					  gss_cred_id_t claimant_cred_handle,
					  gss_ctx_id_t *context_handle,
					  gss_name_t target_name,
					  gss_OID mech_type,
					  int req_flags,
					  int time_req,
					  gss_channel_bindings channel,
					  gss_buffer_t input_token,
					  gss_OID *actual_mech_type,
					  gss_buffer_t output_token,
					  int *ret_flags,
					  OM_uint32 *time_rec));

/* make_tok.c */
OM_uint32 gss_make_token PROTOTYPE((OM_uint32 *minor_status,
				    unsigned int mechanism,
				    unsigned int type,
				    size_t length,
				    Voidptr data,
				    gss_buffer_t output_token));

/* rel_buffer.c */
OM_uint32 gss_release_buffer PROTOTYPE((OM_uint32 *minor_status,
					gss_buffer_t buffer));

/* rel_cred.c */
OM_uint32 gss_release_cred PROTOTYPE((OM_uint32 *minor_status,
				      gss_cred_id_t *cred_handle));

/* rel_name.c */
OM_uint32 gss_release_name PROTOTYPE((OM_uint32 *minor_status,
				      gss_name_t *name));

/* rel_oidset.c */
OM_uint32 gss_release_oid_set PROTOTYPE((OM_uint32 *minor_status,
					 gss_OID_set set));

/* rel_sec.c */
OM_uint32 gss_release_security_context PROTOTYPE((OM_uint32 *minor_status,
						  gss_ctx_id_t context));

/* seal.c */
OM_uint32 gss_seal PROTOTYPE((OM_uint32 *minor_status,
			      gss_ctx_id_t context,
			      int conf_req_flag,
			      int qop_req,
			      gss_buffer_t input_message_buffer,
			      int *conf_state,
			      gss_buffer_t output_message_buffer));
OM_uint32 gss_sign PROTOTYPE((OM_uint32 *minor_status,
			      gss_ctx_id_t context,
			      int qop_req,
			      gss_buffer_t input_message_buffer,
			      gss_buffer_t output_message_buffer));

/* sign.c */
OM_uint32 gss_sign PROTOTYPE((OM_uint32 *minor_status,
			      gss_ctx_id_t context,
			      int qop_req,
			      gss_buffer_t input_message_buffer,
			      gss_buffer_t output_message_buffer));

/* unseal.c */
OM_uint32 gss_unseal PROTOTYPE((OM_uint32 *minor_status,
				gss_ctx_id_t context,
				gss_buffer_t input_message_buffer,
				gss_buffer_t output_message_buffer,
				int *conf_state,
				int *qop_state));
OM_uint32 gss_verify PROTOTYPE((OM_uint32 *minor_status,
				gss_ctx_id_t context,
				gss_buffer_t message_buffer,
				gss_buffer_t token_buffer,
				int *qop_state));

/* verify.c */
OM_uint32 gss_verify PROTOTYPE((OM_uint32 *minor_status,
				gss_ctx_id_t context,
				gss_buffer_t message_buffer,
				gss_buffer_t token_buffer,
				int *qop_state));

