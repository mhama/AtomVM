/***************************************************************************
 *   Copyright 2019 by Davide Bettio <davide@uninstall.it>                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#ifndef _PLATFORM_DEFAULTATOMS_H_
#define _PLATFORM_DEFAULTATOMS_H_

#include "defaultatoms.h"

#define SET_LEVEL_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 0)
#define READ_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 1)
#define INPUT_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 2)
#define OUTPUT_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 3)
#define SET_DIRECTION_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 4)
#define SET_INT_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 5)
#define GPIO_INTERRUPT_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 6)

#define PROTO_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 7)
#define UDP_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 8)
#define TCP_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 9)
#define SOCKET_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 10)
#define FCNTL_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 11)
#define BIND_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 12)
#define GETSOCKNAME_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 13)
#define RECVFROM_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 14)
#define SENDTO_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 15)

#define STA_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 16)
#define SSID_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 17)
#define PSK_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 18)
#define SNTP_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 19)
#define STA_GOT_IP_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 20)
#define STA_CONNECTED_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 21)
#define STA_DISCONNECTED_ATOM_INDEX (PLATFORM_ATOMS_BASE_INDEX + 22)

#define SET_LEVEL_ATOM TERM_FROM_ATOM_INDEX(SET_LEVEL_ATOM_INDEX)
#define READ_ATOM TERM_FROM_ATOM_INDEX(READ_ATOM_INDEX)
#define INPUT_ATOM TERM_FROM_ATOM_INDEX(INPUT_ATOM_INDEX)
#define OUTPUT_ATOM TERM_FROM_ATOM_INDEX(OUTPUT_ATOM_INDEX)
#define SET_DIRECTION_ATOM TERM_FROM_ATOM_INDEX(SET_DIRECTION_ATOM_INDEX)
#define SET_INT_ATOM TERM_FROM_ATOM_INDEX(SET_INT_ATOM_INDEX)
#define GPIO_INTERRUPT_ATOM TERM_FROM_ATOM_INDEX(GPIO_INTERRUPT_ATOM_INDEX)

#define PROTO_ATOM TERM_FROM_ATOM_INDEX(PROTO_ATOM_INDEX)
#define UDP_ATOM TERM_FROM_ATOM_INDEX(UDP_ATOM_INDEX)
#define TCP_ATOM TERM_FROM_ATOM_INDEX(TCP_ATOM_INDEX)
#define SOCKET_ATOM TERM_FROM_ATOM_INDEX(SOCKET_ATOM_INDEX)
#define FCNTL_ATOM TERM_FROM_ATOM_INDEX(FCNTL_ATOM_INDEX)
#define BIND_ATOM TERM_FROM_ATOM_INDEX(BIND_ATOM_INDEX)
#define GETSOCKNAME_ATOM TERM_FROM_ATOM_INDEX(GETSOCKNAME_ATOM_INDEX)
#define RECVFROM_ATOM TERM_FROM_ATOM_INDEX(RECVFROM_ATOM_INDEX)
#define SENDTO_ATOM TERM_FROM_ATOM_INDEX(SENDTO_ATOM_INDEX)

#define STA_ATOM TERM_FROM_ATOM_INDEX(STA_ATOM_INDEX)
#define SSID_ATOM TERM_FROM_ATOM_INDEX(SSID_ATOM_INDEX)
#define PSK_ATOM TERM_FROM_ATOM_INDEX(PSK_ATOM_INDEX)
#define SNTP_ATOM TERM_FROM_ATOM_INDEX(SNTP_ATOM_INDEX)
#define STA_GOT_IP_ATOM TERM_FROM_ATOM_INDEX(STA_GOT_IP_ATOM_INDEX)
#define STA_CONNECTED_ATOM TERM_FROM_ATOM_INDEX(STA_CONNECTED_ATOM_INDEX)
#define STA_DISCONNECTED_ATOM TERM_FROM_ATOM_INDEX(STA_DISCONNECTED_ATOM_INDEX)

#endif