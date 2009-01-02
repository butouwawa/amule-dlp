///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2000-2003 Intel Corporation 
// All rights reserved. 
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met: 
//
// * Redistributions of source code must retain the above copyright notice, 
// this list of conditions and the following disclaimer. 
// * Redistributions in binary form must reproduce the above copyright notice, 
// this list of conditions and the following disclaimer in the documentation 
// and/or other materials provided with the distribution. 
// * Neither name of Intel Corporation nor the names of its contributors 
// may be used to endorse or promote products derived from this software 
// without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////

// Modified by Angel Vidal Veiga (kry@amule.org) for the aMule project.
// Really crippled version of the original header. Keep just what we need.

#ifndef UPNP_H
#define UPNP_H

#include "ixml.h"

#ifndef WIN32
#include <sys/types.h>
#include <netinet/in.h>
#else
#include <winsock.h>
#endif

#define LINE_SIZE  180
#define NAME_SIZE  256

/// @name Constants, Structures, and Types
//@{

/** @name UPNP_E_SUCCESS [0]
 *  {\tt UPNP_E_SUCCESS} signifies that the operation completed successfully.
 *  For asynchronous functions, this only means that the packet generated by 
 *  the operation was successfully transmitted on the network.  The result of 
 *  the entire operation comes as part of the callback for that operation.
 */
//@{
#define UPNP_E_SUCCESS          0
//@}

/** Returned when a control point application registers with {\bf
 *  UpnpRegisterClient}.  Client handles can only be used with 
 *  functions that operate with a client handle.  */

typedef int  UpnpClient_Handle;

/** @name UPnP_EventType
    @memo The reason code for an event callback.
    @doc The {\bf Event} parameter will be different depending on the
         reason for the callback.  The descriptions for each event
	 type describe the contents of the {\bf Event} parameter.
  */

enum Upnp_EventType_e {

  //
  // Control callbacks
  //

  /** Received by a device when a control point issues a control
   *  request.  The {\bf Event} parameter contains a pointer to a {\bf
   *  Upnp_Action_Request} structure containing the action.  The application
   *  stores the results of the action in this structure. */

  UPNP_CONTROL_ACTION_REQUEST,

  /** A {\bf UpnpSendActionAsync} call completed. The {\bf Event}
   *  parameter contains a pointer to a {\bf Upnp_Action_Complete} structure
   *  with the results of the action.  */

  UPNP_CONTROL_ACTION_COMPLETE,

  /** Received by a device when a query for a single service variable
   *  arrives.  The {\bf Event} parameter contains a pointer to a {\bf
   *  Upnp_State_Var_Request} structure containing the name of the variable
   *  and value.  */

  UPNP_CONTROL_GET_VAR_REQUEST,

  /** A {\bf UpnpGetServiceVarStatus} call completed. The {\bf Event}
   *  parameter contains a pointer to a {\bf Upnp_State_Var_Complete} structure
   *  containing the value for the variable.  */

  UPNP_CONTROL_GET_VAR_COMPLETE,

  //
  // Discovery callbacks
  //

  /** Received by a control point when a new device or service is available.  
   *  The {\bf Event} parameter contains a pointer to a {\bf
   *  Upnp_Discovery} structure with the information about the device
   *  or service.  */

  UPNP_DISCOVERY_ADVERTISEMENT_ALIVE,

  /** Received by a control point when a device or service shuts down. The {\bf
   *  Event} parameter contains a pointer to a {\bf Upnp_Discovery}
   *  structure containing the information about the device or
   *  service.  */

  UPNP_DISCOVERY_ADVERTISEMENT_BYEBYE,

  /** Received by a control point when a matching device or service responds.
   *  The {\bf Event} parameter contains a pointer to a {\bf
   *  Upnp_Discovery} structure containing the information about
   *  the reply to the search request.  */

  UPNP_DISCOVERY_SEARCH_RESULT,

  /** Received by a control point when the search timeout expires.  The
   *  SDK generates no more callbacks for this search after this 
   *  event.  The {\bf Event} parameter is {\tt NULL}.  */

  UPNP_DISCOVERY_SEARCH_TIMEOUT,

  //
  // Eventing callbacks
  //

  /** Received by a device when a subscription arrives.
   *  The {\bf Event} parameter contains a pointer to a {\bf
   *  Upnp_Subscription_Request} structure.  At this point, the
   *  subscription has already been accepted.  {\bf UpnpAcceptSubscription}
   *  needs to be called to confirm the subscription and transmit the
   *  initial state table.  This can be done during this callback.  The SDK
   *  generates no events for a subscription unless the device 
   *  application calls {\bf UpnpAcceptSubscription}.
   */

  UPNP_EVENT_SUBSCRIPTION_REQUEST,

  /** Received by a control point when an event arrives.  The {\bf
   *  Event} parameter contains a {\bf Upnp_Event} structure
   *  with the information about the event.  */

  UPNP_EVENT_RECEIVED,

  /** A {\bf UpnpRenewSubscriptionAsync} call completed. The status of
   *  the renewal is in the {\bf Event} parameter as a {\bf
   *  Upnp_Event_Subscription} structure.  */

  UPNP_EVENT_RENEWAL_COMPLETE,

  /** A {\bf UpnpSubscribeAsync} call completed. The status of the
   * subscription is in the {\bf Event} parameter as a {\bf
   * Upnp_Event_Subscription} structure.  */

  UPNP_EVENT_SUBSCRIBE_COMPLETE,

