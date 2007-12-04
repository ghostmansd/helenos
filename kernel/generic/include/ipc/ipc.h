/*
 * Copyright (c) 2006 Ondrej Palkovsky
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/** @addtogroup genericipc
 * @{
 */
/** @file
 */

#ifndef KERN_IPC_H_
#define KERN_IPC_H_

/* Length of data being transfered with IPC call */
/* - the uspace may not be able to utilize full length */
#define IPC_CALL_LEN		6	

/** Maximum active async calls per thread */
#ifdef CONFIG_DEBUG
#define IPC_MAX_ASYNC_CALLS	4
#else
#define IPC_MAX_ASYNC_CALLS	4000
#endif

/* Flags for calls */

/** This is answer to a call */
#define IPC_CALL_ANSWERED	(1 << 0)
/** This call will not be freed on error */
#define IPC_CALL_STATIC_ALLOC	(1 << 1)
/** Answer will not be passed to userspace, will be discarded */
#define IPC_CALL_DISCARD_ANSWER	(1 << 2)
/** Call was forwarded */
#define IPC_CALL_FORWARDED	(1 << 3)
/** Identify connect_me_to answer */
#define IPC_CALL_CONN_ME_TO	(1 << 4)
/** Interrupt notification */
#define IPC_CALL_NOTIF		(1 << 5)

/*
 * Bits used in call hashes.
 * The addresses are aligned at least to 4 that is why we can use the 2 least
 * significant bits of the call address.
 */
/** Type of this call is 'answer' */
#define IPC_CALLID_ANSWERED	1
/** Type of this call is 'notification' */
#define IPC_CALLID_NOTIFICATION	2

/* Return values from sys_ipc_call_async(). */
#define IPC_CALLRET_FATAL	-1
#define IPC_CALLRET_TEMPORARY	-2


/* Macros for manipulating calling data */
#define IPC_SET_RETVAL(data, retval)	((data).args[0] = (retval))
#define IPC_SET_METHOD(data, val)	((data).args[0] = (val))
#define IPC_SET_ARG1(data, val)		((data).args[1] = (val))
#define IPC_SET_ARG2(data, val)		((data).args[2] = (val))
#define IPC_SET_ARG3(data, val)		((data).args[3] = (val))
#define IPC_SET_ARG4(data, val)		((data).args[4] = (val))
#define IPC_SET_ARG5(data, val)		((data).args[5] = (val))

#define IPC_GET_METHOD(data)		((data).args[0])
#define IPC_GET_RETVAL(data)		((data).args[0])

#define IPC_GET_ARG1(data)		((data).args[1])
#define IPC_GET_ARG2(data)		((data).args[2])
#define IPC_GET_ARG3(data)		((data).args[3])
#define IPC_GET_ARG4(data)		((data).args[4])
#define IPC_GET_ARG5(data)		((data).args[5])

/* Well known phone descriptors */
#define PHONE_NS	0

/* Forwarding flags. */
#define IPC_FF_NONE		0
/**
 * The call will be routed as though it was initially sent via the phone used to
 * forward it. This feature is intended to support the situation in which the
 * forwarded call needs to be handled by the same connection fibril as any other
 * calls that were initially sent by the forwarder to the same destination. This
 * flag has no imapct on routing replies.
 */
#define IPC_FF_ROUTE_FROM_ME	(1 << 0)

/* System-specific methods - only through special syscalls
 * These methods have special behaviour
 */
/** Protocol for CONNECT - TO - ME 
 *
 * Calling process asks the callee to create a callback connection,
 * so that it can start initiating new messages.
 *
 * The protocol for negotiating is:
 * - sys_connect_to_me - sends a message IPC_M_CONNECT_TO_ME
 * - recipient         - upon receipt tries to allocate new phone
 *                       - if it fails, responds with ELIMIT
 *                     - passes call to userspace. If userspace
 *                       responds with error, phone is deallocated and
 *                       error is sent back to caller. Otherwise 
 *                       the call is accepted and the response is sent back.
 *                     - the allocated phoneid is passed to userspace 
 *                       (on the receiving side) as ARG5 of the call.
 */
#define IPC_M_CONNECT_TO_ME	1
/** Protocol for CONNECT - ME - TO
 *
 * Calling process asks the callee to create for him a new connection.
 * E.g. the caller wants a name server to connect him to print server.
 *
 * The protocol for negotiating is:
 * - sys_connect_me_to - send a synchronous message to name server
 *                       indicating that it wants to be connected to some
 *                       service
 *                     - arg1/2/3 are user specified, arg5 contains
 *                       address of the phone that should be connected
 *                       (TODO: it leaks to userspace)
 *  - recipient        -  if ipc_answer == 0, then accept connection
 *                     -  otherwise connection refused
 *                     -  recepient may forward message.
 *
 */
