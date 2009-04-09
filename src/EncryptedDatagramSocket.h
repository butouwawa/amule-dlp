//
// This file is part of the aMule Project.
//
// Copyright (c) 2003-2009 aMule Team ( admin@amule.org / http://www.amule.org )
// Copyright (c) 2002 Merkur ( devs@emule-project.net / http://www.emule-project.net )
//
// Any parts of this program derived from the xMule, lMule or eMule project,
// or contributed by third-party developers are copyrighted by their
// respective authors.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301, USA
//

#include "Proxy.h"
#include "Types.h"

class CEncryptedDatagramSocket : public CDatagramSocketProxy
{
public:
	CEncryptedDatagramSocket( wxIPaddress &address, wxSocketFlags flags = wxSOCKET_NONE,	const CProxyData *proxyData = NULL);
	virtual ~CEncryptedDatagramSocket();

// TODO: Make protected once the UDP socket is again its own class.
	static int DecryptReceivedClient(uint8_t *bufIn, int bufLen, uint8_t **bufOut, uint32_t ip, uint32_t *receiverVerifyKey, uint32_t *senderVerifyKey);
	static int EncryptSendClient(uint8_t **buf, int bufLen, const uint8_t *clientHashOrKadID, bool kad, uint32_t receiverVerifyKey, uint32_t senderVerifyKey);

	static int DecryptReceivedServer(uint8* pbyBufIn, int nBufLen, uint8** ppbyBufOut, uint32 dwBaseKey, uint32 dbgIP);
	static int EncryptSendServer(uint8** ppbyBuf, int nBufLen, uint32 dwBaseKey);

};