  /** A {\bf UpnpUnSubscribeAsync} call completed. The status of the
   *  subscription is in the {\bf Event} parameter as a {\bf
   *  Upnp_Event_Subscribe} structure.  */

  UPNP_EVENT_UNSUBSCRIBE_COMPLETE,

  /** The auto-renewal of a client subscription failed.   
   *  The {\bf Event} parameter is a {\bf Upnp_Event_Subscribe} structure 
   *  with the error code set appropriately. The subscription is no longer 
   *  valid. */

  UPNP_EVENT_AUTORENEWAL_FAILED,

  /** A client subscription has expired. This will only occur 
   *  if auto-renewal of subscriptions is disabled.
   *  The {\bf Event} parameter is a {\bf Upnp_Event_Subscribe}
   *  structure. The subscription is no longer valid. */
  
  UPNP_EVENT_SUBSCRIPTION_EXPIRED

};

typedef enum Upnp_EventType_e Upnp_EventType;

/** The {\bf Upnp_SID} holds the subscription identifier for a subscription
    between a client and a device.  The SID is a string representation of
    a globally unique id (GUID) and should not be modified.
  */
    
typedef char Upnp_SID[44];

/** All callback functions share the same prototype, documented below.
 *  Note that any memory passed to the callback function
 *  is valid only during the callback and should be copied if it
 *  needs to persist.  This callback function needs to be thread
 *  safe.  The context of the callback is always on a valid thread 
 *  context and standard synchronization methods can be used.  Note, 
 *  however, because of this the callback cannot call SDK functions
 *  unless explicitly noted.
 *
 *  \begin{verbatim}
      int CallbackFxn( Upnp_EventType EventType, void* Event, void* Cookie );
    \end{verbatim} 
 *
 *  where {\bf EventType} is the event that triggered the callback, 
 *  {\bf Event} is a structure that denotes event-specific information for that
 *  event, and {\bf Cookie} is the user data passed when the callback was
 *  registered.
 *
 *  See {\bf Upnp_EventType} for more information on the callback values and
 *  the associated {\bf Event} parameter.  
 *
 *  The return value of the callback is currently ignored.  It may be used
 *  in the future to communicate results back to the SDK.
 */

typedef int  (*Upnp_FunPtr) (
    IN Upnp_EventType EventType, 
    IN void *Event, 
    IN void *Cookie
    );

//
// This typedef is required by Doc++ to parse the last entry of the 
// Upnp_Discovery structure correctly.
//

struct Upnp_Discovery
{
	/** The result code of the {\bf UpnpSearchAsync} call. */
	int  ErrCode;                  
				     
	/** The expiration time of the advertisement. */
	int  Expires;                  
				     
	/** The unique device identifier. */
	char DeviceId[LINE_SIZE];      

	/** The device type. */
	char DeviceType[LINE_SIZE];    

	/** The service type. */
	char ServiceType[LINE_SIZE];

	/** The service version. */
	char ServiceVer[LINE_SIZE];    

	/** The URL to the UPnP description document for the device. */
	char Location[LINE_SIZE];      

	/** The operating system the device is running. */
	char Os[LINE_SIZE];            
				     
	/** Date when the response was generated. */
	char Date[LINE_SIZE];            
				     
	/** Confirmation that the MAN header was understood by the device. */
	char Ext[LINE_SIZE];           
				     
	/** The host address of the device responding to the search. */
	struct sockaddr_in DestAddr; 
};

struct Upnp_Action_Complete
{
  /** The result of the operation. */
  int ErrCode;

  /** The control URL for service. */
  char CtrlUrl[NAME_SIZE];

  /** The DOM document describing the action. */
  IXML_Document *ActionRequest;

  /** The DOM document describing the result of the action. */
  IXML_Document *ActionResult;
};

/** Represents the reply for the current value of a state variable in an
    asynchronous call. */

struct Upnp_State_Var_Complete
{
  /** The result of the operation. */
  int ErrCode;

  /** The control URL for the service. */
  char CtrlUrl[NAME_SIZE];

  /** The name of the variable. */
  char StateVarName[NAME_SIZE];

  /** The current value of the variable or error string in case of error. */
  DOMString CurrentVal;
};

/** Returned along with a {\bf UPNP_EVENT_RECEIVED} callback.  */

struct Upnp_Event
{
  /** The subscription ID for this subscription. */
  Upnp_SID Sid;

  /** The event sequence number. */
  int EventKey;

  /** The DOM tree representing the changes generating the event. */
  IXML_Document *ChangedVariables;

};

/** Returned along with a {\bf UPNP_EVENT_SUBSCRIBE_COMPLETE} or {\bf
 * UPNP_EVENT_UNSUBSCRIBE_COMPLETE} callback.  */

struct Upnp_Event_Subscribe {

  /** The SID for this subscription.  For subscriptions, this only
   *  contains a valid SID if the {\bf Upnp_EventSubscribe.result} field
   *  contains a {\tt UPNP_E_SUCCESS} result code.  For unsubscriptions,
   *  this contains the SID from which the subscription is being
   *  unsubscribed.  */

  Upnp_SID Sid;            

  /** The result of the operation. */
  int ErrCode;              

  /** The event URL being subscribed to or removed from. */
  char PublisherUrl[NAME_SIZE]; 

  /** The actual subscription time (for subscriptions only). */
  int TimeOut;              
                              
};

//@} // Constants, Structures, and Types

#endif

// File_checked_for_headers