#define IPC_M_CONNECT_ME_TO	2
/** This message is sent to answerbox when the phone
 * is hung up
 */
#define IPC_M_PHONE_HUNGUP	3

/** Send as_area over IPC.
 * - ARG1 - source as_area base address
 * - ARG2 - size of source as_area (filled automatically by kernel)
 * - ARG3 - flags of the as_area being sent
 * 
 * on answer, the recipient must set:
 * - ARG1 - dst as_area base adress
 */
#define IPC_M_AS_AREA_SEND	4	

/** Receive as_area over IPC.
 * - ARG1 - destination as_area base address
 * - ARG2 - destination as_area size
 * - ARG3 - user defined argument
 * 
 * on answer, the recipient must set:
 *
 * - ARG1 - source as_area base address
 * - ARG2 - flags that will be used for sharing
 */
#define IPC_M_AS_AREA_RECV	5	

/** Send data to another address space over IPC.
 * - ARG1 - destination address space virtual address, may be overriden by the
 *	    recipient
 * - ARG2 - source address space virtual address
 * - ARG3 - size of data to be copied, may be overriden by the recipient
 *
 * on answer, the recipient must set:
 *
 * - ARG1 - final destination address space virtual address
 * - ARG3 - final size of data to be copied
 */
#define IPC_M_DATA_SEND		6

/* Well-known methods */
#define IPC_M_LAST_SYSTEM	511
#define IPC_M_PING		512
/* User methods */
#define IPC_FIRST_USER_METHOD	1024

#ifdef KERNEL

#define IPC_MAX_PHONES  16

#include <synch/waitq.h>

struct answerbox;
struct task;

typedef enum {
	/** Phone is free and can be allocated */
	IPC_PHONE_FREE = 0,
	/** Phone is connecting somewhere */
	IPC_PHONE_CONNECTING,
	/** Phone is connected */
	IPC_PHONE_CONNECTED,
	/** Phone is hung up, waiting for answers to come */
	IPC_PHONE_HUNGUP,
	/** Phone was hungup from server */
	IPC_PHONE_SLAMMED
} ipc_phone_state_t;

/** Structure identifying phone (in TASK structure) */
typedef struct {
	SPINLOCK_DECLARE(lock);
	link_t link;
	struct answerbox *callee;
	ipc_phone_state_t state;
	atomic_t active_calls;
} phone_t;

typedef struct answerbox {
	SPINLOCK_DECLARE(lock);

	struct task *task;

	waitq_t wq;

	/** Phones connected to this answerbox. */
	link_t connected_phones;
	/** Received calls. */
	link_t calls;			
	link_t dispatched_calls;	/* Should be hash table in the future */

	/** Answered calls. */
	link_t answers;

	SPINLOCK_DECLARE(irq_lock);
	/** Notifications from IRQ handlers. */
	link_t irq_notifs;
	/** IRQs with notifications to this answerbox. */
	link_t irq_head;
} answerbox_t;

typedef struct {
	unative_t args[IPC_CALL_LEN];
	phone_t *phone;
} ipc_data_t;

typedef struct {
	link_t link;

	int flags;

	/** Identification of the caller. */
	struct task *sender;
	/** The caller box is different from sender->answerbox for synchronous
	 *  calls. */
	answerbox_t *callerbox;

	/** Private data to internal IPC. */
	unative_t priv;

	/** Data passed from/to userspace. */
	ipc_data_t data;

	/** Buffer for IPC_M_DATA_SEND. */
	uint8_t *buffer;
} call_t;

extern void ipc_init(void);
extern call_t * ipc_wait_for_call(answerbox_t *box, uint32_t usec, int flags);
extern void ipc_answer(answerbox_t *box, call_t *request);
extern int ipc_call(phone_t *phone, call_t *call);
extern void ipc_call_sync(phone_t *phone, call_t *request);
extern void ipc_phone_init(phone_t *phone);
extern void ipc_phone_connect(phone_t *phone, answerbox_t *box);
extern void ipc_call_free(call_t *call);
extern call_t * ipc_call_alloc(int flags);
extern void ipc_answerbox_init(answerbox_t *box);
extern void ipc_call_static_init(call_t *call);
extern void task_print_list(void);
extern int ipc_forward(call_t *call, phone_t *newphone, answerbox_t *oldbox,
    int mode);
extern void ipc_cleanup(void);
extern int ipc_phone_hangup(phone_t *phone);
extern void ipc_backsend_err(phone_t *phone, call_t *call, unative_t err);
extern void ipc_print_task(task_id_t taskid);

extern answerbox_t *ipc_phone_0;

#endif

#endif

/** @}
 */
